   <?php
   // root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    //echo '<pre>';print_r($rows);
    ?>
<ul class="tags">
    
    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
    <?php if($rows):
        for($i=0; $i<count($rows); $i++){
           $tid = $rows[$i]['tid'];
           $count = db_result(db_query("SELECT COUNT(nid) FROM {term_node} WHERE tid = %d", $tid));
           if($count>0){
           $pid = db_result(db_query("SELECT parent FROM term_hierarchy WHERE tid = '".$tid."'"));
           if($pid!=0){
                $ppid = db_result(db_query("SELECT parent FROM term_hierarchy WHERE tid = '".$pid."'"));
           }
           if($ppid!=0){
               $href = 'issues/0/'.$ppid.'/'.$pid.'/'.$tid.'/0/0/0';
           }else if($ppid==0 && $pid!=0){
               $href = 'issues/0/'.$pid.'/'.$tid.'/0/0/0/0';
           }else{
               $href = 'issues/0/'.$tid.'/0/0/0/0/0';
           }
           print $href;
           print '<li><a href="'.$sitelink.$href.'">'.t($rows[$i]['name']).'('.$count.')</a></li>';
           }
         }
         endif;?>

</ul>
