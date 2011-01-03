<?php
// $Id: heartbeat-message-row.tpl.php,v 1.1.2.11 2010/06/09 20:05:23 stalski Exp $

/**
 * @file
 *   Template file for one row, rendered by heartbeat
 *
 * @var
 * - $message : after it was parsed by heartbeat (grouped)
 * - $time_info : information about the time of activity
 * - $class : extra classes to use on the row
 * - $attachments : attachment on the message id (of the grouped message)
 *
 * @remarks
 *   beat-item-<uaid> is necessairy. The beat item id is used to toggle
 *   visibility of the "number more" messages when grouping exceeded the
 *   maximum allowed grouped property.
 */
//echo userPicture($message->uaid); 
?>
<!--
<div class="heartbeat-message-block <?php print $message->message_id . ' ' . $zebra; ?>">

  <div class="beat-item <?php print $message->classes ?>" id="beat-item-<?php print $message->uaid ?>">

    <?php print $message->content['message']; ?>
    <?php if (!empty($message->content['time_info'])): ?>
    <span class="heartbeat_times"><?php print $message->content['time_info']; ?></span>
    <?php endif; ?>

    <div class="clear"></div>

    <?php if (!empty($message->content['widgets'])) : ?>
    <div class="heartbeat-attachments">
      <?php print $message->content['widgets']; ?>
    </div>
    <?php endif; ?>

    <?php if (!empty($message->content['buttons'])) :?>
    <div class="heartbeat-buttons">
      <?php print $message->content['buttons']; ?>
    </div>
    <?php endif; ?>

    <br class="clearfix" />

  </div>
-->
             <div class="act-out">
              <div class="act-im" style="overflow:hidden;"><?php echo userPicture($message->uaid); ?></div>
               <div class="act-text"><span class="blue11"><?php print $message->content['message'] ?></span><br>
               <div class="comme"> 
              <ul>
              <li><?php print $message->content['time_info']; ?></li>
              <li><img height="11" width="12" src="images/act1.jpg"></li>
              <li class="commentic"><a href="#">2</a></li>
              <li><img height="14" width="12" src="images/act3.jpg"></li>
              <li> <?php if (!empty($message->content['widgets'])) : ?>    
					<?php print $message->content['widgets']; ?>    
					<?php endif; ?>
			</li>              
              </ul>
              </div> 
               <img height="6" width="33" src="images/comment-top.png">
               <div style="background-color: rgb(204, 204, 204);">
               <div style="padding: 3px;">
			    <?php if (!empty($message->content['buttons'])) :?>
				<?php print $message->content['buttons']; ?>
			       <?php endif; ?>
			   <br>
				<div class="com-wline"></div>
				<!--div class="comin"><div class="cominimg"><img height="28" align="absmiddle" width="32" src="images/img2.jpg"></div><div><strong>Mickey Mousecomment</strong> 1 day ago</div></div>
				<div class="clr"></div-->
				</div>
               </div>
				</div>
				</div>