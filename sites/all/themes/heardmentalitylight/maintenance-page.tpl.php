<div class="maintenance_wrapper">

  <div class="maintenance_top" style="width: 100%; height: 52%; background-color: #362750; background-position: bottom center; background-repeat: no-repeat;">
  </div>

  <div class="maintenance_bottom" style="width: 100%; height: 48%; background-color: #251b38;">
    <?php if ($content) : ?>
      <div class="white-box clearfix full din" id="region-content" style="width: 80%; font-family: 'DINLightRegular', 'Open Sans Condensed', Arial, sans-serif; font-size: 50px; color: white; padding: 20px 0 0 0; margin: 0 auto; text-align: center;">
        We're terribly sorry but we've down for maintenance.
        <?php print $content; ?>
      </div>
    <?php endif; ?>
  </div>
</div>
<? theme(); ?>
