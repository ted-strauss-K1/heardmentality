<?php

/**
 * @return array
 */
function moderation_merge_form($form_state, $merge, $base) {
  $form = array();

  $base = node_load($base);
  $merge = node_load($merge);

  $base_choices = array();
  foreach ($base->choices as $chid => $choice) {
    $base_choices[$chid] = t('Merge into '). ' "'.$choice['chtext'].'"';
  }
  $base_choices[0] = t('Remove the answer');
  $base_choices[-1] = t('Transfer the answer');

  $form['warning'] = array(
    '#type' => 'markup',
    '#value' => t('The action cannot be undone. Merged issue will be removed.'),
    '#prefix' => '<span class="warning">',
    '#suffix' => '</span>',
  );

  $form['table'] = array(
    '#type' => 'markup',
    '#value' => '&nbsp;',
    '#prefix' => '<table class="merge-issue"><th><tr>
      <td class="merge-main">'.t('Merged Issue').'</td>
      <td class="merge-center">' .
        l(t('Swap Issues'), 'moderation/merge/'.$base->nid.'/'.$merge->nid) .
      '</td>
      <td class="merge-main">'.t('Base Issue').'</td>
    </tr></th>',
    '#suffix' => '</table>',
  );
  $form['table']['item'] = array(
    '#type' => 'markup',
    '#value' => 'Choices',
    '#prefix' => '<tr><td class="merge-header" colspan=3>',
    '#suffix' => '</td><tr>',
  );
  foreach ($merge->choices as $chid => $choice) {
    $index = $choice['index'];
    $form['table']['choices-'.$index] = array(
      '#type' => 'fieldset',
      '#prefix' => '<tr>',
      '#suffix' => '</tr>',
      '#tree' => TRUE,
    );

    $form['table']['choices-'.$index]['name-'.$index] = array(
      '#type' => 'markup',
      '#value' => $choice['chtext'],
      '#prefix' => '<td>',
      '#suffix' => '</td>',
    );
    $form['table']['choices-'.$index]['chid-'.$index] = array(
      '#type' => 'hidden',
      '#value' => $chid,
      '#prefix' => '<td>&gt;&gt;',
      '#suffix' => '</td>',
    );
    $form['table']['choices-'.$index]['select-'.$index] = array(
      '#type' => 'select',
      '#options' => $base_choices,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
      '#attributes' => array('class' => 'chosen-select->moderatio'),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Merge'),
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_merge_form_submit($form, $form_state) {

  var_dump($form_state['values']);

  exit;
}