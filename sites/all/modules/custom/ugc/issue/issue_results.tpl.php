<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
global $gSitePath,$theme,$apikey;
 $path=$gSitePath.  drupal_get_path('theme',$theme);
 $node=node_load(array('nid'=>$nid));
?>

<script>
    var conf =
        {
        APIKey:'<?php print $apikey; ?>'
    };

    function onLoad()
    {
        gigya.services.socialize.getUserInfo(conf,{callback:renderUI});


        gigya.services.socialize.addEventHandlers(conf, { onConnect:renderUI, onDisconnect:renderUI}   );

    }

    function showShareUI() {


        var act = new gigya.services.socialize.UserAction();

        act.setUserMessage("Your comment here...");


        act.setTitle("<?php print t($node->title); ?>");
        act.setDescription("<?php print t(trim(strip_tags($node->body))); ?>");


        act.setLinkBack("<?php print $gSitePath.request_uri(); ?>");


    act.addActionLink("<?php print t($node->title); ?>","<?php print $gSitePath.request_uri(); ?>");





        var params =
            {
            userAction: act,
            onError: onError,
            onSendDone: onSendDone,
            showEmailButton:true,
            showMoreButton:true
        };


        gigya.services.socialize.showShareUI(conf, params);

    }


    function onError(event) {
        alert('An error has occured' + ': ' + event.status + '; ' + event.statusMessage);
    }


    function onSendDone(event)
    {
        document.getElementById('status').style.color = "green";
        document.getElementById('status').innerHTML =
            'The newsfeed has been posted to: '
            + event.providers;
    }
    function formsubmittype(mtype,ids){
		jQuery("#txt_act").val(mtype);
		if(mtype==1)
		{


		document.getElementById('answer_frm').submit();
		}
		if(mtype==2)
		{

		load_invite(' <?php print $gSitePath; ?>invite/invite_friends?qid=<?php print $node->nid; ?>','Profile ');
		//onclick="load_invite('' . $gSitePath . 'c?qid=' . $qid . '','Profile');
		}
		if(mtype==3)
		{
		loadflagquestion('<?php print $gSitePath; ?>qlite/flag/'+ids,'Report ');

		}
		if(mtype==4)
		{
		loadsuggest('<?php print $gSitePath; ?>qlite/suggest/'+ids,'Answers ');

		}
		if(mtype==5)
		{
		window.location.href="<?php print $gSitePath; ?>mashup/<?php print $node->nid; ?>";

		}
		}
</script>
     <div class="sharing-section">
            <div  class="but-cont"><div class="but-left"><img src="<?php print $path; ?>/images/but-left.jpg"></div>
              <a title="Bookmark" class="but butnew share-link" onclick="showShareUI();" href="javascript:void(0);">
                 <img ALIGN=ABSMIDDLE title="Share" alt="<?php print t('Share'); ?>" src="<?php print $path; ?>/images/face-ic.jpg"/>&nbsp;
                    <?php print t('Share'); ?></a>
             <div class="but-right">
           <img width="7" height="24" src="<?php print $path; ?>/images/but-right.jpg"></div></div>
              <!-- <div class="share2">
            <a title="Invite" onclick="formsubmittype(2,<?php print $nid; ?>);" href="javascript:void(0);" class="share-link"> Invite</a>
             </div>-->
            <div  class=""><div class="but-left"><img src="<?php print $path; ?>/images/but-left.jpg"></div>
              <a class="but butnew share-link" title="<?php print t('Suggest a new answer'); ?>"   onclick="formsubmittype(4,<?php print $nid; ?>);" href="javascript:void(0);"><?php print t('Suggest a new answer'); ?></a>
<div class="but-right">
           <img width="7" height="24" src="<?php print $path; ?>/images/but-right.jpg"></div></div>
            <!-- <div class="share3">
        <a title="Create Mashup" class="share-link" onclick="formsubmittype(5,<?php print $nid; ?>);" href="javascript:void(0);">&lt;Embed&gt;</a>
             </div>-->
  <div  class=""><div class="but-left"><img src="<?php print $path; ?>/images/but-left.jpg"></div>
             <a title="Flag" class="but butnew share-link"  onclick="formsubmittype(3,<?php print $nid; ?>);" href="javascript:void(0);"><img  src="<?php print $path; ?>/images/flag.png" alt="flag" /></a>
              <div class="but-right">
           <img width="7" height="24" src="<?php print $path; ?>/images/but-right.jpg"></div></div>

            </div>
<div class="clr"></div>

<?php   if (!$logged_in || $allowvotes) { ?>

<div id="rotate">
<ul id="maintabs" class="mytabs" >
    <li class="current" id="in"><?php print l( t('Details'),'issue/tab/'.$nid.'/details',array('attributes' => array('title' => 'Info')) );?></li>
<li class=""><a id="AF" href='#' onClick="jQuery('#twitMsg').html('You must vote on the issue before you can see the results!');jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);jQuery(this).die('click');jQuery(this).unbind('click');return false;"><span ><?php print t('Reporting');?></span></a></li>
<li id="par1"><?php print l( t('Debate').'('.$cdebate.')','issue/tab/'.$nid.'/debate',array('attributes' => array('title' => 'Debate')) );?></li>
<li class="" id="par2"><?php print l( t('Resources').'('.$cresource.')','issue/tab/'.$nid.'/resource',array('attributes' => array('title' => 'Resource')) );?></li>
<li class=""><?php print l( t('Pundits').'('.$cpundit.')','issue/tab/'.$nid.'/guru',array('attributes' => array('title' => 'Gurus')) );?></li>

              </ul>
              <div class="mytabs-container" id="tabcontent">
            <?php print t('Loading. Please Wait...'); ?>
        </div><div class="clr"></div>
           </div>
<?php }else{ ?>

	<div id="rotate">
<ul id="maintabs" class="mytabs" >
<li class="current" id="in"><?php print l( t('Reporting'),'issue/tab/'.$nid.'/report',array('attributes' => array('title' => 'Report')) );?></li>
<li id="par1"><?php print l( t('Debate').'('.$cdebate.')','issue/tab/'.$nid.'/debate',array('attributes' => array('title' => 'Debate')) );?></li>
<li class="" id="par2"><?php print l( t('Resources').'('.$cresource.')','issue/tab/'.$nid.'/resource',array('attributes' => array('title' => 'Resource')) );?></li>
<li class=""><?php print l( t('Pundits').'('.$cpundit.')','issue/tab/'.$nid.'/guru',array('attributes' => array('title' => 'Gurus')) );?></li>
<li class="" id="in"><?php print l( t('Details'),'issue/tab/'.$nid.'/details',array('attributes' => array('title' => 'Info')) );?></li>
              </ul>
              <div class="mytabs-container" id="tabcontent">
          <?php print t('Loading. Please Wait...'); ?>
        </div><div class="clr"></div>
           </div>

<?php }  // print '<pre>';
//  var_dump(get_defined_vars());
//print '</pre>';
?>
