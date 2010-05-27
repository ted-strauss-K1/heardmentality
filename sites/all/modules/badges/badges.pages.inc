<?php
/**
 * @var ExecuteQuery
 *
 */

// tree menu listing
function badges_list() {
    global $gSitePath,$user,$gDocPath,$base_root;
    
    drupal_add_css(drupal_get_path('module', 'badges').'/styles/badge.css');
    
    //	drupal_add_js(drupal_get_path('module', 'category').'/scripts/demo.js');
    $strReturn = '';
    
    //print_r($user);
    
    $query = "select *,IFNULL((select count(*) from {user_badges} as ub where ub.bid=b.bid group by ub.bid ),0) as cnt from  {badges} as b where b.status='1'";
    
    $list = ExecuteQuery($query, 'select');

    
    // print_r($list);
    
    foreach ($list as $bad) {
        
        $strReturn .= "<div class='lft'> <b>".$bad['name']." X ".$bad['cnt']."</b> </div><div class='rht'>".$bad['info']."</div><br/>";

    
    }
    
  set_badges();
    return $strReturn;

}

