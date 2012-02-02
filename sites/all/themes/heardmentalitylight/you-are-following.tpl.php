<?php global $user; ?>
<div class="dark-grey-box ">
        <div class="following">
                <label for="following" class="following"><?php print t('You\'re Following'); ?></label>
                <?php
                if($requestcount>0){
                foreach ($relationships as $rtid => $relationship) {?>

                <a href="<?php print $front_page.'profile/'.$relationship->requestee->name; ?>"><img class="following-user" src="<?php print UserPicture_small_src($relationship->requestee_id); ?>" alt="<?php print $relationship->requestee->name; ?>" /></a>
                <?php }?>
                 <br class="clear">
                 <a class="more" href="<?php print $front_page.'user/following/'.$user->uid.'/following'; ?>">(<?php print $requestcount; ?>) <?php print t('See All'); ?></a>
                <?php }else{
                    print t('You\'re not following anyone from the Heard yet.
You can follow users by clicking the \'Follow\' button
on their profile pages.');
                }?>
                <br class="clear">
                <hr class="dark">

        </div>
        <br class="clear">
</div>