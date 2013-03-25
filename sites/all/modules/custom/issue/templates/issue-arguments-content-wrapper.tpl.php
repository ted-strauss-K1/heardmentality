<?php global $base_url; ?>

<div id="debate_work_area">
  <div class="inner">

    <div class="expanding arg">
      <h6 value="Reply" id="add-arg"
          class="button <?php print theme('user_login_modal_class'); ?>"><?php print t('Add'); ?></h6>
    </div>

    <?php $arguments = $node->arguments; ?>
    <?php if ($arguments['#all']) : ?>
    <?php print theme('issue_charts_strength', $node); ?>
    <?php endif; ?>

    <div id="leave_comment_area" class="leave-a-comment hidden_ar" style="display: none;">
      <?php print $form; ?>
    </div>

    <div id="analytics-area" class="hidden_deb" style="display: none;">
      <h2><span>Debate statistics</span></h2>

      <div id="deb-ana-load-txt"></div>
      <div id="load-deb-statics"></div>
    </div>

  </div>
  <!--/.inner -->
</div><!--/#debate_work_area -->

<div id="debate_list_area">
  <h2>
    <span class="argcount"><?php print $arguments[TYPE_DEBATE]; ?>&nbsp;</span><span>Arguments&nbsp;&amp;&nbsp;</span>
    <span class="rescount"><?php print $arguments[TYPE_RESOURCE]; ?>&nbsp;</span><span>References</span>

    <div class="show_only">
      <span class="button" id="show_filter">&#9660; Show only</span>

      <div class="inc">
        <form id="inc_ref">
          <input type="checkbox" checked="yes" value="include references" id="inc_check"/>
          <label for="inc_check">Include References</label>
        </form>
      </div>
      <div class="popup hidden" id="filter_content">
        <span class="title">Show all</span>
        <?php foreach ($node->choice as $index => $choice) : ?>
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
          <dt><?php print $choice['chtext_short'] ? $choice['chtext_short'] : $choice['chtext']; ?></dt>
        </dl>
        <?php endforeach; ?>
        <span class="title reset">Reset filters</span>
      </div>
    </div>
  </h2>

  <div id="empty_helper">&nbsp;</div>

  <ul>
    <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/0/0">recent</a></li>
    <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/1/0">older</a></li>
    <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/2/0">supported</a></li>
  </ul>
  <div id="ui-tabs-1">
    <?php print argument_tab($node->nid); ?>
  </div>
  <div id="ui-tabs-2">
    <div style="padding: 20px; width: 100%;text-align: center;">
      <?php print theme('sub_loader', 'margin-top: 15px auto; display: block; ') ?>
    </div>
  </div>
  <div id="ui-tabs-3">
    <div style="padding: 20px; width: 100%;text-align: center;">
      <?php print theme('sub_loader', 'margin-top: 15px auto; display: block; ') ?>
    </div>
  </div>

</div><!--/#debate_list_area -->