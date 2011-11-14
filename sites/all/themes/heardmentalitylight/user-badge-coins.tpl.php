<?php
global $user;
$directoryPath = $base_path . $directory;
?>
<div class="medals">
            <div class="medal quick-profile" ><span class="gold" id="medal1" title="<?php print t('Gold Medals');?>">&nbsp;</span><?php print $badges['gold'];?></div>
            <div class="medal quick-profile" ><span class="silver" id="medal2" title="<?php print t('Silver Medals');?>">&nbsp;</span><?php print $badges['silver'];?></div>
            <div class="medal quick-profile" ><span class="bronze" id="medal3" title="<?php print t('Bronze Medals');?>">&nbsp;</span><?php print $badges['bronze'];?></div>
            <br class="clear">
            <img src="<?php print $directoryPath;?>/images/icons/coin.png" class="coin floatleft"> <p class="points" >  x <?php print $coins; ?> <span class="lighter" title="<?php print t('These are the points you use to vote etc...'); ?>">(?)</span></p>
    </div>
