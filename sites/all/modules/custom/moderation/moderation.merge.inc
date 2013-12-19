<?php

/**
 * @return array
 */
function moderation_merge_form($form_state, $merge, $base) {
  $form = array();

  $form['merge'] = array(
    '#type'  => 'hidden',
    '#value' => $merge,
  );
  $form['base'] = array(
    '#type'  => 'hidden',
    '#value' => $base,
  );

  $base = node_load($base);
  $merge = node_load($merge);

  $base_link = l(issue_translate($base, 'title'), $base->path);
  $merge_link = l(issue_translate($merge, 'title'), $merge->path);

  $form['warning'] = array(
    '#type'   => 'markup',
    '#value'  => t('The action cannot be undone. Merged issue will be removed.'),
    '#prefix' => '<div class="warning">',
    '#suffix' => '</div>',
  );

  $base_allow = empty($base->field_base_issue[0]['nid']);
  $merge_allow = empty($merge->field_base_issue[0]['nid']);

  if (!$base_allow) {
    $form['warning2'] = array(
      '#type'   => 'markup',
      '#value'  => t('You cannot merge to issue duplicating another one.') . '<span>(' . $base_link . ')<//span>',
      '#prefix' => '<div class="warning">',
      '#suffix' => '</div>',
    );
  }

  if (!$merge_allow) {
    $form['warning3'] = array(
      '#type'   => 'markup',
      '#value'  => t('This issue is duplicating another one already.') . '<span>(' . $merge_link . ')</span>',
      '#prefix' => '<div class="warning">',
      '#suffix' => '</div>',
    );
  }

  if (!$merge_allow || !$base_allow) {
    return $form;
  }

  $base_choices = array();
  foreach ($base->choices as $chid => $choice) {
    $base_choices[$chid] = t('Merge into ') . ' "' . $choice['chtext'] . '"';
  }
  $base_choices[0] = t('Transfer the answer');
  $base_choices[-1] = t('Remove the answer');

  $form['table'] = array(
    '#type'   => 'markup',
    '#value'  => '&nbsp;',
    '#prefix' => '<table class="merge-issue"><th><tr>
      <td class="merge-main">' . t('Merged Issue') . '<br>' . $merge_link . '</td>
      <td class="merge-center">' . l(t('Swap Issues'), 'moderation/merge/' . $base->nid . '/' . $merge->nid) . '</td>
      <td class="merge-main">' . t('Base Issue') . '<br>' . $base_link . '</td>
    </tr></th>',
    '#suffix' => '</table>',
  );
  $form['table']['item'] = array(
    '#type'   => 'markup',
    '#value'  => t('Choices'),
    '#prefix' => '<tr><td class="merge-header" colspan=3>',
    '#suffix' => '</td><tr>',
  );
  $form['table']['choices'] = array(
    '#type' => 'fieldset',
    //    '#prefix' => '<tr>',
    //    '#suffix' => '</tr>',
    '#tree' => TRUE,
  );
  foreach ($merge->choices as $chid => $choice) {
    $form['table']['choices'][$chid]['name'] = array(
      '#type'   => 'markup',
      '#value'  => $choice['chtext'],
      '#prefix' => '<tr><td>',
      '#suffix' => '</td>',
    );
    $form['table']['choices'][$chid]['chid'] = array(
      '#type'   => 'hidden',
      '#value'  => $chid,
      '#prefix' => '<td>&gt;&gt;',
      '#suffix' => '</td>',
    );
    $form['table']['choices'][$chid]['chid_to'] = array(
      '#type'       => 'select',
      '#options'    => $base_choices,
      '#prefix'     => '<td>',
      '#suffix'     => '</td></tr>',
      '#attributes' => array('class' => 'chosen-select'),
    );
  }

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Merge'),
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_merge_form_submit($form, $form_state) {
  $values = $form_state['values'];
  #
  $base = $values['base'];
  $merge = $values['merge'];

  $base_choices = cpoll_load_choices($base);
  $merge_choices = cpoll_load_choices($merge);
  # create all the choices that should be transferred
  foreach ($values['choices'] as $chid => &$info) {
    // transfer choice
    if (0 == $info['chid_to']) {
      if ($choice = $merge_choices[$chid]) {
        $choice_new = array(
          'chid'         => -1,
          'nid'          => $base,
          'uid'          => $choice['uid'],
          'chtext'       => $choice['chtext'],
          'chtext_short' => $choice['chtext_short'],
          'weight'       => count($base_choices),
          'chtype'       => $choice['chtype'],
        );
        if ($object = cpoll_choice_save($choice_new)) {
          $info['chid_to'] = $object->chid;
        }
      }
    }

    // cpoll meta
    if (-1 != $info['chid_to']) {
      db_query("
        INSERT IGNORE INTO {cpoll_meta_values} (
          SELECT '%d', uid, cid, value
          FROM {cpoll_meta_values}
          WHERE chid = '%d')", $info['chid_to'], $chid);
    }
  }

  # voters
  $voters = db_result(db_query("
    SELECT GROUP_CONCAT(v.uid) uids
    FROM {cpoll_choices} c
    LEFT JOIN {cpoll_votes} v ON v.chid = c.chid AND v.status = 1
    WHERE c.nid = '%d'", $base));
  if (!$voters) {
    $voters = 0;
  }

  # insert updated votes
  $case = "";
  foreach ($values['choices'] as $chid => &$info) {
    if (-1 != $info['chid_to']) {
      $case .= " WHEN " . $chid . " THEN " . $info['chid_to'];
    }
  }
  db_query("
    INSERT INTO cpoll_votes (chid, uid, status, cdate) (
	    SELECT (CASE v.chid WHEN 0 THEN 0 " . $case . " END) chid, v.uid, v.status, v.cdate
	    FROM cpoll_choices c
	    INNER JOIN cpoll_votes v ON v.chid = c.chid
	    WHERE c.nid = '%d' AND v.uid NOT IN (" . $voters . "))", $merge);

  # make them duplicate each other
  $merge_node = node_load($merge);
  $merge_node->field_base_issue[0]['nid'] = $base;
  node_save($merge_node);

  // todo messages

  # actions
  global $user;
  function_exists('action_queue') && action_queue(array(
    'uid'         => $user->uid,
    'operation'   => 'merge',
    'entity_id'   => $merge,
    'entity_type' => 'node',
  ));

  drupal_goto('node/' . $base);
}
