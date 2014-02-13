<?php global $theme_path; ?>

<tr>
  <td align="center" style="border-top: 3px solid #3c3c3c; background : #444444; padding: 30px 0 40px 0;">

    <p
      style="background: #3c3c3c; height: 48px; font-size: 22px; color: #cccccc; font-family: Arial; padding: 30px 0 0 0; margin: 0 100px;"><?php print t("Be Heard! Don't Be Part of the Herd."); ?></p>

    <p style=" background: #3c3c3c; padding: 0; margin: 0 100px; height: 53px;">
      <a href="http://twitter.com/HeardMentality"
         style="padding: 6px 22px; text-decoration: none; background: #45b0e3; color: #ffffff; font-family: Arial; font-size: 15px;"
         target="_blank">TWITTER </a> <a href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts"
                                         style="padding: 6px 22px; text-decoration: none; background: #3b5998; color: #ffffff; font-family: Arial; font-size: 15px;"
                                         target="_blank">FACEBOOK </a> <a
        href="https://plus.google.com/102365576412479164048"
        style="padding: 6px 22px; text-decoration: none; background: #427fed; color: #ffffff; font-family: Arial; font-size: 15px; "
        target="_blank">GOOGLE+ </a>
    </p>

  </td>
</tr>

<tr>
  <td
    style="background: #444444; height: 16px;  font-size: 18px; font-family: Arial; text-align: center; padding: 0 0 70px 0;">

    <?php print l('View this email on website', 'newsletter/' . $data['newsletter']['hash'], array(
      'absolute'   => TRUE,
      'attributes' => array(
        'style' => 'text-decoration: none; color: #ee3a3b;',
      ),
    )); ?>

    <?php if ($data['uid']) : ?>
      &nbsp;&nbsp;<span style="color: #3a4da1">|</span>&nbsp;&nbsp;

      <?php print l('Unsubscribe', 'user/profile/view/' . $data['uid'], array(
        'absolute'   => TRUE,
        'query'      => array('newsletter_action' => 'unsubscribe'),
        'attributes' => array(
          'style' => 'text-decoration: none; color: #3bc7f4;',
        ),
      )); ?>
    <?php endif; ?>

  </td>
</tr>
