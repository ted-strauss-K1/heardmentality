<div class="moderation_header clearfix">
  <div class="form-item">
    <ul class="date_filter moderation_options">

      <li><?php print l(
          t('Issues'), 'moderation/issues', array(
            'attributes' => array(
              'class' => 'first ' . ('issues' == $page ? 'active' : '')
            ),
        )); ?></li>

      <li><?php print l(
          t('Arguments'), 'moderation/arguments', array(
          'attributes' => array(
            'class' => ('arguments' == $page ? 'active' : '')
          ),
        )); ?></li>

      <li><?php print l(
          t('Comments'), 'moderation/comments', array(
          'attributes' => array(
            'class' => 'last ' . ('comments' == $page ? 'active' : '')
          ),
        )); ?></li>

    </ul>
  </div>
  <div class="form-item">
    <ul class="options_filter moderation_options">
      <?php if (user_access(MODERATION_ADMIN)) : ?>

      </li>
        <li><?php print l(
            t('Users'), 'moderation/users', array(
            'attributes' => array(
              'class' => 'first last ' . ('users' == $page ? 'active' : '')
            ),
          )); ?></li>

      <?php endif; ?>
    </ul>
  </div>
</div>