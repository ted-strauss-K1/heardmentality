<?php
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
$foll = user_load($followid);

?>
<?php if($follow_status['action']!=''){ ?>
        <div id="<?php print $follow_status['uid']; ?>-<?php print $follow_status['target']; ?>">
        <a class="button light" onclick="follow_unfollow('<?php print $follow_status['uid']; ?>','<?php print $follow_status['target']; ?>', '<?php print $follow_status['action']; ?>')" href="javascript:void(0);"><?php print $follow_status['status']; ?></a>
        </div>
<?php }?>
        <a href="<?php print $sitelink.'profile/'.$foll->name; ?>"><img class="following-user-2" src="<?php print UserPicture_small_src($followid); ?>" alt="" /></a>
        <h2 class="din"><span class=""><a href="<?php print $sitelink.'profile/'.$foll->name; ?>"><?php print $foll->name; ?></a></span></h2>
        <p><?php print $ranking!=''?$ranking:'&nbsp;'; ?></p>
        <hr class="short">

        
        