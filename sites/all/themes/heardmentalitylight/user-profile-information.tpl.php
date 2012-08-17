<?php
global $base_url, $base_path;
$directoryPath = $base_path . $directory;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
//echo '<pre>';print_r($badgeList);exit;
?>
            <div class="profile-meta profile_page_wrapper">
                    <!--<div class="icon profile text"></div>-->
                    <label for="profile" class="profile profile_page"><?php print $getuser->name; ?></label>
                    <div id="own_info">
						<img class="profile-meta" src="<?php print UserPicture_small_src($getuser->uid, 0); ?>" />
						<div class="medals">
								<div class="medal" ><span class="gold" id="medal1" title="Gold Medals">&nbsp;</span><?php print $badges['gold'];?></div>
								<div class="medal" ><span class="silver" id="medal2" title="Silver Medals">&nbsp;</span><?php print $badges['silver'];?></div>
								<div class="medal" ><span class="bronze" id="medal3" title="Bronze Medals">&nbsp;</span><?php print $badges['bronze'];?></div>
								<!--<div class="medal" ><span class="coins_char">&cent;</span><?php print $coins; ?></div>-->
						</div>
					</div>

				<div class="user_info">
                    <div class="section">
						<span class="right_wrapper">
							<span class="user-title"><?php print t('Member since');?>:</span>
							<span class="user-data"><?php print date("d-m-y",$getuser->created); ?></span>
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
							<span class="user-data"><?php print number_format($followers); ?></span>
						</span>

                    </div>
					<div class="section vcard">
						<?php if($settings['real_name']):?>
						<span class="user-data"><?php print $settings['real_name']; ?></span>

						<?php endif; ?>
						<?php if($settings['location']): ?>
						<span class="user-info"><?php print $getuser->profile_state; ?>, <?php print $getuser->profile_country; ?></span>

						<?php endif; ?>
						<?php if($settings['dob']):?>
						<span class="user-info"><?php print $settings['dob']; ?></span>

						<?php endif; ?>
						<?php if($settings['gender']):?>
						<span class="user-info"><?php print t($settings['gender']); ?></span>

						<?php endif; ?>
						<?php if($settings['sorient']):?>
						<span class="user-info"><?php print t($settings['sorient']); ?></span>

						<?php endif; ?>
						<?php if($settings['ethnic']):?>
						<span class="user-info"><?php print t($settings['ethnic']); ?></span>

						<?php endif; ?>
						<?php if($settings['edu']):?>
						<span class="user-info"><?php print t($settings['edu']); ?></span>
						<?php endif; ?>
                    </div>
				</div>

            </div>
            <div class="following">
                    <label for="following" class="following"><?php print t('Following'); ?></label>
                    <?php if($followingList):
                        foreach($followingList as $name => $image){
                        ?>
                    <a href="<?php print $sitelink.'profile/'.$name; ?>"><img class="following-user" src="<?php print $image; ?>" /></a>
                    <?php }?>

                    <a class="more" href="<?php print $sitelink.'user/following/'.$getuser->uid.'/following';?>"><?php print t('See All');?> (<?php print $following; ?>)</a>

                    <?php endif; ?>
            </div>
            <div class="following">
                    <label for="following" class="following"><?php print t('Following This User'); ?></label>
                    <?php if($followerList):
                        foreach($followerList as $name => $image){
                        ?>
                    <a href="<?php print $sitelink.'profile/'.$name; ?>"><img class="following-user" src="<?php print $image; ?>" /></a>
                    <?php }?>

                    <a class="more" href="<?php print $sitelink.'user/following/'.$getuser->uid.'/follower';?>"><?php print t('See All');?> (<?php print $followers; ?>)</a>

                    <?php endif; ?>
            </div>

            <ul class="badges profile">
                <label for="badges" class="badges"><?php print t('Badges'); ?></label>
                    <?php
                    if($badgeList):
                    foreach($badgeList as $badgeName=>$type){?>
                    <li><span class="badge <?php print $type;?>"></span><?php print $badgeName;?></li>
                    <?php }
                    endif;?>
            </ul>