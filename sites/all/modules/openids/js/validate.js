function validate_reg()
{


    if (document.getElementById("uname").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "User Name must not blank..."; 	   
	return false;
	}



	if (document.getElementById("pass1").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Password must not blank..."; 	   
	return false;
	}
	if (document.getElementById("pass2").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Confirm Password must not blank..."; 	   
	return false;
	}
	if(document.getElementById("pass1").value != document.getElementById("pass2").value)
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Your Password and confirm Password must be same...";
	return false;
	}
    
	if (document.getElementById("pass2").value=='')
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Confirm Password must not blank..."; 	   
	return false;
	}
	
	if (!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(document.getElementById("email").value)))
	{
	document.getElementById("errbox").focus();
	document.getElementById("err_div").innerHTML = "Please Enter the Valid Email Id...";
	return false;
	} 
	
	return true;
}