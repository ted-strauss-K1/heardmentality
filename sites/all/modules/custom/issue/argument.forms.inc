<?php

/**
 * Agrument Add Comment Form
 *
 * @param $form
 * @param $nid
 * @return array
 */
function reply_form($form, $nid)
{
  $form = array();

  if (!user_is_logged_in()) {
    $form['log_in'] = array(
      '#type' => 'markup',
      '#value' => t('Please login to post reply'),
      '#attributes' => array('class' => theme('user_login_modal_class', true)),
    );
    return $form;
  }

  $form['#attributes'] = array('class' => 'arg-reply-form');
  $form['#action'] = url('argument/create/comment', array('absolute' => true));
  $form['comment'] = array('#type' => 'textarea',
    '#size' => 70,
    '#cols' => 10,
    '#id' => 'comment_' . $nid,
    '#rows' => 3,
    '#attributes' => array('class' => 'textarea-input'),
    '#resizable' => FALSE,
  );
  $form['reply_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit reply'),
    '#prefix' => '<div align="right">',
    '#suffix' => '</div>' . theme('sub_loader', 'display:none; margin-bottom:-15px; float:left;'),
  );
  $form['content_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );
  $form['support'] = array(
    '#type' => 'hidden',
    '#value' => 1,
    '#name' => 'support',
  );

  return $form;
}