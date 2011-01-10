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
         	<div class="debate-cor-inner">
            	<div>
                        <div class="debate-cor-inner-left">
                        <img width="33" height="28" alt="Goat-thumb" src="<?php echo $directory; ?>/images/cor-goat.jpg">
                        </div>
                        	<div class="debate-cor-inner-right">
                            	<ul>
                                	<li>Citizen <br><span>51,730</span></li>
                                    <li><img width="10" height="10" alt="Gold" src="<?php echo $directory; ?>/images/cor-gold.jpg"><br><span>20</span></li>
                                    <li><img width="10" height="10" alt="Silver" src="<?php echo $directory; ?>/images/cor-silver.jpg"><br><span>5</span></li>
                                    <li><img width="10" height="10" alt="Gray" src="<?php echo $directory; ?>/images/cor-gray.jpg"><br><span>18</span></li>
                                </ul>

                            </div>
                 </div>

                 	<div class="clr"></div>



                <div class="clr"></div>
            </div>


             <div class="clr"></div>
            </div>

            <div class="debate-second-2">
              <ul>
               <li><img width="16" height="16" alt="Ctegory" src="<?php echo $directory; ?>/images/category.png"> <span>X 32</span></li>
              	<li><img width="16" height="16" alt="Coins" src="<?php echo $directory; ?>/images/coins.png"> <span>X 32</span></li>
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

