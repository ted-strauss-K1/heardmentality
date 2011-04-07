<?php
 error_reporting(0);
 $txt_search = $_REQUEST['txt_search'];
$q_country = $_REQUEST['q_country'];
$q_state = $_REQUEST['q_state'];
$q_city = $_REQUEST['q_city'];

$options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo',NULL,$options);
	//echo '<form name="thisform" action="' . $gSitePath . 'searchquestion" method="post">';
    echo '<span class="black12" style="margin-left:10px">Location:</span>';
   echo '  <div class="padding10" >';
$optionlist.=' <option value="0" >Country</option>';
    foreach ($result->results as $country) {
        if($country['countryname']==$q_country)
        {
           // $select = "'selected'";
            $select =  "selected=selected";
        }
        else
        {
            $select = '';
        }
        $optionlist .= sprintf('<option value="%s" '.$select.'>%s</option>', $country['countryname'], $country['countryname']);
    }
   //$txt_search =  $_GET['txt_search'];
   $cid =  $_GET['cid'];

    /*onchange="click_submit(this.value,<?php echo $_GET['permission']?>)"*/?>
 <div class="listmenu">
<select name="q_country" class="listbox" style="width: 125px;" tabindex="16"  onchange="get_stateuser(this.value,'<?php echo $txt_search; ?>')" id="q_country"><?php echo  $optionlist ?></select>
 </div>
<?php
//echo '<input type="hidden" name="q_country" value='.$q_country.'/>';
//echo $optionlist;
$q_country = $_GET['q_country'];

if($q_country!='')
{

    $query = array('query'=>$_REQUEST['q_country'],'maxRows'=>'1','featureclass'=>'S');
                $result = geonames_query('search', $query);
               // $cc=$result->results[0]['countrycode'];
               // $result = geonames_query('countryinfo', $query);
               // $result->results[0][geonameid];
                $query = array('country'=>$result->results[0]['countrycode']);
                $result = geonames_query('countryinfo', $query);
                 $query = array('geonameid'=>$result->results[0]['geonameid']);
                $result = geonames_query('children', $query);


                /*$query = array('country'=>$q_country);
                $result = geonames_query('countryinfo', $query);

                $query = array('geonameid'=>$result->results[0][geonameid]);
                $result = geonames_query('children', $query);*/
                $q_country = $_GET['q_country'];
                ?>
               <div class="listmenu">
                <select tabindex="18" class="listbox" style="width: 125px;" onchange="get_cityuser(this.value,'<?php echo $txt_search ?>','<?php echo $q_country ?>')"  id="q_state" name="q_state"> <option value="">--States--</option>
                    <?php
                foreach ($result->results as $state) {

                    if($state['geonameid']==$q_state)
                    {
                       // $select = "'selected'";
                        $select =  "selected=selected";
                    }
                    else
                    {
                        $select = '';
                    }

                    $ret .= sprintf('<option value="%s"'.$select.'>%s</option>', $state['geonameid'], $state['name']);
                }
               echo  $ret .= "</select></div>";
}
else
{
echo'<div id="chg_state">
    <div class="listmenu">
    <select id="q_state" class="listbox" name="q_state" onchange="get_citysquestion(this.value);" style="width: 125px;" tabindex="18">
    <option value="0" >State/Province</option>
    </select>
    </div></div>';
}

                $query = array('geonameid'=>$q_state);
                $result = geonames_query('children', $query);
                //print_r($result);
                ?>
                    <div class="listmenu">
                <select class="listbox"  tabindex="19" onchange="get_user(this.value,'<?php echo $txt_search ?>','<?php echo $q_country ?>','<?php echo $q_state ?>')"  style="width: 125px;"  id="q_city" name="q_city">
                    <?php
                 $ret = '<option value="">Cities</option> ';
                foreach ($result->results as $state) {

                     if($state['geonameid']==$q_city)
                    {
                        //$select = "'selected'";
                         $select =  "selected=selected";
                    }
                    else
                    {
                        $select = '';
                    }

                    $ret .= sprintf('<option value="%s" '.$select.'>%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select></div>";
                echo $ret;

               // else
               // {
                //echo '<div id="chg_city"><select name="q_city" id="q_city" style="width: 125px;" tabindex="19"> <option value="0" >--Cities--</option></select></div>';
               // }

echo '</div>';
//echo '</form>';
?>