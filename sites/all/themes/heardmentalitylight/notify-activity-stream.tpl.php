<?php
global $base_url;
 $url = drupal_get_path_alias('node/' . $data['qid']);
 $node = node_load($data['qid']);
 // root path
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';

 $username = '<span class="name">
        <a href="'.$sitelink.'profile/' .$udetails->name.'" title="'.t($udetails->name).'">'. $udetails->name.'</a>
    </span>'; 
?>
<li>
    <a href="<?php print $sitelink.'profile/'.$udetails->name; ?>"><img class="following-user listed" src="<?php print $userPicture;?>" alt="" /></a>

 <?php if($message_id == 'add_question'){?>
	<p class="action-item">
            <?php print $username; ?>
            <?php print t('added a new issue'); ?>: "
            <?php print l($data['q_title'].'?', $url); ?>"</p>
        <?php }else if($message_id == 'add_vote'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('voted on the issue'); ?>: "
            <?php print l($data['q_title'].'?', $url); ?>"</p>
        <p class="action-comment-ref"><?php print t($node->body); ?></p>
        <?php }else if($message_id == 'add_debate'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('posted an argument on the issue'); ?>: "
            <a href="<?php print $sitelink.$url.'#forum-block-'.$data['did'];?>"><?php print t($data['q_title']); ?>?</a>"</p>
        <p class="action-comment-ref"><?php print t($data['d_title']); ?></p>
        <?php }else if($message_id == 'add_resource'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('posted a reference on the issue'); ?>: "
            <a href="<?php print $sitelink.$url.'#forum-block-'.$data['rid'];?>"><?php print t($data['q_title']); ?>?</a>"</p>
        <p class="action-comment-ref">
            <?php
                $rtype = $data['rtype'];
                switch ($rtype) {
                 case '1':
                     $image = !empty($data['file']) ? $data['file'] : file_directory_path() . '/noimage.jpg';
                     print '<a href="'.$data['r_title'].'" target="_blank">'.theme('image', $image, t('Resources'), 'Resources', array('width' => '44px', 'height' => '44px', 'class' => 'following-user listed'), FALSE).'</a>';
                     break;
                 case '2':
                     print '<a href="'.$data['r_title'].'" target="_blank"><img class="following-user listed" width="125" height="100" src="http://img.youtube.com/vi/' . $data['videoid'] . '/default.jpg" alt="Video " /></a>';
                     break;
                }
            ?>
            <span class="name"><a href="<?php print t($data['r_title']); ?>" target="_blank"><?php print t($data['r_title']); ?></a></span>
            <?php print $data['description']; ?>
        </p>
        <?php }else if($message_id == 'resource_reply'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('Posted an argument on a reference on the issue'); ?>: "
            <?php print l($data['q_title'].'?', $url); ?>"</p>
             <p class="action-comment-ref">
                <?php
                $rtype = $data['rtype'];
                switch ($rtype) {
                 case '1':
                     $image = !empty($data['file']) ? $data['file'] : file_directory_path() . '/noimage.jpg';
                     print '<a href="'.$data['r_title'].'" target="_blank">'.theme('image', $image, t('Resources'), 'Resources', array('width' => '44px', 'height' => '44px', 'class' => 'following-user listed'), FALSE).'</a>';
                     break;
                 case '2':
                     print '<a href="'.$data['r_title'].'" target="_blank"><img class="following-user listed" width="125" height="100" src="http://img.youtube.com/vi/' . $data['videoid'] . '/default.jpg" alt="Video " /></a>';
                     break;
                }
            ?>
                <span class="name"><a href="<?php print t($data['r_title']); ?>" target="_blank"><?php print t($data['r_title']); ?></a></span>
                <?php print $data['description']; ?>
            </p>
        <?php }else if($message_id == 'deb_agree'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('strengthened an argument on the issue'); ?>: "
            <a href="<?php print $sitelink.$url.'#forum-block-'.$data['did'];?>"><?php print t($data['q_title']); ?>?</a>"</p>
        <p class="action-comment-ref"><?php print t($data['d_title']); ?></p>
        <?php }else if($message_id == 'deb_disagree'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('weakened an argument on the issue'); ?>: " 
            <a href="<?php print $sitelink.$url.'#forum-block-'.$data['did'];?>"><?php print t($data['q_title']); ?>?</a>"</p>
        <p class="action-comment-ref"><?php print t($data['d_title']); ?></p>
        <?php }else if($message_id == 'resource_reply_agree' || $message_id == 'resource_reply_disagree'){
            $token = $message_id == 'resource_reply_agree'?'Strengthened':'Weakened';
            ?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t($token.' an argument on a reference on the issue'); ?>: "
            <?php print l($data['q_title'].'?', $url); ?>"</p>
             <p class="action-comment-ref">
                <?php
                $rtype = $data['rtype'];
                switch ($rtype) {
                 case '1':
                     $image = !empty($data['file']) ? $data['file'] : file_directory_path() . '/noimage.jpg';
                     print '<a href="'.$data['r_title'].'" target="_blank">'.theme('image', $image, t('Resources'), 'Resources', array('width' => '44px', 'height' => '44px', 'class' => 'following-user listed'), FALSE).'</a>';
                     break;
                 case '2':
                     print '<a href="'.$data['r_title'].'" target="_blank"><img class="following-user listed" width="125" height="100" src="http://img.youtube.com/vi/' . $data['videoid'] . '/default.jpg" alt="Video " /></a>';
                     break;
                }
            ?>
                <span class="name"><a href="<?php print t($data['r_title']); ?>" target="_blank"><?php print t($data['r_title']); ?></a></span>
                <?php print $data['description']; ?>
            </p>
        <?php }else if($message_id == 'add_badge'){?>
        <p class="action-item">
            <?php print $username; ?>
            <?php print t('Earned the badge'); ?>: "
            <?php print $data['badge']; ?>?"</p>
        <?php }else if($message_id == 'user_follow'){
                $target = user_load($data['target_id']);
            ?>

        <p class="action-item">
            <?php print $username; ?>
            
            </p>
            <span class="now-foll-txt"><?php print t('Now following'); ?>: </span>
            <div class="foll-user-area">

                <a href="<?php print $sitelink.'profile/'.$target->name; ?>"><?php print $target->name; ?><br /><img alt="<?php print $target->name; ?>" src="<?php print UserPicture_small_src($data['target_id']);?>" width="44" height="44" /></a>
            </div>

        <?php }?>
<br class="clr" />
<span class="submitted"><?php print $submitted; ?></span>
</li>
