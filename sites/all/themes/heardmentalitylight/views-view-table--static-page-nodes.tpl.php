<?php 
//echo '<pre>';print_r($rows);

foreach($rows as $key=>$row){
    $name[$row['tid']] = $row['name'];
}

$uniques = array_unique($name);
foreach($uniques as $temp=>$unique){
    $newArray[$temp]['name'] = $unique;
    foreach($rows as $ver=>$row){
        if($unique == $row['name']){
            $newArray[$temp]['title'][$ver] = $row['title'];
            $newArray[$temp]['path'][$ver] = $row['path'];
        }
    }
}
//echo '<pre>';print_r($newArray);

?>
<div class="grey-box">
				<label for="" class="tags-on">PAGES</label>
				<ul class="sub-pages">
          
                                <?php foreach($newArray as $row){?>
                                 <li><a><?php print t($row['name']);?></a>
                                 <ul>
                                     <?php foreach($row['title'] as $key=>$title){?>
                                     <li><a href="<?php print $row['path'][$key];?>"><?php print t($title);?></a></li>
                                      <?php }?>
                                 </ul>
                                <?php }?>


				</ul>


                                

				<div class="clear"></div>
			</div>