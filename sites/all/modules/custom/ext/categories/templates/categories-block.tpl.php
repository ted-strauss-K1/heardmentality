<?php if ($nid) : ?>
  <div class="grey-box poll-box">
    <i class="icon cat text icon-tag"></i>
    <ul class="tags">
      <label class="tags-on"><?php print __('This issue is listed under', array('@code' => 'categories-listed')); ?></label>
      <?php if ($categories) {
        foreach ($categories as $hierarchy => $name) : ?>
          <li><?php print theme('categories_subscribe', $name, $hierarchy); ?></li>
        <?php endforeach;
      } ?>
    </ul>
    <br class="clear">
    <hr class="short">
    <br>

    <p class="issue-meta">
      <?php if ($author_status) : ?>
        <?php print __('Posted by !name on !time', array(
          '@code' => 'categories-posted-by-on',
          '!name' => l($node->name, 'user/profile/view/' . $node->uid, array('attributes' => array('class' => 'username'))),
          '!time' => date('M j, Y @ H:i', $node->created),
        ));?>
      <?php else : ?>
        <?php print __('Posted on !time', array(
          '@code' => 'categories-posted-on',
          '!time' => date('M j, Y @ H:i', $node->created),
        )); ?>
      <?php endif; ?>
      <br>
      <?php if ($original) : ?>
        <br>
        <?php
          $original['language'] = __($original['language'], array('@code' => 'language-' . $original['langcode']));
        ?>
        <?php print __('Read original post in !language', array(
          '@code' => 'categories-read-original',
          '!language' => l($original['language'], $original['path']),
        )); ?>
      <?php endif; ?>
    </p>

    <div class="clear"></div>
  </div>
<?php endif; ?>
