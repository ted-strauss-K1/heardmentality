<div class="grey-box full icon_inside">
  <i class="icon cat text icon-rubberstamp"></i>
  <label class="with_icon"><?php echo t('Moderation history'); ?></label>
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
    default :
      return;
  }
  $history = moderation_history('get', $content_id, $content_type, true, array(), 10);
  ?><?php if ($history) : ?>
  <?php foreach ($history as $item) : ?>
    <div class="mh_cell">
      <?php
      $account = user_load($item['uid']);
      $link = l($account->name, $account->viewlink);
      ?>
		  <?php if ($item['type'] == 'approve') : ?>
		  <?php echo '<strong>' . t('Approved by'), ' ', $link . '</strong>'; ?>
		  <?php elseif ($item['type'] == 'delete') : ?>
		  <?php echo '<strong>' . t('Deletion requested by'), ' ', $link . '</strong>'; ?>
		  <?php elseif ($item['type'] == 'edit') : ?>
		  <?php echo '<strong>' . t('Edited by'), ' ', $link . '</strong>'; ?>
      <ul>
        <?php foreach ($item['vars'] as $main => $edit) : ?>
        <li>
          <?php if ($main == 'choices') : ?>
          <?php foreach ($edit as $choice) : ?>
            <?php if (isset($choice['chtext'])) : ?>
              <?php if ($choice['chtext'] == '') : ?>
                <div><?php print '<span class="action">' . t('Requested deletion of choice #') . ($choice['chorder'] + 1) . '</span>'; ?></div>
                <?php else : ?>
                <div><?php print '<span class="action">' . t('Changed the text of choice #') . ($choice['chorder'] + 1) . ' ' . t('to') . '</span> "' . $choice['chtext'] . '"'; ?></div>
                <?php endif; ?>
              <?php endif; ?>
            <?php if (isset($choice['chtext_short'])) : ?>
              <div><?php print '<span class="action">' . t('Changed the short text of choice #') . ($choice['chorder'] + 1) . ' ' . t('to') . '</span> "' . $choice['chtext_short'] . '"'; ?></div>
              <?php endif; ?>
            <?php endforeach; ?>
          <?php elseif ($main == 'body') : ?>
          <div><?php print '<span class="action">' . t('Set description value to: ') . '</span>' . $edit; ?></div>
          <?php elseif ($main == 'title') : ?>
          <div><?php print '<span class="action">' . t('Set title to: ') . '</span>' . $edit; ?></div>
          <?php elseif ($main == 'comment') : ?>
          <div><?php print '<span class="action">' . t('Set text value to: ') . '</span>' . $edit; ?></div>
          <?php elseif ($main == 'str_wk') : ?>
          <div><?php print '<span class="action">' . t('Set strength value to: ') . '</span>' . t($edit ? 'Strenghten' : 'Weaken'); ?></div>

          <?php endif; ?>
        </li>
        <?php endforeach; ?>
      </ul>
      <?php endif; ?>
	  <hr class="short" />
    </div>
    <?php endforeach; ?>
  <?php else : ?>
  <?php print t('Moderation history is empty'); ?>
  <?php endif; ?>
</div>