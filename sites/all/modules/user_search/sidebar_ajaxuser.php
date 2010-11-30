<?php
mysql_connect("localhost","root",""); //oPenWave#1220
mysql_select_db("heardmentality");
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
//print_r($_REQUEST);
if($_REQUEST['sel_id']!=''){

        $selid = $_REQUEST['sel_id'];

          $left_qry = mysql_query("select * from category  where parent_id='" .$selid. "'");

    while($left_rows = mysql_fetch_object($left_qry))
    {
        $count_row3 =  mysql_num_rows(mysql_query("SELECT count(*) FROM users reg, user_profile img, follower fol where (fol.cat_id=$left_rows->cat_id) AND reg.status=1 and reg.uid=fol.uid group by fol.uid"));
        if($count_row3>0){ $count_row3 =  "[$count_row3]";}else{$count_row3='';}

       echo "<br/><span style='padding-left:10px' class='sidelinks'><a href='JavaScript:void(0);' sid=".$left_rows->cat_id." class='sidelinks nike'>".$left_rows->cat_name."$count_row3</a></span>";
    }
        exit;
    }
?>


