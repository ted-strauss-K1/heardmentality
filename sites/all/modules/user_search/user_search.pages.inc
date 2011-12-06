<?php
// follow / unfollow
function save_follow() {
    $uid = $_GET['uid'];
    $target = $_GET['target'];
    if($_GET['action'] == 'unfollow'){
        $sql = db_query("DELETE FROM {user_relationships} WHERE requester_id = '$uid' AND requestee_id = '$target'");
        if($sql){
            print '<a class="button light" onclick="follow_unfollow('.$uid.', '.$target.', \'follow\')" href="javascript:void(0);">'.t('Follow').'</a>';
        }else{
           print '<a class="button light">'.t('Failed').'</a>';
        }
    }else if($_GET['action'] == 'follow'){
        $sql = "INSERT INTO {user_relationships}(requester_id, requestee_id, rtid, approved, created_at, updated_at, flags)
                    VALUES($uid, $target, 1, 1, '".time()."', '".time()."', 0)";
        $insert = db_query($sql);
        if($insert){
            /*New SET NOTIFY LOG*/
            $variable = array('target_id' => $target);
            set_notify_log($uid, '', 'user_follow', $variable);
            /*New SET NOTIFY LOG*/
            print '<a class="button light" onclick="follow_unfollow('.$uid.', '.$target.', \'unfollow\')" href="javascript:void(0);">'.t('Un-Follow').'</a>';
        }else{
            print '<a class="button light">'.t('Failed').'</a>';
        }
    }

}

// user following / followers
function _user_follows(){
    global $user;
    $output = '';
    $threads = '';
    // root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    
    $limit = 25;

    $inline = 'var sitepath = "'.$sitelink.'";';
    drupal_add_js($inline,'inline');

    // get relations
    $relationshipsQuery = "SELECT * FROM {user_relationships} WHERE (requester_id = '$user->uid' OR requestee_id = '$user->uid') AND approved = 1 ORDER BY rid DESC";
    $relationships = pager_query($relationshipsQuery, $limit);
    if($relationships){
    while($relationship = db_fetch_object($relationships)){
        if($relationship->requester_id == $user->uid){
            
            $type = 'following';
            $followingid = check_follow_unfollow($user->uid, $relationship->requestee_id);
            if($followingid){
                $flink = $sitelink. 'user/'.$user->uid.'/relationships/'.$relationship->requestee_id.'/remove/';
                $uid = $user->uid;
                $target = $relationship->requestee_id;
                $status = 'Un-Follow' ;
            }else{
                $flink = $sitelink. 'relationship/'.$getuser->uid.'/request/'.$user->uid;
                $status = 'Follow' ;
                $uid = $user->uid;
                $target = $getuser->uid;
            }
            // following stayus
            $fClass = 'user_relationships_popup_link';
            $follow_status['uid'] = $uid;
            $follow_status['target'] = $target;
            $follow_status['status'] = $status;
            $follow_status['href'] = $flink;
            $follow_status['fclass'] = $fClass;
            // get ranking
            $ranking = db_result(db_query("SELECT ranking FROM {tbl_ranking} WHERE rank_id = '$relationship->requestee_id'"));
            // followid
            $followid = $relationship->requestee_id;

        }elseif($relationship->requestee_id == $user->uid){
            
            $type = 'follower';
            $follow_status = array();
            // get ranking
            $ranking = db_result(db_query("SELECT ranking FROM {tbl_ranking} WHERE rank_id = '$relationship->requester_id'"));
            // followid
            $followid = $relationship->requester_id;  
        }
        // theme
        $threads .= theme('following_users_thread', $followid, $type, $follow_status, $ranking);
        
    }
    $pagination = theme('pager', NULL, $limit, 0);
    $output = theme('following_users', $threads, $pagination);
   }else{
    $output = t('No Followers / Following Found');
   }
   return $output;
        
}

function user_search_theme(){
    return array(
        'following_users_thread' => array(
            'template' => 'following-users-thread',
            'arguments' => array('followid' => NULL, 'type' => NULL, 'follow_status' => NULL, 'ranking' => NULL),
        ),
        'following_users' => array(
            'template' => 'following-users',
            'arguments' => array('threads' => NULL, 'pagination' => NULL),
        ),
   );
}