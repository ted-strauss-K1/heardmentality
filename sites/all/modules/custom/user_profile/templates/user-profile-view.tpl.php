<?php
print theme('follower_button', $account);

global $user;
if ($user->uid == $account->uid) {
  print l(t('Edit Profile'), 'user/profile/edit', array(
    'attributes' => array(
      'class' => 'button light editlink',
    )
  ));
}
?>
<h2 class="din"><?php print $account->name; ?></h2>

<div class="user-info">
  <p><?php print t($rank); ?></p>

  <?php $fields = profile_privacy_get_fields(); ?>
  <?php foreach ($fields as $field) : ?>
    <?php if (!empty($account->{$field->name}) && profile_privacy_get_field_access($account, $field)) : ?>
      <span class="URL block">
          <strong><?php print t($field->title); ?>:</strong>
        <?php switch ($field->name) :
          case 'profile_twitter' :
            ?>
            <a href="<?php print htmlspecialchars($account->{$field->name}); ?>"
               target="_blank"><?php print $account->{$field->name}; ?></a>
            <?php break;
          case 'profile_facebook':
            ?>
            <a href="<?php print htmlspecialchars($account->{$field->name}); ?>"
               target="_blank"><?php print $account->{$field->name}; ?></a>
            <?php break;
          case 'profile_website':
            ?>
            <a href="<?php print htmlspecialchars($account->{$field->name}); ?>"
               target="_blank"><?php print $account->{$field->name}; ?></a>
            <?php break;
          case 'profile_country':
            ?>
            <?php print location_country_name($account->{$field->name}); ?>
            <?php break;
          default :
            ?>
            <?php print $account->{$field->name}; ?>
            <?php break; ?>
            <?php endswitch; ?>
        </span>
    <?php endif; ?>
  <?php endforeach; ?>

</div>