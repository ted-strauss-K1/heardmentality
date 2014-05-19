<?php global $theme_path; ?>

<table style="border-spacing: 0; width: 100%">
    <tbody>
    <tr>
        <td align="center" style="border-top: 3px solid #3c3c3c;
        background : #444444;
        padding: 30px 0 40px 0;">

            <p
                style="background: #3c3c3c;
                font-size: 22px;
                color: #cccccc;
                font-family: Arial;
                padding: 30px 5px 10px 5px;
                margin: 0 85px;"><?php print t("Be Heard! Don't Be Part of the Herd."); ?></p>

            <p style=" background: #3c3c3c;
            padding: 10px 5px 40px 5px;
            margin: 0 85px;
            letter-spacing: 0;
            word-spacing: 0;
            font-size: 0;
            text-align: center">
                <a href="http://twitter.com/HeardMentality"
                   style="display: inline-block;
                   padding: 6px 0;
                   width: 118px;
                   text-decoration: none;
                   background: #45b0e3;
                   color: #ffffff;
                   font-family: Arial;
                   font-size: 15px;"
                   target="_blank">TWITTER </a>
                <a href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts"
                   style="display: inline-block;
                   padding: 6px 0;
                   width: 118px;
                   text-decoration: none;
                   background: #3b5998;
                   color: #ffffff;
                   font-family: Arial;
                   font-size: 15px;"
                   target="_blank">FACEBOOK </a>
                <a
                    href="https://plus.google.com/102365576412479164048"
                    style="display: inline-block;
                    padding: 6px 0;
                    width: 118px;
                    text-decoration: none;
                    background: #427fed;
                    color: #ffffff;
                    font-family: Arial;
                    font-size: 15px; "
                    target="_blank">GOOGLE+ </a>
            </p>

        </td>
    </tr>

    <tr>
        <td
            style="background: #444444;
            height: 16px;
            font-size: 18px;
            font-family: Arial;
            text-align: center;
            padding: 0 0 70px 0;">

            <?php print l('View this email on website', 'newsletter/' . $data['newsletter']['hash'], array(
                'absolute' => TRUE,
                'attributes' => array(
                    'style' => 'text-decoration: none; color: #ee3a3b;',
                ),
            )); ?>
            <?php if ($data['uid']) : ?>
                &nbsp;&nbsp;<span style="color: #3a4da1">|</span>&nbsp;&nbsp;

                <?php print l('Unsubscribe', 'user/profile/view/' . $data['uid'], array(
                    'absolute' => TRUE,
                    'query' => array('newsletter_action' => 'unsubscribe'),
                    'attributes' => array(
                        'style' => 'text-decoration: none; color: #3bc7f4;',
                    ),
                )); ?>
            <?php endif; ?>

        </td>
    </tr>
    </tbody>
</table>
