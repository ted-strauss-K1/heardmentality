<?php
$txt_search = $_REQUEST['txt_search'];
$q_country = $_REQUEST['q_country'];
$q_state = $_REQUEST['q_state'];
$q_city = $_REQUEST['q_city'];

$options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo',NULL,$options);
	//echo '<form name="thisform" action="' . $gSitePath . 'searchquestion" method="post">';
   echo '  <div class="padding10" >';
$optionlist.=' <option value="0" >--Country--</option>';
    foreach ($result->results as $country) {
        if($country['countrycode']==$q_country)
        {
            $select = "'selected'";
        }
        else
        {
            $select = '';
        }
        $optionlist .= sprintf('<option value="%s" '.$select.'>%s</option>', $country['countrycode'], $country['countryname']);
    }
   $txt_search =  $_GET['txt_search'];
   $cid =  $_GET['cid'];

    /*onchange="click_submit(this.value,<?php echo $_GET['permission']?>)"*/?>
<select name="q_country" style="width: 125px;" tabindex="16"  onchange="get_statequestion(this.value,'<?php echo $txt_search ?>','<?php echo $cid ?>')" id="q_country"><?php echo  $optionlist ?></select>
<?php
//echo '<input type="hidden" name="q_country" value='.$q_country.'/>';
//echo $optionlist;
$q_country = $_GET['q_country'];

if($q_country!='')
{
$query = array('country'=>$q_country);
                $result = geonames_query('countryinfo', $query);

                $query = array('geonameid'=>$result->results[0][geonameid]);
                $result = geonames_query('children', $query);
                $q_country = $_GET['q_country'];
                ?>
               
                <select tabindex="18" class="listbox2" style="width: 125px;" onchange="get_cityquestion(this.value,'<?php echo $txt_search ?>','<?php echo $cid ?>','<?php echo $q_country ?>')"  id="q_state" name="q_state"> <option value="">--States--</option>
                    <?php 
                foreach ($result->results as $state) {

                    if($state['geonameid']==$q_state)
                    {
                        $select = "'selected'";
                    }
                    else
                    {
                        $select = '';
                    }
                    
                    $ret .= sprintf('<option value="%s"'.$select.'>%s</option>', $state['geonameid'], $state['name']);
                }
               echo  $ret .= "</select>";
}
else
{
echo'<div id="chg_state">
    <select id="q_state" name="q_state" onchange="get_citysquestion(this.value);" style="width: 125px;" tabindex="18">
    <option value="0" >--State--</option>
    </select>
    </div>';
}
               
                $query = array('geonameid'=>$q_state);
                $result = geonames_query('children', $query);
                //print_r($result);
                ?>
                <select class="listbox2"  tabindex="19" onchange="get_question(this.value,'<?php echo $txt_search ?>','<?php echo $cid ?>','<?php echo $q_country ?>','<?php echo $q_state ?>')"  style="width: 125px;"  id="q_city" name="q_city">
                    <?php
                 $ret = '<option value="">--Cities--</option> ';
                foreach ($result->results as $state) {

                     if($state['geonameid']==$q_city)
                    {
                        $select = "'selected'";
                    }
                    else
                    {
                        $select = '';
                    }

                    $ret .= sprintf('<option value="%s" '.$select.'>%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select>";
                echo $ret;
               
               // else
               // {
                //echo '<div id="chg_city"><select name="q_city" id="q_city" style="width: 125px;" tabindex="19"> <option value="0" >--Cities--</option></select></div>';
               // }

echo '</div>';
//echo '</form>';
?>