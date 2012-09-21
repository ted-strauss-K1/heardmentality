<?php drupal_add_js('misc/collapse.js'); global $base_url; ?>

<div id="debate_work_area">
  <div class="inner">

    <div class="expanding arg">
      <h6 value="Reply" id="add-arg" class="button <?php print user_profile_login_class(); ?>"><?php print t('Add'); ?></h6>
    </div>

    <?php $arguments = arguments_get_list($nid); ?>
    <?php if ($arguments['#count']['#all']) : ?>
    <div class="expanding stat">
      <h6 class="button" id="deb-ana"><?php print t('Stats'); ?></h6>
    </div>
    <?php endif; ?>

    <div id="leave_comment_area" class="leave-a-comment hidden_ar" style="display: none;">
      <?php print $arguments_form; ?>
    </div>

    <div id="analytics-area" class="hidden_deb" style="display: none;">
      <h2><span>Debate statistics</span></h2>
      <div id="deb-ana-load-txt"></div>
      <div id="load-deb-statics"></div>
    </div>

  </div><!--/.inner -->
</div><!--/#debate_work_area -->

<div id="debate_list_area">
  <h2>
    <span class="argcount"><?php print $debate_count; ?>&nbsp;</span><span>Arguments&nbsp;&amp;&nbsp;</span><span class="rescount"><?php print $resource_count; ?>&nbsp;</span><span>References</span>

    <div class="show_only">
      <span class="button" id="show_filter">&#9660; Show only</span>
      <div class="inc">
        <form id="inc_ref">
          <input type="checkbox" checked="yes" value="include references" id="inc_check" />
          <label for="inc_check">Include References</label>
        </form>
      </div>
      <div class="popup hidden" id="filter_content">
        <span class="title">Show all</span>
        <?php foreach ($choices as $index => $choice) : ?>
          <dl name="<?php print $choice['chorder'] ?>">
            <dd>
              <a href="" class="neutral">
                <span class="small_pos">+</span>
                <span class="small_neg">-</span>
              </a>
              <a href="" class="positive">
                <span class="small_pos">+</span>
              </a>
              <a href="" class="negative">
                <span class="small_neg">-</span>
              </a>
            </dd>
            <dt><?php print $choice['short_answer']; ?></dt>
          </dl>
        <?php endforeach; ?>
		    <span class="title reset">Reset filters</span>
      </div>
    </div>
  </h2>

  <div id="empty_helper">&nbsp;</div>

  <ul>
    <li><a href="<?php print $base_url ?>/arguments/tabs/<?php print $nid; ?>/1/0">recent</a></li>
    <li><a href="<?php print $base_url ?>/arguments/tabs/<?php print $nid; ?>/0/0">older</a></li>
    <li><a href="<?php print $base_url ?>/arguments/tabs/<?php print $nid; ?>/2/0">supported</a></li>
  </ul>

</div><!--/#debate_list_area -->
