<div class="one-third column centered main-banner-display">
  <div class="circle-box">
    <div class="error-banner"><a href="/"><span class="title"><?php print __($title, array('@code' => 'node-page-' . $node->nid . '-title', '@textgroup' => 'page')); ?></span></a></div>
  </div>
</div>

<div class="container">
  <div class="sixteen columns">
    <p class="din banner-text centered"><?php print strip_tags(__($content, array('@code' => 'node-page-' . $node->nid . '-content', '@textgroup' => 'page'))); ?></p><br class="clear">
  </div>
</div><br class="clear">
