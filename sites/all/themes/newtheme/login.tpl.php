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
	,enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,orkut,wordpress,typepad,verisign,openid,netlog,bloglines,signon,mixi,livedoor'
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
 		    
       	  <div class="debate-outer">
            <div id="masterdiv">

	<div onclick="SwitchMenu('sub1')" class="menutitle">My Account</div>
    <div class="clr"></div>
	<span id="sub1" class="submenu" style="display: none;">
            <a href="<?php echo $gSitePath;?>profile" ><?php
				 $user_prof = db_fetch_object(db_query("SELECT first_name from {user_profile} where  uid=".$user->uid." "));
				if($user_prof->first_name=='')
				{
				 $unaprint= explode("@",$user->mail);
                                 if(!empty($unaprint[0]))
                                 echo $unaprint[0];
                                 else
                                    echo $user->name;

                 }
                 else
                 {
                echo myTruncate($user_prof->first_name,7,'..','..');

                 }
				 ?>
                 </a><br/>
		
		 <a onclick="loadeditquestion('<?php echo $gSitePath;?>edit','Edit Profile ');" href="javascript:void(0);">Edit Profile</a><br>
		 <a href="<?php echo $gSitePath?>mynotify">Notify </a><br>
                 <a  href="<?php echo $gSitePath; ?>logout">Sign Out</a>
	</span>

</div>
  
            <div class="clr"></div>
         	<?php 
                echo load_bubble($user->uid);
                $coins = $user->total_coins!=''?$user->total_coins:0;
                $notification = db_result(db_query("SELECT COUNT(nid) FROM {notification} WHERE uid = '".$user->uid."'"));
                ?>


             <div class="clr"></div>
            </div>

            <div class="debate-second-2">
              <ul>
               <li><img width="16" height="16" alt="Ctegory" src="<?php echo $directory; ?>/images/category.png"> <span>X <?php echo $notification;?></span></li>
              	<li><img width="16" height="16" alt="Coins" src="<?php echo $directory; ?>/images/coins.png"> <span>X <?php echo $coins;?></span></li>
                <li>Some text</li>

              </ul>

            </div>
            <div class="clr"></div>
<?php   $block= module_invoke('pcp', 'block', 'view', 'user'); print $block['content'];?>



    <script>
        function SwitchMenu(obj){
	if(document.getElementById){
	var el = document.getElementById(obj);
	var ar = document.getElementById("masterdiv").getElementsByTagName("span"); //DynamicDrive.com change
		if(el.style.display != "block"){ //DynamicDrive.com change
			for (var i=0; i<ar.length; i++){
				if (ar[i].className=="submenu") //DynamicDrive.com change
				ar[i].style.display = "none";
			}
			el.style.display = "block";
		}else{
			el.style.display = "none";
		}
	}
}


        </script>
			
            <?php
            endif;
			
			?>

