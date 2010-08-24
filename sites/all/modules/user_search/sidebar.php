<?php

$link1 = '';
$link2 = '';
$link3 = '';
$cid = '';
$scid = '';
global $gSitePath, $user, $gDocPath, $base_root, $base_path;
$query = facetad_refine();
$sel_search = mysql_query($query['query']);
$txt_search = $query['txt_search'];
$qids = array();
while ($push = db_fetch_array($sel_search)) {

    array_push($qids, $push['qid']);
}

$qids = implode(",", $qids);

if (isset($_REQUEST['scid']) || isset($_REQUEST['cid'])) {
    $suid = $_REQUEST['scid'];
    if ($_REQUEST['cid'] == '') {
        $sel_catm = db_query("select * from category  where cat_id='" . $suid . "'   ");
        $saveresult = db_fetch_object($sel_catm);
        $cid = $saveresult->parent_id;
    } else {
        $cid = $_REQUEST['cid'];
    }

    $catlist = "<b>Category</b>";
    $sel_cat = db_query("select * from category where cat_id=" . $cid . "   ");
    $saveresult = db_fetch_object($sel_cat);


    $sel_suge = "select * from category  where parent_id=" . $cid . "   ";

    $rs_folwin = db_query($sel_suge);

    if (!empty($qids)) {
        $numrancnt = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . "   "));

        $catlist.='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul><li><b><a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&txt_search=' . $txt_search . '">' . $saveresult->cat_name . '(' . $numrancnt . ')</a></b></li>';

        while ($flwing_result = db_fetch_object($rs_folwin)) {
            //echo "SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id."";

            $numrancnts = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . " "));


            $catlist.='<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '&txt_search=' . $txt_search . '">' . $flwing_result->cat_name . '(' . $numrancnts . ')</a></li>';
            //echo $flwing_result->cat_id;

            $sel_sugess = "select * from category as c  where c.parent_id=" . $flwing_result->cat_id . "   ";
            $rs_folwinss = db_query($sel_sugess);
            while ($sm_result = db_fetch_object($rs_folwinss)) {

                $numrancntss = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . " and  sscid=" . $sm_result->cat_id . " AND qid in (" . $qids . ")"));
                $catlist.='<li>&nbsp;&nbsp; <a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '&sscid=' . $sm_result->cat_id . '">' . $sm_result->cat_name . '(' . $numrancntss . ') </a> </li>';
            }
        }
    } else {
        $catlist.='<li>&nbsp;&nbsp;No Category Found</li>';
    }


    $catlist.='</ul></div>
	</div>
	</div>
	';
} else {

    $catlist = "<b>Category</b>";

    if (!empty($qids)) {


        $sel_sugef = "select * from {category} as c join {question} as q on c.cat_id=q.cid where q.qid in (" . $qids . ") AND parent_id='0' group by c.cat_id   ";

        $rs_cat = db_query($sel_sugef);


        $catlist.='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';

        while ($cat_result = db_fetch_object($rs_cat)) {

            $cntquery = "SELECT COUNT(*) from  question where  cid=" . $cat_result->cat_id . " AND qid in (" . $qids . ")";
            $numrancnts = db_result(db_query($cntquery));


            $catlist.='<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cat_result->cat_id . '&txt_search=' . $txt_search . '">' . $cat_result->cat_name . '(' . $numrancnts . ')</a></li>';
        }
        $catlist.='</ul></div>
	</div>
	</div>
	';
    } else {

        $catlist.='<p>No Result Found</p>';
    }
}
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
if (isset($_REQUEST['cid'])) {
    $tagslist = "<b>Tags</b>";
    if (!empty($qids)) {
        $qry_tags = "select  distinct(tag.tag_id)  from question as  q,qtag as tag ,tagging as tg WHERE tag.qid in (" . $qids . ") AND q.cid='" . $_REQUEST['cid'] . "' and tag.qid=q.qid and tg.tid=tag.tag_id";
        $rs_tags = db_query($qry_tags);
        $tagslist.='
	<div id="container">
	<div class="feature">
	<div class="l col">
	<ul>';
        if (db_result($rs_tags) > 0) {
            while ($tag_result = db_fetch_object($rs_tags)) {
                $numtag = db_result(db_query("SELECT COUNT(*) from  qtag   where tag_id=" . $tag_result->tag_id . ""));
                $tagnme = db_query("select  *  from tagging  WHERE tid=" . $tag_result->tag_id . " ");
                $tagnme_result = db_fetch_object($tagnme);
                $tagslist.='<li>&nbsp;&nbsp; <a href="' . $gSitePath . 'searchquestion?tag=' . $tag_result->tag_id . '' . $link1 . '' . $link2 . '' . $link3 . '">' . $tagnme_result->tag . '(' . $numtag . ') </a> </li>';
            }
        } else {
            $tagslist.='<li>&nbsp;&nbsp;No Tags Found</li>';
        }

        $tagslist.='</ul></div>
	</div>
	</div>
	';
    } else {
        $tagslist.='<li>No Tags Found</li>';
    }
} else {
    $tagslist = "<b>Tags</b>";
    if (!empty($qids)) {
        $qry_tags = "select  distinct(tag.tag_id)  from question as  q,qtag as tag ,tagging as tg WHERE tag.qid in (" . $qids . ") AND tag.qid=q.qid and tg.tid=tag.tag_id";
        $rs_tags = db_query($qry_tags);

        $tagslist.='
	<div id="container">
	<div class="feature">
	<div class="l col">
	<ul>';
        if (db_result($rs_tags) > 0) {

            while ($tag_result = db_fetch_object($rs_tags)) {
                $numtag = db_result(db_query("SELECT COUNT(*) from  qtag   where tag_id=" . $tag_result->tag_id . ""));
                $tagnme = db_query("select  *  from tagging  WHERE tid=" . $tag_result->tag_id . " ");
                $tagnme_result = db_fetch_object($tagnme);
                $tagslist.='<li>&nbsp;&nbsp; <a href="' . $gSitePath . 'searchquestion?tag=' . $tag_result->tag_id . '' . $link1 . '' . $link2 . '' . $link3 . '&txt_search=' . $txt_search . '">' . $tagnme_result->tag . '(' . $numtag . ') </a> </li>';
            }
        } else {

            $tagslist.='<li>No Tags Found</li>';
        }

        $tagslist.='</ul></div>
	</div>
	</div>
	';
    } else {
        $tagslist.='<li>&nbsp;&nbsp;No Tags Found</li>';
    }
}
echo $tagslist;
?>