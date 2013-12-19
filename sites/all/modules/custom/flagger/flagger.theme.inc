<?php

// this file contains only theming functions

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_flag($content_id, $content_type) {
  if (user_is_logged_in()) {
    return l(t('flag'), '', array(
      'attributes' => array(
        'class'          => 'flagger flagger-btn-flag-' . $content_type . '-' . $content_id,
        'name'           => $content_type . '/' . $content_id,
        'original-title' => t('flag'),
      )
    ));
  }
  else {
    return l(t('flag'), '', array(
      'attributes' => array(
        'class' => theme('user_login_modal_class', TRUE),
      )
    ));
  }
}

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_flags($content_id, $content_type, $flagged = NULL, $uid = FALSE) {
  if (!module_exists('moderation') || !moderation_check_perm($uid)) {
    return '';
  }

  return l(t('flags'), '', array(
    'attributes' => array(
      'class'          => 'flagger_flags flagger-btn-flags-' . $content_type . '-' . $content_id . ((!is_null($flagged) && !$flagged) || !flagger_get_flags($content_type, $content_id) ? '' : ' flagged'),
      'name'           => $content_type . '/' . $content_id,
      'original-title' => t('flags'),
    )
  ));
}

/**
 * @param $content_id
 * @param $content_type
 *
 * @return string
 */
function theme_flagger_btn_history($content_id, $content_type, $uid = FALSE) {
  if (!module_exists('moderation') || !moderation_check_perm($uid)) {
    return '';
  }

  return l(t('history'), '', array(
    'attributes' => array(
      'class'          => 'flagger_history flagger-btn-flags-history-' . $content_type . '-' . $content_id,
      'name'           => $content_type . '/' . $content_id,
      'original-title' => t('flags history'),
    )
  ));
}
