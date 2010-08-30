<?php include "header.tpl.php"; ?>
<!--content area-->
<div class="contarea">
    <div class="fact">
        <?php if (! empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
            <?php print $left; ?>
        </div>
        <!-- /sidebar-left -->
        <?php endif; ?>
    </div>
    <div class="inner-page-cont">
        <span class="padding10"><h3>SEARCH RESULTS</h3></span>
        <?php print $content; ?>
    </div>
    <div class="commu">
        <?php if (! empty($right)): ?>
        <div id="sidebar-right" class="column sidebar">
            <?php print $right; ?>
        </div>
        <!-- /sidebar-right -->
        <?php endif; ?>
    </div>
    <div class="clr">
    </div>
</div>
<?php include "footer.tpl.php"; ?>
