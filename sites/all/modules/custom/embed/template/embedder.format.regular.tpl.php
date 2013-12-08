<?php if ($node->choices) : global $user, $language; ?>
  <div <?php if ($node->vote) : ?>class="voted"<?php endif; ?>>
    <?php print l('<h1>' . $node->title . '</h1>', 'node/' . $node->nid, array(
        'attributes' => array('target' => '_blank'),
        'absolute'   => TRUE,
        'html'       => TRUE,
      )); ?>
    <input type="hidden" name="nid" value="<?php print $node->nid; ?>"> <input type="hidden" name="lang"
                                                                               value="<?php print $language->prefix ? '/' . $language->prefix : ''; ?>">
    <table width="100%">
      <?php foreach ($node->choices as $choice) : ?>
        <?php $percents = $node->votecount ? 100 * $choice['votes'] / $node->votecount : 0; ?>
        <tr>
          <td colspan=2><input type="radio" name="chid" id="chid-<?php print $choice['chid']; ?>"
              <?php if ($choice['chid'] == $node->vote) {
                print 'checked';
              } ?>
                               value="<?php print $choice['chid']; ?>"><label
              for="chid-<?php print $choice['chid']; ?>"><?php print $choice['chtext']; ?></label></td>
        </tr>
        <tr data-width="<?php print intval($percents); ?>%" data-percent="<?php print number_format($percents, 2); ?>"
            data-votes="<?php print $choice['votes']; ?>" data-count="<?php print $node->votecount + 1; ?>"
            class="vote-results vote-results-<?php print $choice['chid']; ?>">
          <td class="percent-bar-wrapper">
            <div class="percent-bar" style="width:<?php print intval($percents); ?>%">&nbsp;</div>
          </td>
          <td class="percent">
            <nobr><b><?php print $choice['votes']; ?></b> (<span><?php print number_format($percents, 2); ?></span>%)
            </nobr>
          </td>
        </tr>
      <?php endforeach; ?>
    </table>
    <input type="button" value="<?php print t('Vote'); ?>">
  </div>
<?php endif; ?>
