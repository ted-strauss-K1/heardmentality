<?php global $theme_path; ?>



<tr>
  <td
    style="background : url(<?php print url($theme_path . '/images/cross_hatch_texture_dark.png', array('absolute' => true)); ?>) repeat scroll 0 0 #A29CAC;border       : solid #A29CAC;border-width : 1px 0;height: 100px;">

    <table>
      <tr>

        <td
          style=""><?php print l('<img style="height: 80px; width: 140px;" title="Heard Mentality Logo" alt="Heard Mentality Logo" src="' . url($theme_path . '/images/hm-logo.png', array('absolute' => true)) . '">', '', array(
            'absolute'   => true,
            'html'       => true,
            'attributes' => array(
              'style' => 'padding: 5px;',
            ),
          )); ?></td>

        <td
          style="width: 100%;text-align: center; font-family: Arial; font-size: 30px; padding-left: 10px;"><?php print l('Heard Mentality Newsletter', '', array(
            'absolute'   => true,
            'attributes' => array(
              'style' => 'text-decoration: none; color: #333;',
            ),
          )); ?></td>

      </tr>
    </table>

  </td>
</tr>
