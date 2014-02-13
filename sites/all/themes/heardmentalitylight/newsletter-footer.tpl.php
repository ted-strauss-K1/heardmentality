<?php global $theme_path; ?>

<tr>
  <td align="center" style="background : #777777; height: 140px;">

    <p
      style="font-size: 25px; color: #333333; font-family: Arial; padding: 10px 0; margin: 0;"><?php print t("Be Heard! Don't Be Part of the Herd."); ?></p>

    <p style=" padding: 0; margin: 0;">
      <a href="http://twitter.com/HeardMentality"
         style="padding: 0 30px 0 10px; text-decoration: none"
         target="_blank">
        <img
          style="width: 48px; height: 48px;"
          alt="Twitter"
          title="Twitter"
          src="<?php print url($theme_path . '/images/twitter.png', array('absolute' => true)); ?>">
      </a>
      <a href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts"
         style="padding: 0 30px; text-decoration: none"
         target="_blank">
        <img
          style="width: 48px; height: 48px;"
          alt="Facebook"
          title="Facebook"
          src="<?php print url($theme_path . '/images/facebook.png', array('absolute' => true)); ?>">
      </a>
      <a href="https://plus.google.com/102365576412479164048"
         style="padding: 0 10px 0 30px; text-decoration: none"
         target="_blank">
        <img
          style="width: 48px; height: 48px;"
          alt="Google Plus"
          title="Google Plus"
          src="<?php print url($theme_path . '/images/gplus.png', array('absolute' => true)); ?>">
      </a>
    </p>

  </td>
</tr>

<tr>
  <td style="height: 16px; line-height: 16px; font-size: 14px; font-family: Arial; text-align: center;">

    <?php print l('View this email on website', 'newsletter/' . $data['newsletter']['hash'], array(
      'absolute'   => true,
      'attributes' => array(
        'style' => 'text-decoration: none; color: #333;',
      ),
    )); ?>

    <?php if ($data['uid']) : ?>
      &nbsp;&nbsp;|&nbsp;&nbsp;

      <?php print l('Unsubscribe', 'user/profile/view/' . $data['uid'], array(
        'absolute'   => true,
        'query'      => array('newsletter_action' => 'unsubscribe'),
        'attributes' => array(
          'style' => 'text-decoration: none; color: #333;',
        ),
      )); ?>
    <?php endif; ?>

  </td>
</tr>
