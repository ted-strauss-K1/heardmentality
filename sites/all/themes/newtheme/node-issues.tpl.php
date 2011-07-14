<?php
global $apikey, $gSitePath;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>

<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) {
    print ' sticky';
} ?><?php if (!$status) {
        print ' node-unpublished';
    } ?> clear-block">

    <?php print $picture ?>

<?php if (!$page): ?>
      <div class="titl"> <?php print rtrim($title, "?"); ?>? </div>
<?php endif; ?>
<?php if($page): ?>
<div>
              <h2 style="<?php print $style; ?>"><?php print rtrim($title, "?"); ?>? </h2>
            </div>          <div class="quesin">
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

            <div class="content">
<?php print $content ?>
                </div><br />
                <?php $url = drupal_get_path_alias('node/'.$nid);?>
                <div><a href="<?php print $sitelink.$url?>"><?php print t('Click');?></a>&nbsp;<?php print t('to see full Issue page with debate and references');?></div>
                <div><b><?php print t('Subject');?>:</b>&nbsp;<?php print $catsubject;?>&nbsp;<b>|</b>&nbsp;
                    <b><?php print t('Area');?>:</b>&nbsp;<?php print $catarea;?>&nbsp;<b>|</b>&nbsp;
                    <b><?php print t('Detail');?>:</b>&nbsp;<?php print $catdetail;?>&nbsp;
                </div>
                <div><?php print $votecount;?>&nbsp;<?php print t('votes');?>&nbsp;<b>|</b>&nbsp;
                    <?php print $totaldebates;?>&nbsp;<?php print t('arguments');?>&nbsp;<b>|</b>&nbsp;
                    <?php print $totalresources;?>&nbsp;<?php print t('references');?>&nbsp;
                </div><br />
                
<?php //print $links; ?>
                    <?php if($page): ?>
</div></div>

</div>
     <?php endif; ?> </div>

<hr />