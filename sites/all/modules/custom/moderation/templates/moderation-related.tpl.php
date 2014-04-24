<?php if ($related) : ?>
  <div class="dark-grey-box">
    <div class="profile-meta profile_page_wrapper">
      <label for="profile" class="profile profile_page"><?php print __('Possible Duplicates', array('@code' => 'moderation-block-related-title')) ?></label>
    </div>

    <ul>
      <?php foreach ($related as $doc) : ?>
        <li>
          [<?php print l(__('merge', array('@code' => 'moderation-block-related-merge')), 'moderation/merge/' . $content_id . '/' . $doc->entity_id); ?>]
          <?php print l($doc->label, $doc->path); ?>
        </li>
      <?php endforeach; ?>
    </ul>

  </div>
<?php endif; ?>
