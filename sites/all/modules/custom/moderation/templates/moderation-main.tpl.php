<div class="moderation_header clearfix">
  <div class="form-item">
    <ul class="date_filter moderation_options">

      <li><?php print l(__('Issues', array('@code' => 'moderation-tab-issues')), 'moderation/issues', array(
          'attributes' => array(
            'class' => 'first ' . ('issues' == $page ? 'active' : '')
          ),
        )); ?></li>

      <li><?php print l(__('Arguments', array('@code' => 'moderation-tab-arguments')), 'moderation/arguments', array(
          'attributes' => array(
            'class' => ('arguments' == $page ? 'active' : '')
          ),
        )); ?></li>

      <li><?php print l(__('Comments', array('@code' => 'moderation-tab-comments')), 'moderation/comments', array(
          'attributes' => array(
            'class' => 'last ' . ('comments' == $page ? 'active' : '')
          ),
        )); ?></li>

    </ul>
  </div>
  <div class="form-item">
    <ul class="options_filter moderation_options">
      <?php if (user_access(MODERATION_ADMIN)) : ?>

        <li><?php print l(__('Flagged Users', array('@code' => 'moderation-tab-users-flagged')), 'moderation/userflags', array(
            'attributes' => array(
              'class' => 'first ' . ('userflags' == $page ? 'active' : '')
            ),
          )); ?></li>
        <li><?php print l(__('Users', array('@code' => 'moderation-tab-users')), 'moderation/users', array(
            'attributes' => array(
              'class' => 'last ' . ('users' == $page ? 'active' : '')
            ),
          )); ?></li>

      <?php endif; ?>
    </ul>
  </div>
</div>
