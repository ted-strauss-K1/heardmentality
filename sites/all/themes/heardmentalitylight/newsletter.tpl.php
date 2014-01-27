<?php if (!$error) : ?>

  <?php foreach ($nids as $nid) : ?>
    <?php echo $nid; ?>
  <?php endforeach; ?>

<?php else : ?>

  <?php print t('ERROR'); ?>

<?php endif; ?>