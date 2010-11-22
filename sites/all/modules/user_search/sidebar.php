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
 $sel_cat = "select *,count(*) as cntc from {category} as c join {question_cat} as qc on qc.cat=c.cat_id  join {question} as q on q.qid=qc.qid  where c.parent_id='0' " . $searchcat . $search . " AND q.status='1' group by c.cat_id";
$listcat = ExecuteQuery($sel_cat, "select");


if (!empty($listcat)) {
    foreach ($listcat as $cat) {
        $style = '';
        if ($cid == $cat['cat_id']) {
            $style = 'class="sidelinks"';
        }
       echo $cat_qry = "SELECT * FROM question_cat WHERE cat ='".$cat['cat_id']."'group by qid";
                 $cat_res = db_query( $cat_qry);
                echo  $total_count1 = mysql_num_rows($cat_res);
        $catlist.='<span ' . $style . ' class="sidelinks"><a class="sidelinks" href="' . $gSitePath . 'searchquestion?cid=' . $cat['cat_id'] . '&txt_search=' . $txt_search . '">' . $cat['cat_name'] . '[' . $cat['cntc'] . ']</a></span><br/>';
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
                 
                $style = 'class="sidelinks"';
                $catlist.='&nbsp;&nbsp;<span ' . $style . '><a '.$style.' href="' . $gSitePath . 'searchquestion?cid=' . $cat['cat_id'] . '&scid=' . $scat['cat_id'] . '&txt_search=' . $txt_search . '">' . $scat['cat_name'] . '[' . $scat['cntc'] . ']</a></span><br/>';
                //sub subcat list
                if ((!empty($scid)) && ($scid == $scat['cat_id'])) {
                    //$catlist.='<ul>';
                     $sel_sscat = "select *,count(*) as cntc from {category} as c join {question_cat} as qc on qc.sscat=c.cat_id  join {question} as q on q.qid=qc.qid  where c.parent_id='" . $scat['cat_id'] . "' " . $search . " AND q.status='1' group by c.cat_id";
                    $listsscat = ExecuteQuery($sel_sscat, "select");
                    
                    foreach ($listsscat as $sscat) {
                          $style = '';
                        if ($sscid == $sscat['cat_id']) {
                            $style = 'style="font-weight:bold"';
                        }
                        $style = 'class="sidelinks"';
                        $catlist.='&nbsp;&nbsp;<span ' . $style . '><a '.$style.' href="' . $gSitePath . 'searchquestion?cid=' . $cat['cat_id'] . '&scid=' . $scat['cat_id'] . '&sscid=' . $sscat['cat_id'] . '&txt_search=' . $txt_search . '">' . $scat['cat_name'] . '[' . $sscat['cntc'] . ']</a></span><br/>';
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

        $tagslist.='<span class="sidelinks"><a class="sidelinks" href="' . $gSitePath . 'searchquestion?tag=' . $tag_result['tag_id'] . '' . $link1 . '' . $link2 . '' . $link3 . '&txt_search=' . $txt_search . '">' . $tag_result['tag'] . '[' . $tag_result['cntc'] . '] </a> </span><br/>';
    }
} else {

    $tagslist.='<span><b>No Tags Found</b></span>';
}


$tagslist.='</div>';
echo $tagslist;*/
?>