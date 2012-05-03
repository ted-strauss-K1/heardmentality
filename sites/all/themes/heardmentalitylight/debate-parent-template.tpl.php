<?php
global $user;
$loginBoxClass = $user->uid == 0 ? 'openlogin_box' : '';
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)) . '/';
$items['title'] = str_replace("\r\n", "<br>", $items['title']);
$items['title'] = str_replace("\n", "<br>", $items['title']);
?>
<div id="forum-block-<?php if (isset($items['debate_tnid']))
  { print $items['debate_tnid'];} else {print $items['resource_id']; $class = ' resources';} ?>" class="one-forum<?php print $class?>">
  <!--<?php if ($comments) { ?>
                              <h6 class="active">/ <?php print t('Argument'); ?></h6>
  <?php } ?>-->


  <ul class="argument_box<?php
  
  ?>">
    <li>

      <div class="arg">
        <?php
        $diff = $items['vote_up'] - $items['vote_down'];
        if ($diff <= 10 and $diff >= -10) {
          $vote_class = 'small';
        }
        else if ($diff <= -100 or $diff >= 100) {
          $vote_class = "large";
        }
        else {
          $vote_class = 'middle';
        }
        ?>
        <span class="sum <?php print $vote_class; ?>">
          <?php if ($diff > 0) { ?>
            <span class="positive"> <?php print $diff; ?></span>
          <?php }
          elseif ($diff < 0) { ?>
            <span class="negative"> <?php print $diff; ?></span>
          <?php }
          else { ?>
            <span class="null"> <?php print $diff; ?></span>
          <?php } ?> 
        </span>
        <div class="goog-trans-section argument_body">
          <?php if (isset($items['image'])) {

            ?>
            <span class="pic">
              <a target="_blank" title="reference" href="<?php print $items['nlink']; ?>" class="floatbox" data-fb-options="width:480 height:384">
                <img src="<?php print $items['image']; ?>" alt=""/> 
              
              <?php //print theme('imagecache', 'scale-width110', $items['image'],'','reference');?>
              
              </a></span> <?php } ?>
          <?php if (isset($items['resource_id'])) { ?>

              <div class="ref_wrap"><h5 class="ref_title"><a target="_blank" title="reference" href="
            <?php print $items['nlink']; ?>" class="floatbox" data-fb-options="width:480 height:384">
            <?php print t($items['title']); ?></a></h5>
                <span class="source">source: <a target="_blank" title="reference" href="<?php print $items['nlink']; ?>" class="floatbox" data-fb-options="width:480 height:384">
                    <?php print t($items['source']); ?> </a></span>
                <p><?php print t($items['body']); ?></p>
              </div>        
            <?php }
            else { ?>
              <p><?php print t($items['title']); ?></p>&nbsp;<div class="sq">[<div class="goog-trans-control translate"></div>]</div>
            <?php } ?>
        </div>

        <?php if (isset($items['debate_id'])) { ?>
          <div class="position">
            <?php print $strength; ?>
          </div>
        <?php } ?>
        <div class="userinfo-debate">
          <span class="date"><?php print t('posted '); ?><span><?php echo $items['ago']; ?></span></span>
          <a class="user-thumb" href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" ></a>
          <span class="name"><a href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><?php print $items['uname']; ?></a></span>
        </div>

      </div>

      <ul class="control_links">
        <li><a href="#" class="icon flag2" title="flag this argument">flag</a></li>
        <li>&nbsp;|&nbsp;<a href="#" class="flag2 permalink" title="permalink">link</a></li>
        <?php if ($delete): ?><li>&nbsp;|&nbsp;<?php print $delete; ?></li><?php endif; ?>
      </ul>

      <div class="replies">

        <?php if ($comments): drupal_add_js('misc/collapse.js');?>

          <fieldset class="collapsible collapsed reply_wrapper">

            <legend class="comment-meta">
  <?php print t('&#9658;'); ?><span><?php print $reply_count; ?><?php print t(' replies'); ?></span>
            </legend>
            <div class="fieldset-wrapper">
              <ul>
                <div id="all_replybox_<?php print $items['debate_tnid']; ?>">
                  <?php print $comments; ?>
                </div>
              </ul>
            </div>
          </fieldset> 

        <?php endif; ?>

      </div>

      <div class="position-question">
        <span class="line"><span>&nbsp;</span></span>
        <?php print $ratings; ?>

        <?php if ($reply_box): ?>
                                <!--<h6 value="Reply" id="reply" class="add-comment button light <?php print $loginBoxClass; ?>"><?php print t('Reply'); ?></h6>-->
          <ul class="argument_replybox">
            <div id="reply-msg-<?php print $items['debate_tnid']; ?>" class="suc-msg"></div>
            <div id="reply-comment" class="hidden"> 
              <?php print $reply_box; ?>
            </div>
          </ul>
        <?php endif; ?>
      </div>

    </li>
  </ul>
</div>

<div id="flag-arg-<?php print $items['debate_tnid']; ?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
  <input type="hidden" value="forum" id="flagtype" />
  <?php print t('Please Wait...'); ?>
</div>

<script type="text/javascript">
  $('#flag-arg-<?php print $items['debate_tnid']; ?>').dialog({
    autoOpen: false,
    modal: false,
    minWidth: 320,
    resizable:false
  });
</script>

