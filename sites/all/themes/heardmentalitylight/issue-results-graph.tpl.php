<div id="results">
  <h2 class="din"><?php print t('Results'); ?></h2>
  <div class="vote-results">
    <?php if ($node->votes['#all'] < 10) : ?>
      <span class="no_show"><?php print t('We need 10 votes to show the results goodies, use the share links above  to let your peeps know.'); ?></span>
    <?php else : ?>
      <?php if ($node->uservoted) : ?>

      <ul>
        <li class="part">
          <div class="space">
            <div class="inner filter"><?php print $filter; ?></div>
          </div>
        </li>
        <li class="part margin">
          <div class="space">
            <p class="result-title dinbold"><?php print t('Quick facts'); ?></p>
            <div id="insight-view" class="inner"><?php print $insightview; ?></div>
          </div>
        </li>
        <li class="full">
          <div class="space">
            <p class="result-title dinbold"><?php print t('Legend'); ?></p>
            <div class="inner legend">
              <?php print $legend; ?>
            </div>
          </div>
        </li>
        <li class="part">
          <div class="space">
            <p class="result-title dinbold"><?php print t('Vote history'); ?></p>
            <div class="inner graf"><?php print $history; ?></div>
          </div>
        </li>
        <li class="part margin">
          <div class="space">
            <p class="result-title dinbold"><?php print t('Vote map'); ?></p>
            <div class="inner map"><?php print $gmap; ?></div>
          </div>
        </li>
      </ul>

      <?php else : ?>
        <span class="no_show"><?php print t('Vote now to show results.'); ?></span>
      <?php endif; ?>
    <?php endif; ?>
  </div>
</div>