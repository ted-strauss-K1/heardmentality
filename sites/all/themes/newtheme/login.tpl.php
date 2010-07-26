<?php 
		if($user->uid == ''|| $user->uid == '0'):

			  ?>
         <div class="loginvi"> <div class="btex"> <span class="black11">       Login via your social network:</span></div>
    
<!-- socialize.js script should only be included once -->
<script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=<?php echo $apikey; ?>"></script>
<script type="text/javascript">
var conf=
{
	APIKey: '<?php echo $apikey; ?>'
	,enabledProviders: 'facebook,twitter,myspace,yahoo,google,linkedin,liveid,aol'
}
</script>
<script type="text/javascript">
var login_params=
{
	useHTML: 'true'
	,showTermsLink: 'false'
	,height: 55
	,width: 150
	,containerID: 'componentDiv'
	,UIConfig: '<config><body><controls><snbuttons buttonsize="20"></snbuttons></controls><background background-color="#FFFFFF"></background></body></config>'
	,useFacebookConnect: 'true'
	, redirectURL:'<?php echo $gSitePath?>openids/save'
}
</script>
<div id="componentDiv"></div>
<script type="text/javascript">
   gigya.services.socialize.showLoginUI(conf,login_params);
</script>
</div>
  
 <?php
			 else:
			
			?>
 			
                    <div class="signin-name-outer">
        
        <div class="signout">
        <ul>
        <li> <p>Welcome <b><a href="<?php echo $gSitePath;?>profile" ><?php
				 $user_prof = db_fetch_object(db_query("SELECT real_name from {user_profile} where  uid=".$user->uid." "));
				if($user_prof->real_name=='')
				{
				 $unaprint= explode("@",$user->mail); 
				 echo $unaprint[0];
				 
                 }
                 else
                 {
                echo $user_prof->real_name;
				
                 }
				 ?>
                 </a></b></p>
       </li>
        <li>|</li>
        <li><a  href="<?php echo $gSitePath; ?>logout">Sign Out</a></li>
        <li>|</li>
        <li><a href="<?php echo $gSitePath?>mynotify">Notify </a></li>
        </ul>
        </div>
        </div><!--signin name outer-->
 
			
            <?php
            endif;
			
			?>