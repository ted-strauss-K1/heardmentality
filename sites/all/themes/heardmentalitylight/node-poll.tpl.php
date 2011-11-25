<?php
global $apikey, $base_path, $theme, $base_url;
$gSitePath = $base_path.'/';
 $path=$gSitePath.  drupal_get_path('theme',$theme);
 $node=node_load(array('nid'=>$nid));
?>

<script type="text/javascript">
   



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




                        
                        <a class="icon flag" title="flag this issue" rel="lightframe"  href="<?php print $base_url; ?>/qlite/flag/<?php print $nid;?>"></a>
                        <h2 class="din"><?php print t(rtrim($title, "?")); ?>?</h2>
                        <p class="description"><?php print t($context); ?>&nbsp;<a>[...]</a></p>
                        <div class="clear"></div>
                        <div class="issue-things">


                        </div>

                        <?php print $content ?>
                        
                        <br class="clear">
                        <div class="expanding">
                          <h6 class="wait">... <?php print t('Or submit a different answer'); ?></h6>
                          <?php print $suggest; ?>
                        </div>
                        <div id="shareDiv" class="floatright"></div>

                        


<?php
$nodepath = 'node/'.$nid;
$pagePath = url($nodepath, array('absolute' => TRUE)).'/'; ?>
<script type="text/javascript">
var act = new gigya.services.socialize.UserAction();
act.setUserMessage("Your comment here...");
act.setTitle("<?php print t($title); ?>");
act.setDescription("<?php
                    $context = str_replace(array("\r", "\n"), '', $context);
                 print t(htmlentities($context));?>");
act.setLinkBack("<?php print $pagePath; ?>");
act.addActionLink("<?php print t($title); ?>","<?php print $pagePath; ?>");

var showShareBarUI_params=
{
  containerID: 'shareDiv',
  shareButtons: 'Facebook-Like,google-plusone,Share,Twitter',
  userAction: act
}
</script>


<script type="text/javascript">
   gigya.services.socialize.showShareBarUI(conf,showShareBarUI_params);
</script>
           