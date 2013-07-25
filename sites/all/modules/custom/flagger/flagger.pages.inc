<?php

// this file contains only menu functions

# flag

/**
 * Callback for FLAGGER_PATH
 *
 * @param $content_type
 * @param $content_id
 */
function flagger_page($content_type, $content_id)
{
  print json_encode(array(
    'message' => drupal_get_form('flagger_form', $content_id, $content_type),
    'texts' => array(
        t('Flag'),
        t('Cancel'),
        t('Thank you for helping us keep this place in order'),
    ),
  ));
}

/**
 * Flagger form
 *
 * @param $form
 * @param $content_id
 * @param $content_type
 * @return array
 */
function flagger_form(&$form, $content_id, $content_type)
{
  global $user;
  $form = array();

  $form['#attributes'] = array(
    'class' => 'flagger_form'
  );
  $form['#action'] = '/' . FLAGGER_PATH . '/save';

  $form['title'] = array(
    '#type' => 'markup',
    "#value" => t("Which one of Heard Mentality's Guidelines and Principles is this debate posting infringing?"),
  );
  $form['guide'] = array(
    '#type' => 'markup',
    "#value" => l(t('Read Guidelines'), '<front>'),
  );

  switch ($content_type) {
    case 'comment' :
      $flags = flag_get_flags($content_type);
      break;
    case 'node' :
      $node = node_load($content_id);
      $flags = flag_get_flags($content_type, $node->type);
      break;
    default :
      $flags = array();
      break;
  }

  $note = '';

  // radios
  $value = -1;
  $options = array();
  foreach ($flags as $flag) {
    $options[$flag->fid] = t($flag->title);
    if ($flag->is_flagged($content_id)) {
      $value = $flag->fid;
      $notes = flag_note_get_notes(array(
        'uid' => $user->uid,
        'content_id' => $content_id,
        'content_type' => $content_type,
        'fid' => $flag->fid,
      ));
      if ($notes) {
        $note = $notes[0]['note'];
      }
    }
  }
  $form['flag'] = array(
    '#type' => 'radios',
    '#default_value' => $value,
    '#options' => $options,
  );

  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    "#value" => $note,
  );

  $form['content_id'] = array(
    '#type' => 'hidden',
    "#value" => $content_id,
  );
  $form['content_type'] = array(
    '#type' => 'hidden',
    "#value" => $content_type,
  );

  return $form;
}

/**
 * Flagger form submit
 */
function flagger_page_save()
{
  $post = $_POST;

  global $user;
  $note = $post['note'];
  $tid = ($post['tid'] > 0 ? $post['tid'] : NULL);

  // radios
  $content_id = $post['content_id'];
  $content_type = $post['content_type'];
  switch ($content_type) {
    case 'comment' :
      $flags = flag_get_flags($content_type);
      break;
    case 'node' :
      $node = node_load($content_id);
      $flags = flag_get_flags($content_type, $node->type);
      break;
    default :
      $flags = array();
      break;
  }
  // remove old notes
  flag_note_remove_notes(array('content_type' => $content_type, 'content_id' => $content_id));

  foreach ($flags as $flag) {
    if ($post['flag'] == $flag->fid) {
      $flag->flag('flag', $content_id);
      $record = $flag;
      $record->uid = $user->uid;
      $record->note = $note;
      $record->tid = $tid;
      $record->content_id = $content_id;
      flag_note_insert_note($record);

      if (module_exists('badges')) {
        badges_queue($user->uid, array(
          'flag_first'
        ));
      }
    } else {
      $fcid = flag_ext_fcid($content_type, $content_id, $user->uid);
      $flag->flag('unflag', $content_id);
      flag_ext_unset($fcid, $user->uid);
    }
  }

  print json_encode(array(
    'content_id' => $content_id,
    'content_type' => $content_type,
    'flagged' => (bool)flagger_get_flags($content_type, $content_id, true),
  ));
  exit;
}


# flags

/**
 * Callback for FLAGGER_PATH
 *
 * @param $content_type
 * @param $content_id
 */
function flagger_page_flags($content_type, $content_id)
{
  if (!module_exists('moderation') || !moderation_check_perm()) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => t('You have no access to that info'),
    ));
    exit;
  }

  $output = '';

  $flags = flagger_get_flags($content_type, $content_id);
  foreach ($flags as $fid => $flag) {
    $output .= t($flag['title']);
    $output .= '<hr style="margin:3px 0 5px 0"/>';
    $output .= '<ul>';
    foreach ($flag['users'] as $uid => $data) {
      $output .= '<li><b>'. l($data['name'],'user/profile/view/'.$uid) . '</b>' .
        (empty($data['note']) ? '' : ': '.$data['note']) .'</li>';
    }
    $output .= '</ul>';
  }

  if (!$flags) {
    $output = t('No flags');
  }

  print json_encode(array(
    'status'  => TRUE,
    'message' => $output,
  ));

  exit;
}

/**
 * Callback for FLAGGER_PATH
 *
 * @param $content_type
 * @param $content_id
 */
function flagger_page_history($content_type, $content_id) {
  if (!module_exists('moderation') || !moderation_check_perm()) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => t('You have no access to that info'),
    ));
    exit;
  }

  $output = '<div class="scrollable">';

  $result = db_query_range("
    SELECT fch.*, f.title, u.name, u1.name name_moderator
    FROM flag_content_history fch
    INNER JOIN flags f ON f.fid = fch.fid
    INNER JOIN users u ON u.uid = fch.uid
    LEFT JOIN users u1 ON fch.uid_moderator = u1.uid
    WHERE fch.content_type = '%s' AND fch.content_id = '%d'
    ORDER BY GREATEST(timestamp_set, timestamp_unset) DESC, status DESC",
    $content_type, $content_id, 0, 100
  );
  $output .= '<ul class="flags-history">';
  while ($row = db_fetch_array($result)) {
    $output .= sprintf('<li name="%d" class="status-%d"><span class="remove" title="%s"></span>', $row['fcid'], $row['status'], t('Remove flag'));
    $output .= sprintf('<span class="flag-name status-%d">%s</span>', $row['status'], t($row['title']));
    $output .= ' ' . t('by') . ' ' . l($row['name'],'user/profile/view/'.$row['uid'], array(
      'attributes' => array(
        'title' => t('at') . ' ' . date('Y.m.d H:i:s', $row['timestamp_set']),
      ),
    ));
    $output .= ' ';
    if (!$row['status']) {
      $output .= ' (' . t('removed by') . ' ' . l($row['name_moderator'],'user/profile/view/'.$row['uid_moderator'], array(
        'attributes' => array(
          'title' => t('at') . ' ' . date('Y.m.d H:i:s', $row['timestamp_unset']),
        ),
      )) . ')';
    }
    $output .= '</li>';
  }
  $output .= '</ul>';
  $output .= '</div>';

  print json_encode(array(
    'status'  => TRUE,
    'message' => $output,
  ));

  exit;
}

/**
 * @param $fcid
 */
function flagger_page_unflag($fcid) {
  if (!module_exists('moderation') || !moderation_check_perm()) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => t('You have no access'),
    ));
    exit;
  }

  # unflag
  $flag = db_fetch_object(db_query("SELECT * FROM {flag_content} WHERE fcid = %d", $fcid));
  if ($flag) {
    $content_id = $flag->content_id;
    $content_type = $flag->content_type;
    $flag = flag_get_flag(null, $flag->fid);
    $flag->flag('unflag', $content_id);
    global $user;
    flag_ext_unset($fcid, $user->uid);
  }
  print json_encode(array(
    'status'  => TRUE,
    'message' => t('Flag was removed'),
    'content_id' => $content_id,
    'content_type' => $content_type,
    'flagged' => (bool)flagger_get_flags($content_type, $content_id, true),
  ));
  exit;
}