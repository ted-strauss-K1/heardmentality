<?php global $theme_path; ?>



<table style="border-spacing: 0">
    <tbody>
    <tr style="background : #362750; height: 80px;">
        <td
            style=""><?php print l('<img style="height: 44px; width: 81px;" title="Heard Mentality Logo" alt="Heard Mentality Logo" src="' . url($theme_path . '/sites/all/themes/heardmentalitylight/images/logo_emails.png', array('absolute' => TRUE)) . '">', '', array(
                'absolute' => TRUE,
                'html' => TRUE,
                'attributes' => array(
                    'style' => 'display: block; padding-left: 10px;',
                ),
            )); ?></td>

        <td
            style="width: 100%;
            text-align: center;
            font-family: Arial;
            font-size: 30px;
            padding: 10px;
            letter-spacing: 1px;"><?php print l('HEARD MENTALITY newsletter', '', array(
                'absolute' => TRUE,
                'attributes' => array(
                    'style' => 'text-decoration: none; color: #ffffff; font-size: 0.9em;',
                ),
            )); ?></td>

    </tr>
    </tbody>
</table>
