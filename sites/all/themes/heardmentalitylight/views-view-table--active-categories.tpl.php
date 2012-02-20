   <?php
   // root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    //echo '<pre>';print_r($rows);
    global $language;
    ?>
<ul class="tags">
    
    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
    <?php if($rows):

       $curLanguage = $language->language;
       if($curLanguage=='en'){
           $langFilter = "AND (n.language = '$curLanguage' OR n.language = '')";
        }else{
           $langFilter = "AND n.language = '$curLanguage'";
        }



        for($i=0; $i<count($rows); $i++){
           $tid = $rows[$i]['tid'];
           $sql = "SELECT COUNT(nid) FROM (SELECT DISTINCT(tn.nid) FROM {term_node} AS tn JOIN {node} AS n ON tn.nid = n.nid WHERE tn.tid = %d and n.type = '%s' $langFilter) AS cTab";
           $count = db_result(db_query($sql, $tid, 'poll'));
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
           print '<li><a href="'.$sitelink.$href.'">'.t($rows[$i]['name']).'('.$count.')</a></li>';
           }
         }
         endif;?>

</ul>
