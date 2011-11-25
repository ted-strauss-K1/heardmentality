<?php
$output = '<a href="' . $base_path . 'profile/' . t($udetails->name) . '" title="' . t($udetails->name) . '">' . UserPicture_small($result->uid) . t($udetails->name) . '</a>
    <div id="msg-' . $result->naid . '" class="notify-text">' . t($result->message)
            . '</div><div id="notify-link">' . l($data['q_title'], $url) . '</div>
    <div align="right">' . ago($submitted) . '</div><hr>';
global $base_url;
 $url = drupal_get_path_alias('node/' . $data['qid']);
 $node = node_load($data['qid']);
?>
<li>
<img class="following-user listed" src="<?php print $userPicture;?>" />
<p class="action-item">
    <span class="name">
        <a href="<?php print $base_url.'profile/' . t($udetails->name); ?>" title="<?php print t($udetails->name); ?>" id="medal1"><?php print t($udetails->name);?></a>
    </span><br>
 <?php if($message_id == 'add_question' || $message_id == 'add_debate' || $message_id == 'add_resource' || $message_id == 'deb_agree'
            || $message_id == 'deb_disagree' || $message_id == 'res_agree' || $message_id == 'res_disagree' || $message_id == 'suggest_answer'
         || $message_id == 'change_answer' || $message_id == 'deb_reply_agree' || $message_id == 'deb_reply_disagree' || $message_id == 'res_reply_agree'
         || $message_id == 'res_reply_disagree' || $message_id == 'debate_reply' || $message_id == 'resource_reply'){?>

 <?php print t($message).'&nbsp;'.t('on');?>:"
 <?php if($data['q_title']):
         print l($data['q_title'].'?', $url).'"<br class="clear">';
         if($message_id == 'add_resource'){
         $rtype = $data['rtype'];
         switch ($rtype) {
             case '1':
                 $image = !empty($data['file']) ? $data['file'] : file_directory_path() . '/noimage.jpg';
                 print '<p class="action-comment-ref">'.theme('image', $image, t('Resources'), 'Resources', array('width' => '70px', 'height' => '60px'), FALSE).$data['description'].'</p>';
                 break;
             case '2':
                 print '<p class="action-comment-ref"><img width="125" height="100" src="http://img.youtube.com/vi/' . $data['videoid'] . '/default.jpg" alt="Video " /></p>';
                 break;
         }
  ?>
    
   <?php      
   }
         endif;
   ?><?php       } else if($message_id == 'add_badge'){
    print t($message).'&nbsp;"'.t($data['badge']).'"';
}else if($message_id == 'update_profile'){
    print t($message);
}
 ?></p>
<?php if($node->body):?>
    <p class="action-comment-ref"><?php print $node->body; ?> <a href="<?php print $url; ?>" id="medal1" title="More">[...]</a></p>
<?php endif;?>
<br />
<span class="submitted"><?php print $submitted; ?></span>
</li>
