<?php
$link1 = '';
$link2 = '';
$link3 = '';
$cid = '';
$scid = '';
global $gSitePath, $user, $gDocPath, $base_root, $base_path;
$query = facetad_refine();
$sel_search = mysql_query($query['query']);
$txt_search = trim($query['txt_search']);
$qids = array();


//keyword exist make count based on that
$search = '';
if (!empty($txt_search)) {

    $search.= " AND q.question LIKE  '%" . $txt_search . "%'";
}
if (!empty($_REQUEST['cid'])) {
    $cid = $_REQUEST['cid'];
   
}
if (!empty($_REQUEST['scid'])) {
    $scid = $_REQUEST['scid'];
}
if (!empty($_REQUEST['sscid'])) {
    $sscid = $_REQUEST['sscid'];
}
$catlist.='<div class="padding10"><span class="black12">Category :</span><br/>';
if (!empty($txt_search)) {
$sel_user = "select * from user_profile where real_name LIKE '%".$txt_search."%'";
$listuser = ExecuteQuery($sel_user, "select");
$user_id = $listuser[0]['uid'];
}

if(!empty($user_id))
{
   $sel_cat = "select * from category as c join follower as f on f.cat_id=c.cat_id where f.uid=$user_id";
}else{
  $sel_cat = "select *,count(*) as cntc from {category} as c join {question_cat} as qc on qc.cat=c.cat_id left join {question} as q on q.qid=qc.qid  where c.parent_id='0' " . $searchcat . $search . " AND q.status='1' group by c.cat_id";
}

$listcat = ExecuteQuery($sel_cat, "select");
if (!empty($listcat)) {
    foreach ($listcat as $cat) {
        $style = '';
        if ($cid == $cat['cat_id']) {
            $style = 'class="sidelinks"';
        }

        $count_row3 =  mysql_num_rows(db_query("SELECT count(*) FROM users reg, user_profile img, follower fol where (fol.cat_id=$cat[cat_id]) AND reg.status=1 and reg.uid=fol.uid group by fol.uid"));
        if($count_row3>0){ $count_row3 =  "[$count_row3]";}else{$count_row3='';}

        
       $catlist.='<span ' . $style . ' class="sidelinks"><a class="sidelinks" href="' . $gSitePath . 'searchuser?cid=' . $cat['cat_id'] . '&txt_search=' . $txt_search . '&q_country='.$_GET['q_country'].'&q_state='.$_GET['q_state'].'&q_city='.$_GET['q_city'].'">' . $cat['cat_name'] .$count_row3 . '</a></span><br/>';

       
        //subcat list
        if ((!empty($cid)) && ($cid == $cat['cat_id'])) {
           // $catlist.='<ul>';
           
            $sel_scat = "select *,count(*) as cntc from {category} as c join {question_cat} as qc on qc.scat=c.cat_id left join {question} as q on q.qid=qc.qid  where c.parent_id='" . $cat['cat_id'] . "' " . $search . " AND q.status='1' group by c.cat_id";
            $listscat = ExecuteQuery($sel_scat, "select");
            foreach ($listscat as $scat) {
                  $style = '';
                if ($scid == $scat['cat_id']) {
                    $style = 'style="font-weight:bold"'; 
                }

                $count_row =  mysql_num_rows(db_query("SELECT count(*) FROM users reg, user_profile img, follower fol where (fol.cat_id=$scat[cat_id]) AND reg.status=1 and reg.uid=fol.uid group by fol.uid"));
                 if($count_row>0){ $count_row =  "[$count_row]";}else{$count_row='';}
                 

                $style = 'class="sidelinks"';
               $catlist.='&nbsp;&nbsp;<span ' . $style . '><a '.$style.' href="' . $gSitePath . 'searchuser?cid=' . $scat['cat_id'] . '&txt_search=' . $txt_search . '&q_country='.$_GET['q_country'].'&q_state='.$_GET['q_state'].'&q_city'.$_GET['q_city'].'">' . $scat['cat_name'] .$count_row. '</a></span><br/>';

                //sub subcat list
                if ((!empty($scid)) && ($scid == $scat['cat_id'])) {
                    //$catlist.='<ul>';
                   
                    $sel_sscat = "select *,count(*) as cntc from {category} as c join {question_cat} as qc on qc.sscat=c.cat_id left join {question} as q on q.qid=qc.qid  where c.parent_id='" . $scat['cat_id'] . "' " . $search . " AND q.status='1' group by c.cat_id";
                    $listsscat = ExecuteQuery($sel_sscat, "select");
                    foreach ($listsscat as $sscat) {
                          $style = '';
                        if ($sscid == $sscat['cat_id']) {
                            $style = 'style="font-weight:bold"';
                        }

                       $count_row1 =  mysql_num_rows(db_query("SELECT count(*) FROM users reg, user_profile img, follower fol where (fol.cat_id=$sscat[cat_id]) AND reg.status=1 and reg.uid=fol.uid group by fol.uid"));
                       if($count_row1>0){ $count_row1 =  "[$count_row1]";}else{$count_row1='';}


                        $style = 'class="sidelinks"';
      $catlist.='&nbsp;&nbsp;<span ' . $style . '><a '.$style.' href="' . $gSitePath . 'searchuser?cid=' . $sscat['cat_id'] .'&txt_search=' . $txt_search . '&q_country='.$_GET['q_country'].'&q_state='.$_GET['q_state'].'&q_city='.$_GET['q_city'].'">' . $scat['cat_name']  .$count_row1 . '</a></span><br/>';
               // $catlist.='<span ' . $style . ' class="sidelinks"><a class="sidelinks" href="' . $gSitePath . 'searchuser?cid=' . $cat['cat_id'] . '&txt_search=' . $txt_search . '&q_country='.$_GET['q_country'].'&q_state='.$_GET['q_state'].'&q_city='.$_GET['q_city'].'">' . $scat['cat_name'] . '[' .$count_row . ']</a></span><br/>';
                        
                    }
                   // $catlist.='</ul>';
                }
            }
           // $catlist.='</ul>';
        }
    }
} else {

    $catlist.='<span><b>No Category Found</b></span>';
}
$catlist.='</div>';
echo $catlist;





if (isset($_REQUEST['cid'])) {
    $link1 = '&cid=' . $_REQUEST['cid'] . '';
    
}
if (isset($_REQUEST['scid'])) {
    $link2 = '&scid=' . $_REQUEST['scid'] . '';
}
if (isset($_REQUEST['sscid'])) {
    $link3 = '&sscid=' . $_REQUEST['sscid'] . '';
}

if (!empty($link3))
         $searchcat = " AND qc.sscat='$sscid' ";
    elseif (!empty($link2))
        $searchcat = " AND qc.scat='$scid' ";
    elseif (!empty($link1))
        $searchcat = " AND qc.cat='$cid' ";



/*$tagslist = '<br/><br/><span class="black12">Tags :</span><br/>';

$tsearch = '';
if (!empty($txt_search)) {

    $tsearch.= " AND q.question LIKE  '%" . $txt_search . "%'";

}
$ins_query='';
if(!empty ($txt_search)||!empty($_REQUEST['cid'])){
 $ins_query="left join {question_cat} as qc on qc.qid=q.qid ";
}
   $qry_tags = "select *,count(*) as cntc from {tagging} as t join {qtag} as qt on qt.tag_id=t.tid  join {question} as q on q.qid=qt.qid ".$ins_query." where  q.status='1' " .$searchcat . $tsearch . "  group by t.tid";
$rs_tags = ExecuteQuery($qry_tags, "select");
$tagslist.='<br/>';
if (!empty($rs_tags)) {

    foreach ($rs_tags as $tag_result) {

        $tagslist.='<span class="sidelinks"><a class="sidelinks" href="' . $gSitePath . 'searchuser?tag=' . $tag_result['tag_id'] . '' . $link1 . '' . $link2 . '' . $link3 . '&txt_search=' . $txt_search . '">' . $tag_result['tag'] . '[' . $tag_result['cntc'] . '] </a> </span><br/>';
    }
} else {

    $tagslist.='<span><b>No Tags Found</b></span>';
}


$tagslist.='</div>';
echo $tagslist;*/
?>