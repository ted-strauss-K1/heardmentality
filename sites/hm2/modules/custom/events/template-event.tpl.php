<?php if (!$skip) : ?>
<li class="clearfix">
  <?php print $userlink; ?>
  <p class="action-item">
    <span class="name">
      <a href="<?php print url($account->viewlink) ?>" title="<?php print $account->name ?>">
        <?php print ucwords($account->name) ?>
      </a>
    </span>
    <?php print $text; ?>
    <?php print $link; ?>
    <?php if ($text2) : ?>
      </p>
      <p class="action-comment-ref"><?php print $text2 ?>
        <br clear="both">
    <?php endif; ?>
  </p>
  <span class="submitted" name="<?php print $item['timestamp']; ?>"><?php print $item['date_added']; ?></span>
</li>
<?php endif; ?>