function validate_reg()
{


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
	document.getElementById("err_div").innerHTML = "NickName must not blank..."; 	   
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
	if (document.getElementById("dob").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "NickName must not blank..."; 	   
	return false;
	}
	return true;
}