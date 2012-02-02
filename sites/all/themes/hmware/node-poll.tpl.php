<?php
// $Id: node.tpl.php,v 1.4.2.1 2009/08/10 10:48:33 goba Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */
global $apikey, $gSitePath, $theme;

 $path=$gSitePath.  drupal_get_path('theme',$theme);
 $node=node_load(array('nid'=>$nid));
?>

<!-- socialize.js script should only be included once -->
<!--<script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=<?php echo $apikey; ?>"></script>-->

<script type="text/javascript">
    var conf =
        {
        APIKey:'<?php print $apikey; ?>'
    };

    function onLoad()
    {
        gigya.services.socialize.getUserInfo(conf,{callback:renderUI});


        gigya.services.socialize.addEventHandlers(conf, { onConnect:renderUI, onDisconnect:renderUI}   );

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


<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) {
    print ' sticky';
} ?><?php if (!$status) {
        print ' node-unpublished';
    } ?> clear-block">

    <?php print $picture ?>

<?php if (!$page): ?>
      <div class="titl"> <a style="<?php print $style; ?>" href="<?php print $gSitePath; ?>qlite/view/<?php print $nid ?>?ajax=1" title="<?php print $title ?>"><?php print rtrim($title, "?"); ?>? </a></div>
<?php endif; ?>
<?php if($page): ?>
        <div class="flag-issue"><div class="but-left"><img src="<?php print $path; ?>/images/but-left.jpg"></div>
             <a title="Flag" class="but butnew share-link"  onclick="formsubmittype(3,<?php print $nid; ?>);" href="javascript:void(0);"><img  src="<?php print $path; ?>/images/flag.png" alt="flag" /></a>
             &nbsp; <?php print t('Flag this Issue');?>
             <div class="but-right">
           <img width="7" height="24" src="<?php print $path; ?>/images/but-right.jpg"></div></div>
      <div class="clr"></div>
            <div>
              <div class="issue-title"><?php print rtrim($title, "?"); ?>? </div>
            </div>
      <div class="quesin">
              <div class="quesinner">
                <div class="quesinnerr">

<?php endif; ?>
    <div class="meta">
        <?php if ($submitted): ?>
            <span class="submitted"><?php //print $submitted ?></span>
        <?php endif; ?>

<?php if ($terms): ?>
                <div class="terms terms-inline"><?php //print $terms ?></div>
        <?php endif; ?>
            </div>
            <?php if($page):?>
            <div class="issue_left">
            <div class="context">
                <div class="sub-title"><?php print t('Context'); ?></div>
                <?php print t($context); ?>
            </div>
            <div class="clr"></div>

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
                        
<div id="shareDiv"></div>
<script type="text/javascript">
   gigya.services.socialize.showShareBarUI(conf,showShareBarUI_params);
</script>
            </div>
            <?php endif; ?>
             <div class="issue_right">
                <div class="content">
                    <div class="sub-title">Vote</div>
                        <?php print $content ?>
                </div>
                 <div class="clr"></div>
<!--                <div  class=""><div class="but-left"><img src="<?php print $path; ?>/images/but-left.jpg"></div>
                  <a class="but butnew share-link" title="<?php print t('Suggest a new answer'); ?>"   onclick="formsubmittype(4,<?php print $nid; ?>);" href="javascript:void(0);"><?php print t('Suggest a new answer'); ?></a>
    <div class="but-right">
               <img width="7" height="24" src="<?php print $path; ?>/images/but-right.jpg"></div></div>-->

                <span> Wait! I want to&nbsp;<a href="javascript:void(0);" id="sugg-btn">suggest a different answer</a></span>
                <div id="sugg-form" class="sugg-form" style="display:none;"><?php print $suggest; ?></div><br /><br />
            </div>
<?php //print $links; ?>
                    <?php if($page): ?>
</div></div>

</div>
     <?php endif; ?> </div>