function trim(pmString)
{
	return pmString.replace( /^ +/, "" ).replace( / +$/, "" );
}

function validMashup(frm)
{
	document.getElementById('errQFSize').innerHTML=""
	document.getElementById('errAFSize').innerHTML=""
	document.getElementById('errWidth').innerHTML=""
	document.getElementById('errHeight').innerHTML=""
	
	if(trim(frm.selQFSize.value) == '')
	{
		document.getElementById('errQFSize').innerHTML="Please select the question font size"
		frm.selQFSize.focus();
		return false;
	}
	else if(trim(frm.selAFSize.value) == '')
	{
		document.getElementById('errAFSize').innerHTML="Please select the answer font size"
		frm.selAFSize.focus();
		return false;
	}
	else if(trim(frm.txtWidth.value) == '')
	{
		document.getElementById('errWidth').innerHTML="Please enter the frame width"
		frm.txtWidth.focus();
		return false;
	}
	else if(trim(frm.txtWidth.value) != '' && isNaN(frm.txtWidth.value) == true)
	{
		document.getElementById('errWidth').innerHTML="Please enter the frame width in numbers"
		frm.txtWidth.focus();
		return false;
	}
	else if(trim(frm.txtHeight.value) == '')
	{
		document.getElementById('errHeight').innerHTML="Please enter the frame height"
		frm.txtHeight.focus();
		return false;
	}
	else if(trim(frm.txtHeight.value) != '' && isNaN(frm.txtHeight.value) == true)
	{
		document.getElementById('errHeight').innerHTML="Please enter the frame height in numbers"
		frm.txtHeight.focus();
		return false;
	}
	else
	{
		return true;
	}
	return false;
}