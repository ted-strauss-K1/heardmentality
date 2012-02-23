<?php
function donation_paypal()
{
global $gSitePath,$user, $gDocPath,$base_root;
$opdonate='        <h1 class="do-intop din">MAKE A DONATION</h1>
        <div class="inside">
        <p>Heard Mentality is a nonprofit and relies on your individual donations.<br />
        Please make your donation now.<br /><br /></p>
<script language="javascript" type="text/javascript">
function validateForm(form) {

  var minimums = {
    "USD" : 1,
    "GBP" : 1, // $1.26
    "EUR" : 1, // $1.26
    "AUD" : 2, // $1.35
    "CAD" : 1, // $0.84
    "CHF" : 1, // $0.85
    "CZK" : 20, // $1.03
    "DKK" : 5, // $0.85
    "HKD" : 10, // $1.29
    "HUF" : 200, // $0.97
    "JPY" : 100, // $1
    "NZD" : 2, // $1.18
    "NOK" : 10, // $1.44
    "PLN" : 5, // $1.78
    "SGD" : 2, // $1.35
    "SEK" : 10 // $1.28
  };

  var error = true;

  // Get amount selection
  var amount = null;
  for ( var i = 0; i < form.amount.length; i++ ) {
    if ( form.amount[i].checked ) {
      amount = form.amount[i].value;
    }
  }
  if ( form.amountGiven.value != "" ) {
    amount = form.amountGiven.value;
  }
  // Check amount is a real number
  error = ( amount == null || isNaN( amount ) || amount.value <= 0 );
  if ( error ) {
    alert( "You must enter a valid amount (for example \'35\')." );
  }

  // Check amount is at least the minimum
  var currency = form.currency_code[form.currency_code.selectedIndex].value;
  if ( typeof( minimums[currency] ) == "undefined" ) {
    minimums[currency] = 1;
  }
  if ( amount < minimums[currency] ) {
    alert( "You must contribute at least $1".replace(\'$1\', minimums[currency] + \' \' + currency ) );
    error = true;
  }
  
  return !error;
}


function redirectPayment(i) {
  action_url="'.$gSitePath.'/paypal";
 
    document.paypalcontribution.action = action_url;
   if(validateForm(i)){
    document.getElementById(\'paypalcontribution\').submit();
    }
}
</script>
<form name="paypalcontribution" method="post" onSubmit="return validateForm(this);" id="paypalcontribution" action="'.$gSitePath.'paypal">
  

<div class="row1">
<strong>Select your tax-deductible gift amount:</strong>
<div class="clr"></div>

<div class="lin1"><input type="radio" value="35" onclick="document.getElementById(\'amountGiven\').value=\'\'" id="input_amount_3" name="amount"/>$35</div> 
<div class="lin1"><input type="radio" value="50" onclick="document.getElementById(\'amountGiven\').value=\'\'" id="input_amount_2" name="amount"/>
$50 </div>
<div class="lin1"><input type="radio" value="75" onclick="document.getElementById(\'amountGiven\').value=\'\'" id="input_amount_1" name="amount"/>
$75 </div>
<div class="lin1"><input type="radio" value="100" onclick="document.getElementById(\'amountGiven\').value=\'\'" id="input_amount_0" name="amount"/>
$100</div>
<div class="lin1">

<input type="radio" value="Other" id="input_amount_other" name="amount"/>Other:
</div>
<div class="lin2">
<input type="text" onfocus="this.form.input_amount_other.checked=true;" size="3" name="amountGiven" id="amountGiven"/> 
</div>
<div class="lin2">
<!-- currency menu --><select onchange="updateCC(this.value);" style="width: 7em;" size="1" id="input_currency_code" name="currency_code"><option selected="" value="USD">USD &#45; &#36</option>
<option value="XXX">-------</option>
<option value="GBP">GBP &#45; &#163;</option>
<option value="EUR">EUR &#45; &#8364;</option>
<option value="USD">USD &#45; &#36</option>
<option value="AUD">AUD &#45; &#36</option>
<option value="CAD">CAD &#45; &#36</option>

<option value="CHF">CHF &#45; Fr.</option>
<option value="CZK">CZK &#45; Kc</option>
<option value="DKK">DKK &#45; kr</option>
<option value="HKD">HKD &#45; HK$</option>
<option value="HUF">HUF &#45; Ft</option>
<option value="ILS">ILS - ?</option>
<option value="JPY">JPY &#45; �</option>
<option value="NOK">NOK &#45; kr</option>
<option value="NZD">NZD &#45; NZ&#36</option>
<option value="PLN">PLN &#45; zl</option>
<option value="SEK">SEK &#45; kr</option>
<option value="SGD">SGD &#45; S&#36</option></select>

</div>
</div>
<div class="clr"></div>
<div class="row1"><br />

<strong>Public comment</strong><br />
Have a thought to share with the world? Put up to 200 characters here:
<div class="textbox-lengthy">
<input type="text" style="width: 70%;" maxlength="200" size="30" name="comment"/>
</div>
<div><input type="checkbox" checked="checked" value="1" id="input_comment-option" name="comment-option" style="margin: 0pt;"/>  <label for="input_comment-option">Please list my name (next to my comment) on the public donor list.</label></div>
<div><input name="" checked="checked"  disabled="disabled" type="checkbox" value="" />&nbsp;&nbsp; I agree to receive future Heard Mentality newsletters or emails .(We will never sell or trade your information . Our privacy policy can be found<span> here</span>) </div>
</div>
<div class="clr"></div>


<div class="donate">
<input type="image" src="'.$gSitePath.path_to_theme().'/images/donate-paypal.png"   class="input-button button-navyblue" value="Donate via PayPal"/>
</div>
<div class="clr"></div>
<div>
<strong>Other ways to give</strong><br />

For more information about our non-profit status or other questions , <span><a href="#" class="links">click here.</a></span>


</div>

        
        
        </div>';

return $opdonate;

}


function paypal_process()
{
global $gSitePath,$user, $gDocPath,$base_root;
if($_REQUEST['amount']=="Other")
$amt = $_REQUEST["amountGiven"];
else
$amt = $_REQUEST["amount"];
//echo $amt;
 $ccode = $_REQUEST["currency_code"];
$cmt=$_REQUEST["comment"];
$amtr=$amt;
$ins_commg="insert into   donor_list (uid,comment,amount,ccode) values('".$user->uid."' ,'".$cmt."','".$amtr."','".$ccode."') ";
$rs_commg=db_query($ins_commg);
$lid=mysql_insert_id();
$chkop='<body>
<form  action="https://www.sandbox.paypal.com/cgi-bin/webscr"  method="get" name= "form1" id="form1">
		<INPUT TYPE="hidden" NAME="cmd" VALUE="_xclick">
		<input type="hidden" name="business" value="nagasubramani@yahoo.com">
		
		<input type="hidden" name="item_name" value="Heardmentality">
		<input type="hidden" name="item_number" value="'.$lid.'">
		<input type="hidden" name="amount" value="'.$amt.'">
		<input type="hidden" name="rm" value="2">
		<input type="hidden" name="txt_cmt" value="'.$cmt.'">
		
		<input type="hidden" name="shipping" value="0.00">
		<input type="hidden" name="shipping_extra" value="0.00">
		<input type="hidden" name="no_shipping" value="1">
			<input type="hidden" name="currency_code" value="'.$ccode.'">
		<input type="hidden" name="cancel_return" value="'.$gSitePath.'payfail">
		<input type="hidden" name="return" value="'.$gSitePath.'paysuccess">
		</form>
        </body>
<script language="javascript">
document.getElementById(\'form1\').submit();;
</script>';
return $chkop;

}
function paypal_fail()
{
global $gSitePath,$user, $gDocPath,$base_root;
$opfail='Transaction Failed';
return $opfail;

}
function paypal_success()
{
global $gSitePath,$user, $gDocPath,$base_root;
if($_POST["item_number"] && $_POST['verify_sign'] && $_POST['payment_status'])
{
$updt="update donor_list set paid='1' where did='".$_POST["item_number"]."'";
$str=db_query($updt);
}

$opsuc='Thanks for donation ';
return $opsuc;

}

function donor_list()
{

global $gSitePath,$user, $gDocPath,$base_root;

$seldonar="select * from donor_list where paid='1'";

$res_donar=db_query($seldonar);
$listd='<table width="100%" border="1">
  <tr>
    <td>Name</td>
    <td>comment</td>
    <td>Amount</td>
    <td>Date</td>
  </tr>';
while($don=db_fetch_object($res_donar))
{
if($don->uid=='0')
{
$uname='Anononyms';
}
else
{
 $sellist="select * from users where uid='".$don->uid."'";
$res_users=db_query($sellist);
$usert=db_fetch_object($res_users);
 $uname=$usert->name;
}
$listd.='<tr>
    <td>'.$uname.'</td>
    <td>'.$don->comment.'</td>
    <td>'.$don->amount.' '.$don->ccode.'</td>
    <td>'.$don->donate_date.'</td>
  </tr>';


}

return $listd;
}

?>