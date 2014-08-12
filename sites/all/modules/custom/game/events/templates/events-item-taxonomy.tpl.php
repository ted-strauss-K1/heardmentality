<?php if (!$skip) : ?>
  <li class="clearfix">
    <ul class="tags">
      <label class="tags-on"></label>
      <?php foreach ($categories as $hierarchy => $name) : ?>
        <li><?php print theme('categories_subscribe', $name, $hierarchy); ?></li>
      <?php endforeach; ?>
    </ul>
    <br clear="both">

    <p class="action-comment-ref">
      <?php print __('New issue posted', array('@code' => 'events-14')) . ' ' . $link ?>
      <br clear="both">
    </p>
    <span class="submitted" name="<?php print $item['timestamp']; ?>"><?php print $item['date_added']; ?></span>
  </li>
<?php endif; ?>
