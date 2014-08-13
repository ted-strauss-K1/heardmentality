<?php
print theme('follower_button', $account);

global $user;
if ($user->uid == $account->uid) {
  print l(__('Edit Profile', array('@code' => 'user_profile-edit')), 'user/profile/edit', array(
    'attributes' => array(
      'class' => 'button light editlink',
    )
  ));
}
?>
<h2 class="din"><?php print $account->name; ?></h2>
<?php $rank = $user->rank; ?>
<div class="user-info">
  <p><?php print __($rank['name'], array('@code' => 'rank-' . $rank['index'], '@textgroup' => 'rank')); ?>
    <!-- points: <?php print points_count($account->uid); ?> --></p>
  <!-- pennies: <?php print pennies_count($account->uid); ?> --></p>

  <?php $fields = profile_privacy_get_fields(); ?>
  <?php foreach ($fields as $field) : ?>
    <?php if (!empty($account->{$field->name}) && profile_privacy_get_field_access($account, $field)) : ?>
      <span class="URL block">
          <strong><?php print __($field->title, array('@code' => 'user_profile-field-' . $field->name)); ?>:</strong>
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
