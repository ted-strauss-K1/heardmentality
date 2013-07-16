<div class="position">
  <?php foreach ($options as $option) : ?>
    <?php if (1 == $option['val']) : ?>
      <p class="position-plus"><strong>+</strong>&nbsp;
        <?php print $option['chtext_short'] ?>
      </p>
    <?php endif; ?>
    <?php if (-1 == $option['val']) : ?>
      <p class="position-minus"><strong>-</strong>&nbsp;
        <?php print $option['chtext_short'] ?>
      </p>
    <?php endif; ?>
  <?php endforeach; ?>
</div>