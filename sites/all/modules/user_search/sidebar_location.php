<?php
$txt_search = $_REQUEST['txt_search'];
$q_country = $_REQUEST['q_country'];
$q_state = $_REQUEST['q_state'];

$options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo',NULL,$options);
	echo '<form name="thisform" action="' . $gSitePath . 'searchquestion" method="post">';
   echo '  <div class="padding10" >';
$optionlist.=' <option value="0" >--Country--</option>';
    foreach ($result->results as $country) {
        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countrycode'], $country['countryname']);
    }
echo '<select name="q_country" style="width: 125px;" tabindex="16"  onchange="get_statequestion();" id="q_country">'.$optionlist.'</select>';

//echo '<input type="hidden" name="q_country" value='.$q_country.'/>';
//echo $optionlist;


$query = array('country'=>$q_country);
                $result = geonames_query('countryinfo', $query);

                $query = array('geonameid'=>$result->results[0][geonameid]);
                $result = geonames_query('children', $query);
                //print_r($result);
                $ret = '<select tabindex="18" class="listbox2" style="width: 125px;"  onchange="get_statequestion();" id="q_state" name="q_state"> <option value="">--States--</option>';
                foreach ($result->results as $state) {
                    if($state['geonameid']==$q_country)
                    {
                        $select = "selected";
                    }
                    $ret .= sprintf('<option value="%s"'.$select.'>%s</option>', $state['geonameid'], $state['name']);
                }
               echo  $ret .= "</select>";
               //echo '<input type="hidden" name="q_state" value='.$q_state.'/>';

/*echo'<div id="chg_state">
    <select id="q_state" name="q_state" onchange="get_citysquestion(this.value);" style="width: 125px;" tabindex="18">
    <option value="0" >--State--</option>
    </select>
    </div>';*/

                $query = array('geonameid'=>$q_state);
                $result = geonames_query('children', $query);
                //print_r($result);
                $ret = '<select class="listbox2"  tabindex="19"  style="width: 125px;"  id="q_city" name="q_city" onchange="get_statequestion();">
                 <option value="">--Cities--</option> ';
                foreach ($result->results as $state) {

                    $ret .= sprintf('<option value="%s">%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select>";
                echo $ret;
//echo '<div id="chg_city"><select name="q_city" id="q_city" style="width: 125px;" tabindex="19"> <option value="0" >--Cities--</option></select></div>';

echo '</div>';
echo '</form>';
?>