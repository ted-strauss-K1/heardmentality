<?php

/*
 * Theme arguments_tabs
 */
function theme_arguments_tabs($nodes) {
  $output = '';
  foreach ($nodes as $node) {
    $output .= theme('arguments_item', $node);
  }
  if (empty($output)) {
    $output = '<div class="messages warning">' . t('No arguments posted yet') . '</div>';
  }
  return $output;
}

/*
 * Theme argument
 *
function theme_argument($node) {
  return '<br>'.$node->nid . ' => ' . time();
}
*/

/*
 * Vote Result Ball
 */
function theme_arguments_result_ball($count) {
  $value = abs($count);
  if ($value >= 100) {
    $class = 'large';
  } elseif ($value >= 10) {
    $class = 'middle';
  } else {
    $class = 'small';
  }
  $type = $count > 0 ? 'positive' : ( $count < 0 ? 'negative' : 'null');
  return sprintf('<span class="sum %s"><span class="%s">%d</span></span>', $class, $type, $count);
}

/*
 * Delete Button
 */
function theme_arguments_delete_button($node, $title = 'Are you sure to delete this argument?') {
  // TODO
  $type = 'forum';
  $id = 1;
  global $user;
  if (is_moderator() || $node->uid == $user->uid) {
    return l( t('Delete'), '#', array('attributes' => array(
      'class' => 'flag2 delete',
      'title' => t('Delete'),
      'name'  => ($name = 'own_'.($type=='reply'?'reply':'forum').'_'.$id.'_'.$type),
    )) ) .
      '<div id="dialog_'.$name.'" style="display:none" title="'.$title.'">
    <input type="button" value="Delete" onclick="delete_thread(\''.$name.'\')">
  </div>';
  }
}

/*
 * Theme arguments_delete
 */
function theme_arguments_delete($content_type, $content_id) {
  global $user;
  if (user_access('moderation', $user) || arguments_check_owner($content_type, $content_id)) {
    return l( t('Delete'), '#', array('attributes' => array(
      'class' => 'flag2 delete argument-delete',
      'title' => t('Delete'),
      'name'  => $content_type . '/' . $content_id,
    )) );
  }
}

/*
 * Rating button
 *
 * @param node - Node or Comment object
 */
function theme_arguments_rating_button($node) {
  $id = $node->content_id;
  $type = $node->content_type;
  $uid = $node->uid;
  $allow_rating = !$node->rated;
  global $user;
  $suffix = $type.'-'.$id;

  # classes and titles
  if( $uid == $user->uid) {
    $agreeTitle = 'You are not able to rate your own post!';
    $disagreeTitle = $agreeTitle;
    $agreeClass = 'agree button light';
    $disagreeClass = 'disagree button light';
  } elseif( $allow_rating == true ) {
    $prefix = 'd'; // $item['type'] != 'resource' ? 'd' : 'r';
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
    '<span class="comment-agree" type="'.$type.'" name="'.$id.'" id="lik-btns-'.$suffix .'">
      <strong>'.t('Do you agree').'<span class="doyou_app"> '.t('with the argument').'</span>' . t('?') . '</strong>
      <a href="javascript:void(0);" id="medal1" title="'.$agreeTitle.'" name="a-'.$id.'" class="'.$agreeClass.'">' .
    t('Yes').'  <span>('.$node->vote_up.')</span>
      </a>&nbsp;|
      <a href="javascript:void(0);" id="medal1" title="'.$disagreeTitle.'" name="da-'.$id.'" class="'.$disagreeClass.'">' .         t('No').' <span>('.$node->vote_dn.')</span>
      </a>
      <strong class="motivat">' . t('(Click yes/no to leave support/oppose comment.)') . '</strong>
    </span>';
}
