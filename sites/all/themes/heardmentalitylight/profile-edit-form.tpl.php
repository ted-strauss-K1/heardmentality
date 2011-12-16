<?php
//echo '<pre>'; print_r($form); exit;
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);


// get hidden values
print drupal_render($form['country']);
print drupal_render($form['state']);
print drupal_render($form['city']);
print drupal_render($form['img_avt']);
print drupal_render($form['image']);
print drupal_render($form['oldimg']);
print drupal_render($form['current_image']);

?>
<div class="twelve columns">
<h2 class="dinbold page-title"><?php print t('EDIT PROFILE'); ?></h2>
			<div class="grey-box">
                            <br />
<h2 class="din"><?php print t('Profile Settings'); ?></h2>
<div class="privacy-info">
    <p><strong><?php print ('Privacy'); ?></strong>
    <br><?php print t('Set the privacy levels for each of your profile characteristics. If you choose to hide your profile details, your demographic info will still be calculated but not shown.'); ?></p></div>
    <div class="user-info">
        <br>
        <ul class="user-info-inputs">
            <hr class="short">
            <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Username'); ?> <small class="red"><br><?php print '('.t('Required').')' ;?></small></span></label>
                <?php print drupal_render($form['username']); ?>
                <div class="visible-to"><?php print t('Visible to'); ?>:</div>
                <ul class="privacy">
                        <fieldset>
                        </fieldset>
                </ul>
            </li>
            <hr class="short-2">
            <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Name'); ?></span></label>
                <?php print drupal_render($form['fname']); ?>

                <div class="visible-to"><?php print t('Visible to'); ?>:</div>
                <ul class="privacy">
                        <fieldset>
                            <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['real_name_privacy']); ?>
                                

                        </fieldset>
                </ul>
             </li>
             <hr class="short-2">
             <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Email'); ?></span></label>
                <?php print drupal_render($form['email']); ?>
                        <div class="visible-to"><?php print t('Visible to'); ?>:</div>
                        <ul class="privacy">
                                <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('Followers'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('No one'); ?></span>
                                    </li> 
                                    <?php print drupal_render($form['mail_privacy']); ?>


                                </fieldset>
                        </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Gender'); ?></span></label>
                 <?php print drupal_render($form['gender']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Followers'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('No one'); ?></span>
                                </li>    
                                <?php print drupal_render($form['gender_privacy']); ?>

                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Year of Birth'); ?></span></label>
                 <?php print drupal_render($form['dob']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Followers'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('No one'); ?></span>
                                </li>   
                              <?php print drupal_render($form['dob_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Zip/Postal Code'); ?></span><br />
                <?php print drupal_render($form['city-state-country']); ?>
                </label>
                 <?php print drupal_render($form['zip']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('Followers'); ?></span>
                                    </li>
                                    <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                         <span class="privacy-answer"><?php print t('No one'); ?></span>
                                    </li>
                                    <?php print drupal_render($form['zip_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Religion'); ?></span></label>
                 <?php print drupal_render($form['religion']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('Followers'); ?></span>
                                </li>
                                <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                     <span class="privacy-answer"><?php print t('No one'); ?></span>
                                </li>
                                <?php print drupal_render($form['religion_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Ethnicity'); ?></span></label>
                 <?php print drupal_render($form['ethnic']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['ethnic_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Education'); ?></span></label>
                 <?php print drupal_render($form['education']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                             <?php print drupal_render($form['edu_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Sexual Orientation'); ?></span></label>
                 <?php print drupal_render($form['sorient']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['sorient_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Household Income'); ?></span></label>
                 <?php print drupal_render($form['income']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                            
                            <li style="float:left;margin:-8px 0px 0px 30px">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <div style="float:left;margin: -1px 0 0 -61px;"><?php print drupal_render($form['income_privacy']); ?></div>
                            
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Marital Status'); ?></span></label>
                 <?php print drupal_render($form['marital']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['marital_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Bio'); ?></span></label>
                 <?php print drupal_render($form['bio']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['bio_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Homepage URL'); ?></span></label>
                 <?php print drupal_render($form['myweb']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['mywebsite_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Facebook URL'); ?></span></label>
                 <?php print drupal_render($form['facebook']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['facebook_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <li>
                <label for="" class="add-on-2"><span class="title-2"><?php print t('Twitter URL'); ?></span></label>
                 <?php print drupal_render($form['twitter']); ?>
                    <div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
                            <fieldset>
                                    <li class="privacy-rules" title="<?php print t('Anyone can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only logged-in users can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Logged-in'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('Only followers can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('Followers'); ?></span>
                            </li>
                            <li class="privacy-rules" title="<?php print t('No one can see this piece of information'); ?>">
                                 <span class="privacy-answer"><?php print t('No one'); ?></span>
                            </li>
                            <?php print drupal_render($form['twitter_privacy']); ?>
                            </fieldset>
                    </ul>
                </li>
                <hr class="short-2">
                <div class="follow-links">
                <?php print drupal_render($form['follow_links']); ?>
                </div>
               
        </ul>
        <div class="clear"></div>
		
	  	<?php print drupal_render($form['submit']); ?>
	  	<div class="clear"></div>
	  				
		<div class="clear"></div>
                
    </div>
</div>
	</div>
            <div class="four columns">
			<br><br>
			<div class="dark-grey-box ">
				<div class="profile-meta">
					<div class="icon photo text"></div>
					<label for="profile" class="profile"><?php print t('CHANGE PHOTO'); ?></label>
                                        <?php print drupal_render($form['file_upload']);?>
                                        <div class="clear"></div>
                                        <div id="brow_img_name"></div>
                                        <p>...<?php print t('or choose a picture'); ?><a href="#" id="dialog_link-pic" title="Pick a photo"> <?php print t('Here'); ?> </a></p>                                        
					<input type="submit" value="Submit" class="submit-issue leftfloat" id="submit_brow-avat" />
					<br class="clear">
				</div>
			</div>


			<div class="grey-box">
				<label for="" class="subscriptions"><?php print t('Social Integration'); ?></label>
				<p class="twelve"><?php print t('Stay logged into these accounts'); ?></p>
				 <?php print drupal_render($form['merge']); ?>
			</div>
			<div class="grey-box">
				<label for="" class="subscriptions"><?php print t('Subscriptions'); ?></label>
				<p class="twelve"><?php print t('Send me a summary'); ?></p>
				<ul class="subscription">
					<fieldset>
						<li>
							<span class="privacy-answer"><?php print t('Never'); ?></span><br>
						  
						</li>
						<li>
						  <span class="privacy-answer"><?php print t('Monthly'); ?></span><br>
							
						</li>
						<li>
							<span class="privacy-answer"><?php print t('Weekly'); ?></span><br>
						  
						</li>
						
						<?php print drupal_render($form['notify']); ?>
                                                <br class="clear"><br>
                                                <?php print drupal_render($form['subscription_email']); ?>
						<input type="submit" value="Submit" class="submit-issue leftfloat" />
					</fieldset>
				</ul>
				<div class="clear"></div>
			</div>
                        <div class="grey-box">
				<label for="" class="subscriptions"><?php print t('Language Settings'); ?></label>
				<p class="twelve"><?php print t('Set your default language'); ?></p>
				 <?php print drupal_render($form['default_language']); ?>
                                <br class="clear">
                                <br class="clear">
			</div>
		</div>

<div id="dialog-profile-pic" title="Pick a Profile Photo" class="dialog">
		<?php print drupal_render($form['picture']['select_avatar']);?>
    <input type="submit" value="Submit" class="submit-issue leftfloat" onclick="update_avatar();" />
</div>