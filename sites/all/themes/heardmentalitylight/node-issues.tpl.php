<?php
global $apikey, $gSitePath;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
//echo '<pre>';print_r($node); exit;
?>



                <div class="clear"></div>
                <h2 class="din half"><a href="<?php print $node_url; ?>" title="permalink" class="issue-title"><?php print t($title); ?>?</a></h2>
                <br>
                <div class="poll-vote-area">
                <?php if($indVoteCounts !='' && $allowvotes == '' ): ?>
                           <div class="vote-count-poll">
                               <?php foreach($indVoteCounts as $vcount){?>
                               <div class="post-vote-result"><span class="vote-count dinbold"><?php print $vcount; ?></span><br><span class="vote-count-title din">votes</span></div>
                               <br class="clear" />
                               <?php }?>
                           </div>
                <?php endif; ?>
                <div class="voting-pane"><?php print $content;?></div>
                </div>
<!--<ul class="vote">
                        <fieldset>
                                <li>
                      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 1" />No, ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam</label>
                                </li>
                                <li>
                      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 2" />Yes, on the other hand, we denounce with righteous indignation</label>
                                </li>
                                <li>
                      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 3" />Dunno, we denounce with righteous indignation</label>
                                </li>
                  </fieldset>
                </ul>-->
                <p class="issue-meta"><a><?php print $votecount;?> <?php print t('Votes');?></a> / <a><?php print $totaldebates;?> <?php print t('Arguments');?></a> / <a><?php print $totalresources;?> <?php print t('References');?></a> </p>
<!--                <a href="#" class="button vote floatright">Vote</a>-->
                <br class="clear">


                <br class="clear">


                <hr>
                <div class="clear"></div>
                
                






