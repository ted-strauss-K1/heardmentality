<?php include "header.tpl.php"; ?>
<!--content area-->
<div class="contarea">
    <div class="refine-search">
        <?php if (! empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
            <?php print $left; ?>
        </div>
        <!-- /sidebar-left -->
        <?php endif; ?>
    </div>
     <div class="issuesearch3">
        <h1>SEARCH RESULTS</h1>
        <div id="qfilter">
        <?php print $content; ?>
        </div>
    </div>
    <div class="contributer">
        <?php if (! empty($right)): ?>
        <div id="sidebar-right" class="column sidebar">
            <div class="hm-cen">
            <?php print $right; ?>
            </div>
        </div>
        <!-- /sidebar-right -->
        <?php endif; ?>
    </div>
    <div class="clr">
    </div>
</div>
<?php include "footer.tpl.php"; ?>
