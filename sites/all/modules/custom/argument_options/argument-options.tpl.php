<div class="position">
  <?php foreach ($options as $option) : ?>
  <?php if ($option['value'] == 1) : ?>
    <p class="position-plus"><strong>+</strong>&nbsp;
      <?php print $option['chtext_short'] ? $option['chtext_short'] : $option['chtext'] ?>
    </p>
    <?php endif; ?>
  <?php if ($option['value'] == -1) : ?>
    <p class="position-minus"><strong>-</strong>&nbsp;
      <?php print $option['chtext_short'] ? $option['chtext_short'] : $option['chtext'] ?>
    </p>
    <?php endif; ?>
  <?php endforeach; ?>
</div>