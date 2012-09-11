<?php

/**
 * The function to handle "/debate/ajax" callbacks
 *
 *
 */
function debate_ajax() {
  global $base_url, $user, $gDocPath, $base_root, $theme;
  # Extract the params: $_REQUEST['action'] to $action
  $action = '';
  $url = '';
  extract($_REQUEST);
  # Get site url with default language


  # Switch $action
  switch( $action ) {
    case 'url' :
      if( empty($url) ) {
        exit("<div class='messages error'>".t('No URL provided.')."</div>");
      }
      _debate_ajax_url($url);
      break;
  }

  switch ($action) {
    case 'url' : break;





    case 'filter':
      $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
      echo list_debate($qid, 1);
      break;

    default:
      echo "<div class='messages error'>No Action found</div>";
      break;
  }

  exit;
}
 
 
/**
 * Function to handle URL calls fro debate_ajax()
 *
 * @param url - the URL to handle
 */
function _debate_ajax_url($url) {
  global $base_url;

  # include required libraries
  require_once('simple_html_dom.php');
  require_once('thumbnail.php');
  require_once('url_to_absolute.php');

  # get html
  $html = file_get_html($url);
  if( !$html ) {
    exit('');
    # exit("<div class='messages error'>".t('Error loading URL')."</div>");
  }

  # get domain
  $domain = parse_url($url, PHP_URL_HOST);
  # get images
  $images = array();
  $images_source = $html->find('img');
  foreach( $images_source as $element ) {
    # $images[$element->src] = true;
    $images[] = url_to_absolute($url, $element->src);
  }
  $images = arguments_resource_validate_images($images);
  # get title
  $title = $html->find('title', 0);
  if( $title ) {
    $title = $title->innertext;
  }
  # get description
  $tags = get_meta_tags($url);
  $description = $tags['description'];
  # get image count
  $count = count($images);
  $image_count = $count > 10 ? '10' : $count;
  $image_first = $count > 0 ? 1 : 0;
  $image_last = $image_count != 0 ? ($image_count - 1) : 0;
  $image_path = $base_url . '/' . drupal_get_path('theme', 'hmware') . '/images/';
  # output
  echo theme('debate_ajax_url',
    $images, $image_count, $image_first, $image_last, $image_path,
    '<em>'.$title.'</em>source:&nbsp;<strong>'.$domain.'</strong><span>'.$description.'</span>'
  );
}










