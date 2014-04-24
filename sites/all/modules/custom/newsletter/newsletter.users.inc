<?php

/**
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function newsletter_form_alter(&$form, &$form_state, $form_id) {
  if ('user_profile_edit_form' == $form_id) {
    global $user;

    # subscription info
    $form['subscription_notify'] = array(
      '#type'          => 'radios',
      '#default_value' => newsletter_frequency_get($user->mail),
      '#options'       => array(
        NEWSLETTER_NEVER   => '',
        NEWSLETTER_MONTHLY => '',
        NEWSLETTER_WEEKLY  => ''
      ),
    );
    //    $form['subscription_email'] = array(
    //      '#type'          => 'textfield',
    //      '#title'         => t(''),
    //      '#maxlength'     => 50,
    //      '#default_value' => $user->subscription_email ? $user->subscription_email : $user->mail,
    //      '#id'            => 'subscription_email',
    //      '#required'      => TRUE,
    //    );
    $form['subscription_submit'] = array(
      '#type'       => 'submit',
      '#value'      => __('Submit', array('@code' => 'newsletter-subscribe-button')),
      '#id'         => 'subscription_submit',
      '#name'       => 'subscription_submit',
      '#attributes' => array('class' => 'submit-issue leftfloat'),
    );

    $form['#submit'][] = 'newsletter_frequency_submit';
  }
}

/**
 * Common Validation of the form
 *
 * @param $form
 * @param $form_state
 */
function newsletter_frequency_submit(&$form, &$form_state) {
  $id = $form_state["clicked_button"]["#name"];

  switch ($id) {
    case 'subscription_submit' :
      global $user;
      $post = $form_state["clicked_button"]["#post"];
      newsletter_frequency_set($user->mail, $post['subscription_notify']);
      break;
  }
}


/**
 *
 */
function newsletter_init() {
  if (isset($_REQUEST['newsletter_action']) && user_is_anonymous()) {
    drupal_set_message(__('Log in to unsubscribe', array('@code' => 'newsletter-subscribe-signin')));
  }
}
