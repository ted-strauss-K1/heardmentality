<?php global $theme_path; ?>

<tr>
  <td style="border-left: #ccc 2px solid; border-right: #ccc 2px solid; font-family: Arial; padding: 10px;">

    <?php foreach ($data['nids'] as $nid) : $index++; ?>
      <?php
      $uid = 1;

      $i = -1;
      $choices = cpoll_load_choices($nid);
      $choices_count = count($choices);
      for ($k = $choices_count + 1; $k <= 4; $k++) {
        $choices['k-' . $k] = false;
      }
      $choices_count = count($choices);

      $title = db_result(db_query("SELECT title FROM {node} WHERE nid = '%s'", $nid));

      ?>

      <table width="100%" style="min-height: 200px;">
        <tr>
          <td rowspan="1" colspan="2" style="padding: 20px 0 10px 0;">
            <div style="background: #ccc; padding: 10px;"><?php
              print l($title, 'node/' . $nid, array(
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

            <?php if ($left && $i == 0) : ?>
              <td rowspan="<?php print $choices_count; ?>" colspan="1" width="30%"
                  style="background: #EEE; min-width: 200px;"></td>
            <?php endif; ?>

            <?php if (is_numeric($chid)) : ?>
              <td rowspan="1" colspan="1" width="70%" style="height: 50px; padding: 0 10px;">
                <a href="<?php
                if ($uid) {
                  print cpoll_vote_external_link($uid, $chid, true);
                } else {
                  print url('node/' . $nid, array('absolute' => true));
                }


                ?>" style="
                            background: none #4298EF;
                            border: 1px solid #849EB7;
                            padding: 10px;
                            margin-right: 10px;
                            color: #fff;
                            font-weight: bold;
                            font-size: 14px;
                            text-decoration: none;
              ">vote</a>
                <?php print $choice['chtext']; ?></td>
            <?php else: ?>
              <td rowspan="1" colspan="1" width="70%" style="height: 50px;">&nbsp;</td>
            <?php endif; ?>

            <?php if (!$left && $i == 0) : ?>
              <td rowspan="<?php print $choices_count; ?>" colspan="1" width="30%"
                  style="background: #EEE;min-width: 200px;"></td>
            <?php endif; ?>

          </tr>

        <?php endforeach; ?>
      </table>
    <?php endforeach; ?>

  </td>
</tr>