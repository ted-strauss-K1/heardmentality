<?php

function core_menu() {
  $menu = array();

  $menu['convert'] = array(
    'page callback' => 'core_convert',
    'access callback' => true,
    'type' => MENU_CALLBACK,
  );

  return $menu;
}

/**
 *
 */
function core_convert() {
  set_time_limit(0);

  $query = "SELECT * FROM node WHERE type IN ('poll')";
  $result = db_query($query);
  while ($row = db_fetch_object($result)) {
    $conv = node_load($row->nid);

    $node = new stdClass();
    $node->type = 'issue';
    $node->language = $conv->language;
    $node->uid = $conv->uid;
    $node->status = $conv->status;
    $node->moderate = 1;
    $node->title = preg_replace('/\?$/', '', trim($conv->title));
    $node->body = $conv->field_description[0]['value'];
    $node->name = $conv->name;
    node_save($node);

    db_query("UPDATE content_type_poll SET n = '%d' WHERE nid = '%d'", $node->nid, $conv->nid);
  }

  $query = "SELECT * FROM node WHERE type IN ('forum')";
  $result = db_query($query);
  while ($row = db_fetch_object($result)) {
    $conv = node_load($row->nid);

    $node = new stdClass();
    $node->language = $conv->language;
    $node->uid = $conv->uid;
    $node->status = $conv->status;
    $node->moderate = 0;
    $node->title = $conv->title;
    $node->body = $conv->body;
    $node->name = $conv->name;
    $node->field_references[0]['nid'] = (int)db_result(db_query("SELECT ctp.n FROM content_type_forum ctf, content_type_poll ctp WHERE ctf.field_issue_nid = ctp.nid AND ctf.nid = '%d'", $conv->nid));

    if ($conv->field_argument_type[0]['value'] == 1) {
      $node->type = 'argument';

    } else {
      $node->type = 'resource';
      $node->field_url = $conv->field_url;
      $node->field_rtype = $conv->field_rtype;
      $node->field_source = $conv->field_source;
      $node->field_youtube = $conv->field_youtube;
      $node->field_image_path = $conv->field_imaeg_path;
    }
    node_save($node);

    db_query("UPDATE content_type_forum SET n = '%d' WHERE nid = '%d'", $node->nid, $conv->nid);
  }

}