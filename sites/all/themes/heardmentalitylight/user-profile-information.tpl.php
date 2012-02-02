<?php
global $base_url, $base_path;
$directoryPath = $base_path . $directory;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
//echo '<pre>';print_r($badgeList);exit;
?>
<div class="icon profile text"></div>
            <div class="profile-meta">
                    <!--<div class="icon profile text"></div>-->
                    <label for="profile" class="profile"><?php print $getuser->name; ?></label>
                    <img class="profile-meta" src="<?php print UserPicture_small_src($getuser->uid, 0); ?>" />
                    <div class="medals">
                            <div class="medal" ><span class="gold" id="medal1" title="Gold Medals">&nbsp;</span><?php print $badges['gold'];?></div>
                            <div class="medal" ><span class="silver" id="medal2" title="Silver Medals">&nbsp;</span><?php print $badges['silver'];?></div>
                            <div class="medal" ><span class="bronze" id="medal3" title="Bronze Medals">&nbsp;</span><?php print $badges['bronze'];?></div>
                            <div class="medal" ><img src="<?php print $directoryPath; ?>/images/icons/coin.png" class="coin2 floatleft" title="Coins"></span><?php print $coins; ?></div>
                    </div>

                    <div class="clear"></div>
                    <hr class="dark">
                    <span class="user-title"><?php print t('Member since');?>:</span>
                    <span class="user-data"><?php print date("d-m-y",$getuser->created); ?></span>
                    <br>
                    <span class="user-title"><?php print t('Votes');?>:</span>
                    <span class="user-data"><?php print number_format($votes); ?></span>
                    <br>
                    <span class="user-title"><?php print t('Comments');?>: </span>
                    <span class="user-data"><?php print number_format($comments); ?></span>
                    <br>
                    <span class="user-title"><?php print t('References');?>: </span>
                    <span class="user-data"><?php print number_format($references); ?></span>
                    <br>
                    <span class="user-title"><?php print t('Followers');?>: </span>
                    <span class="user-data"><?php print number_format($followers); ?></span>
                    <br>
                    <hr class="dark">
                    <?php if($settings['real_name']):?>
                    <span class="user-data"><?php print $settings['real_name']; ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['location']): ?>
                    <span class="user-info"><?php print $getuser->profile_state; ?>, <?php print $getuser->profile_country; ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['dob']):?>
                    <span class="user-info"><?php print $settings['dob']; ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['gender']):?>
                    <span class="user-info"><?php print t($settings['gender']); ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['sorient']):?>
                    <span class="user-info"><?php print t($settings['sorient']); ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['ethnic']):?>
                    <span class="user-info"><?php print t($settings['ethnic']); ?></span>
                    <br>
                    <?php endif; ?>
                    <?php if($settings['edu']):?>
                    <span class="user-info"><?php print t($settings['edu']); ?></span>
                    <?php endif; ?>
                    <hr class="dark">

            </div>
            <div class="following">
                    <label for="following" class="following"><?php print t('Following'); ?></label>
                    <?php if($followingList):
                        foreach($followingList as $name => $image){
                        ?>
                    <a href="<?php print $sitelink.'profile/'.$name; ?>"><img class="following-user" src="<?php print $image; ?>" /></a>
                    <?php }?>
                    <br class="clear">
                    <a class="more" href="<?php print $sitelink.'user/following/'.$getuser->uid.'/following';?>"><?php print t('See All');?> (<?php print $following; ?>)</a>
                    <br class="clear">
                    <?php endif; ?>
                    <hr class="dark">
            </div>
            <div class="following">
                    <label for="following" class="following"><?php print t('Following This User'); ?></label>
                    <?php if($followerList):
                        foreach($followerList as $name => $image){
                        ?>
                    <a href="<?php print $sitelink.'profile/'.$name; ?>"><img class="following-user" src="<?php print $image; ?>" /></a>
                    <?php }?>
                    <br class="clear">
                    <a class="more" href="<?php print $sitelink.'user/following/'.$getuser->uid.'/follower';?>"><?php print t('See All');?> (<?php print $followers; ?>)</a>
                    <br class="clear">
                    <?php endif; ?>
                    <hr class="dark">
            </div>

            <ul class="badges">
                <label for="badges" class="badges"><?php print t('BADGES'); ?></label>
                    <?php
                    if($badgeList):
                    foreach($badgeList as $badgeName=>$type){?>
                    <li><span class="badge <?php print $type;?>"></span><?php print $badgeName;?></li>
                    <?php }
                    endif;?>
            </ul>
            <br class="clear">