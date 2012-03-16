<?php
//echo '<pre>'; print_r($form); exit;
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);

// get hidden values
print drupal_render($form['defarea']);
print drupal_render($form['defdetail']);
print drupal_render($form['defstate']);
print drupal_render($form['defcity']);

  /**Rallydev:518**/
  //IMPORTANT : Need to move this logic to module section, after approval from client
  $final_category = "";
  $final_location = "";
  $search_filters = "";
  
  if(arg(1)) {
    $search_filters[] = arg(1);
  }
  
  $subject = arg(2);
  $subject_term = taxonomy_get_term($subject)->name;
  if(trim($subject_term)!="") {
     $search_filters[] =  $final_category = t($subject_term);
  } 
  
  $subject_sub_cat_1 = arg(3);
  $subject_sub_cat_1_term = taxonomy_get_term($subject_sub_cat_1)->name;
  if(trim($subject_sub_cat_1_term)!="") {
     $search_filters[] = t($subject_sub_cat_1_term);
  } 
  
  $subject_sub_cat_2 = arg(4);
  $subject_sub_cat_2_term = taxonomy_get_term($subject_sub_cat_2)->name;
  if(trim($subject_sub_cat_2_term)!="") {
     $search_filters[] = t($subject_sub_cat_2_term);
  } 
  

  $country = arg(5);
  if(trim($country) != '0') {
     $search_filters[] = $country;
  } 
  
   $results = array();
   $xyz=geonames_countryinfo(arg(5));
   $country_goe_id = $xyz['geonameid'];
   $query = array('geonameid' => $country_goe_id);
   $results = geonames_query('children', $query);
	foreach ($results->results as $state) {
		if(arg(6) == $state['geonameid']) {
		  $search_filters[] = $state['name'];
		}
	}	  
	
   $results = array();
   $query = array('geonameid' => arg(6));
   $results = geonames_query('children', $query);
   $citycode = str_replace(arg(6),"",arg(7));
	foreach ($results->results as $city) {
		if($citycode == $city['geonameid']) {
		  $search_filters[] = $city['name'];
		}
	}
  
?>
<h2 class="dinbold page-title"><?php print '<label class="cat" style="padding:11px 0 0 11px;">'.implode(" / ",$search_filters).'</label>'; ?></h2>
<?php   /**********************/ ?>
<div class="grey-box search">
<div class="search">
            <br>
            <div class="form-item" id="edit-issue-key-wrapper">

                    <?php print drupal_render($form['issue_key']); ?>

                    <?php print drupal_render($form['search']); ?>
            </div>
            <div class="clear"></div>
            <div class="expanding">
                    <h6 class="search-options-expand"><?php print t('Filter Options'); ?></h6>
                    <ul>
                            <li>
                                    <div class="options">
                                            <label class="cat"><?php print t('CATEGORY:') ?></label>
                                            <?php print drupal_render($form['subject']); ?>
                                            <?php print drupal_render($form['sub_categories']); ?>
                                            <?php print drupal_render($form['sub_sub_categories']); ?>
                                    </div>
                                    <div class="clear"></div>
                                    <div class="options">
                                            <label class="cat"><?php print t('LOCATION:'); ?></label>
                                            <?php print drupal_render($form['country']); ?>
                                            <?php print drupal_render($form['state_div']); ?>
                                            <?php print drupal_render($form['city_div']); ?>
                                    </div>
                                    <div class="clear"></div>
                                    <?php print drupal_render($form['reset_btn']); ?><?php print drupal_render($form['submit']); ?>
                            </li>

                    </ul>

            </div>

    </div>
        <div class="clear"></div>
</div>