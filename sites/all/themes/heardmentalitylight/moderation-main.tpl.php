<div class="moderation_header clearfix">
  <div class="form-item">
    <ul class="date_filter moderation_options">
      <li><a class="first <?php if ($page == 'issues') : ?>active<?php endif; ?>" href="/moderation/issues">Issues</a></li>
      <li><a class=" <?php if ($page == 'arguments') : ?>active<?php endif; ?>" href="/moderation/arguments">Arguments</a></li>
      <li><a class="last <?php if ($page == 'comments') : ?>active<?php endif; ?>" href="/moderation/comments">Comments</a></li>
    </ul>
  </div>
  <div class="form-item">
    <ul class="options_filter moderation_options">
      <?php if (user_access(MODERATION_ADMIN)) : ?>
        <li><a class="first last <?php if ($page == 'users') : ?>active<?php endif; ?>" href="/moderation/users">Users</a></li>
      <?php endif; ?>
    </ul>
  </div>
</div>