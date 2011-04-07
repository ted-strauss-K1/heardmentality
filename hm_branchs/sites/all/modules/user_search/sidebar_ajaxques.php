<?php
$link1 = '';
$link2 = '';
$link3 = '';
$cid = '';
$scid = '';
global $gSitePath, $user, $gDocPath, $base_root, $base_path;
//$query = facetad_refine();
//$sel_search = mysql_query($query['query']);
//$txt_search = trim($query['txt_search']);
//$qids = array();
//echo $_REQUEST['scid'];

$cond = '';
       
       
           $scid = $_REQUEST['scid'];
           //$cond =" AND cat.scat=$scid";
       
if($_REQUEST['sel_id']!=''){

        $selid = $_REQUEST['sel_id'];
      $sel_cat = "select * from category as cat join question_cat as ques on ques.cat=cat.cat_id where cat.parent_id=$selid group by cat.cat_id";

       // echo $sel_cat = "select * from category as cat join question_cat as ques on ques.cat=cat.cat_id join question as q on q.qid=ques.qid  where cat.parent_id='" .$selid. "'";
          $left_qry = mysql_query($sel_cat);

    while($left_rows = mysql_fetch_object($left_qry))
    {
        $ct_qry = "select * from question as q join question_cat as cat on q.qid=cat.qid where 1 AND cat.scat=$left_rows->cat_id AND cat.cat=$selid group by cat.qid";
        $ct_res = mysql_query($ct_qry);
        $ct_rows = mysql_num_rows($ct_res);

       echo "<br/><span style='padding-left:10px' class='sidelinks'><a href='JavaScript:void(0);' sid=".$left_rows->cat_id." class='speciallinks nike'>".$left_rows->cat_name."[$ct_rows]</a></span>";
    }
        exit;
    }
?>


