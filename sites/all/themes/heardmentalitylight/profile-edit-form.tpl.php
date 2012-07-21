<?php
//echo '<pre>'; print_r($form); exit;
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);


// get hidden values
//print drupal_render($form['country']);
print drupal_render($form['state']);
print drupal_render($form['city']);
print drupal_render($form['img_avt']);
print drupal_render($form['image']);
print drupal_render($form['oldimg']);
print drupal_render($form['current_image']);

?>
<div class="twelve columns">
	<h2 class="dinbold page-title"><?php print t('EDIT PROFILE'); ?></h2>
	<div class="grey-box clearfix" id="edit_profile">

		<h2 class="din"><?php print t('Profile Settings'); ?></h2>
		
		<div class="privacy-info">
			<p><strong><?php print t('Privacy'); ?></strong>
				<?php print t('Set the privacy levels for each of your profile characteristics. If you choose to hide your profile details, your demographic info will still be calculated but not shown.  No one will ever know.'); ?>
			</p>
		</div>
		
		<div class="user-info">

			<ul class="user-info-inputs clearfix">
				<li class="username">
					<label for="" class="add-on-2"><span class="title-2"><?php print t('Username'); ?> <small class="red">*</small></span></label>
					<?php print drupal_render($form['username']); ?>
				</li>

				<li>
					<label for="" class="add-on-2"><span class="title-2"><?php print t('Name'); ?></span></label>
					<?php print drupal_render($form['fname']); ?>

					<div class="visible-to"><?php print t('Visible to'); ?>:</div>
					<ul class="privacy">
							<fieldset>
								<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
									 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
								</li>
								<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
									 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
								</li>
								<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
									 <span class="privacy-answer"><?php print t('Followers'); ?></span>
								</li>
								<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
									 <span class="privacy-answer"><?php print t('No one'); ?></span>
								</li>
								<?php print drupal_render($form['real_name_privacy']); ?>
							</fieldset>
					</ul>
				 </li>
				 
				 <li>
					<label for="" class="add-on-2"><span class="title-2"><?php print t('Email'); ?></span></label>
					<?php print drupal_render($form['email']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div>
							<ul class="privacy">
									<fieldset>
										<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Followers'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('No one'); ?></span>
										</li> 
										<?php print drupal_render($form['mail_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Gender'); ?></span></label>
						 <?php print drupal_render($form['gender']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
										<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Followers'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('No one'); ?></span>
										</li>    
										<?php print drupal_render($form['gender_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2"><span class="title-2"><?php print t('Year of Birth'); ?></span></label>
						 <?php print drupal_render($form['dob']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
										<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Followers'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('No one'); ?></span>
										</li>   
									  <?php print drupal_render($form['dob_privacy']); ?>
									</fieldset>
							</ul>
					</li>
					
					<li class="country-info">
						<div class="c_wrapper">
							<label class="add-on-2 small">
								<span class="title-2"><?php print t('Country'); ?></span>
							</label>

							<div class="form-item">
								<?php print drupal_render($form['country']); ?>
							</div>
						</div>
						<div class="z_wrapper">
							<label class="add-on-2">
								<span class="title-2"><?php print t('Zip/Postal Code'); ?></span>
							</label>
							
							<div class="form-item">
								<?php print drupal_render($form['zip']); ?>
								<?php print drupal_render($form['city-state-country']); ?>
							</div>
						</div>
						
						<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
												 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
											</li>
											<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
												 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
											</li>
											<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
												 <span class="privacy-answer"><?php print t('Followers'); ?></span>
											</li>
											<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
												 <span class="privacy-answer"><?php print t('No one'); ?></span>
											</li>
											<?php print drupal_render($form['zip_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Religion'); ?></span></label>
						 <?php print drupal_render($form['religion']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
										<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										<span class="privacy-answer"><?php print t('Anyone'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('Followers'); ?></span>
										</li>
										<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
											 <span class="privacy-answer"><?php print t('No one'); ?></span>
										</li>
										<?php print drupal_render($form['religion_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Ethnicity '); ?></span></label>
						 <?php print drupal_render($form['ethnic']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['ethnic_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Education'); ?></span></label>
						 <?php print drupal_render($form['education']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									 <?php print drupal_render($form['edu_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Sexual Orientation'); ?></span></label>
						 <?php print drupal_render($form['sorient']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['sorient_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Household income'); ?></span></label>
						 <?php print drupal_render($form['income']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset id="income">
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['income_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2 small"><span class="title-2"><?php print t('Marital Status'); ?></span></label>
						 <?php print drupal_render($form['marital']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['marital_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2"><span class="title-2"><?php print t('Bio'); ?></span></label>
						 <?php print drupal_render($form['bio']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['bio_privacy']); ?>
									</fieldset>
							</ul>
					</li>
					
					<li>
						<label for="" class="add-on-2"><span class="title-2"><?php print t('My Homepage'); ?></span></label>
						 <?php print drupal_render($form['myweb']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['mywebsite_privacy']); ?>
									</fieldset>
							</ul>
					</li>
					
					<li>
						<label for="" class="add-on-2"><span class="title-2"><?php print t('Facebook URL'); ?></span></label>
						 <?php print drupal_render($form['facebook']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['facebook_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<li>
						<label for="" class="add-on-2"><span class="title-2"><?php print t('Twitter URL'); ?></span></label>
						 <?php print drupal_render($form['twitter']); ?>
							<div class="visible-to"><?php print t('Visible to'); ?>:</div><ul class="privacy">
									<fieldset>
											<li class="privacy-rules" title="<?php print t('Anyone in the world can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Anyone'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('All logged in users can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Logged in'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('Only followers can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('Followers'); ?></span>
									</li>
									<li class="privacy-rules" title="<?php print t('No one can see this piece of information about you'); ?>">
										 <span class="privacy-answer"><?php print t('No one'); ?></span>
									</li>
									<?php print drupal_render($form['twitter_privacy']); ?>
									</fieldset>
							</ul>
					</li>

					<!-- <div class="follow-links">
						<?php print drupal_render($form['follow_links']); ?>
					</div>-->
				   
			</ul>
			
			<?php print drupal_render($form['submit']); ?>
  
		</div><!-- /.user-info -->
	</div><!-- /.grey-box.edit_profile -->
</div><!-- /.twelve.columns -->

<div class="four columns">
	<div class="dark-grey-box top clearfix">
				<div class="profile-meta">
					<div class="icon photo text"></div>
					<label for="profile" class="profile"><?php print t('Change Photo'); ?></label>
                                        <?php print drupal_render($form['file_upload']);?>
                                        <div id="brow_img_name"></div>
                                        <p class="choose_pic">...<?php print t('or choose a picture'); ?><a href="#" id="dialog_link-pic" title="Pick a photo"> <?php print t('Here'); ?> </a></p>                                        
					<input type="submit" value="Submit" class="submit-issue leftfloat" id="submit_brow-avat" />
				</div>
	</div>

	<div class="grey-box full clearfix">
				<label for="" class="subscriptions"><?php print t('Social Integration'); ?></label>
				<p class="twelve"><?php print t('Stay logged in to these accounts - This makes sharing with your external networks easier.'); ?></p>
				 <?php print drupal_render($form['merge']); ?>
	</div>
	
	<div class="grey-box full clearfix">
				<label for="" class="subscriptions"><?php print t('Subscriptions'); ?></label>
				<p class="twelve"><?php print t('Send me a summary of what\'s happening on Heard Mentality to my email'); ?></p>
				<ul class="subscription">
						<li>
							<span class="privacy-answer"><?php print t('Never'); ?></span><br>
						  
						</li>
						<li>
						  <span class="privacy-answer"><?php print t('Monthly'); ?></span><br>
							
						</li>
						<li>
							<span class="privacy-answer"><?php print t('Weekly'); ?></span>
						  
						</li>
						
						<?php print drupal_render($form['notify']); ?>
                        <?php print drupal_render($form['subscription_email']); ?>
						<input type="submit" value="Submit" class="submit-issue leftfloat" />
				</ul>
	</div>
	
    <div class="grey-box full clearfix">
				<label for="" class="subscriptions"><?php print t('Language settings'); ?></label>
				<p class="twelve"><?php print t('Set your default language'); ?></p>
				 <?php print drupal_render($form['default_language']); ?>

	</div>
</div>

<div id="dialog-profile-pic" title="Pick a Profile Photo" class="dialog">
		<?php print drupal_render($form['picture']['select_avatar']);?>
		<input type="submit" value="Submit" class="submit-issue leftfloat" onclick="update_avatar();" />
</div>