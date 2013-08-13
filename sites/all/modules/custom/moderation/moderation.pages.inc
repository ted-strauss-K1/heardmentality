<?php

/**
 * Moderation for Issues
 *
 * @return array
 */
function moderation_issues_form()
{
  return _moderation_form('issues');
}

/**
 * Moderation for Arguments
 *
 * @return array
 */
function moderation_arguments_form()
{
  return _moderation_form('arguments');
}

/**
 * Moderation for Comments
 *
 * @return array
 */
function moderation_comments_form()
{
  return _moderation_form('comments');
}

/**
 * Moderation for Users
 *
 * @return array
 */
function moderation_users_form()
{
  return _moderation_form('users');
}

/**
 * Common way to call the list form
 *
 * @param string $type
 * @return array
 */
function _moderation_form($type = 'issues')
{
  $form = array();

  // get header for the form
  $form['#prefix'] = theme('moderation_main', $type);

  // get the pages
  $page = arg(2);
  $page = is_null($page) || !is_numeric(arg(2)) || $page <= 0 ? 1 : (int)$page;
  $pages = 1;

  // request the filters
  $filters = _moderation_content_filter($type);

  // filters to form elements
  $form += _moderation_form_filter_elements($filters);

  // choose the elements
  $items = _moderation_form_content_filter($type, $filters, $page);

  // add the filtered items to form
  foreach ($items as $index => $item) {
    $value = '';
    switch ($type) {
      case 'issues' :
      case 'arguments' :
      case 'comments' :
        $value = theme('moderation_item', $item);
        break;
      case 'users' :
        $value = moderation_markup_user($item);
        break;
    }
    $form['item-' . $index] = array(
      '#type' => 'markup',
      '#value' => $value,
    );
  }

  if (empty($items)) {
    $form['item_none'] = array(
      '#type' => 'markup',
      '#value' => '<span>'.t('No items found').'</span>',
    );
  }

  // add pager
  $pattern = 'moderation/' . $type . '/%d/' . arg(3);
  $form['#suffix'] = theme('moderation_pager', $page, $pages, $pattern);

  // add redirect
  $form['#redirect'] = sprintf($pattern, 1);

  return $form;
}

/**
 * @param $type
 */
function _moderation_content_filter($type = 'issues') {
  $list = array();

  switch ($type) {
    case 'issues' :
      /**
       * @code 1 - flagged
       * @code 2 - not moderated
       */
      $list['status'] = is_null($_SESSION['status']) ? 1 : $_SESSION['status'];
      break;
  }

  // perpage works for every list
  $list['perpage'] = is_null($_SESSION['perpage']) ? 10 : $_SESSION['perpage'];

  return $list;
}

/**
 * Filters for Content
 *
 * @param $filters
 * @return array
 */
function _moderation_form_filter_elements($filters)
{
  $form = array();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if (isset($filters['status'])) {
    $form['filters']['status'] = array(
      '#type' => 'select',
      '#title' => t('Content'),
      '#options' => array(1 => t('Flagged'), 2 => t('Not moderated')),
      '#default_value' => $filters['status'],
    );
  }

  if (isset($filters['perpage'])) {
    $form['filters']['perpage'] = array(
      '#type' => 'select',
      '#title' => t('Per page'),
      '#options' => array(10 => 10, 15 => 15, 20 => 20, 25 => 25),
      '#default_value' => $filters['perpage'],
    );
  }

  if (!empty($filters)) {
    $form['filters']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('_moderation_form_filter_save'),
    );
  } else {
    $form = array();
  }

  return $form;
}

/**
 * Stores the values to $_SESSION
 *
 * @param $form
 * @param $form_state
 */
function _moderation_form_filter_save($form, &$form_state)
{
  foreach (array('status', 'perpage') as $key) {
    if (isset($form_state['values'][$key])) {
      $_SESSION[$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Returns the list of items
 *
 * @param $type
 * @param $filters
 * @param $page
 * @param $pages
 */
function _moderation_form_content_filter($type, $filters, $page) {
  if (in_array($type, array('issues', 'arguments', 'comments', 'users'))) {
    $function = '_moderation_form_content_filter_'.$type;
    if (function_exists($function)) {
      return $function($filters, $page);
    }
  }
  return array();
}

/**
 * @param $count
 * @param $perpage
 * @param $page
 * @param $pages
 */
function _moderation_pages($count, $perpage, &$page, &$pages) {
  $pages = ceil($count / $perpage);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }
}

/**
 * @param $filters
 * @param $page
 * @return array
 */
function _moderation_form_content_filter_issues($filters, $page) {
  $items = array();

  # build query
  $query = "SELECT %% FROM {node} n";
  $params = array();

  # filters
  global $user;
  switch ($filters['status']) {
    case 1 :
      $query .= " INNER JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = '%s'";
      $params[] = 'node';
      break;
    case 2 :
      $query .= " LEFT JOIN {moderation_history} mh ON mh.content_type = '%s' AND mh.type = '%s' AND mh.content_id = n.nid AND mh.uid = '%d'";
      $params[] = 'node';
      $params[] = 'approve';
      $params[] = $user->uid;
      break;
  }

  # WHERE
  $query .= " WHERE 1";

  # type = issue
  $query .= " AND n.type = '%s'";
  $params[] = 'issue';

  # status = 1
  $query .= " AND n.status = '%d'";
  $params[] = 1;

  # not moderated
  $query .= " AND n.moderate <> '%d'";
  $params[] = 0;

  # moderation
  switch ($filters['status']) {
    case 1 :
      //
      break;
    case 2 :
      $query .= " AND mh.type IS NULL";
      break;
  }

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT n.nid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  _moderation_pages($count, $filters['perpage'], $page, $pages);

  $query .= " GROUP BY n.nid";
  $query .= " ORDER BY n.changed ASC";

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT n.nid', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $items[] = node_load($node->nid);
  }

  return $items;
}

/**
 * @param $filters
 * @param $page
 * @return array
 */
function _moderation_form_content_filter_arguments($filters, $page) {
  $items = array();

  # build query
  $query = "SELECT %% FROM {node} n";
  $params = array();

  # only that require moderation
  $query .= " INNER JOIN {content_field_reference} cfr ON cfr.nid = n.nid AND cfr.vid = n.vid";

  # only flagged ones
  $query .= " INNER JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = '%s'";
  $params[] = 'node';

  # WHERE
  $query .= " WHERE 1";

  # specific argument
  if (($issue_id = arg(3)) && is_numeric($issue_id)) {
    $query .= " AND ct.field_reference_nid = '%d'";
    $params[] = $issue_id;
  }

  # type = poll
  $query .= " AND n.type IN ('%s', '%s')";
  $params[] = 'argument';
  $params[] = 'resource';

  # status = 1
  $query .= " AND n.status = '%d'";
  $params[] = 1;

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT n.nid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  _moderation_pages($count, $filters['perpage'], $page, $pages);

  $query .= " GROUP BY n.nid";
  $query .= " ORDER BY n.changed ASC";

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT n.nid', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $items[] = node_load($node->nid);
  }

  return $items;
}

/**
 * Filters the list of Comments
 *
 * @param $filters
 * @param $page
 * @param $pages
 * @return array
 */
function _moderation_form_content_filter_comments($filters, $page)
{
  $items = array();

  # build query
  $query = "SELECT %% FROM {comments} c";
  $params = array();

  # flagged
  $query .= " LEFT JOIN {flag_content} fc ON fc.content_id = c.cid AND fc.content_type = '%s'";
  $params[] = 'comment';

  # WHERE
  $query .= " WHERE 1";

  # specific argument
  if (($argument_id = arg(3)) && is_numeric($argument_id)) {
    $query .= " AND c.nid = '%d'";
    $params[] = $argument_id;
  }

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT c.cid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  _moderation_pages($count, $filters['perpage'], $page, $pages);

  $query .= " GROUP BY c.nid";
  $query .= " ORDER BY c.cid ASC";

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT c.*', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $items[] = $node;
  }

  return $items;
}

/**
 * Filters the list of Users
 *
 * @param $filters
 * @param $page
 * @param $pages
 * @return array
 */
function _moderation_form_content_filter_users($filters, $page)
{
  $items = array();

  # build query
  $query = "SELECT %% FROM {users} u WHERE u.uid > 0";
  $params = array();

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(*) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  _moderation_pages($count, $filters['perpage'], $page, $pages);

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT u.*', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $items[] = user_load($node->uid);
  }

  return $items;
}

/**
 * Markup for the User in moderation list
 *
 * @param $user
 * @return string
 */
function moderation_markup_user($user)
{
  static $perms = array();

  if (empty($perms)) {
    $perms = variable_get(MODERATION_USERS, array());
  }

  return user_access(MODERATION_ADMIN, $user) ? '' :
    '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . ucwords($user->name) . ' <div class="open"></div> </h2>
    <div class="mod-buttons">' .
      sprintf('<a href="%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a>', $user->viewlink, t('View Profile')) .
      sprintf('<a href="#" class="permission %s" name="%s"><span class="mod-edit mod-icon" title="%s"></span></a>',
        !moderation_check_perm($user->uid) ? '' : 'remove', 'moderation/user/' . $user->uid, t('Change permissions')) .
      '</div>
  </div>';
}

/**
 * Moderation for Issues (View)
 *
 * @return array
 */
function moderation_issue_view_form($form_state, $nid)
{
  $form = array();

  drupal_add_js(drupal_get_path("module", "moderation") . "/moderation.lists.js");

  $form['content_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );
  $form['content_type'] = array(
    '#type' => 'hidden',
    '#value' => 'node',
  );

  $form['#prefix'] = theme('moderation_main', 'issues');
  $form['#attributes']['class'] = 'mod-form';

  $node = node_load($nid);

  if ($node->moderate != MODERATION_ALLOWED) {
    drupal_set_message(t('Moderation of that issue is not allowed'), 'warning');
  }

  if ('issue' != $node->type) {
    drupal_goto('moderation');
  }

  //
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#value' => issue_translate($node, 'title'),
    '#prefix' =>
    '<div class="dark-grey-box" style="margin:10px 0; width: 90%">' .
      '<div style="float:right;margin-right: 30px;">' .
      l(
        sprintf('<span class="mod-view mod-icon" title="%s"></span>', t('View')),
        $node->path,
        array(
          'html' => TRUE,
          'attributes' => array('target' => '_blank'),
        )
      ) .
      '</div>',
    '#suffix' => '</div>',
  );
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#value' => issue_translate($node, 'body'),
    '#prefix' => sprintf('<div class="dark-grey-box" style="margin:10px 0; width: 90%%">'),
    '#suffix' => '</div>',
  );

  $form['fixed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Forbid suggesting answers'),
    '#value' => $node->cpoll['fixed'],
  );
  $form['active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active Poll'),
    '#value' => $node->cpoll['active'],
  );

  $form['choices'] = array(
    '#type' => 'fieldset',
    '#title' => t('Leave the choice text empty to request its deletion'),
    '#prefix' => '<div id="choices-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#disabled' => TRUE,
  );

  //
  foreach ($node->choices as $chid => $choice) {
    $choice['chtext'] = issue_translate($node, 'chtext', $chid);
    $choice['chtext_short'] = issue_translate($node, 'chtext_short', $chid);
    $form_element = _moderation_ahah_choice($choice['index'], $choice, $nid);
    $form['choices'][$choice['index']] = $form_element;
  }

  // todo add choices when viewing on other language

  # original language
  global $language;
  if (($node->language == $language->language) && !$node->cpoll['fixed']) {
    // add more
    $form['choices']['add_more'] = array(
      '#type' => 'submit',
      '#value' => '+ ' . t('Add another choice'),
      '#weight' => 1,
      '#ahah' => array(
        'path' => 'moderation/ahah/choices',
        'wrapper' => 'choices-wrapper',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
  }

  // taxonomy
  $tft_codes = empty($node->taxonomy) ? array() : array_keys($node->taxonomy);
  moderation_issue_view_form_taxonomy($form, $tft_codes);

  // locations
  $tfl_codes = array(0 => array(), 1 => array(), 2 => array());
  if (!empty($node->locations)) {
    foreach ($node->locations as $location) {
      if (!empty($location['country'])) {
        $tfl_codes[0][] = $location['country'];
        if (!empty($location['province'])) {
          $tfl_codes[1][] = $location['country'] . '_' . $location['province'];
          if (!empty($location['city'])) {
            $tfl_codes[2][] = $location['country'] . '_' . $location['province'] . '_' . $location['city'];
          }
        }
      }
    }
  }
  moderation_issue_view_form_location($form, $tfl_codes);

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save and Approve'),
    '#submit' => array('moderation_issue_view_form_save'),
  );
  global $user;
  if (!moderation_history_get($form['content_id']['#value'], $form['content_type']['#value'], array(
    'type' => 'delete',
    'uid' => $user->uid
  ))) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Deletion request'),
      '#submit' => array('moderation_issue_view_form_delete'),
    );
  }

  return $form;
}

/**
 * Choice form element for
 *
 * @param $delta
 * @param bool $choice
 * @param int $nid
 * @return array
 */
function _moderation_ahah_choice($delta, $choice = FALSE, $nid = 0)
{
  # create empty choice
  if (FALSE === $choice) {
    global $user;
    $choice = (array)cpoll_choice_save(array(
      'chid' => -1,
      'uid' => $user->uid,
      'nid' => $nid,
      'chtext' => '',
      'chtext_short' => '',
      'weight' => 100,
      'chtype' => 'regular',
    ));
  }

  $form = array(
    '#tree' => TRUE,
  );
  // We'll manually set the #parents property of these fields so that
  // their values appear in the $form_state['values']['choice'] array.
  $form['votes'] = array(
    '#type' => 'markup',
    '#value' => '<div class="mod-votecount-wrapper"><span>'.t('Votes') . ': ' . intval($choice['votes']) . '</span></div>',
  );
  $form['chtext'] = array(
    '#type' => 'textfield',
    '#title' => t('Choice @n', array('@n' => ($delta + 1))),
    '#default_value' => $choice['chtext'],
    '#parents' => array('choices', $delta, 'chtext'),
  );
  $form['chtext_short'] = array(
    '#type' => 'textfield',
    '#title' => t('Choice short text @n', array('@n' => ($delta + 1))),
    '#default_value' => $choice['chtext_short'],
    '#parents' => array('choices', $delta, 'chtext_short'),
  );
  $form['chid'] = array(
    '#type' => 'hidden',
    '#default_value' => $choice['chid'],
    '#parents' => array('choices', $delta, 'chid'),
  );
  $form['uid'] = array(
    '#type' => 'hidden',
    '#default_value' => $choice['uid'],
    '#parents' => array('choices', $delta, 'uid'),
  );

  global $user;
  $form['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metadata'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $meta = cpoll_meta_values_get($nid, $user->uid);
  if ($meta[$choice['chid']]) {
    foreach ($meta[$choice['chid']] as $cid => $value) {
      $form['meta']['char'.$cid] = array(
        '#type' => 'select',
        '#title' => t($value['chtext']),
        '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
        '#value' => $value['val'],
        '#size' => 5,
        '#parents' => array('choices', $delta, 'meta', 'char'.$cid),
        '#prefix' => '<div class="poll-meta poll-meta-'.$cid.'">',
        '#suffix' => '</div>',
      );
    }
  } else {
    $meta = cpoll_meta_get();
    foreach ($meta as $cid => $text) {
      $form['meta']['char'.$cid] = array(
        '#type' => 'select',
        '#title' => t($text),
        '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
        '#value' => CPOLL_META_AVG,
        '#size' => 5,
        '#parents' => array('choices', $delta, 'meta', 'char'.$cid),
        '#prefix' => '<div class="poll-meta poll-meta-'.$cid.'">',
        '#suffix' => '</div>',
      );
    }
  }


  return $form;
}

/**
 * Moderation/ahah menu callback
 *
 * @param $type
 */
function moderation_ahah($type, $page = 0)
{
  # build new form
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  if (!$form = form_get_cache($form_build_id, $form_state)) {
    exit();
  }

  # change the form parts
  switch ($type) {
    case 'choices' :
      $delta = count($_POST['choices']);

      $form_element = _moderation_ahah_choice($delta);
      @drupal_alter('form', $form_element, array());
      $form['choices'][$delta] = $form_element;

      $post_choices = $_POST['choices'];

      if (is_array($post_choices)) {
        foreach ($post_choices as $chorder => $vals) {
          if ($vals['meta']) {
            foreach ($vals['meta'] as $_key => $_val) {
              $form['choices'][$chorder]['meta'][$_key]['#value'] = $_val;
            }
          }
        }
      }
      break;
  }

  # save the form
  form_set_cache($form_build_id, $form, $form_state);

  # rebuild new form
  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form = form_builder($form_id, $form, $form_state);

  # render the form parts
  switch ($type) {
    case 'choices' :
      $choice_form = $form['choices'];
      $output = drupal_render($choice_form);
      break;
  }

  print json_encode(array('status' => TRUE, 'data' => $output, 'post' => $_POST));
  exit;
}

/**
 * @param $form
 * @param array $tft_codes
 */
function moderation_issue_view_form_taxonomy(&$form, $tft_codes = FALSE)
{
  // taxonomy container
  $form['taxonomy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Categories'),
    '#prefix' => '<div id="taxonomy-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  // gather info:: taxonomy
  if ($tft_codes === FALSE) {
    $tft_codes = array();
    $data = $_POST['taxonomy'];
    for ($i = 0; $i >= 0; $i++) {
      if (empty($data['taxonomy-' . $i])) {
        break;
      }
      foreach ($data['taxonomy-' . $i] as $tid) {
        $tft_codes[] = (int)$tid;
      }
    }
  }
  $tft = tft_list('poll', $tft_codes);

  // taxonomy depth::
  $tree = taxonomy_node_type_terms();
  $depth = 0;
  foreach ($tree as $leaf) {
    if ($depth < $leaf->depth) {
      $depth = $leaf->depth;
    }
  }

  // lists:: taxonomy
  $count = count($tft['list']);
  for ($i = 0; $i <= 2 /*$depth*/; $i++) {
    if ($i < $count) {
      $options = $tft['list'][$i];
      $checked = $tft['checked'][$i];
    } else {
      $options = array();
      $checked = array();
    }
    $form['taxonomy']['taxonomy-' . $i] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $checked,
      '#size' => '4',
      '#attributes' => array('class' => 'chosen-mod tft '.($i>0 ? 'hideable':'')),
      '#validated' => TRUE,
    );
  }
}

/**
 * @param $form
 * @param array $tft_codes
 */
function moderation_issue_view_form_location(&$form, $tfl_codes = FALSE)
{
  // location container
  $form['location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Location'),
    '#prefix' => '<div id="location-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  // gather info:: location
  if ($tfl_codes === FALSE) {
    $data = $_POST['location'];
    $tfl_codes = array();
    for ($i = 0; $i <= 2; $i++) {
      $tfl_codes[$i] = !empty($data['location-' . $i]) ? $data['location-' . $i] : array();
    }
  }

  $tfl = tfl_list($tfl_codes[0], $tfl_codes[1], $tfl_codes[2]);

  for ($i = 0; $i < 3 /*count($tfl['list'])*/; $i++) {
    $options = $tfl['list'][$i];
    $checked = $tfl['checked'][$i];

    $form['location']['location-' . $i] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $checked,
      '#size' => '4',
      '#attributes' => array('class' => 'chosen-mod tfl '.($i>0 ? 'hideable':'')),
      '#validated' => TRUE,
    );
  }
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_issue_view_form_delete(&$form, &$form_state)
{
  moderation_delete_request($form);

  moderation_badges();
}

/**
 *
 */
function moderation_badges() {
  if (module_exists('badges')) {
    $result = db_query("SELECT DISTINCT(uid) FROM {flag_content}");
    while ($uid = db_result($result)) {
      badges_queue($uid, array(
        'flag_success'
      ));
    }
  }
}

/**
 *
 */
define('MODERATION_DELETE_COUNT', 1);

/**
 * @param $form
 */
function moderation_delete_request($form)
{
  moderation_history_set($form['content_id']['#value'], $form['content_type']['#value'], 'delete');
  $delete_requests = count(moderation_history_get($form['content_id']['#value'], $form['content_type']['#value'], array('type' => 'delete')));

  if ($delete_requests >= MODERATION_DELETE_COUNT) {
    switch ($form['content_type']['#value']) {
      case 'comment' :
        $comment = _comment_load($form['content_id']['#value']);
        comment_unpublish_action($comment);
        rules_invoke_event('comment_unpublish', $comment);
      break;
      case 'node' :
        db_query("UPDATE node SET status = '%d' WHERE nid = '%d'", 0, $form['content_id']['#value']);
      break;
    }
    drupal_set_message(t('Content deletion approved.'));
  } else {
    drupal_set_message(t('Content deletion not approved.') . ' ' . (MODERATION_DELETE_COUNT - $delete_requests) . ' ' . t('deletion requests from other moderators are required.'));
  }
}

/**
 * @param $uid
 */
function moderation_perms($uid)
{
  $perms = variable_get(MODERATION_USERS, array());
  if ($perms[$uid]) {
    unset($perms[$uid]);
  } else {
    $perms[$uid] = 1;
  }
  variable_set(MODERATION_USERS, $perms);
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_issue_view_form_save(&$form, &$form_state)
{
  global $user;
  $values = $form_state["clicked_button"]['#post'];
  $nid = $values['content_id'];
  $node = node_load($nid);

  // there we store changes
  $changed = array();


  // title changed
  $title = issue_translate($node, 'title');
  if ($title != $values['title']) {
    $changed['title'] = $values['title'];
  }

  // body changed
  $body = issue_translate($node, 'body');
  if ($body != $values['body']) {
    $changed['body'] = $values['body'];
  }

  // choices changed
  $meta = cpoll_meta_get();
  $usermeta = cpoll_meta_values_get($node->nid, $user->uid);
  foreach ($values['choices'] as $choice) {
    $chid = $choice['chid'];
    // chtext
    foreach (array('chtext', 'chtext_short') as $key) {
      $$key = issue_translate($node, $key, $chid);
      if ($choice[$key] != $$key) {
        $changed['choices'][$chid][$key] = $choice[$key];
        $changed['choices'][$chid][$key . '_old'] = $$key;
      }
    }
    # meta
    foreach ($meta as $cid => $text) {
      if ($choice['meta']['char'.$cid] != $usermeta[$chid][$cid]) {
        // todo history of meta changes
      }
      cpoll_meta_value_set($chid, $user->uid, $cid, $choice['meta']['char'.$cid]);
    }
  }

  // poll status
  $node->cpoll['fixed'] = $values['fixed'];
  $node->cpoll['active'] = $values['active'];

  # taxonomy changes
  $taxonomy_old = array();
  foreach ($node->taxonomy as $term) {
    $taxonomy_old[intval($term->tid)] = $term;
  }
  $taxonomy_diff = array();
  $node->taxonomy = array();
  for ($i = 0; $i >= 0; $i++) {
    if (!empty($values['taxonomy']['taxonomy-' . $i])) {
      foreach ($values['taxonomy']['taxonomy-' . $i] as $tid) {
        $node->taxonomy[] = taxonomy_get_term($tid);
        if (!isset($taxonomy_old[intval($tid)])) {
          $taxonomy_diff[] = $tid;
        }
      }
    } else break;
  }

  // events
  module_invoke_all('process_event', 'taxonomy', array(
    'content_type' => 'node',
    'content_id' => $node->nid,
    'tids' => $taxonomy_diff,
  ), $user->uid);

  # locations
  $node->locations = array();
  # counties
  if (is_array($values['location']['location-0'])) {
    foreach ($values['location']['location-0'] as $country) {
      # empty location
      $location = location_empty_location(array());
      # init it with countrycode
      $location['country'] = $country;
      $location['name'] = $country;
      # provinces
      $provinces = FALSE;
      foreach (location_get_provinces($country) as $pcode => $pname) {
        if (is_array($values['location']['location-1'])) {
          # province selected found
          if (in_array($location['name'].'_'.$pcode, $values['location']['location-1'])) {
            $provinces = TRUE;
            # add province code
            $location2 = $location;
            $location2['province'] = $pcode;
            $location2['name'] .= '_' . $pcode;
            # cities
            $cities = FALSE;
            foreach (location_get_cities($location2['country'], $location2['province']) as $ccode => $name) {
              if (is_array($values['location']['location-2'])) {
                # city selection found
                if (in_array($location2['name'] . '_' . $ccode, $values['location']['location-2'])) {
                  $cities = TRUE;
                  # add city code
                  $location3 = $location2;
                  $location3['city'] = $ccode;
                  $location3['name'] .= '_' . $ccode;
                  $node->locations[] = $location3;
                }
              }
            }
            // if no cities are set - let the location be just a province
            if (!$cities) {
              $node->locations[] = $location2;
            }
          }
        }
      }
      # if no provinces are set - let the location be just a country
      if (!$provinces) {
        $node->locations[] = $location;
      }
    }
  }

  # save
  global $language;
  # original language
  if ($node->language == $language->language) {
    $node->title = $values['title'];
    $node->body = $values['body'];

    # add new choices
    foreach ($values['choices'] as $choice) {
      if (!isset($node->choices[$choice['chid']])) {
        $count = count($node->choice);
        $node->choices[$choice['chid']] = array(
          'chid' => $choice['chid'],
          'nid' => $node->nid,
          'uid' => $choice['uid'],
          'chtext' => $choice['chtext'],
          'chtext_short' => $choice['chtext_short'],
          'weight' => $count,
          'type' => 'regular',
        );
      } else {
        $node->choices[$choice['chid']]['chtext'] = $choice['chtext'];
        $node->choices[$choice['chid']]['chtext_short'] = $choice['chtext_short'];
      }
    }
  }

  # translation
  else {
    # init translation if it does not exist
    if (!$node->t) {
      $node->t = array();
    }
    if (!$node->t[$language->language]) {
      $node->t[$language->language] = array();
    }
    $t = & $node->t[$language->language];

    $t['title'][0] = $values['title'];
    $t['body'][0] = $values['body'];
    foreach ($values['choices'] as $choice) {
      $t['chtext'][$choice['chid']] = $choice['chtext'];
      $t['chtext_short'][$choice['chid']] = $choice['chtext_short'];
    }
  }

  # record the changes to history
  moderation_history_set($nid, 'node', 'edit', $changed);

  # approved
  moderation_history_del($nid, 'node', array('type' => 'approve'));
  moderation_history_set($nid, 'node', 'approve');
  moderation_history_del($nid, 'node', array('!uid' => $user->uid));

  # save node
  node_save($node);

  # reindex
  if (module_exists('issue_search')) {
    issue_search_index_node($node->nid);
  }
}