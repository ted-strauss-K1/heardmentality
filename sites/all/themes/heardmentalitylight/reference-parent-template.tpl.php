<?php
global $base_url;
    $image = !empty($items['image']) ? $items['image'] : file_directory_path() . '/noimage.jpg';
?>
<div id="forum-block-<?php print $items['resource_id'];?>">


<li>
    <a href="#" class="icon flag2" title="flag this argument"></a>
    <img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" >
    <span class="name"><a><?php print $items['uname']; ?></a></span>
        <?php
        if($items['rtype'] == 'news' || $items['rtype'] == 'facts'){
        ?>
            <p class="action-ref"><span class="name"><a href="<?php print t($items['title']); ?>" target="_blank"><?php print t($items['title']); ?></a></span>
            <span><?php print theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE); ?></span>
            <br><?php print t($items['body']); ?></p>
            
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
                <h6 value="Reply" id="reply" class="add-comment button light" onclick="resOpenReplyBox(<?php print $items['resource_id'];?>)"><?php print t('Reply'); ?></h6>
                 
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

