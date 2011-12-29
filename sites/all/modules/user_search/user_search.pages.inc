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
function _user_follows($uid = '', $fType = ''){
    global $user;

    $uid = $uid!=''?$uid:$user->uid;

    $output = '';
    $threads = '';
    // root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    
    $limit = 25;

    $inline = 'var sitepath = "'.$sitelink.'";';
    drupal_add_js($inline,'inline');

    // get relations
    //$relationshipsQuery = "SELECT * FROM {user_relationships} WHERE (requester_id = '$uid' OR requestee_id = '$uid') AND approved = 1 ORDER BY rid DESC";
    if($fType == 'following'){
         $relationshipsQuery = "SELECT * FROM {user_relationships} WHERE requester_id = '$uid' AND approved = 1 ORDER BY rid DESC";
         $relationships = pager_query($relationshipsQuery, $limit);
          if($relationships){
            while($relationship = db_fetch_object($relationships)){
                // get ranking
                $ranking = db_result(db_query("SELECT ranking FROM {tbl_ranking} WHERE rank_id = '$relationship->requestee_id'"));
                // followid
                $followid = $relationship->requestee_id;
                if($relationship->requestee_id != $user->uid){
                    $checkFid = check_follow_unfollow($user->uid, $relationship->requestee_id);
                    if($checkFid){
                        $flink = $sitelink. 'user/'.$user->uid.'/relationships/'.$relationship->requestee_id.'/remove/';
                        $currid = $user->uid;
                        $target = $relationship->requestee_id;
                        $status = 'Un-Follow' ;
                        $action = 'unfollow';
                    }else{
                        $flink = $sitelink. 'relationship/'.$relationship->requestee_id.'/request/'.$user->uid;
                        $status = 'Follow' ;
                        $currid = $user->uid;
                        $target = $relationship->requestee_id;
                        $action = 'follow';
                    }
                    // following stayus
                    $fClass = 'user_relationships_popup_link';
                    $follow_status['uid'] = $currid;
                    $follow_status['target'] = $target;
                    $follow_status['status'] = $status;
                    $follow_status['href'] = $flink;
                    $follow_status['fclass'] = $fClass;
                    $follow_status['action'] = $action;
                }else{
                    $follow_status = array();
                }
                $threads .= theme('following_users_thread', $followid, $type, $follow_status, $ranking);
            }     
        }
    }else if($fType == 'follower'){
        $relationshipsQuery = "SELECT * FROM {user_relationships} WHERE requestee_id = '$uid' AND approved = 1 ORDER BY rid DESC";
         $relationships = pager_query($relationshipsQuery, $limit);
         if($relationships){
            while($relationship = db_fetch_object($relationships)){
                // get ranking
                $ranking = db_result(db_query("SELECT ranking FROM {tbl_ranking} WHERE rank_id = '$relationship->requester_id'"));
                // followid
                $followid = $relationship->requester_id;
                if($relationship->requester_id != $user->uid){
                    $checkFid = check_follow_unfollow($user->uid, $relationship->requester_id);
                    if($checkFid){
                        $flink = $sitelink. 'user/'.$user->uid.'/relationships/'.$relationship->requester_id.'/remove/';
                        $uid = $user->uid;
                        $target = $relationship->requester_id;
                        $status = 'Un-Follow' ;
                        $action = 'unfollow';
                    }else{
                        $flink = $sitelink. 'relationship/'.$relationship->requester_id.'/request/'.$user->uid;
                        $status = 'Follow' ;
                        $uid = $user->uid;
                        $target = $relationship->requester_id;
                        $action = 'follow';
                    }
                    // following stayus
                    $fClass = 'user_relationships_popup_link';
                    $follow_status['uid'] = $uid;
                    $follow_status['target'] = $target;
                    $follow_status['status'] = $status;
                    $follow_status['href'] = $flink;
                    $follow_status['fclass'] = $fClass;
                    $follow_status['action'] = $action;
                }else{
                    $follow_status = array();
                }

                $threads .= theme('following_users_thread', $followid, $type, $follow_status, $ranking);
            }
         }
         
    }
    if($threads){
              // pagination
            $pagination = theme('pager', NULL, $limit, 0);
            // theme thread
            $output = theme('following_users', $threads, $pagination);
         }else{
            $output = '<br />'.t('No Following / Followers Found');
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