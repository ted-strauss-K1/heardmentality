<?php
  switch (arg(1)) {
    case 'issue' :
    case 'argument' :
      $content_id = arg(2);
      $content_type = 'node';
    break;
    case 'comment' :
      $content_id = arg(2);
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
          <li><?php print json_encode($edit); ?></li>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>
  </div>
<?php endforeach; ?>