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

  $final_category = "";
  
  $subject = arg(2);
  $subject_term = taxonomy_get_term($subject)->name;
  if(trim($subject_term)!="") {
     $final_category = $subject_term;
  } 
  
  $subject_sub_cat_1 = arg(3);
  $subject_sub_cat_1_term = taxonomy_get_term($subject_sub_cat_1)->name;
  if(trim($subject_sub_cat_1_term)!="") {
     $final_category .= '&nbsp;/&nbsp;'.$subject_sub_cat_1_term;
  } 
  
  $subject_sub_cat_2 = arg(4);
  $subject_sub_cat_2_term = taxonomy_get_term($subject_sub_cat_2)->name;
  if(trim($subject_sub_cat_2_term)!="") {
     $final_category .=  '&nbsp;/&nbsp;'.$subject_sub_cat_2_term;
  } 
  
  if(trim($final_category)!="") {
    print '<label class="cat">CATEGORY : '.$final_category.'</label>';
  }
  
?>
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