<?php
/*
 * This file contains all the functions related to theming
 */

/*
 * Delete debate/resource/comment link
 *
 * @id    - one of the debate_tnid, resource_id, comment_id
 * @type  - one of the 'debate', 'resource', 'reply'
 *
 * @requires javascript function delete_thread
 */
function theme_delete_button($id, $type, $title = 'Are you sure to delete this argument?') {
  if( !$id ) return;
  return l( t('Delete'), '#', array('attributes' => array(
    'class' => 'flag2 delete',
    'title' => t('Delete'),
    'name'  => ($name = 'own_'.($type=='reply'?'reply':'forum').'_'.$id.'_'.$type),
  )) ) .
  '<div id="dialog_'.$name.'" style="display:none" title="'.$title.'">
    <input type="button" value="Delete" onclick="delete_thread(\''.$name.'\')">
  </div>';
}

/*
 * Like/Dislike bar
 *
 * @pro    - agree count
 * @con    - disagree count
 */
function theme_like_dislike_bar($pro, $con) {
  $total = $pro + $con;
  $pro_perc = $total != 0 ? ($pro*100)/$total : 0;
  $con_perc = $total != 0 ? ($con*100)/$total : 0;
  return
    '<span id="like-percent-area" class="like-per" style="width:'.$pro_perc.'%;"></span>'.
    '<span id="dislike-percent-area" class="dislike-per" style="width:'.$con_perc.'%;"></span>';
}

/*
 * Rating button
 *
 * @item   - debate/resource/reply
 */
function theme_rating_button($item) {
  $text = $item['type'] == 'debate' ? t('Do you agree with the argument?') : t('Do you agree?');
  $id = $item['content_id'];
  $ntype = $item['type'] == 'reply' ? 'comment' : 'node';
  $like_dislike_bar = theme('like_dislike_bar', $item['vote_up'], $item['vote_down']);
  $suffix = $ntype.'-'.$id;

  # classes and titles
  global $user;
  if( $item['posted_by'] == $user->uid) {
    $agreeTitle = 'You are not able to rate your own post!';
    $disagreeTitle = $agreeTitle;
    $agreeClass = 'agree button light';
    $disagreeClass = 'disagree button light';
  } elseif( $item['allow_rating'] == true ) {
    $prefix = $item['type'] != 'resource' ? 'd' : 'r';
    $agCls = $prefix.'agree';
    $dagCls = $prefix.'disagree';
    $agreeClass = 'agree button light '.$agCls ;
    $disagreeClass = 'disagree button light '.$dagCls;
    $agreeTitle = 'Agree This!';
    $disagreeTitle = 'Disagree This!';
  } else {
    $agreeTitle = 'You have rated this!';
    $disagreeTitle = $agreeTitle;
    $agreeClass = 'agree button light';
    $disagreeClass = 'disagree button light';
  }

  return
    '<div id="likebar-'.$suffix.'" class="likebar">'.$like_dislike_bar.'</div>' .
    '<span class="comment-agree" type="'.$item['type'].'" name="'.$id.'" id="lik-btns-'.$suffix .'">
      <strong>'.t('Do you agree').'<span class="doyou_app"> '.t('with the argument').'</span>' . t('?') . '</strong>
      <a href="javascript:void(0);" id="medal1" title="'.$agreeTitle.'" name="a-'.$id.'" class="'.$agreeClass.'">' .
        t('Yes').'  <span>('.$item['vote_up'].')</span>
      </a>&nbsp;|
      <a href="javascript:void(0);" id="medal1" title="'.$disagreeTitle.'" name="da-'.$id.'" class="'.$disagreeClass.'">' .         t('No').' <span>('.$item['vote_down'].')</span>
      </a>
      <strong class="motivat">' . t('(Click yes/no to leave support/oppose comment.)') . '</strong>
    </span>';
}

/*
 * Forum replies list
 */
function theme_forum_replies($content_id, $pid = 0) {
  global $user;
  $output = '';
  $query = "
    SELECT *
    FROM {comments} AS c
    WHERE
      c.nid='%d' AND
      c.status='0' AND
      c.pid='%d' AND
      (c.cid = c.tcid OR c.tcid = 0)
    ORDER BY c.cid DESC";
  $result = db_query($query, $content_id, $pid);
  while( $row = db_fetch_array($result) ) {
    if( !empty($row['comment']) ) {
      $item = load_reply($row['cid']);
      $ratings = theme('rating_button', $item);
      if( is_moderator() || $item['uid'] == $user->uid ) {
        $delete = theme('delete_button', $item['content_id'], $item['type'], 'Are you sure you want to delete this argument?');
      }
      $userPicture = UserPicture_small_src($item['uid']);
      $output .= theme('forum_child_reply_template', $item, $userPicture, $ratings, $delete);
    }
  }
  return $output;
}

/*
 * Sub Loader Image
 */
function theme_sub_loader( $styles ) {
  global $base_url, $theme;
  return
    '<span id="sub_loader" style="'.$styles.'">
      <img src="'.$base_url.'/'.drupal_get_path('theme', $theme).'/images/loading_min.gif" alt="loading">
    </span>';
}