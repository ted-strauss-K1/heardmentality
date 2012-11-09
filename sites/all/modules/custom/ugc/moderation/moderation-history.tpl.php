<?php
  $type = arg(1);
  $content_id = arg(2);
  switch ($type) {
    case 'issue' :
    case 'argument' :
      $content_type = 'node';
    break;
    case 'comment' :
      $content_type = 'comment';
    break;
    default : return;
  }
  $history = moderation_history('get', $content_id, $content_type, true, array(), 10);
?><?php foreach ($history as $item) : ?>
  <div style="border-bottom: 1px #ccc dotted; margin-bottom: 5px; padding: 5px 0;">
    <?php
      $account = user_load($item['uid']);
      $link = l($account->name, $account->viewlink);
    ?>

    <?php if ($item['type'] == 'approve') : ?>
      <?php echo t('Approved by') , ' ' , $link; ?>
    <?php elseif ($item['type'] == 'delete') : ?>
      <?php echo t('Deletion requested by') , ' ' , $link; ?>
    <?php elseif ($item['type'] == 'edit') : ?>
      <?php echo t('Edited by') , ' ' , $link; ?>
      <ul>
        <?php foreach ($item['vars'] as $main => $edit) : ?>
          <li>
            <?php if ($main == 'choices') : ?>
              <?php foreach ($edit as $choice) : ?>
                <?php if (isset($choice['chtext'])) : ?>
                  <?php if ($choice['chtext'] == '') : ?>
                    <span><?php print t('Requested deletion of choice #') . ($choice['chorder']+1); ?></span>
                  <?php else : ?>
                    <span><?php print t('Changed the text of choice #') . ($choice['chorder']+1) . ' ' . t('to') . ' "' . $choice['chtext'] . '"'; ?></span>
                  <?php endif; ?>
                <?php endif; ?>
                <?php if (isset($choice['chtext_short'])) : ?>
                  <span><?php print t('Changed the short text of choice #') . ($choice['chorder']+1) . ' ' . t('to') . ' "' . $choice['chtext_short'] . '"'; ?></span>
                <?php endif; ?>
              <?php endforeach; ?>
            <?php elseif ($main == 'body') : ?>
              <?php print t('Set description value to: ') . $edit; ?>
            <?php elseif ($main == 'title') : ?>
              <?php print t('Set title to: ') . $edit; ?>
            <?php elseif ($main == 'comment') : ?>
              <?php print t('Set text value to: ') . $edit; ?>
            <?php elseif ($main == 'str_wk') : ?>
              <?php print t('Set strength value to: ') . t($edit ? 'Strenghten' : 'Weaken'); ?>


            <?php endif; ?>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>
  </div>
<?php endforeach; ?>