<?php

/**
 * Form for adding arguments
 *
 * @param $form
 * @param $node
 * @return array
 */
function argument_form($form, $node)
{
  $form = array();

  $choices = $node->choices;
  drupal_add_js(array('argument_form' => array('count' => count($choices))), 'setting');
  drupal_add_js(drupal_get_path('module', 'argument') . "/argument.js");

  $form['#id'] = 'argument-add-form';

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['image'] = array(
    '#type' => 'hidden',
    '#value' => '',
    '#id' => 'image',
  );
  $form['type'] = array(
    '#type' => 'hidden',
    '#value' => 'argument',
    '#id' => 'argument_type',
  );

  $form['head'] = array(
    '#type' => 'markup',
    '#value' => '<table><tr><td class="first">',
  );
  $form['title'] = array(
    '#type' => 'textarea',
    '#size' => 70,
    '#cols' => 10,
    '#rows' => 3,
    '#resizable' => FALSE,
    '#id' => 'deb_title',
    '#prefix' => '<div class="argument-form"><label for="deb_title">' . t('What\'s your argument?') . '</label>',
    '#suffix' => '</div>',
  );
  $form['url'] = array(
    '#type' => 'textfield',
    '#default_value' => 'http://',
    '#size' => 60,
    '#maxlength' => 256,
    '#id' => 'url',
    '#prefix' => '
      <div class="reference-form">
        <label for="edit-ref-title">' . t('Post a reference') .
      '<span>(' . t('news, blog, gov, data') . '...).</span>
        </label>',
    '#suffix' => '
      </div>
      <span class="error-msg" id="deb-err"></span>',
  );
  $form['asgn_val'] = array(
    '#type' => 'markup',
    '#value' => '
      </td>
      <td class="argument-form">
        <div class="assign">
          <table>
            <th>
              <td style="width: 100%;"><span class="label">' . t('Assign values') . ':</span></td>
              <td><span class="small_neg">' . t('-') . '</span></td>
              <td><span class="small_pos">' . t('+') . '</span></td>
            </th>
          </table>
        </div>'
  );

  foreach ($choices as $i => $choice) {
    $form['option_' . $i] = array(
      '#type' => 'select',
      '#options' => array('-1' => '-', '0' => '-/+', '1' => '+'),
      '#attributes' => array('class' => 'select-value'),
      '#id' => 'sup_' . $i,
      '#default_value' => 0,
      '#prefix' => '
        <div class="value-select">
          <table>
            <tr>
              <td class="first">
                <label class="value floatleft">' . $choice['chtext_short'] . '</label>
              </td>
              <td>',
      '#suffix' => '
              </td>
            </tr>
          </table>
        </div>',
    );
    $form['chorder_' . $i] = array(
      '#type' => 'hidden',
      '#value' => $choice['chid']
    );
  }
  $form['clr_div'] = array(
    '#type' => 'markup',
    '#value' => '<div class="clr"></div><span class="req_assign">(' . t('Required to set one or more') . ')</span>'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#attributes' => array('class' => 'orange-btn'),
    '#prefix' => '</td></tr></table><div class="add_button">',
    '#suffix' => theme('sub_loader', 'display:none; float:left; margin-right:17px; position:relative; top:2px;'),
    '#id' => 'add_argument',
  );

  $form['link-arg'] = array(
    '#type' => 'item',
    '#value' => l(t('Or post a reference') . '<br><span class="desc">('.t('News, Data, Video, etc.').')</span>', '', array('html' => TRUE)),
    '#prefix' => '<div class="argument-form">',
    '#suffix' => '</div>',
    '#id' => 'link_arg',
  );
  $form['link-ref'] = array(
    '#type' => 'item',
    '#value' => l(t('Or write an argument'), '#'),
    '#prefix' => '<div class="reference-form">',
    '#suffix' => '</div></div>',
    '#id' => 'link_ref',
  );
  $form['linkbox'] = array(
    '#type' => 'item',
    '#value' => '<div id ="linkbox"></div>',
  );

  return $form;
}

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