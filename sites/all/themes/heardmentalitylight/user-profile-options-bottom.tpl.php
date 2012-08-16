<?php
global $user, $base_url;
$directoryPath = $base_path . $directory;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<div class="icon profile-i text"></div>
    <label for="profile" class="profile-dark dinbold"><?php print $name; ?>, <?php print t($ranking); ?></label>
    <p class="profile-links">
        <a href="<?php print $sitelink?>profile"><?php print t('View Profile');?></a> |
        <a href="<?php print $sitelink?>account/edit"><?php print t('Edit Profile');?></a>
    </p>
    <?php if($complete_percent['percent']<100){?>
    <div class="profile-meta">
            <div class="profile-meta footerfloat">
                    <p><?php print t('Your profile is !complete% Complete', array('!complete' => $complete_percent['percent']))?></p>
                    <div class="profile-complete">
                            <div class="progress" style="width: <?php print $complete_percent['percent']; ?>%;"></div>
                    </div>
            </div>
    </div>
    <?php }?>
    <div class="floatleft">
        <a href="<?php print $sitelink.'profile'?>" title="<?php print t('View Profile');?>"><img class="user-profile" src="<?php print $user_picture;?>"></a>
            <?php print $medal_list; ?>

    </div>
    <a type="submit" title="<?php print t('Log out');?>" href="<?php print $base_url.'/logout';?>" class="button darker floatright"><?php print t('Logout'); ?></a>