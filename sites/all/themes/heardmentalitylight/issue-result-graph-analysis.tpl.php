<div id="results">
  <h2 class="din"><?php print t('Results'); ?></h2>
  <div class="vote-results">
    <ul>
      <li class="part">

        <p class="result-title dinbold"><?php print t('by'); ?></p>
        <div class="inner filter"><?php print $report_percent; ?></div>
		
      </li>
      <li class="part">
	  
        <p class="result-title dinbold"><?php print t('Quick facts'); ?></p>
        <div id="insight-view" class="inner">
          <?php print $insight_view; ?>
        </div>
		
      </li>
	  <li class="full">
	  
		<p class="result-title dinbold"><?php print t('Legend'); ?></p>
		<div class="inner legend">
			<dl>
				<dd>Name variant 1</dd><dt>color</dt>
				<dd>Name variant 2</dd><dt>color</dt>
				<dd>Name variant 3</dd><dt>color</dt>
				<dd>Name 4</dd><dt>color</dt>
				<dd>Name variant 5</dd><dt>color</dt>
			</dl>
		</div>
		
	  </li>      
	  <li class="part">
	  
        <p class="result-title dinbold"><?php print t('Vote history'); ?></p>
        <div class="inner graf"><?php print $report_graph; ?></div>
		
      </li>
      <li class="part">

        <p class="result-title dinbold"><?php print t('Vote map'); ?></p>
        <div class="inner map"><?php print $map; ?></div>

      </li>
    </ul>
  </div>
</div>
