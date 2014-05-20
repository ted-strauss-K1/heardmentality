<?php if (!$denied) : ?>
  <div class="dark-grey-box top clearfix">
    <div class="profile-meta profile_page_wrapper">
      <i class="icon cat text icon-businesscardalt"></i> <label for="profile"
                                                                class="white_text with_icon"><?php print $account->name; ?></label>

      <div id="own_info">
        <img class="profile-meta" src="<?php print user_profile_image($account) ?>"/>

        <div class="medals">
          <?php if (isset($badges['#stat'])) : ?>
            <?php foreach ($badges['#stat'] as $type => $badge) : ?>
              <span class="medal_box"><span class="medal1 <?php print $type ?>"
                                            title="<?php print t(ucfirst($type) . ' Medals'); ?>">&nbsp;</span><?php print $badge; ?>
          </span>
            <?php endforeach; ?>
          <?php endif; ?>
        </div>
      </div>

      <div class="user_info">
        <div class="section">
        <span class="right_wrapper">
          <span class="user-title"><?php print t('Member since'); ?>:</span>
          <span class="user-data"><?php print date("d-m-y", $account->created); ?></span>
        </span>

        <span class="right_wrapper">
          <span class="user-title"><?php print t('Votes'); ?>:</span>
          <span class="user-data"><?php print number_format($votes); ?></span>
        </span>

        <span class="right_wrapper">
          <span class="user-title"><?php print t('Comments'); ?>: </span>
          <span class="user-data"><?php print number_format($comments); ?></span>
        </span>

        <span class="right_wrapper">
          <span class="user-title"><?php print t('References'); ?>: </span>
          <span class="user-data"><?php print number_format($references); ?></span>
        </span>
        </div>
      </div>

    </div>

    <?php if (!empty($following)) : ?>
      <div class="following clearfix">
        <label for="following" class="following"><?php print user_profile_follow_title('following'); ?></label>
        <?php foreach ($following as $f_user) : ?>
          <?php print l('<img class="following-user"                                                                              src="' . user_profile_image($f_user->requestee) . '" />', 'user/profile/view/' . $f_user->requestee->name, array(
            'attributes' => array('class' => 'floatleft'),
            'html'       => TRUE,
          ));?>
        <?php endforeach; ?>
        <?php print l(t('See all') . ' (' . $following_count . ')', 'user/profile/follow/' . $account->uid . '/following', array('attributes' => array('class' => 'more'))); ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($followers)) : ?>
      <div class="following clearfix">
        <label for="following" class="following"><?php print user_profile_follow_title('followers'); ?></label>
        <?php foreach ($followers as $f_user) : ?>
          <?php print l('<img class="following-user"                                                                              src="' . user_profile_image($f_user->requester) . '" />', 'user/profile/view/' . $f_user->requester->name, array(
            'attributes' => array('class' => 'floatleft'),
            'html'       => TRUE,
          ));?>
        <?php endforeach; ?>
        <?php print l(t('See all') . ' (' . $followers_count . ')', 'user/profile/follow/' . $account->uid . '/followers', array('attributes' => array('class' => 'more'))); ?>
      </div>
    <?php endif; ?>

    <?php if ($badges['#list']) : ?>
      <ul class="badges profile clearfix">
        <label for="badges" class="badges"><?php print t('Badges'); ?></label>
        <?php foreach ($badges['#list'] as $name => $info) : ?>
          <li>
            <span class="badge <?php print $info['type']; ?>"></span>
            <?php print $info['name']; ?> x <?php print $info['#count']; ?>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>

  </div>
<?php endif; ?>
