<?php







/*****************************************
 ******************************************
 ******************************************
 ******************************************/


// issue search form
function issue_search_form(&$form_state)
{
//$form['#method'] = 'get';
  $key = arg(1) == '0' ? '' : check_plain(arg(1));
  $subject = check_plain(arg(2));
  $area = check_plain(arg(3));
  $detail = check_plain(arg(4));
  $getcountry = check_plain(arg(5));
  $getState = check_plain(arg(6));
  $getCity = check_plain(arg(7));

  $inline = 'function clrForm(thisform){jQuery(":input", "#issue-search-form").not(":button, :submit, :hidden").val("").removeAttr(":selected");}';
  drupal_add_js($inline, 'inline');


  $form['issue_key'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $key
  );
  $form['category_mark'] = array(
    '#type' => 'markup',
    '#value' => t('FILTER BY CATEGORY') . '<br /><div class="clr"></div>'
  );
  /* categories */
  $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s' AND module = '%s'", 'Sections', 'taxonomy'));
  $client_select = db_query("SELECT t.tid AS cat_id, t.name AS cat_name FROM term_data t RIGHT JOIN term_hierarchy h ON t.tid = h.tid where h.parent='0' AND t.vid = '$vid'");
  $options[''] = t('SUBJECT');
  while ($list = db_fetch_object($client_select)) {
    $cnt = taxonomy_term_count_nodes($list->cat_id);
    if ($cnt != 0) {
      $options[$list->cat_id] = t(stripslashes($list->cat_name));
    }
  }
  $form['subject'] = array('#type' => 'select',
    '#options' => $options,
    '#prefix' => '<div style="float:left;">',
    '#suffix' => '</div>',
    '#ahah' => array('wrapper' => 'sub-cat-wrapper',
      'event' => 'change',
      'path' => 'issue/ahah/category/scat',
      'effect' => 'fade',
      'method' => 'replace'),
    '#attributes' => array('class' => 'selectbox-sm'),
    '#default_value' => $subject,
    '#id' => 'subject');
// get first level category
  $form['defarea'] = array(
    '#type' => 'hidden',
    '#default_value' => $area
  );
  $form['defdetail'] = array(
    '#type' => 'hidden',
    '#default_value' => $detail
  );
  $form['sub_categories'] = array(
    '#type' => 'markup',
    '#value' => '<div id="sub-cat-wrapper" style="float:left"></div>',
  );
  $form['sub_sub_categories'] = array(
    '#type' => 'markup',
    '#value' => '<div id="sub-sub-cat-wrapper" style="float:left">
                                                </div>',
    '#suffix' => '<br /><div class="clr"></div>');
  $form['location_mark'] = array(
    '#type' => 'markup',
    '#value' => t('FILTER BY LOCATION') . '<br /><div class="clr"></div>'
  );
// location
  $countries[''] = t('COUNTRY');


  /*   * Ralldev : 481* */
  global $language;
  $curLanguage = $language->language;
  $cck_country = db_query("select cc.field_issue_country_value from content_field_issue_country cc, node n where cc.nid = n.nid and n.language = '$curLanguage' group by field_issue_country_value");
  /*   * */

  while ($ccklist = db_fetch_object($cck_country)) {
    if (!empty($ccklist->field_issue_country_value))
      $countries[$ccklist->field_issue_country_value] = $ccklist->field_issue_country_value;
  }
//  array_filter($countries, 'strlen');
  $form['country'] = array('#type' => 'select',
    '#options' => $countries,
    '#prefix' => '<div style="float:left;">',
    '#suffix' => '</div>',
    '#ahah' => array('wrapper' => 'state-wrapper',
      'path' => 'issue/ahah/location/state',
      'effect' => 'fade',
      'event' => 'change',),
    '#attributes' => array('class' => 'selectbox-sm'),
    '#default_value' => $getcountry,
    '#id' => 's_country');

// default state, city
  $form['defstate'] = array(
    '#type' => 'hidden',
    '#default_value' => $getState
  );
  $form['defcity'] = array(
    '#type' => 'hidden',
    '#default_value' => $getCity
  );
  $form['cur_language'] = array(
    '#type' => 'hidden',
    '#value' => $curLanguage
  );
  $form['state_div'] = array(
    '#type' => 'markup',
    '#value' => '<div id="state-wrapper" style="float:left"></div>'
  );
  $form['city_div'] = array(
    '#type' => 'markup',
    '#value' => '<div id="city-wrapper" style="float:left"></div>',
    '#suffix' => '<br /><div class="clr"></div>'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('SUBMIT'),
    '#attributes' => array(
      'class' => 're-submit light floatleft')
  );
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#attributes' => array('class' => 'search-button')
  );
  $form['reset_btn'] = array(
    '#type' => 'markup',
    '#value' => '<input type="button" value="' . t('CLEAR OPTIONS') . '" name="reset" onclick="javascript:clrForm(this.form)" class="re-submit light floatleft" />');
  return $form;
}

// issue search form submit
function issue_search_form_submit($form, &$form_state)
{
//echo '<pre>';print_r($form_state);exit;
  $key = $form_state['values']['issue_key'];
  $key = $key != "" ? $key : 0;

  $subject = $form_state['values']['subject'];
  $subject = $subject != "" ? $subject : 0;
  $area = $form_state['clicked_button']['#post']['area'];
  $area = $area != "" ? $area : 0;
  $detail = $form_state['clicked_button']['#post']['detail'];
  $detail = $detail != "" ? $detail : 0;

  $country = $form_state['values']['country'];
  $country = $country != "" ? $country : 0;
  $state = $form_state['clicked_button']['#post']['state'];
  $state = $state != "" ? $state : 0;
  $city = $form_state['clicked_button']['#post']['city'];
  $city = $city != "" ? $city : 0;

// $path = 'issues/?key='.$key.'&subject='.$subject.'&area='.$area.'&detail='.$detail.'&country='.$country.'&state='.$state.'&city='.$city;
  $path = 'issues/' . $key . '/' . $subject . '/' . $area . '/' . $detail . '/' . $country . '/' . $state . '/' . $city;
  drupal_goto($path);
}

function issue_ajax_($task = '', $nid = '')
{
  global $base_url, $user;
  switch ($task) {
    case 'debate_statistics':
      $result = '<div id="debate_statistic" width="520" height="360">
        <div id="container" class="highcharts-container" style="height:400px; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
</div>';
      break;

  }
  echo $result;
}
