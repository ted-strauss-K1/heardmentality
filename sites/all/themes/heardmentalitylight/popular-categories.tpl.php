<?php
   // root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    ?>
<ul class="tags">
    <div class="icon cat2 text"></div>
    <label for="" class="tags-on"><?php print t('POPULAR CATEGORIES'); ?></label>
    <?php if(popular):
foreach($popular as $tid=>$name){
                $pid = db_result(db_query("SELECT parent FROM term_hierarchy WHERE tid = '".$tid."'"));
           if($pid!=0){
                $ppid = db_result(db_query("SELECT parent FROM term_hierarchy WHERE tid = '".$pid."'"));
           }
           if($ppid!=0){
               $href = 'issues/0/'.$ppid.'/'.$pid.'/'.$tid.'/0/0/0/alltime';
           }else if($ppid==0 && $pid!=0){
               $href = 'issues/0/'.$pid.'/'.$tid.'/0/0/0/0/alltime';
           }else{
               $href = 'issues/0/'.$tid.'/0/0/0/0/0/alltime';
           }
           print '<li><a href="'.$sitelink.$href.'">'.t($name).'</a></li>';
}
         endif;?>

</ul>