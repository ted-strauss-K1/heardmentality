<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
  <meta name="viewport" content="width=device-width"/>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>

  <title><?php print t('Heard Mentality Newsletter'); ?></title>
</head>

<?php global $theme_path; ?>

<body bgcolor="#FFFFFF" topmargin="0" leftmargin="0" marginheight="0" marginwidth="0">

<table style="margin: 0 auto; width: 100%; max-width: 800px">

  <tr>
    <td style="height: 16px; line-height: 16px; font-size: 14px; font-family: Arial; text-align: center;">

      <?php print l('View this email on website', 'newsletter/' . context_get('newsletter', 'hash'), array(
        'absolute'   => true,
        'attributes' => array(
          'style' => 'text-decoration: none; color: #333;',
        ),
      )); ?>
    </td>
  </tr>

  <tr>
    <td
      style="background : url(<?php print url($theme_path . '/images/cross_hatch_texture_dark.png', array('absolute' => true)); ?>) repeat scroll 0 0 #A29CAC;border       : solid #A29CAC;border-width : 1px 0;height: 100px;">

      <table>
        <tr>

          <td
            style=""><?php print l('<img style="height: 80px;" src="' . url($theme_path . '/images/hm-logo.png', array('absolute' => true)) . '">', '', array(
              'absolute'   => true,
              'html'       => true,
              'attributes' => array(
                'style' => 'padding: 10px;',
              ),
            )); ?></td>

          <td
            style="font-family: Arial; font-size: 40px; padding-left: 30px;"><?php print l('Heard Mentality Newsletter', '', array(
              'absolute'   => true,
              'attributes' => array(
                'style' => 'text-decoration: none; color: #333;',
              ),
            )); ?></td>

        </tr>
      </table>

    </td>
  </tr>

  <tr>
    <td style="border-left: #ccc 2px solid; border-right: #ccc 2px solid; font-family: Arial; padding: 10px;">
      <?php print $content; ?>
    </td>
  </tr>

  <tr>
    <td align="center" style="background : #777777; height: 140px;">

      <p
        style="font-size: 25px; color: #333333; font-family: Arial; padding: 10px 0; margin: 0;"><?php print t("Be Heard! Don't Be Part of the Herd."); ?></p>

      <p style=" padding: 0; margin: 0;">
        <a href="http://twitter.com/HeardMentality" style="padding: 0 40px;" target="_blank"><img
            src="<?php print url($theme_path . '/images/twitter.png', array('absolute' => true)); ?>"></a> <a
          href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts" tyle="padding: 0 40px;"
          target="_blank"><img
            src="<?php print url($theme_path . '/images/facebook.png', array('absolute' => true)); ?>"></a> <a
          href="https://plus.google.com/102365576412479164048" style="padding: 0 40px;" target="_blank"><img
            src="<?php print url($theme_path . '/images/gplus.png', array('absolute' => true)); ?>"></a>
      </p>

    </td>
  </tr>
</table>

</body>
</html>