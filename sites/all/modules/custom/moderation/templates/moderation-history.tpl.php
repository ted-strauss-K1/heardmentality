<div class="grey-box full icon_inside">
  <i class="icon cat text icon-rubberstamp"></i> <label class="with_icon"><?php echo __('Moderation history', array('@code' => 'moderator-41')); ?></label>
  <?php if ($history) : ?>
    <?php foreach ($history as $item) : ?>
      <div class="mh_cell">
        <?php
        $account = user_load($item['uid']);
        $link = l($account->name, $account->viewlink);
        ?>

        <?php if ($item['type'] == 'approve') : ?>

          <strong><?php echo __('Approved by !name', array('@code' => 'moderator-42', '!name' => $link)); ?></strong>

        <?php elseif ($item['type'] == 'delete') : ?>

          <strong><?php echo __('Deletion requested by !name', array('@code' => 'moderator-43', '!name' => $link)); ?></strong>

        <?php
        elseif ($item['type'] == 'edit') : ?>

          <strong><?php echo __('Edited by !name', array('@code' => 'moderator-44', '!name' => $link)); ?></strong>

          <ul><?php foreach ($item['vars'] as $main => $edit) : ?>
              <li>

              <?php if ($main == 'choices') : ?>

              <?php foreach ($edit as $choice) : ?>
                <?php if (isset($choice['chtext'])) : ?>
                  <?php if ($choice['chtext'] == '') : ?>
                    <div><span
                        class="action"><?php print __('Requested deletion of choice #!index', array('@code' => 'moderator-45', '!index' => ($choice['index'] + 1))); ?></span>
                    </div>
                  <?php else : ?>
                    <div><span class="action"><?php print __('Changed the text of choice #!index to', array(
                            '@code' => 'moderator-46',
                            '!index' => ($choice['chorder'] + 1),
                          )) . '</span> "' . $choice['chtext'] . '"'; ?>
                    </div>
                  <?php endif; ?>
                <?php endif; ?>
                <?php if (isset($choice['chtext_short'])) : ?>
                  <div>

                    <span class="action">
                      <?php print __('Changed the short text of choice #!index to', array(
                          '@code' => 'moderator-47',
                          '!index' => ($choice['chorder'] + 1),
                        )); ?>
                    </span> "<?php print $choice['chtext_short']; ?>" ?>

                  </div>
                <?php endif; ?>
              <?php endforeach; ?>

            <?php elseif ($main == 'body') : ?>

              <div><span
                  class="action"><?php print __('Set description value to: ', array('@code' => 'moderator-48')) ?></span><?php print trim_better($edit, 200); ?>
              </div>

            <?php
            elseif ($main == 'title') : ?>

              <div><span class="action"><?php print __('Set title to: ', array('@code' => 'moderator-50')) ?></span><?php print $edit; ?>

            <?php endif; ?>

              </li><?php endforeach; ?></ul>
        <?php endif; ?>
        <hr class="short"/>
      </div>
    <?php endforeach; ?>
  <?php else : ?>
    <?php print __('Moderation history is empty', array('@code' => 'moderator-49')); ?>
  <?php endif; ?>
</div>
