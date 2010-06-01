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
        
        $strReturn .= "<div class='lft'> <a href='".$gSitePath."badges/user/".$bad['bid']."'>".$bad['name']." X ".$bad['cnt']."</a> </div><div class='rht'>".$bad['info']."</div><br/>";

    
    }
    
    set_badges();
    return $strReturn;

}

function user_list() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $bid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $strReturn = '';
    
    $badge = db_fetch_object(db_query("SELECT name,info FROM {badges} where bid='$bid'"));
    $badgecnt = db_result(db_query("SELECT count(*) FROM {user_badges} where bid='$bid' group by bid"));
    $query = "SELECT * FROM {user_badges} AS ub join {user_profile} as u on u.uid=ub.uid LEFT JOIN badges AS b ON ub.bid = b.bid WHERE b.status = '1' AND ub.bid = '$bid' group by ub.uid";
    $strReturn .= '<h1>'.$badge->name.'</h1> <br/>- '.$badge->info.'<hr/><br/>';
    
    $strReturn .= '<b>'.$badgecnt.' Users earned this badge. Recently awarded to:</b><br/><br/>';
	
    $list = ExecuteQuery($query, 'select');
    foreach ($list as $bad) {

          $totalbad = db_result(db_query("SELECT count(*) FROM {user_badges} where uid='".$bad['uid']."' group by uid"));
		        $uname = db_result(db_query("SELECT name FROM {users} where uid='".$bad['uid']."' "));
        $strReturn .= '<a href="'.$gSitePath.'profile/'.$uname.'">'.$bad['real_name'].'</a> ('.$totalbad.')<br/>';

    
    }

    
    return $strReturn;
}
