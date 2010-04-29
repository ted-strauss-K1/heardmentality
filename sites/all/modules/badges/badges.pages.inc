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
    
    $query = "select * from  {badges} where status='1'";
    
    $list = ExecuteQuery($query, 'select');

    
    // print_r($list);
    
    foreach ($list as $bad) {
        
        $strReturn .= "<div class='lft'> <b>".$bad['name']."</b> </div><div class='rht'>".$bad['info']."</div><br/>";

    
    }
    
    biographer();
    citizen_patrol();
    return $strReturn;

}

// fill profile get the biographer badge
function biographer($uid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;
    $i = 0;
    
    if ( empty($uid)) {
        $uid = $user->uid;
    }

    
    $data = db_fetch_object(db_query('SELECT * FROM {user_profile} WHERE uid=%d LIMIT 1', $uid));
    //print_r($data);
    if (! empty($data->real_name))
        $i++;
    
    if (! empty($data->bio))
        $i++;
    
    if ($data->gender > 0)
        $i++;
    
    if (! empty($data->zip))
        $i++;
    
    if (! empty($data->country))
        $i++;
    
    if (! empty($data->religion))
        $i++;
    
    if (! empty($data->ethnic))
        $i++;
    
    if (! empty($data->slant))
        $i++;
    
    if (! empty($data->facebook))
        $i++;
    
    if (! empty($data->twitter))
        $i++;
    
    if (! empty($data->dob))
        $i++;
    
    if ($i == 11) {
        db_query("INSERT INTO {user_badges} (bid, uid) VALUES (%d, %d)", 1, $uid);
    }
}


function citizen_patrol($uid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;

    
    if ( empty($uid)) {
        $uid = $user->uid;
    }
    
    $count = db_result(db_query('SELECT COUNT(uid) FROM {question_flags} where uid=$uid'));
    
    if ($count == 1) {
        
        db_query("INSERT INTO {user_badges} (bid, uid) VALUES (%d, %d)", 2, $uid);
    }

}
