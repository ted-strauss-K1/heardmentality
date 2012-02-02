<?php
//echo '<pre>'; print_r($form); exit;
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);

// get hidden values
print drupal_render($form['nid']);
?>
<div class="sugg-hide">
      <p class="suggest-answer"><strong><?php print t('Suggested answers'); ?>:</strong><br>
    <?php print t('The following answers have been suggested by other users.You can vote for one of the suggested answers, or contribute a new answer sug- gestion of your own. When the votes on a suggested answer reach [still working out requirements], that vote joins the list of official answers and will be counted in the results.'); ?>
      </p>
            <div class="suggest">
                <?php if($form['suggested_answer']):?>
                        <div class="choices">
                        <?php print drupal_render($form['suggested_answer']);?>
                        </div>
                <?php endif; ?>

                <?php print drupal_render($form['submit_suggest_vote']);?>
                <div class="clear"></div>
                <?php if($form['submit_suggest_answer']):
                        print drupal_render($form['submit_suggest_answer']);
                        print drupal_render($form['new_suggest_answer']);
                ?>
                        <br class="clear">
                        <p class="small"><em>(<?php print t('Answers must not exceed 140 carachters in length'); ?>)</em></p>
                <?php endif; ?>
                <?php if($form['vote_error']):
                      print drupal_render($form['vote_error']);
                      endif;
                ?>
                <?php if($form['login_error']):
                      print drupal_render($form['login_error']);
                      endif;
                ?>
            </div>
            <br class="clear">
</div>