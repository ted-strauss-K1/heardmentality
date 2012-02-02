<?php include "header.tpl.php"; ?>
<!--content area-->
<div class="contarea">
    <div class="refine-search search-lay1-1">

        <?php if (!empty($left)): ?>
            <div id="sidebar-left" class="column sidebar">


            <?php print $left; ?>

        </div>
        <!-- /sidebar-left -->
        <?php endif; ?>



        </div>    
        <div class="user_search_3 search-lay1-2">
            <h1>SEARCH RESULTS</h1>
            <div id="ufilter">
            <?php print $content; ?>
        </div>
    </div>
    <div class="contributer search-lay1-3">
       	<div id="user_info">
            <div class="inner-commutop">
                <p>CONTRIBUTOR</p>

            </div>
            <div class="commu-profile" align="center" style="padding-top:10px">No User Selected!</div>

            <div class="clr"></div>

        </div>

        <!--content area close-->
    </div>
    <div class="clr">  </div>
</div>
<?php include "footer.tpl.php"; ?>
