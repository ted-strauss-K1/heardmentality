<?php include "header.tpl.php"; ?>
<!--content area-->
<div class="contarea">
    <div class="fact">

        <?php if (!empty($left)): ?>
            <div id="sidebar-left" class="column sidebar">


            <?php print $left; ?>

        </div>
        <!-- /sidebar-left -->
        <?php endif; ?>



        </div>    
        <div class="user_search_3">
            <span class="padding10">SEARCH RESULTS</span>
            <div id="ufilter">
            <?php print $content; ?>
        </div>
    </div>
    <div class="contributer">
       	<div id="user_info">
            <div class="inner-commutop">
                <p>CONTRIBUTOR</p>

            </div>
            <div class="inner" align="center" style="padding-top:10px">No User Selected!</div>

            <div class="clr"></div>

        </div>

        <!--content area close-->
    </div>
    <div class="clr">  </div>
</div>
<?php include "footer.tpl.php"; ?>
