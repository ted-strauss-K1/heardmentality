<?php global $user;
$loginBoxClass = $user->uid==0?'openlogin_box':'';
?>
<div class="expanding">
              <h3 class="din floatleft">></h3>
              <h6 value="Reply" id="add-arg" class="add-comment button <?php print $loginBoxClass;?>"><?php print t('Add an Argument'); ?></h6>

            <ul>
              <li>
            <div class="leave-a-comment">
              <?php print $addNewDebateForm; ?>
            </div>
            </li>
          </ul>
</div>
<hr class="short">
<div class="expanding">
        <h6 class="blue-link"><?php print t('FILTER ARGUMENTS'); ?></h6>
        <ul>
        <?php print $debateFilterForm; ?>
        </ul>

</div>
<hr class="short">
<div class="expanding">
        <h6 class="blue-link" id="deb-ana"><?php print t('Debate Statistics'); ?></h6>
        <div id="analytics-area">
          <?php print $debateStatistics; ?>
          <div id="deb-ana-load-txt"></div>
          <br class="clear">
          <div id="load-deb-statics"></div>
          <br class="clear">
        </div>

</div>

<hr>
<div class="comments expanding">
        <?php print $debateList; ?>
</div>
