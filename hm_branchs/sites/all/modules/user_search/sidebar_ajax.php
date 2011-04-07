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

if($_REQUEST['sel_id']!=''){

        $selid = $_REQUEST['sel_id'];

          $left_qry = db_query("select * from category  where parent_id='" .$selid. "'");

    while($left_rows = db_fetch_object($left_qry))
    {

       echo "<br/><span style='padding-left:10px' class='sidelinks'><a href='JavaScript:void(0);' sid=".$left_rows->cat_id." class='sidelinks nike'>".$left_rows->cat_name."</a></span>";
    }
        exit;
    }
?>


