<?php if (
  !$denied &&
  $complete['percent'] < 100 &&
  (!isset($_SESSION['hide_profile_box']) || $_COOKIE['profile_status'] == 0)
) : ?>
<div class="message right-message profile-status-toggle">
  <a href="#" id="button" class="hide-message2 ui-dialog-titlebar-close profile-close-icon">
    <span class="ui-icon ui-icon-closethick">close</span>
  </a>

  <p class="profile-status">
    <strong>
      <?php print t('Your profile is !complete% Complete', array('!complete' => $complete['percent']))?>
    </strong>
  </p>

  <div class="profile-complete">
    <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
  </div>
  <p>
    <?php print t('Filling in your <em>!empty-field</em> will bring you to !complete% Complete', array('!empty-field' => $complete['nextfield'], '!complete' => $complete['nextpercent'])); ?>
    <a class="bolded" href="/user/profile/edit/#<?php print $complete['nextname'] ?>-wrapper">
      <?php print t('Add it here.'); ?>
    </a>
  </p>
</div>
<?php endif; ?>