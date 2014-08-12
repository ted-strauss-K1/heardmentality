<div class="moderation_header clearfix">
  <div class="form-item">
    <ul class="date_filter moderation_options">

      <li><?php print l(__('Issues', array('@code' => 'moderator-51')), 'moderation/issues', array(
          'attributes' => array(
            'class' => 'first ' . ('issues' == $page ? 'active' : '')
          ),
        )); ?></li>

      <li><?php print l(__('Arguments', array('@code' => 'moderator-52')), 'moderation/arguments', array(
          'attributes' => array(
            'class' => ('arguments' == $page ? 'active' : '')
          ),
        )); ?></li>

      <li><?php print l(__('Comments', array('@code' => 'moderator-53')), 'moderation/comments', array(
          'attributes' => array(
            'class' => 'last ' . ('comments' == $page ? 'active' : '')
          ),
        )); ?></li>

    </ul>
  </div>
  <div class="form-item">
    <ul class="options_filter moderation_options">
      <?php if (user_access(MODERATION_ADMIN)) : ?>

        <li><?php print l(__('Flagged Users', array('@code' => 'moderator-54')), 'moderation/userflags', array(
            'attributes' => array(
              'class' => 'first ' . ('userflags' == $page ? 'active' : '')
            ),
          )); ?></li>
        <li><?php print l(__('Users', array('@code' => 'moderator-55')), 'moderation/users', array(
            'attributes' => array(
              'class' => 'last ' . ('users' == $page ? 'active' : '')
            ),
          )); ?></li>

      <?php endif; ?>
    </ul>
  </div>
</div>
