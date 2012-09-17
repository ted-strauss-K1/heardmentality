<?php if (!$denied) : ?>


<div class="profile-meta profile_page_wrapper">

  <label for="profile" class="profile profile_page"><?php print $user->name; ?></label>
  <div id="own_info">
    <img class="profile-meta" src="<?php print user_profile_image($user) ?>" />
    <div class="medals">
      <?php foreach ($badges['#stat'] as $type => $badge) : ?>
      <div class="medal" ><span class="<?php print $type ?>" id="medal1" title="<?php print ucfirst($type) ?> Medals">&nbsp;</span><?php print $badge;?></div>
      <?php endforeach; ?>
    </div>
  </div>

  <div class="user_info">
    <div class="section">
      <span class="right_wrapper">
        <span class="user-title"><?php print t('Member since');?>:</span>
        <span class="user-data"><?php print date("d-m-y",$user->created); ?></span>
      </span>

      <span class="right_wrapper">
        <span class="user-title"><?php print t('Votes');?>:</span>
        <span class="user-data"><?php print number_format($votes); ?></span>
      </span>

      <span class="right_wrapper">
        <span class="user-title"><?php print t('Comments');?>: </span>
        <span class="user-data"><?php print number_format($comments); ?></span>
      </span>

      <span class="right_wrapper">
        <span class="user-title"><?php print t('References');?>: </span>
        <span class="user-data"><?php print number_format($references); ?></span>
      </span>

      <span class="right_wrapper">
        <span class="user-title"><?php print t('Followers');?>: </span>
        <span class="user-data"><?php print number_format($follower_count); ?></span>
      </span>
    </div>
  </div>

</div>

<?php if (!empty($following)) : ?>
  <div class="following clearfix">
    <label for="following" class="following"><?php print t('Following'); ?></label>
    <?php foreach ($following as $f_user) : ?>
    <a href="/profile/<?php print $f_user->requestee->name; ?>" class="floatleft"><img class="following-user" src="<?php print user_profile_image($f_user->requestee); ?>" /></a>
    <?php endforeach; ?>
    <a class="more" href="/user/following/<?php print $user->uid ?>/following"><?php print t('See All');?> (<?php print $following_count; ?>)</a>
  </div>
  <?php endif; ?>

<?php if(!empty($followers)) : ?>
  <div class="following clearfix">
    <label for="following" class="following"><?php print t('Followers'); ?></label>
    <?php foreach($followers as $f_user) : ?>
    <a href="/profile/<?php print $f_user->requestee->name; ?>" class="floatleft"><img class="following-user" src="<?php print user_profile_image($f_user->requestee); ?>" /></a>
    <?php endforeach; ?>
    <a class="more" href="/user/following/<?php print $user->uid ?>/follower"><?php print t('See All');?> (<?php print $followers_count; ?>)</a>
  </div>
  <?php endif; ?>

<?php if($badges['#list']) : ?>
  <ul class="badges profile clearfix">
    <label for="badges" class="badges"><?php print t('Badges'); ?></label>
    <?php foreach ($badges['#list'] as $badge) : ?>
    <li>
      <span class="badge <?php print $badge['badgetype'];?>"></span>
      <?php print $badge['name'];?> x <?php print $badge['#count'];?>
    </li>
    <?php endforeach; ?>
  </ul>
  <?php endif;?>


<?php endif; ?>