<div class="grey-box full icon_inside">
  <i class="icon cat text icon-rubberstamp"></i>
  <label class="with_icon"><?php echo t('Moderation history'); ?></label>
  <?php if ($history) : ?>
  <?php foreach ($history as $item) : ?>
    <div class="mh_cell">
      <?php
        $account = user_load($item['uid']);
        $link = l($account->name, $account->viewlink);
      ?>

      <?php if ($item['type'] == 'approve') : ?>

        <strong><?php echo t('Approved by'), ' ', $link; ?></strong>

      <?php elseif ($item['type'] == 'delete') : ?>

        <strong><?php echo t('Deletion requested by'), ' ', $link; ?></strong>

      <?php elseif ($item['type'] == 'edit') : ?>

        <strong><?php echo t('Edited by'), ' ', $link; ?></strong>

        <ul><?php foreach ($item['vars'] as $main => $edit) : ?><li>

          <?php if ($main == 'choices') : ?>

            <?php foreach ($edit as $choice) : ?>
              <?php if (isset($choice['chtext'])) : ?>
                <?php if ($choice['chtext'] == '') : ?>
                  <div><span class="action"><?php print t('Requested deletion of choice #') . ($choice['chorder'] + 1); ?></span></div>
                <?php else : ?>
                  <div><span class="action"><?php print t('Changed the text of choice #') . ($choice['chorder'] + 1) . ' ' . t('to') . '</span> "' . $choice['chtext'] . '"'; ?></div>
                <?php endif; ?>
              <?php endif; ?>
            <?php if (isset($choice['chtext_short'])) : ?>
              <div><span class="action"><?php print t('Changed the short text of choice #') . ($choice['chorder'] + 1) . ' ' . t('to') . '</span> "' . $choice['chtext_short'] . '"'; ?></div>
                <?php endif; ?>
              <?php endforeach; ?>

            <?php elseif ($main == 'body') : ?>

            <div><span class="action"><?php print t('Set description value to: ') ?></span><?php print trim_better($edit, 200); ?></div>

            <?php elseif ($main == 'title') : ?>

            <div><span class="action"><?php print t('Set title to: ') ?></span><?php print $edit; ?>

            <?php endif; ?>

        </li><?php endforeach; ?></ul>
      <?php endif; ?>
      <hr class="short" />
    </div>
    <?php endforeach; ?>
  <?php else : ?>
  <?php print t('Moderation history is empty'); ?>
  <?php endif; ?>
</div>