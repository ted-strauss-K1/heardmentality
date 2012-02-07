<?php include "header.tpl.php"; ?>
<div class="contarea">
        <div class="popup-add-issue">
            <!--main div-->
            <div class="do-in2">
                <div class="do-intop"><?php print t('ADD AN ISSUE');?></div>
                <div class="inside2">
                    <div id="err" class=""></div>
                  
                    <div class="left"><strong>
                           <?php print t('Please follow'); ?> <?php print t('Heard Mentality\'s'); ?>,<br/>
                           <span class="ytex"><?php print t('Guidelines & Principles'); ?></span>
                           <?php print t('when creating a new issue'); ?></strong><br>
                            <strong><br>
                                   <?php print t('All issues should be'); ?> :   </strong>
                            <div class="creat"><ul>
                                    <li rel="Take pity on the reader – information<br/> should be presented in a non verbose manner. <br/>Pride should be taken from wording things concisely.<br/> This will ensure users can consume and retain<br/> a larger amount of information as well as making technical <br/>features like the translations and search more effective. <br/>Studies also show that more people will stop to read a shorter comment and more likely to pass over longer ones. ones."><?php print t('Concise'); ?></li>
                                    <li rel="No profanity please. Consider all users when choosing your language. <br/>People take the posting more seriously when <br/>it refrains from using harsh and negative words.<br/> Also, abbreviations should be avoided as other users <br/>or the translation feature may not understand."><?php print t('Clean'); ?></li>
                                    <li rel="Pleased do not repeat anything that has been already posted.<br/> Any duplicate content dilutes the overall accuracy of the compiled information.<br/> Any new issue or posting added to Heard Mentality should be<br/> significantly different than existing content. Good practice would be to “agree” <br/>with the posting you may want to reiterate or <br/>voting on the issue that already exists - <br/>this will ultimately draw more attention to it."><?php print t('Original'); ?></li>
                                    <li rel="This is the fundamental rule to make any social community work. <br/>Please treat others like you would like to be treated yourself <br/>and you in return will get the same."><?php print t('Golden Rules'); ?></li>
                                    <li rel="Issues should be classifiable into the provided high level sections.<br/> Please do not post issues that could be considered <br/>unimportant, for example: The hairdo of a certain<br/> celebrity or which restaurant or movie is best.<br/> While these may be important questions, these are not the types of issues to be discussed here."><?php print t('Important'); ?></li>
                                    <li rel="Issues should be posted in an unbiased and non-leading way.<br/> Issues should be posed simply and direct. All realistic possible answers should be introduced."><?php print t('Unbiased'); ?></li>

                                </ul></div>
                           <div class="clr"></div><br />
                            <div>When you submit Issues that are unique,
                                clear, popular and require no editing, you can
                                <strong>win a badge.</strong></div><br />
                             <?php
                             global $user;
                             if (is_array($user->roles) && in_array('administrator', $user->roles)){
                             ?>
                             <div class="clr" id="dupe-issue-area" style="font-weight:bold;color:black"><?php print t('Dupe questions'); ?>:</div>

                             <div id="inside_content"></div>
                             <?php }?>
                    </div>
                    <div class="right" id="qform">
                     
                        <div class="clr"></div>
<?php print $content; ?>
                        <div class="clr"></div>

                    </div>
                </div>
            </div></div>
</div>

   <?php include "footer.tpl.php"; ?>

