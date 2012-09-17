<?php print theme('follower_button', $user); ?>
<h2 class="din"><?php print $user->name; ?></h2>

<div class="user-info">
  <p><?php print t($rank); ?></p>

  <?php if (module_exists('profile_privacy')) : ?>

    <?php $fields = profile_privacy_get_fields(); ?>
    <?php foreach ($fields as $field) : ?>
      <?php if (!empty($user->{$field->name}) && profile_privacy_get_field_access($user, $field)) : ?>
        <span class="URL block">
          <strong><?php print t($field->title); ?>:</strong>
          <?php switch ($field->name) :
            case 'profile_twitter' : ?>
              <a href="https://twitter.com/<?php print htmlspecialchars($user->{$field->name}); ?>" target="_blank"><?php print $user->{$field->name}; ?></a>
            <?php break;
            case 'profile_facebook': ?>
              <a href="http://www.facebook.com/<?php print htmlspecialchars($user->{$field->name}); ?>" target="_blank"><?php print $user->{$field->name}; ?></a>
            <?php break;
            case 'profile_website': ?>
              <a href="<?php print htmlspecialchars($user->{$field->name}); ?>" target="_blank"><?php print $user->{$field->name}; ?></a>
            <?php break;

            default : ?>
              <?php print $user->{$field->name}; ?>
            <?php break; ?>
          <?php endswitch; ?>
        </span>
      <?php endif; ?>
    <?php endforeach; ?>
  <?php endif; ?>
  <?php #var_dump($user); ?>
</div>

