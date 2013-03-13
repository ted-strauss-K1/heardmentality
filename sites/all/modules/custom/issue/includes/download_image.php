<?php
/**
 * Save a remote image.  Returns a file object.
 *
 * @see https://gist.github.com/1849861
 */
function download_image($url, $save_dir = '')
{
  global $user;

  // Check if the file extension is valid.
  $extensions = array('jpg', 'jpeg', 'png', 'gif');
  $parsed = parse_url($url);
  $regex = '/\.(' . implode('|', $extensions) . ')$/i';
  if (!preg_match($regex, $parsed['path'], $matches)) {
    watchdog('download', 'Download Image Error: Bad file extension.', array(), WATCHDOG_ERROR);
    return FALSE;
  }
  $extension = $matches[0];

  // Check if we have already saved this image.
  $hash = md5($url);
  $dir = file_create_path();
  if ($save_dir) {
    $dir .= '/' . $save_dir;
  }
  if (!file_check_directory($dir, FILE_CREATE_DIRECTORY)) {
    watchdog('download', 'Download Image Error: Could not create external directory.', array(), WATCHDOG_ERROR);
    return FALSE;
  }
  $filepath = $dir . '/' . $hash . $extension;
  if (is_file($filepath)) {
    if ($file = db_fetch_object(db_query("SELECT * FROM {files} WHERE filepath = '%s'", $filepath))) {
      return $file;
    }
  }

  // Download the image.
  if ($response = drupal_http_request($url)) {
    // Check response code.
    if ($response->code != 200) {
      watchdog('download', 'Download Image Error: Bad response code (!code).', array('!code' => $response->code), WATCHDOG_ERROR);
      return FALSE;
    }

    // Check mime type.
    $types = array('image/jpeg', 'image/png', 'image/gif');
    if (!in_array($response->headers['Content-Type'], $types)) {
      watchdog('download', 'Download Image Error: Bad Content-Type header (!type).', array('!type' => $response->headers['Content-Type']), WATCHDOG_ERROR);
      return FALSE;
    }

    // Save image to temp directory.
    $destination = $filepath;
    $filepath = $tmp = file_directory_temp() . '/' . $hash . $extension;
    if (!$fp = fopen($filepath, 'wb')) {
      drupal_set_message(t('The file could not be created.'), 'error');
      return FALSE;
    }
    fwrite($fp, $response->data);
    fclose($fp);

    // Validate image via getimagesize().
    if (!getimagesize($filepath)) {
      watchdog('download', 'Download Image Error: Failed to validate with getimagesize().', array(), WATCHDOG_ERROR);
      return FALSE;
    }

    // Move the file to destination.
    if (file_move($filepath, $destination, FILE_EXISTS_RENAME)) {
      // Delete temp file.
      file_delete($tmp);

      // Build file object.
      $file = new stdClass();
      $file->filename = trim(basename($filepath));
      $file->filepath = $filepath;
      $file->filemime = $response->headers['Content-Type'];
      $file->filesize = $filepath;
      $file->uid = $user->uid;
      $file->status = FILE_STATUS_TEMPORARY;
      $file->timestamp = time();

      // Save file record.
      if (drupal_write_record('files', $file)) {
        return $file;
      } else {
        watchdog('download', 'Download Image Error: Could not save file record.', array(), WATCHDOG_ERROR);
        return FALSE;
      }
    } else {
      watchdog('download', 'Download Image Error: Could not save data.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  return FALSE;
}