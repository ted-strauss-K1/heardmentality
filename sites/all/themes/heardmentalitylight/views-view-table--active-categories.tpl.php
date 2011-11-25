   <?php
           //echo '<pre>';print_r($rows);
    ?>
<ul class="tags">
    
    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
    <?php if($rows):
        for($i=0; $i<count($rows); $i++){
           print '<li>'.t($rows[$i]['name']).'</li>';
         }
         endif;?>

</ul>
