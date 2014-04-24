<?php

// this file contains only theming functions

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_flag ($content_id, $content_type) {
  $text = 'user' == $content_type ? __('block user', array('@code' => 'flagger-flag-user')) : __('flag', array('@code' => 'flagger-flag'));

  if (flagger_permission($content_type)) {
    global $user;
    return ('user' == $content_type && $content_id == $user->id) ? '' : l($text, '', array(
      'attributes' => array(
        'class'          => 'flagger flagger-btn-flag-' . $content_type . '-' . $content_id,
        'name'           => $content_type . '/' . $content_id,
        'original-title' => $text,
      )
    ));
  } else {
    if ('user' == $content_type) {
      return '';
    } else {
      return l($text, '', array(
        'attributes' => array(
          'class' => theme('user_login_modal_class', TRUE),
        )
      ));
    }
  }
}

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_flags ($content_id, $content_type, $flagged = NULL, $uid = FALSE) {
  if (!flagger_permission('moderation')) {
    return '';
  }

  $text = __('flags', array('@code' => 'flagger-flags'));
  return l($text, '', array(
    'attributes' => array(
      'class'          => 'flagger_flags flagger-btn-flags-' . $content_type . '-' . $content_id . ((!is_null($flagged) && !$flagged) || !flagger_get_flags($content_type, $content_id) ? '' : ' flagged'),
      'name'           => $content_type . '/' . $content_id,
      'original-title' => $text,
    )
  ));
}

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_history ($content_id, $content_type, $text = false) {
  if (!flagger_permission('moderation')) {
    return '';
  }

  $text1 = __('history', array('@code' => 'flagger-history1'));
  $text2 = __('flags history', array('@code' => 'flagger-history2'));
  return l(false === $text ? $text1 : $text, '', array(
    'attributes' => array(
      'class'          => 'flagger_history flagger-btn-flags-history-' . $content_type . '-' . $content_id,
      'name'           => $content_type . '/' . $content_id,
      'original-title' => $text2,
    ),
    array('html' => true),
  ));
}
