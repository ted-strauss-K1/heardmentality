<br class="clear"><br><br>
	<div class="line-bottom2"></div>
	<div id="footer">
	  <div class="container">
			<div class="two columns">
				<div class="black-box">
					<a class="facebook" href=""></a>
					<br>
					<a class="twitter" href=""></a>
				</div>
			</div>
			<div class="eight columns">
  			<div class="black-box">
					<?php 
                                        if($user->uid != ''|| $user->uid != '0'){
                                        if($profile_options_bottom): print $profile_options_bottom; endif;
                                        }else{ ?>
                                            <div class="foot-empty">
                                            <div class="profile-meta footerfloat"><p><?php print t('Please Login to view your profile details'); ?></p></div>
                                            </div>
                                        <?php }?>
				</div>
  		</div>

  		<div class="six columns">
  			<div class="black-box">
					<img src="<?php print $directoryPath;?>/images/dark_logo.png" class="dark-logo">
					<ul class="din foot-link">
						<li><a href="">ABOUT</a></li>
						<li><a href="">CONTACT</a></li>
						<li><a href="">DONATE</a></li>
						<li><a href="">VOLUNTEER</a></li>

					</ul>

  			</div>

  		</div>
			<a rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/" style="float:right;margin:0px 10px 0px 10px"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/3.0/88x31.png" /></a>
			<p class="policy"> HEARD MENTALITY &copy; 2011<br><a>Legal</a><a>Privacy</a><a>User Agreement</a></p>
		</div>

	</div>

        <!-- gigya login / logout -->
<!-- ui-dialog -->
        <?php if($user->uid != ''|| $user->uid != '0'){
            print $profile_option_block;
         }else{?>
        <div id="dialog" title="Login" class="dialog">
        <p>Login to Heard Mentality using one of your favorite Social network logins</p>
        <script type="text/javascript">
        var conf=
        {
                APIKey: '<?php echo $apikey; ?>'
                ,enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,orkut,wordpress,typepad,verisign,openid,netlog,bloglines,signon,mixi,livedoor'
        }
        </script>
        <script type="text/javascript">
        var login_params=
        {
                useHTML: 'false'
                ,showTermsLink: 'false'
                ,height: 50
                ,width: 280
                ,containerID: 'componentDiv'
                ,useFacebookConnect: 'true'
                , redirectURL:'<?php print $base_url;?>openids/save'
                ,facepilePosition: 'top'
        }
        </script>
        <div id="componentDiv" style="margin:0px 0px 0px 5px"></div>
        <script type="text/javascript">
           gigya.services.socialize.showLoginUI(conf,login_params);
        </script>
        <?php }?>
	</div>
<!-- gigya login / logout ends -->
<!-- JS
================================================== -->


	<script>window.jQuery || document.write("<script src='<?php echo $directoryPath; ?>/javascripts/jquery-1.6.2.min.js'>\x3C/script>")</script>

	<script src="<?php echo $directoryPath; ?>/javascripts/app.js"></script>