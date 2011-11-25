<div class="expanding">
              <h3 class="din floatleft">></h3>
              <h6 value="Reply" id="add-arg" class="add-comment button"><?php print t('Add an Argument'); ?></h6>

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
        <h6 class="blue-link"><?php print t('Debate Statistics'); ?></h6>
        <div id="analytics-area">
          <br class="clear">
        <?php //print $debateStatistics; ?>
        <br class="clear">
        </div>

</div>
<hr>
<div class="comments expanding">
        <?php print $debateList; ?>
</div>
