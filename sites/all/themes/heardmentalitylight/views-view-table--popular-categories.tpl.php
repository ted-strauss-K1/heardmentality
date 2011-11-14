   <?php
           //echo '<pre>';print_r($rows);
    ?>
<ul class="tags">
    <div class="icon cat2 text"></div>
    <label for="" class="tags-on">POPULAR CATEGORIES</label>
    <?php if($rows):
        for($i=0; $i<count($rows); $i++){
           print '<li>'.t($rows[$i]['name']).'</li>';
         }
         endif;?>
               
</ul>