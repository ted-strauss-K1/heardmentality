<?php

/**
 * @return array
 */
function tt_menu() {
  $items = array();

  $items['admin/settings/tt'] = array(
    'title'            => t('Translation'),
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('tt_admin_form'),
    'access arguments' => array('administer content'),
    'type'             => MENU_NORMAL_ITEM,
  );

  $items['admin/settings/tt-ajax'] = array(
    'page callback'    => 'tt_admin_ajax',
    'access arguments' => array('administer content'),
    'type'             => MENU_CALLBACK,
  );

  return $items;
}

/**
 * @return array
 */
function tt_admin_form() {
  $form = array();

  //
  global $language;

  //
  drupal_add_js(drupal_get_path('module', 'tt') . '/tt.admin.js');
  drupal_add_js(array('langcode' => $language->language), 'setting');

  // filter not translated
  $query = array('filter' => intval($_GET['filter']));

  // languages enabled
  $form['#prefix'] = array();
  $language_list   = language_list();
  foreach ($language_list as $langcode => $language_item) {
    if ($language_item->enabled) {
      $form['#prefix'][] = $langcode == $language->language ? '<strong>' . $language_item->name . '</strong>' : l($language_item->name, $_GET['q'], array(
        'html'     => TRUE,
        'language' => $language_item,
        'query'    => $query
      ));
    }
  }
  $form['#prefix'] = '<div class="form-item">LANGUAGES:&nbsp;&nbsp;&nbsp;' . implode('&nbsp;/&nbsp;', $form['#prefix']) . '</div>';

  // available textgroups
  $textgroups = array();
  $result     = db_query("SELECT textgroup FROM {locales_source} WHERE code <> '' AND version = '%s' GROUP BY textgroup", VERSION);
  while ($textgroup_item = db_result($result)) {
    $textgroups[] = $textgroup_item;
  }

  // textgroup
  $textgroup = in_array(arg(3), $textgroups) ? arg(3) : 'default';

  $form['textgroup'] = array(
    '#type'  => 'hidden',
    '#value' => $textgroup,
  );

  // textgroup links
  foreach ($textgroups as &$textgroup_item) {
    $textgroup_item = $textgroup_item == $textgroup ? '<strong>' . $textgroup_item . '</strong>' : l($textgroup_item, 'admin/settings/tt/' . $textgroup_item, array(
      'html'     => TRUE,
      'language' => $language,
      'query'    => $query
    ));
  }
  $form['#prefix'] .= '<div class="form-item">TEXTGROUP:&nbsp;&nbsp;&nbsp;' . implode('&nbsp;/&nbsp;', $textgroups) . '</div>';

  //
  $filter = array();
  foreach (array(0 => 'Show All', 1 => 'Show not Translated') as $val => $key) {
    $filter[] = $val == $query['filter'] ? '<strong>' . $key . '</strong>' : l($key, $_GET['q'], array(
      'html'     => TRUE,
      'language' => $language,
      'query'    => array('filter' => $val),
    ));
  }
  $form['#prefix'] .= '<div class="form-item">FILTER:&nbsp;&nbsp;&nbsp;' . implode('&nbsp;/&nbsp;', $filter) . '</div>';

  $form['update'] = array(
    '#type'   => 'submit',
    '#value'  => 'Update not translated strings',
    '#submit' => array('tt_batch_update'),
  );

  // rows
  $rows = array();

  //
  $sql = "
    SELECT %%
    FROM {locales_source} s
    LEFT JOIN {locales_target} t ON s.lid = t.lid AND t.language = '%s'
    WHERE s.code <> '' AND s.version = '%s' AND s.textgroup = '%s'";
  if ($query['filter']) {
    $sql .= " AND t.translation IS NULL";
  }
  // pager
  $pager_perpage = 25;
  $pager_count   = (int) db_result(db_query(str_replace('%%', 'COUNT(*)', $sql), $language->language, VERSION, $textgroup));
  $pager_pages   = ceil($pager_count / $pager_perpage);
  $pager_page    = intval($_GET['page']);

  // request
  $result = db_query_range(str_replace('%%', 's.lid, s.code, s.source, t.translation', $sql) . " ORDER BY s.source ASC", $language->language, VERSION, $textgroup, $pager_page * $pager_perpage, $pager_perpage);
  while ($row = db_fetch_array($result)) {
    $rows[] = array(
      $row['code'],
      $row['source'],
      $row['translation'],
      $row['lid'],
    );
  }

  // override
  foreach ($rows as &$row) {
    $row[1] = '<div style="width: 300px;">' . $row[1] . '</div>';
    $row[2] = '<textarea name="' . $row[3] . '" style="width: 500px;">' . htmlspecialchars($row[2]) . '</textarea><br><input type="button" value="Save" class="form-submit tt-admin">';
    unset($row[3]);
  }

  $form['content'] = array(
    '#type'  => 'item',
    '#value' => $rows ? theme('table', array('Code', 'Default Text', 'Translated Text'), $rows) : 'Nothing here.',
  );

  // pager
  global $pager_page_array, $pager_total;
  $element                    = 0;
  $pager_page_array[$element] = intval($_GET['page']);
  $pager_total[$element]      = $pager_pages;
  $form['#suffix']            = theme('pager', array(), 25, $element);

  return $form;
}

/**
 *
 */
function tt_admin_ajax() {
  if ($translation = $_REQUEST['translation']) {
    $lid      = intval($_REQUEST['lid']);
    $language = $_REQUEST['language'];

    // save
    db_query("DELETE FROM {locales_target} WHERE lid = '%s' AND language = '%s'", $lid, $language);
    db_query("INSERT INTO {locales_target} SET lid = '%s', language = '%s', translation = '%s'", $lid, $language, $translation);

    //
    print json_encode(array('status' => TRUE));
    exit;
  }

  //
  print json_encode(array('status' => FALSE));
  exit;
}

/**
 *
 */
function tt_batch_update($form, $form_state) {
  // init batch
  global $language;
  $batch = tt_batch_update_batch($form_state['values']['textgroup'], $language->language);

  // Start the batch process running
  batch_set($batch);
}

/**
 *
 */
function tt_batch_update_batch($textgroup, $langcode) {
  //
  $sql    = "
    SELECT s.lid, s.code, s.source, s.source translation, '%s' langcode
    FROM {locales_source} s
    LEFT JOIN {locales_target} t ON s.lid = t.lid AND t.language = '%s'
    WHERE s.code <> '' AND s.version = '%s' AND s.textgroup = '%s' AND t.translation IS NULL";
  $result = db_query($sql . " ORDER BY s.source ASC", $langcode, $langcode, VERSION, $textgroup);

  $index              = 0;
  $perpage            = 10;
  $operations_default = array('tt_batch_update_op', array());
  $operations[$index] = $operations_default;
  while ($row = db_fetch_array($result)) {
    // next op
    if (count($operations[$index][1]) >= $perpage) {
      $index++;
    }

    // init if no operation
    if (is_null($operations[$index])) {
      $operations[$index] = $operations_default;
    }

    // item
    $operations[$index][1][] = $row;
  }

  foreach ($operations as &$operation) {
    $operation[1] = array(json_encode($operation[1]));
  }

  // Create an array which contains an array of the operations to
  // perform and a method to call when the operations are all finished
  $batch = array(
    'operations' => $operations,
    'finished'   => 'tt_batch_update_finished',
  );
  return $batch;
}

/**
 * Batch operation for batch 1 : load a node...
 */
function tt_batch_update_op($args, &$context) {
  // langcode
  $langcode = 'en';

  // texts to translate
  $texts = array();
  $args  = json_decode($args);
  foreach ($args as $arg) {
    $texts[$arg->source] = (array) $arg;
    $langcode            = $arg->langcode;
  }

  // no texts
  if (empty($texts)) {
    return;
  }

  // translate
  $output = mstapi_exec('en', $langcode, array_keys($texts));

  //
  $messages = array();

  // update translations in DB
  foreach ($output as $source => $translation) {
    if (isset($texts[$source])) {
      // save
      db_query("DELETE FROM {locales_target} WHERE lid = '%s' AND language = '%s'", $texts[$source]['lid'], $langcode);
      db_query("INSERT INTO {locales_target} SET lid = '%s', language = '%s', translation = '%s'", $texts[$source]['lid'], $langcode, $translation);
    }

    $texts[$source]['translation'] = $translation;
  }

  // messages
  foreach ($texts as $source => $arg) {
    $messages[] = $source . " >> " . $arg['translation'];
  }

  // Store some result for post-processing in the finished callback.
  $context['results'][] = implode(", ", $messages);

  // Optional message displayed under the progressbar.
  $context['message'] = t('!text', array(
    '!text' => implode("<br>", $messages),
  ));
}

/**
 * Batch 'finished' callback used by both batch 1 and batch 2
 */
function tt_batch_update_finished($success, $results, $operations) {
  if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    $message = count($results) . ' groups were processed.';
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message         = 'An error occurred while processing ' . $error_operation[0] . ' with arguments :' . print_r($error_operation[0], TRUE);
  }
  drupal_set_message($message);
}
