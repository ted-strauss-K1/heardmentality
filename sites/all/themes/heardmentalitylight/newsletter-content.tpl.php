<?php global $theme_path; ?>

<tr>
  <td style="border-left: #ccc 2px solid; border-right: #ccc 2px solid; font-family: Arial; padding: 10px;">

    <?php foreach ($data['nids'] as $nid) : $index++; ?>
      <?php
      $uid = 1;

      $i = -1;
      $choices = cpoll_load_choices($nid);
      $choices_count = count($choices);

      $node = node_load($nid);
      $account = user_load($node->uid);

      ?>

      <table width="100%" style="min-height: 200px;">
        <tr>
          <td rowspan="1" colspan="1" style="padding: 20px 0 10px 0;">
            <div style="background: #ccc; padding: 10px;"><?php
              print l($node->title, 'node/' . $nid, array(
                'absolute'   => true,
                'attributes' => array(
                  'style' => 'text-decoration: none; color: #333;',
                ),
              ));
              ?>?
            </div>
          </td>
        </tr>
        <?php foreach ($choices as $chid => $choice) : $i++;
          $left = $index % 2 == 0; ?>

          <tr>
            <?php if (is_numeric($chid)) : ?>
              <td rowspan="1" colspan="1" nowrap="nowrap" width="70%" style="height: 50px; padding: 0 10px;">
                <a
                  href="<?php print $uid ? cpoll_vote_external_link($uid, $chid, true) : url('node/' . $nid, array('absolute' => true)) ?>"
                  style="background: none #4298EF; border: 1px solid #849EB7; padding: 10px; margin-right: 10px; color: #fff; font-weight: bold; font-size: 14px; text-decoration: none;">vote</a>
                <span style=""><?php print $choice['chtext']; ?></span></td>
            <?php else: ?>
              <td rowspan="1" colspan="1" width="70%" style="height: 50px;">&nbsp;</td>
            <?php endif; ?>
          </tr>

        <?php endforeach; ?>
      </table>
    <?php endforeach; ?>

  </td>
</tr>