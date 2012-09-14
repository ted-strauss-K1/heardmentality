<?php global $user; ?>
<div class="dark-grey-box top clearfix">
     <label for="following" class="profile profile_page" style="padding-bottom: 8px;"><?php print t('You\'re Following'); ?></label>
        <div class="following one clearfix">

                <?php if($requestcount>0){
                foreach ($relationships as $rtid => $relationship) {?>

                <a href="<?php print $front_page.'profile/'.$relationship->requestee->name; ?>" class="floatleft"><img class="following-user" src="<?php print UserPicture_small_src($relationship->requestee_id); ?>" alt="<?php print $relationship->requestee->name; ?>" /></a>
                <?php }?>

                 <a class="more" href="<?php print $front_page.'user/following/'.$user->uid.'/following'; ?>"><?php print t('See All'); ?> (<?php print $requestcount; ?>)</a>
                <?php }else{
                    print t('You\'re not following anyone from the Heard yet. You can follow users by clicking the \'Follow\' button on their profile pages.');
                }?>

        </div>
</div>
