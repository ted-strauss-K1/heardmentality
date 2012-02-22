<?php
global $base_url;
    $image = !empty($items['image']) ? $items['image'] : file_directory_path() . '/noimage.jpg';
    $loginBoxClass = $user->uid==0?'openlogin_box':'';
    $path = '<front>';
	$sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<div id="forum-block-<?php print $items['resource_id'];?>">


<li>
    <a href="#" class="icon flag2" title="flag this argument"></a>
    <a href="<?php print $sitelink.'profile/'.$items['uname']; ?>"><img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" ></a>
    <span class="name"><a href="<?php print $sitelink.'profile/'.$items['uname']; ?>"><?php print $items['uname']; ?></a></span>
        <?php
        if($items['rtype'] == 'news' || $items['rtype'] == 'facts'){

        $refTit = str_replace('http://', '', $items['title']);
        $refBody = str_replace($refTit, '<span title="'.$items['title'].'">'.$refTit.'</span>', $items['body']);
        ?>
            <p class="action-ref">
<!--                <span class="name">
                    <a href="<?php //print t($items['title']); ?>" target="_blank"><?php //print t($items['title']); ?></a>
                </span>-->
            <span><?php print theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE); ?></span>
            <br><?php print $refBody; ?></p>
            
        <?php
            
        }elseif($items['rtype'] == 'multimedia' && $items['filepath']==''){?>
            <div class="comm-text">
            <a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/<?php print $items['video_id']; ?>" class="floatbox" data-fb-options="width:480 height:384">
            <span><img width="125" height="100" src="http://img.youtube.com/vi/<?php print $items['video_id']; ?>/default.jpg" alt="Video " ></span></a>
            <a target="_blank" href="<?php print $items['nlink']; ?> "><?php print $items['nlink']; ?></a>
            </div>
            
        <?php 
        }elseif($items['filepath']!=''){
            $url = explode('/', $items['filepath']);
            ?>
            <div class="comm-text"><a href="<?php print $base_url.'/' . $items['filepath'] ?>" target="_blank" ><?php print $url[2]; ?> </a></div>
            
            
       <?php } ?>
    <br class="clear">
    <br />
          <div class="position">
            <?php print $strength; ?>
          </div>
        <div class="position-question">
	<?php print $ratings; ?>
    	</div>
       <br class="clear">
        <?php if($delete):
              print $delete;
              endif;
          ?>
      <div class="expanding">
               <?php if($reply_box): ?>
                <h6 value="Reply" id="reply" class="add-comment button light <?php print $loginBoxClass;?>" onclick="resOpenReplyBox(<?php print $items['resource_id'];?>)"><?php print t('Reply'); ?></h6>
                 
                   <ul>
                      <li>
                        <br class="clear">
                        <br />
                        
                            <div id="reply-msg-<?php print $items['resource_id'];?>" class="suc-msg"></div>
                            <div class="leave-a-comment" id="reply-box-<?php print $items['resource_id'];?>" style="display: none;">
                            <?php print $reply_box; ?>
                            </div>
                        
                    </li>
                  </ul>
                <?php endif; ?>
                <hr>
      <?php if($comments): ?>

      <h6 class="active" onclick="resOpenReplies(<?php print $items['resource_id'];?>)">/ <?php print $reply_count; ?> <?php print t('REPLIES'); ?></h6>
      <ul><div class="top-arrow"></div>
          <div id="all_replybox_<?php print $items['resource_id'];?>" class="res-reply">
          <?php print $comments; ?>
          </div>
      </ul>
      <?php endif; ?>
    </div>
</li>

</div>
<div id="flag-arg-<?php print $items['resource_id'];?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
    <input type="hidden" value="forum" id="flagtype" />
    <?php print t('Please Wait...'); ?>
</div>
<script type="text/javascript">
    $('#flag-arg-<?php print $items['resource_id'];?>').dialog({
		autoOpen: false,
		modal: false,
		minWidth: 320,
		resizable:false
	});
</script>

