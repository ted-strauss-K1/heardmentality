<?php
global $apikey, $gSitePath;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
//echo '<pre>';print_r($node); exit;
?>



                <div class="clear"></div>
                <div id="vote-msg-alert-<?php print $tnid; ?>" class="v-msg"></div>
                <h2 class="din half"><a href="<?php print $node_url; ?>" title="permalink" class="issue-title"><?php print t($title); ?>?</a></h2>
                <br>
                <div class="poll-vote-area">
                <?php if($allowvotes == 1){
                    $display = 'style="display: none;"';
                }?>
                    <div class="vote-count-poll" <?php print $display; ?> id="vote-count-poll-<?php print $tnid; ?>">
                               <?php foreach($indVoteCounts as $chorder => $vcount){?>
                               <div class="post-vote-result"><span class="vote-count dinbold" id="<?php print $tnid; ?>-chorder-<?php print $chorder; ?>"><?php print $vcount; ?></span><br><span class="vote-count-title din">votes</span></div>
                               <br class="clear" />
                               <?php }?>
                    </div>
                
                <div class="voting-pane" id="voting-pane-<?php print $tnid; ?>"><?php print $content;?></div>
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
                <p class="issue-meta"><a><span id="tot-count-<?php print $tnid; ?>"><?php print $votecount;?></span> <?php print t('Votes');?></a> / <a><?php print $totaldebates;?> <?php print t('Arguments');?></a> / <a><?php print $totalresources;?> <?php print t('References');?></a> </p>
<!--                <a href="#" class="button vote floatright">Vote</a>-->
                <br class="clear">
                 <?php if($allowvotes != 1){ ?>
                <br class="clear">
                <a class="button stats stats-quick" title="See the Debate Statistics" href="<?php print $node_url; ?>#statistic-analysis"><span class="icon stats "></span></a>
                <?php }?>


                <hr>
                <div class="clear"></div>
                
                






