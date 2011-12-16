<?php
global $user, $base_url;
$directoryPath = $base_path . $directory;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<style type="text/css">
    .profile-complete .progress {
                background: none repeat scroll 0 0 #99F279;
                height: 7px;
                width: <?php print $complete_percent['percent']; ?>%;
            }
</style>
<div id="dialog" title="<?php print $name; ?>" class="dialog">

		<label for="profile" class="profile"></label>
		<a href="<?php print $sitelink.'profile'?>" title="<?php print t('View Profile');?>"><img class="user-profile" src="<?php print $user_picture;?>" /></a>
		<div class="floatleft small-prog">
		  <div class="profile-meta quick-profile">
                      <div class="profile-meta quick-profile">
			  <p><?php print t('Your profile is !complete% Complete', array('!complete' => $complete_percent['percent']))?></p>
			  <div class="profile-complete">
				  <div class="progress"></div>
			  </div>
                          <?php if($complete_percent['percent']<100){?>
			  <p> <?php print t('Filling out <em>!empty-field</em> will bring your profile to !complete% Complete', array('!empty-field' => $complete_percent['nextfield'], '!complete' => $complete_percent['nextpercent'])); ?> <a class="blue" href="<?php print $front_page.'account/edit';?>"><?php print t('Add it here.'); ?></a></p>
                          <?php }?>
			</div> 
                  </div>
		</div>
		<br class="clear"><br>
		<p class="profile-links quick-profile">
                    <a href="<?php print $sitelink?>profile"><?php print t('View Profile');?></a> |
                    <a href="<?php print $sitelink?>account/edit"><?php print t('Edit Profile');?></a> |
                    <a href="<?php print $sitelink?>message"><?php print t('Message followers');?></a>
                </p>

		<div class="floatleft">
			<?php print $medal_list; ?>
		</div>
                <a href="<?php print $base_url.'/logout';?>" title="<?php print t('Log out');?>" class="button lighter" ><?php print t('Logout'); ?></a>
        </div>
