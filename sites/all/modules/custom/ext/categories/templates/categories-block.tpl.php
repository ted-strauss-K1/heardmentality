<?php if ($nid) : ?>
  <div class="grey-box poll-box">
    <i class="icon cat text icon-tag"></i>
    <ul class="tags">
      <label class="tags-on"><?php print __('This issue is listed under', array('@code' => 'categories-03')); ?></label>
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
        <?php print __('Posted by !name on !date', array(
          '@code' => 'categories-04',
          '!name' => l($node->name, 'user/profile/view/' . $node->uid, array('attributes' => array('class' => 'username'))),
          '!date' => date('M j, Y @ H:i', $node->created),
        )); ?>
      <?php else : ?>
        <?php print __('Posted on !date', array(
          '@code' => 'categories-05',
          '!date' => date('M j, Y @ H:i', $node->created),
        )); ?>
      <?php endif; ?>
      <br>
      <?php if ($original) : ?>
        <br>
        <?php print __('Read original post in !language', array(
          '@code' => 'categories-06',
          '!language' => l($original['language'], $original['path']),
        )); ?>
      <?php endif; ?>
    </p>

    <div class="clear"></div>
  </div>
<?php endif; ?>
