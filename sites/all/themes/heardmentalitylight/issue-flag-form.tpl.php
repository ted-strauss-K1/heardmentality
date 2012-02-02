<?php
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);
//echo '<pre>';
//print_r($form); exit;
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

?>
<div id="flag-error"></div>
<?php print drupal_render($form['reason']); ?>
<br class="clear"/>
<div id="other-reason">
<?php print drupal_render($form['body']); ?>
</div>
<hr>
<?php print drupal_render($form['submit']); ?>


