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