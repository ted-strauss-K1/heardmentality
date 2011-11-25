<div class="references">
      <div class="expanding">
          <h3 class="din floatleft">></h3>
                <h6 value="Reply" id="add-arg" class="add-comment button"><?php print t('Add a Reference'); ?></h6>

        <ul>
          <li>
                <div class="leave-a-comment">
                  <?php print $addNewReferenceForm; ?>
                </div>
        </li>
      </ul>
      </div>
        <hr class="short">
      <div class="expanding">
                    <h6 class="blue-link"><?php print t('FILTER References'); ?></h6>
                    <ul>
                    <?php print $referenceFilterForm; ?>
                    </ul>

                    </div>
                    <hr class="short">
                    <div class="expanding">
                            <h6 class="blue-link"><?php print t('Reference Statistics'); ?></h6>
                            <ul>
                              <br class="clear">
                            <?php //print $referenceStatistics; ?>
                            <br class="clear">
                            </ul>

                    </div>
                    <hr class="short">
                    <?php print $refTypeFilter; ?>
                    <br class="clear">
                    <ul class="action ref" id="load-resource">
                    <?php print $referenceList; ?>
                    </ul>
</div>