function validate_reg()
{

//alert("llll");
    if (document.getElementById("fname").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "First Name must not blank..."; 	   
	return false;
	}



	if (document.getElementById("lname").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Last Name must not blank..."; 	   
	return false;
	}
	if (document.getElementById("rname").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "RealName must not blank..."; 	   
	return false;
	}
	
    
	if (document.getElementById("edit-mail").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Email Id must not blank..."; 	   
	return false;
	}
	
	if (!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(document.getElementById("edit-mail").value)))
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Please Enter the Valid Email Id...";
	return false;
	} 
	
        if (document.getElementById("dob").value!='')
	{
            
        if(!(/^([0-2]\d|3[0-1]|[1-9])\/(0\d|1[0-2]|[1-9])\/(\d{4})$/.test(document.getElementById("dob").value)))
        {
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Date Of Birth must be valid format MM/DD/YYYY-[14/07/1986]...";
	return false;
	}}
	/*//alert(document.getElementById("edit-religion").value);
	if (document.getElementById("edit-religion").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Select Religion..."; 	   
	return false;
	}
	if (document.getElementById("edit-ethnic").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Select Ethinic..."; 	   
	return false;
	}
	
	
	if (document.getElementById("edit-slant").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Select Slant..."; 	   
	return false;
	}
	
	
	
	
	if (document.getElementById("edit-zip").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "ZipCode must not blank..."; 	   
	return false;
	}
	
	*/
	
	return true;
}