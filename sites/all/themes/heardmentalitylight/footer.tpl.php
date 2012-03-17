<?php
// root path
    /**Rallydev:503**/
    global $base_url;
	/**/
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<br class="clear"><br><br>
	<div class="line-bottom2"></div>
	<div id="footer">
	  <div class="container">
			<div class="four columns">
				<div class="black-box">
					<p class="blurb ryde"><?php print t('Be Heard. Don\'t Be Part of the Herd!'); ?></p>
					<hr class="dark">
					<div class="floatleft"><a class="twitter" href=""></a></div>
					<div class="floatleft"><a class="facebook" href=""></a>	</div>
					<div class="clear"></div>
				</div>
			</div>
			<div class="seven columns">
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

  		<div class="five columns">
  			<div class="black-box">
                            <a href="<?php print $front_page; ?>"><img src="<?php print $directoryPath;?>/images/dark_logo.png" class="dark-logo"></a>
					<ul class="din foot-link">
						<li><a href="<?php print $sitelink;?>aboutus"><?php print t('ABOUT'); ?></a></li>
						<li><a href="<?php print $sitelink;?>node/305"><?php print t('CONTACT'); ?></a></li>
						<li><a href="<?php print $sitelink;?>donation"><?php print t('DONATE'); ?></a></li>
						<li><a href=""><?php print t('VOLUNTEER'); ?></a></li>

					</ul>

  			</div>

  		</div>
			<a rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/" style="float:right;margin:0px 10px 0px 10px"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/3.0/88x31.png" /></a>
			<p class="policy"> <?php print t('HEARD MENTALITY'); ?> &copy; 2011<br><a><?php print t('Legal'); ?></a><a><?php print t('Privacy'); ?></a><a><?php print t('User Agreement'); ?></a></p>
		</div>

	</div>

        <!-- gigya login / logout -->
<!-- ui-dialog -->
        <?php if($user->uid != ''|| $user->uid != '0'){
            print $profile_option_block;
         }else{
           ?>




<div id="dialog">
   <ul>
      <li><a href="#tabs-1">Log in</a></li>
      <li><a href="#tabs-2">Sign up</a></li>
   </ul>

        <div id="tabs-1" title="Login" class="dialog">
          <div id="user-login">

      	  </div>
          <p><?php //print t('Or login to Heard Mentality using one of your favorite Social network logins'); ?></p>
          
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
                , redirectURL:'<?php print $base_url;?>/openids/save'
                ,facepilePosition: 'top'
        }
        </script>
        <div id="componentDiv"></div>
        <script type="text/javascript">
           gigya.services.socialize.showLoginUI(conf,login_params);
        </script>
        <?php }?>
        
        
             <div class ="gigya-login"> </div>
	</div>
  
     <div id="tabs-2">
    <div id ="user-register"> 
    
    </div>
       
       <div class ="gigya-login"></div>
   </div>
  
  </div>
<?php print $closure; ?>
<!-- gigya login / logout ends -->
<!-- JS
================================================== -->


	<script>window.jQuery || document.write("<script src='<?php echo $directoryPath; ?>/javascripts/jquery-1.6.2.min.js'>\x3C/script>")</script>

	<script src="<?php echo $directoryPath; ?>/javascripts/app.js"></script>