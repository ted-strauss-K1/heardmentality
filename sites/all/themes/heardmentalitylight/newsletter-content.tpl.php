<?php global $theme_path; ?>

<?php foreach ($data['nids'] as $nid) :
    $index++; ?>
    <?php
    $uid = 1;

    $i = -1;
    $choices = cpoll_load_choices($nid);
    $choices_count = count($choices);

    $node = node_load($nid);
    $node->debate = argument_get_list($node->nid, $node->info);
    $account = user_load($node->uid);

    ?>

    <table style="border-spacing: 0; width: 100%">
        <tbody>
        <tr>
            <td style="background: #e2e2e2 ;
                border-left: 1px solid #c0c0c0;
                border-right: 1px solid #c0c0c0;
                font-family: Arial;
                padding: 12px;">

                <table width="100%"
                       style="border-spacing: 0;
                       background: #ffffff;
                   border-top: 1px solid #c0c0c0;
                   border-left: 1px solid #c0c0c0;
                   border-right: 1px solid #c0c0c0;
                   margin: 15px 0 0 0;
                   padding: 20px 12px 10px 12px;">
                    <tbody>
                    <tr>
                        <td>
                            <div style="background: #ffffff;
                        padding: 0 0 5px 0;
                        font-size: 20px"><?php
                                print l($node->title, 'node/' . $nid, array(
                                    'absolute' => TRUE,
                                    'attributes' => array(
                                        'style' => 'text-decoration: none; color: #3c3c3c; font-size: 20px;',
                                    ),
                                ));
                                ?>?
                            </div>
                        </td>
                    </tr>
                    <tr>
                      <td rowspan="1" colspan="1"
                          style=" width: 100%;
                        font-family: Arial;
                        padding: 2px 8px;
                        font-size: 10px;
                        text-align: right;
                        background: #eee;
                        font-style: italic;
                        background: #76d2dc;
                        border: 1px solid #92b7dd;
                        color: #362750;">
                        <?php print __('@count&nbsp;ARGUMENTS', array(
                          '@code'  => 'newsletter-01',
                          '@count' => intval($node->info['argument'])
                        )); ?>
                        &nbsp;|&nbsp;
                        &nbsp;<?php print __('@count&nbsp;REFERENCES', array(
                          '@code'  => 'newsletter-02',
                          '@count' => intval($node->info['resource'])
                        )); ?>
                        &nbsp;|&nbsp;
                        &nbsp;<?php print __('@count&nbsp;VOTES', array(
                          '@code'  => 'newsletter-03',
                          '@count' => intval($node->votecount)
                        )); ?>

                      </td>
                    </tr>
                    </tbody>
                </table>

                <table class="variant_answer"
                       style="border-spacing: 0;
                       width: 100%;
                       background: #ffffff;
                       border-left: 1px solid #c0c0c0;
                       border-right: 1px solid #c0c0c0;
                       padding: 0 12px;">
                    <tbody>
                    <?php foreach ($choices as $chid => $choice) :
                        $i++;
                        $left = $index % 2 == 0; ?>
                        <tr>
                            <?php if (is_numeric($chid)) : ?>
                                <td rowspan="1" colspan="1" nowrap="nowrap" width="60px"
                                    style="height: 44px;
                                    padding: 0;">
                                    <a
                                        href="<?php print $uid ? cpoll_vote_external_link($uid, $chid, TRUE) : url('node/' . $nid, array('absolute' => TRUE)) ?>"
                                        style=" background: none #4298EF;
                                        border: 1px solid #849EB7;
                                        padding: 12px 6px;
                                        margin-right: 10px;
                                        color: #fff;
                                        font-weight: bold;
                                        font-size: 15px;
                                        text-decoration: none;
                                        letter-spacing: 1px;
                                        height: 44px;">VOTE</a>
                                </td>
                                <td style="background: #e4e4e4;
                                padding: 0 10px;
                                height: 42px;
                                border: 1px solid #d7d7d7;">
                                    <span><?php print $choice['chtext']; ?></span>
                                </td>
                            <?php else: ?>
                                <td rowspan="1" colspan="1" width="70%" style="height: 50px;">&nbsp;
                                </td>
                            <?php endif; ?>
                        </tr>
                        <tr style="width: 100%;
                        height: 8px;"></tr>
                    <?php endforeach; ?>


                    </tbody>
                </table>

                <table
                    style="border-spacing: 0;
                    width: 100%;
                    height: 22px;
                    background: #ffffff;
                    border-bottom: 1px solid #c0c0c0;
                    border-left: 1px solid #c0c0c0;
                    border-right: 1px solid #c0c0c0;">
                    <tbody>
                    <tr>
                        <td style="height: 22px">

                        </td>
                    </tr>
                    </tbody>
                </table>


            </td>
        </tr>

        </tbody>
    </table>
<?php endforeach; ?>

