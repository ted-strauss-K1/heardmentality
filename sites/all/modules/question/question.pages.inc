<?php



function question_ajax() {
    //print_r($_REQUEST['code']);
    // print_r($action);
	$ret = '';
	global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    extract($_REQUEST);
    if (isset($_REQUEST['ids'])) {
        //$client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ($ids)");
        /********Node Conversion********/
        $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s' AND module = '%s'", 'Sections', 'taxonomy'));
        $client_select = db_query("SELECT t.tid AS cat_id, t.name AS cat_name FROM term_data t RIGHT JOIN term_hierarchy h ON t.tid = h.tid WHERE parent IN ($ids) AND t.vid = '$vid'");
        /********Node Conversion********/
        $client_array = array();
        $client_key = array();
        while ($list = db_fetch_object($client_select)) {

            $client_array[] = $list->cat_name;
            $client_key[] = $list->cat_id;
        }
        if (!empty($client_array)) {

            if ($action == 1) {
                $qscat = "q_scat";
                $tab = 15;
            }
            if ($action == 2) {
                $qscat = "q_sscat";
                $tab = 16;
            }
            $ret = '<select class="listbox2" tabindex="' . $tab . '"  size="5" multiple="multiple" onchange="get_subcat(' . $qscat . ',\'chg_sscat\',' . ++$action . ');" id="' . $qscat . '" name="q_scat[]"> ';

            for ($i = 0; $i < count($client_array); $i++) {

                $ret .= '<option value="' . $client_key[$i] . '">' . stripslashes($client_array[$i]) . '</option>';
            }
            $ret .= "</select>";
        } else {
            $ret .= 'No Subcategory';
        }
        echo $ret;
        exit;
    } elseif (isset($_REQUEST['code'])) {
        switch ($action) {

            case 1: //get state
                $query = array('query' => $_REQUEST['code'], 'maxRows' => '1', 'featureclass' => 'S');
                $result = geonames_query('search', $query);
                print_r($result->results[0]['url']);
                // $cc=$result->results[0]['countrycode'];
                // $result = geonames_query('countryinfo', $query);
                // $result->results[0][geonameid];
                $query = array('country' => $result->results[0]['countrycode']);
                $result = geonames_query('countryinfo', $query);
                $query = array('geonameid' => $result->results[0]['geonameid']);
                $result = geonames_query('children', $query);

                if ($select && $user->uid > 0) {
                    $udet = load_user($user->uid);

                    $setstate = $udet->state;
                    $fcity = $udet->city;
                }
                $ret = "<script>
                $(document).ready(function() {
	$('select').change(function(){
		alert('ID: ' + $(this).attr('id') + ' Value: ' + $(this).attr('value'));
	});
                    </script>";

                $ret = '<select tabindex="18" class="listbox2" style="width: 125px;"  onchange="get_city(this.value);" id="q_state" name="q_state"> <option value="">--States--</option>';
                foreach ($result->results as $state) {
                    $set = '';
                    if (strpos(strtolower($setstate), strtolower($state['name']))) {
                        $set = 'SELECTED=SELECTED';
                    }
                    $ret .= sprintf('<option value="%s" %s >%s</option>', $state['geonameid'], $set, $state['name']);
                }
                $ret .= "</select>";
                echo $ret;
                break;
                exit;
            case 2: //get city

                $query = array('geonameid' => $code);
                $result = geonames_query('children', $query);
                //print_r($result);

                $ret = "<script>
                $(document).ready(function() {
	$('select').change(function(){
		alert('ID: ' + $(this).attr('id') + ' Value: ' + $(this).attr('value'));
	});
                    </script>";

                $ret = '<select class="listbox2"  tabindex="19"  style="width: 125px;"  id="q_city" name="q_city" > <option value="">--Cities--</option> ';
                foreach ($result->results as $state) {

                    $ret .= sprintf('<option value="%s">%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select>";
                echo $ret;
                break;
		/*RELEATED QUESTIONS AUTO POPULATE*/		
			case 3: 
				echo get_releated_questions($_POST['question'],$_POST['cat_id'],$_POST['context']);                
                break;				
		/*RELEATED QUESTIONS AUTO POPULATE*/				
        }
    } elseif (isset($_REQUEST['tag'])) {

        extract($_REQUEST);

        $tarr = explode(' ', $tag);
        $qns = explode(' ', $qns);
        $tarr = array_merge($tarr, $qns);
        $tarr = array_filter($tarr);
        $tarr = array_unique($tarr);

        $taglist = array();

        foreach ($tarr as $list) {

            $query = " SELECT * FROM {tagging} WHERE `tag` LIKE  '%$list%' LIMIT 0 , 15 ";
            $result = ExecuteQuery($query, "select");
            foreach ($result as $single) {
                array_push($taglist, $single['tag']);
            }
        }
        //for category taglist
        if (!empty($cat1)) {

            $exp = explode(',', $cat1);

            $qids = array();
            foreach ($exp as $scat) {

                 $query = " SELECT * FROM {question}  ";
               
                $result = ExecuteQuery($query, "select");

                foreach ($result as $man) {

                    $getcat = explode(',', $man['cid']);

                    if (in_array($scat, $getcat)) {

                        array_push($qids, $man['qid']);
                    }
                }




                $qids = array_unique($qids);
                $qids = implode(',', $qids);

                $query = " SELECT * FROM {tagging} WHERE `qid` IN ($qids) ";
                $result = ExecuteQuery($query, "select");
                foreach ($result as $single) {
                    array_push($taglist, $single['tag']);
                }
            }
        }


        $taglist = array_filter($taglist);

        $taglist = array_unique($taglist);
        $taglist = implode(',', $taglist);
        $taglist = explode(',', $taglist);
        $taglist = array_filter($taglist);
        $taglist = array_unique($taglist);

        $tag = ' <label>
            	                    Suggestions:
            	                </label>';
        if (!empty($taglist)) {
            foreach ($taglist as $ins) {
                $tag .= '	
            	                    <div id="tagging-1" class="tagging-suggest-tag processed">
            	                        ' . $ins . '</div>';
            }
        } else {

            $tag .= '<b>No Suggestions</b>';
        }

        echo $tag;
      
    } elseif (isset($_REQUEST['ssearch'])) {


        $input = trim(strtolower($_REQUEST['input']));
        $stype = $_REQUEST['stype'];
        $aResults = array();
        if ($stype == '2') {


            $query = "select u.uid as id,u.name as value,up.first_name as info from user_profile as up,users as u where u.uid=up.uid AND (u.name like '%%%s%%' OR up.real_name like '%%%s%%')  ORDER BY u.uid ASC ";
            //  $aResults = ExecuteQuery($query, "select");
          //  printf($query,$input,$input);die;
            $Result = db_query($query,$input,$input);
        } else {


           // $query = "select qid as id,question as value,context as info from question where question like '%$input%' OR context like '%$input%' AND status='1' ORDER BY qid ASC ";
          $query = "select qid as id,question as value,context as info from question where question like '%$input%' AND status='1' ORDER BY qid ASC ";
          
           
            //$aResults = ExecuteQuery($query, "select");
            $Result = mysql_query($query);
        }
        while ($ResultSet1 = mysql_fetch_array($Result)) {
            $aResults[] = $ResultSet1;
        }
        //print_r($aResults);
        // $aResults[]=array('id'=>'question_1','value'=>'Question vs','info'=>'currency','currency'=>'hello');
        // $aResults[]=array('id'=>'question_2','value'=>'Question info','info'=>'currency','currency'=>'hello');
        //print_r($aResults);
        header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); // Date in the past
        header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // always modified
        header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
        header("Pragma: no-cache"); // HTTP/1.0

        header("Content-Type: application/json");

        echo "{\"results\": [";
        $arr = array();
        for ($i = 0; $i < count($aResults); $i++) {
            $arr[] = "{\"id\": \"" . $aResults[$i]['id'] . "\", \"value\": \"" . mysql_real_escape_string($aResults[$i]['value']) . "\", \"info\": \"" . mysql_real_escape_string(myTruncate($aResults[$i]['info'], 20, '...')) . "\"}";
        }
        echo implode(", ", $arr);
        echo "]}";
    } elseif (isset($_REQUEST['sel_id'])) {


        $link1 = '';
        $link2 = '';
        $link3 = '';
        $cid = '';
        $scid = '';
        $cond = '';
                    //print_r($_REQUEST);

        $scid = $_REQUEST['scid'];
        //$cond =" AND cat.scat=$scid";

        if ($_REQUEST['sel_id'] != '') {
        $cid=$_REQUEST['sel_id'];

                        /*Node conversion*/
                              $parent = taxonomy_get_parents($cid);
                              $childrens = taxonomy_get_children($cid);
                              foreach($childrens as $children){
                                  $style = '';
                              if ($sscid == $children->tid) {
                                 $style = 'style="font-weight:bold"';
                              }
                              $sscat_qry = "SELECT count(distinct cat.tid) FROM term_node as cat join node as q on q.nid=cat.nid where q.status='1' AND cat.tid ='" . $children->tid. "' $cond group by q.nid";
                              $total = db_result(db_query($sscat_qry));
                              $total = $total!=''?$total:0;
                              $style = 'class="sublinks scat" style="padding-left:10px"';
                              $catlist.= '<br class="scat"/><span ' . $style . '><a  id="sc-' . $children->tid . '" href="JavaScript:void(0);" ' . $style . '>' . stripslashes($children->name) . '[' .$total. ']' .'</a></span>';
                                }
                            echo $catlist;
                       /*Node conversion*/

            
        }
    }else if(isset($_REQUEST['user_scat'])){

         $cid=$_REQUEST['user_scat'];

         $parent=load_parent_cat($cid,3);
         $catid=(!empty($parent['lev1']))?$parent['lev1']:$parent['lev2'];
         if(!empty($catid)){
                        foreach ($listsscat as $sscat) {
                            $style = '';
                            if ($sscid == $sscat['cat_id']) {
                                $style = 'style="font-weight:bold"';
                            }
                      
                            $sscat_qry = "select count(uid) from follower where cat_id='".$sscat['cat_id']."'";
                           $total_count3= db_result(db_query($sscat_qry));


                            $style = 'class="sublinks scat" style="padding-left:10px"';
                            $catlist.='<br class="scat"/><span ' . $style . '><a  id="sc-'.$sscat['cat_id'].'" ' . $style . ' href="javascript:void(0);">' . $sscat['cat_name'] . '[' . $total_count3 . ']</a></span>';
                        }
                        echo $catlist;
         }

    }else if(isset($_REQUEST['notupdate'])){
        // update user message status, sent from moderator
            $mid = $_REQUEST['mid'];
            $uid = $_REQUEST['uid'];
            $sql = db_query("UPDATE {moderator_messages} SET status= '1' WHERE id = '%d' AND to_uid = '%d'", $mid, $uid);
            if($sql){
                echo "success";
            }
    }

     exit;
}

//delete confirm
function get_releated_questions($question,$cat_id,$context)
{	
	$where_condition = '';	
	$words = explode(" ", $question);
           $words = array_filter($words, 'word_array_filter');
            $words = array_filter($words);
	 for ($i = 0; $i < count($words); $i++) {
		$wheres2 	= array();
			if($words[$i]!='')
			{
				$wheres2[]  = "  q.title  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
				$wheres[] 	= implode( ' OR ', $wheres2 );
			}	
		}
	$where_condition = '((' . implode( ($match == 'all' ? ') AND (' : ') OR ('), $wheres ) . '))';
	
	if($context!='')
	{
		$words = explode(" ", $context);
		 for ($i = 0; $i < count($words); $i++) {
			$wheres2 	= array();
				if($words[$i]!='')
				{
					$wheres2[]  = "  q.context  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
					$wheres1[] 	= implode( ' OR ', $wheres2 );
				}	
			}	
		$where_condition .= ' and ((' . implode( ($match == 'all' ? ') AND (' : ') OR ('), $wheres1 ) . '))';
	}
	if($cat_id!=0)
	{
		$where_condition .= " and qc.cat in ($cat_id)";
	}
         $text="$question $context";
//printf("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
	$count = db_result(db_query("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0));
	$rel_output.= '<div class="innerbox" style="width:auto;height:auto; overflow:auto; min-height:150px;"><ul>';
	if (($count!=0)&&($question!=''))
	{
		$rel_count = 1;
		$rel_query = db_query("SELECT r.nid,r.title, MATCH(r.body, r.title) AGAINST ('%s') AS score FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
		while ($rel_options = db_fetch_object($rel_query)) {		
		  $rel_output.='<li><input style="width:15px;" type="checkbox" name="chk_rel_issue[]" id="chk_rel_issue[]" value="'.$rel_options->nid.'"> ';
		  $rel_output .= substr($rel_options->title,0,50).'...</li>';
		  $rel_count ++;
		}
	} else {
		$rel_output.= 'No Releated question available';
	}		
	$rel_output.= '</ul></div>';
	echo  $rel_output;	
//echo "SELECT q.qid, q.question FROM {question} q  left join question_cat qc on qc.qid=q.qid  WHERE $where_condition  group by q.qid ";	
	
}







