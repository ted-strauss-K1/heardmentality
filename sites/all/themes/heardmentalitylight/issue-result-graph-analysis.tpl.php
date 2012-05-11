<div id="results">
  <h2 class="din"><?php print t('Results'); ?></h2>
  <div class="vote-results">
    <ul>
      <li class="part"><div class="space">

        <p class="result-title dinbold" style="width: auto; padding: 2px 8px 0 0;"><?php print t('by'); ?></p>
        <div class="inner filter"><?php print $report_percent; ?></div>
		
      </div></li>
      <li class="part margin"><div class="space">
	  
        <p class="result-title dinbold"><?php print t('Quick facts'); ?></p>
        <div id="insight-view" class="inner">
          <?php print $insight_view; ?>
        </div>
		
      </div></li>
	  <li class="full"><div class="space">
	  
		<p class="result-title dinbold"><?php print t('Legend (short answers)'); ?></p>
		<div class="inner legend">
                  
                  <?php foreach ($short_answers as $answer) { ?>
              
			<dl><dd><?php print $answer['name'] . ':'?></dd><dt style="background-color: <?php print $answer['color']?>;">color</dt></dl>
			
                  <?php } ?>
		</div>
		
	  </div></li>
	  <li class="part"><div class="space">
	  
        <p class="result-title dinbold"><?php print t('Vote history'); ?></p>
        <div class="inner graf"><?php print $report_graph; ?></div>
		
      </div></li>
      <li class="part margin"><div class="space">

        <p class="result-title dinbold"><?php print t('Vote map'); ?></p>
        <div class="inner map"><?php print $map; ?></div>

      </div></li>
    </ul>
  </div>
</div>
