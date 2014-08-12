<?php

/**
 * Form for adding arguments
 *
 * @param $form
 * @param $node
 *
 * @return array
 */
function argument_form($form, $node) {
  $form = array();

  $choices = $node->choices;
  drupal_add_js(array('argument_form' => array('count' => count($choices))), 'setting');

  $form['#id'] = 'argument-add-form';

  $form['nid'] = array(
    '#type'  => 'hidden',
    '#value' => $node->nid,
  );
  $form['image'] = array(
    '#type'  => 'hidden',
    '#value' => '',
    '#id'    => 'image',
  );
  $form['type'] = array(
    '#type'  => 'hidden',
    '#value' => 'argument',
    '#id'    => 'argument_type',
  );

  $form['head'] = array(
    '#type'  => 'markup',
    '#value' => '<table><tr><td class="first">',
  );
  $form['title'] = array(
    '#type'      => 'textarea',
    '#size'      => 70,
    '#cols'      => 10,
    '#rows'      => 3,
    '#resizable' => FALSE,
    '#id'        => 'deb_title',
    '#prefix'    => '<div class="argument-form"><label for="deb_title">' . __('What\'s your argument?', array('@code' => 'argument-01')) . '</label>',
    '#suffix'    => '</div>',
  );
  $form['url'] = array(
    '#type'          => 'textfield',
    '#default_value' => 'http://',
    '#size'          => 60,
    '#maxlength'     => 256,
    '#id'            => 'url',
    '#attributes'    => array('class' => 'embedly'),
    '#prefix'        => '
      <div class="reference-form">
        <label for="edit-ref-title">' . __('Post a reference', array('@code' => 'argument-02')) . '<span>(' . __('news, blog, gov, data', array('@code' => 'argument-03')) . '...).</span>
        </label>',
    '#suffix'        => '
      </div>
      <span class="error-msg" id="deb-err"></span>',
  );
  $form['asgn_val'] = array(
    '#type'  => 'markup',
    '#value' => '
      </td>
      <td class="argument-form">
        <div class="assign">
          <table>
            <th>
              <td style="width: 100%;"><span class="label">' . __('Assign values', array('@code' => 'argument-04')) . ':</span></td>
              <td><span class="small_neg">-</span></td>
              <td><span class="small_pos">+</span></td>
            </th>
          </table>
        </div>'
  );

  foreach ($choices as $chid => $choice) {
    $form['option_' . $chid] = array(
      '#type'          => 'select',
      '#options'       => array('-1' => '-', '0' => '-/+', '1' => '+'),
      '#attributes'    => array('class' => 'select-value'),
      '#id'            => 'sup_' . $chid,
      '#default_value' => 0,
      '#prefix'        => '
        <div class="value-select">
          <table>
            <tr>
              <td class="first">
                <label class="value floatleft">' . $choice['chtext_short'] . '</label>
              </td>
              <td>',
      '#suffix'        => '
              </td>
            </tr>
          </table>
        </div>',
    );
    $form['chorder_' . $choice['index']] = array(
      '#type'  => 'hidden',
      '#value' => $choice['chid']
    );
  }
  $form['clr_div'] = array(
    '#type'  => 'markup',
    '#value' => '<div class="clr"></div><span class="req_assign">(' . __('Required to set one or more', array('@code' => 'argument-12')) . ')</span>'
  );

  $form['submit'] = array(
    '#type'       => 'submit',
    '#value'      => __('Add', array('@code' => 'argument-05')),
    '#attributes' => array('class' => 'orange-btn'),
    '#prefix'     => '</td></tr></table><div class="add_button">',
    '#suffix'     => theme('sub_loader', 'display:none; float:left; margin-right:17px; position:relative; top:2px;'),
    '#id'         => 'add_argument',
  );

  global $user;
  $allow_resources = ranks_permission(0, $user->uid); // todo has sufficient permissions
  $form['link-arg'] = array(
    '#type'   => 'item',
    '#value'  => $allow_resources ? (l(__('Or post a reference', array('@code' => 'argument-06')) . '<br><span class="desc">(' . __('News, Data, Video, etc.', array('@code' => 'argument-07')) . ')</span>', '', array('html' => TRUE,))) : ('<span class="desc">(' . __('You need to have higher rank to posts resources', array('@code' => 'argument-08')) . ')</span>'),
    '#prefix' => '<div class="argument-form">',
    '#suffix' => '</div>',
    '#id'     => 'link_arg',
  );
  $form['link-ref'] = array(
    '#type'   => 'item',
    '#value'  => l(__('Or write an argument', array('@code' => 'argument-09')), '#'),
    '#prefix' => '<div class="reference-form">',
    '#suffix' => '</div></div>',
    '#id'     => 'link_ref',
  );
  $form['linkbox'] = array(
    '#type'  => 'item',
    '#value' => '<div class="embedly-wrapper"></div><a href="#" class="close"></a>',
  );

  return $form;
}

/**
 * Agrument Add Comment Form
 *
 * @param $form
 * @param $nid
 *
 * @return array
 */
function reply_form($form, $nid) {
  $form = array();

  if (!user_is_logged_in()) {
    $form['log_in'] = array(
      '#type'       => 'markup',
      '#value'      => __('Please login to post reply', array('@code' => 'argument-10')),
      '#attributes' => array('class' => theme('user_login_modal_class', TRUE)),
    );
    return $form;
  }

  $form['#attributes'] = array('class' => 'arg-reply-form');
  $form['#action'] = url('argument/create/comment', array('absolute' => TRUE));
  $form['comment'] = array(
    '#type'       => 'textarea',
    '#size'       => 70,
    '#cols'       => 10,
    '#id'         => 'comment_' . $nid,
    '#rows'       => 3,
    '#attributes' => array('class' => 'textarea-input'),
    '#resizable'  => FALSE,
  );
  $form['reply_submit'] = array(
    '#type'   => 'submit',
    '#value'  => __('Submit reply', array('@code' => 'argument-11')),
    '#prefix' => '<div align="right">',
    '#suffix' => '</div>' . theme('sub_loader', 'display:none; margin-bottom:-15px; float:left;'),
  );
  $form['content_id'] = array(
    '#type'  => 'hidden',
    '#value' => $nid,
  );
  $form['support'] = array(
    '#type'  => 'hidden',
    '#value' => 1,
    '#name'  => 'support',
  );

  return $form;
}
