<?php

/*
 * New debate/resource form
 *
 * @param nid - Issue Node Id
 */
function arguments_form($form, $nid) {
  $form = array();

  $form['#id'] = 'argument-add-form';
  $form['nid'] = array(
    '#type'   => 'hidden',
    '#value'  => $nid,
  );
  $form['image'] = array(
    '#type'   => 'hidden',
    '#value'  => '',
    '#id'     => 'image',
  );
  $form['type'] = array(
    '#type'   => 'hidden',
    '#value'  => 1,
    '#id'     => 'argument_type',
  );
  $choices = issue_choices($nid);
  drupal_add_js(array('arguments_form' => array('count' => count($choices))), 'setting');

  $form['head'] = array(
    '#type'   => 'markup',
    '#value'  => '<table><tr><td class="first">',
  );
  $form['title'] = array('#type' => 'textarea',
    '#size'       => 70,
    '#cols'       => 10,
    '#rows'       => 3,
    '#resizable'  => false,
    '#id'         => 'deb_title',
    '#prefix'     => '<div class="argument-form"><label for="deb_title">What\'s your argument?</label>',
    '#suffix'     => '</div>',
  );
  $form['url'] = array(
    '#type'           => 'textfield',
    '#default_value'  => 'http://',
    '#size'           => 60,
    '#maxlength'      => 256,
    '#id'             => 'url',
    '#prefix'         => '
      <div class="reference-form">
        <label for="edit-ref-title">Post a reference
          <span>(news, blog, gov, data...).</span>
        </label>',
    '#suffix'         => '
      </div>
      <span class="error-msg" id="deb-err"></span>',
  );
  $form['asgn_val'] = array(
    '#type'   => 'markup',
    '#value'  => '
      </td>
      <td class="argument-form">
        <div class="assign">
          <table>
            <th>
              <td style="width: 100%;"><span class="label">' . t('Assign Values:') . '</span></td>
              <td><span class="small_neg">' . t('-') . '</span></td>
              <td><span class="small_pos">' . t('+') . '</span></td>
            </th>
          </table>
        </div>'
  );
  foreach ($choices as $i => $choice) {
    $form['option_' . $i] = array(
      '#type'           => 'select',
      '#options'        => array('-1' => '-', '0' => '-/+', '1' => '+'),
      '#attributes'     => array('class' => 'select-value'),
      '#id'             => 'sup_' . $i,
      '#default_value'  => 0,
      '#prefix'         => '
        <div class="value-select">
          <table>
            <tr>
              <td class="first">
                <label class="value floatleft">' . $choice['short_answer'] . '</label>
              </td>
              <td>',
      '#suffix' => '
              </td>
            </tr>
          </table>
        </div>',
    );
    $form['chorder_' . $i] = array(
      '#type'   => 'hidden',
      '#value'  => $choice['chorder']
    );
  }
  $form['clr_div'] = array(
    '#type'   => 'markup',
    '#value'  => '<div class="clr"></div><span class="req_assign">(Required to set one or more)</span>'
  );
  $form['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add'),
    '#attributes' => array('class' => 'orange-btn'),
    '#prefix'     => '</td></tr></table><div class="add_button">',
    '#suffix'     => theme('sub_loader', 'display:none; float:left; margin-right:17px; position:relative; top:2px;'),
    '#id'         => 'add_argument',
  );
  # TODO -- remove this button
  $form['attach'] = array(
    '#type'       => 'submit',
    '#value'      => t('Attach'),
    '#attributes' => array('class' => 'orange-btn'),
    '#prefix'     => '<div class="reference-form pic_ref">',
    '#suffix'     => '</div>',
    '#id'         => 'lattach',
  );
  $form['link-arg'] = array(
    '#type'       => 'item',
    '#value'      => l(t('Or post a reference'), '#') . t(' (news, blog, gov, data...)'),
    '#prefix'     => '<div class="argument-form">',
    '#suffix'     => '</div>',
    '#id'         => 'link_arg',
  );
  $form['link-ref'] = array(
    '#type'       => 'item',
    '#value'      => l(t('Or write an argument'), '#'),
    '#prefix'     => '<div class="reference-form">',
    '#suffix'     => '</div></div>',
    '#id'         => 'link_ref',
  );
  $form['linkbox'] = array(
    '#type'       => 'item',
    '#value'      => '<div id ="linkbox"></div>',
  );

  return $form;
}

/*
 * New debate/resource form
 *
 * Validation
 */
function arguments_form_validate(&$form, &$form_state) {
  // don't use this function cause it's ajax-submitted form
}

/*
 * New debate/resource form
 *
 * Submission
 */
function arguments_form_submit(&$form, &$form_state) {
  global $user;
  $post = $form_state['clicked_button']['#post'];
  switch ($post['type']) {
    case 1 : # Debate
      $node = arguments_add_debate($post['nid'], $post['title']);
      if ($node) {
        $choices = issue_choices($post['nid']);
        $choices_count = count($choices);
        $options = array();
        for ($i = 0; $i < $choices_count; $i++) {
          $options[] = array(
            'chorder' => $post['chorder_'.$i],
            'option' => $post['option_'.$i],
          );
          arguments_options($node->nid, $options);
        }
        drupal_json(array(
          'success' => true,
          'message' => '<span class="posted">Your argument posted successfully!</span>',
        ));
      } else {
        drupal_json(array(
          'success' => false,
          'message' => '<div class="messages error"><b>Error occurred. Please try again.</b></div>',
        ));
      }
      break;

    case 0 : # Resource
      if (!empty($post['url'])) {
        $node = arguments_add_resource($post['nid'], $post['url'], $post['image']);
        if ($node) {
          drupal_json(array(
            'success' => true,
            'message' => '<span class="posted">Your argument posted successfully!</span>',
            'node' => $node,
          ));
        } else {
          $url = parse_url($post['url']);
          if (false !== strpos($url['host'], 'youtube.com')) {
            drupal_json(array(
              'success' => false,
              'message' => '<div class="messages error"><b>YouTube video ID not found</b></div>',
            ));
          } else {
            drupal_json(array(
              'success' => false,
              'message' => '<div class="messages error"><b>Error occurred. Please check you URL</b></div>',
            ));
          }
        }

      } else {
        drupal_json(array(
          'success' => false,
          'message' => '<div class="messages error"><b>Please enter an URL</b></div>',
        ));
      }

      break;
  }
  exit;
}

/*
 * Agrument Add Comment Form
 *
 * @param nid - Argument Node Id
 */
function reply_form($form, $nid) {
  $form = array();

  if (!user_is_logged_in()) {
    $form['log_in'] = array(
      '#type' => 'markup',
      '#value' => t('Please login to post reply'),
      '#attributes' => array('class' => ugc_loginbox_class(true)),
    );
    return $form;
  }

  $form['#attributes'] = array('class' => 'arg-reply-form');
  $form['#action'] = url('arguments/comment', array('absolute' => true));
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
  $form['str_wk'] = array(
    '#type' => 'hidden',
    '#value' => 1,
    '#name' => 'str_wk',
  );

  return $form;
}

/*
 * Forum Reply Form submitter
 *
 * TODO find out how the coins' part works and fix it
 */

function reply_form_submit($form, &$form_state) {
  global $user;
  $json = array();
  # find out if user has enough points to leave a comment
  $coins = $user->total_coins;
  $coins_threshold = 0; # get_coins('p_debate');
  if ($coins < $coins_threshold) {
    $json['message'] = '<span>' . t('Sorry, you do not have enough coins to reply for this post') . '</span>';
  }
  else {
    # collect comment data
    $comment = check_plain($form_state['values']['reply_content']);
    $values = array(
      'nid' => $form_state['values']['content_id'],
      'uid' => $user->uid,
      'name' => $user->name,
      'language' => ugc_detect_language($comment),
      'subject' => $comment,
      'comment' => $comment,
      'status' => 0,
      'format' => '',
      'mail' => '',
      'homepage' => '',
      'str_wk' => $form_state['values']['str_wk'],
    );
    # save the comment
    $cid = comment_save($values);
    comment_update($cid, $values['str_wk'], $values['language']);
    # notify log
    /*
     * TODO -
     * find out if d_title, q_title are used somewhere else,
     * since they're related to both debates and resources
     * these names may be confusing for developers later
     */
    $vars = json_decode($form_state['values']['variables']);
    $issue_tnid = get_tnid($vars->issue_id);
    $issue_title = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $issue_tnid));
    $content_title = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $values['nid']));
    set_notify_log($user->uid, $values['nid'], 'reply', array(
      'did' => $values['nid'],
      'd_title' => $content_title,
      'uid' => $user->uid,
      'qid' => $issue_tnid,
      'q_title' => $issue_title,
    ));
    # output
    if (!$cid) {
      $json['message'] = '<span>' . t('Sorry, your reply not able to post') . '</span>';
    }
    else {
      $item = load_reply($cid);
      $ratings = theme('rating_button', $item);
      if (is_moderator() || $item['uid'] == $user->uid) {
        $delete = theme('delete_button', $item['cid'], 'reply', 'Are you sure you want to delete this argument?');
      }
      $userPicture = UserPicture_small_src($item['uid']);
      $json['content'] = theme('forum_child_reply_template', $item, $userPicture, $ratings, $delete);
      $json['message'] = '<span>' . t('Thanks, Your reply posted!') . '</span>';
    }
  }
  print json_encode($json);
  exit;
}


