function validate_reg()
{
var err='';
//alert("llll");
    if (document.getElementById("fname").value=='')
	{
	document.getElementById("#errbox").focus();
	err=err+"<li>First Name must not blank!</li>";
	
	}



	if (document.getElementById("lname").value=='')
	{
	document.getElementById("#errbox").focus();
	err=err+"<li>Last Name must not blank!</li>";
	
	}
	if (document.getElementById("rname").value=='')
	{
	document.getElementById("#errbox").focus();
	err=err+"<li>RealName must not blank!</li>";
	
	}
	
    
	if (document.getElementById("edit-mail").value=='')
	{
	document.getElementById("#errbox").focus();
	err=err+"<li>Email Id must not blank!</li>";
	
	}
	
	if (!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(document.getElementById("edit-mail").value)))
	{
	document.getElementById("#errbox").focus();
	err=err+"<li>Please Enter the Valid Email Id!</li>";
	
	} 
	
        if (document.getElementById("dob").value!='')
	{
            
        if(!(/^[0-9]{4}$/.test(document.getElementById("dob").value)))
        {
	document.getElementById("#errbox").focus();
	err=err+"<li>Date Of Birth must be valid format YYYY-[1986]!</li>";
	
	}}
            var pic=jQuery('input:radio[name=pic_avt]:checked').val();
    if(pic==1&&jQuery('#edit-file-upload').val().length<2){
       err=err+"<li>Please upload Image for your profile or pick an avatar below! </li>";

    }

    if(pic==2&&jQuery("input[name=select_avatar]:checked").length<1){
       err=err+"<li>Please pick any avatar or upload an image above </li>";

    }


        if(err.length>0){
       // err=err.wrap('<ul></ul>');
        jQuery('#err_div').html(err);
          jQuery('#err_div').animate({backgroundcolor: "#fff568"}, "slow").animate({backgroundcolor: "#FF0000"}, "slow");
          jQuery('#err_div').addClass('error');
        return false;
        }else{
              jQuery('#err_div').addClass('');
        }
	
	return true;
}



jQuery('#edit-file-upload').live('change', function() {
jQuery('input:radio[name=pic_avt]:first').attr('checked',true);
jQuery("div.form-item img").hasClass("avatar-select").removeClass('avatar-select');
});


jQuery('div.form-item img').live('click', function() {
 
jQuery('input:radio[name=pic_avt]:nth(1)').attr('checked',true);
});


jQuery('div.avatar-selection-pager-nav a').live('click', function() {
setTimeout('chk_avatar()',1000);

});


 function onLoad() {
	        // get user info
	        gigya.services.socialize.getUserInfo(conf, { callback: renderUI });

	        // register for connect status changes
	        gigya.services.socialize.addEventHandlers(conf,
	                  { onConnectionAdded: renderUI, onConnectionRemoved: renderUI });

	    }


                function renderUI(res) {

	    }

	    // Get the user's friends
	    function getFriends() {
	        gigya.services.socialize.getFriendsInfo(conf, { callback: getFriends_callback });
	        document.getElementById('btnGetFriends').disabled = true;
	    }

	    // Use the reponse of getFriends and render HTML to display the first five friends.
	    function getFriends_callback(response) {
	        document.getElementById('btnGetFriends').disabled = false;
	        document.getElementById('friends').innerHTML = "";
	        if (response.errorCode == 0) {
	            var array = response.friends.asArray();
	            var html = "You have " + array.length + " friends, here are a few of them:<BR/>";
	            html += "<table cellpadding=20><tr>";
	            for (var i = 0; i < Math.min(5, array.length); i++) {
	                html += "<td align=center valign='bottom'>";
	                if (array[i].thumbnailURL)
	                    html += "<img width='50' height='50' src='"
	                    + array[i].thumbnailURL + "' ><br>";
	                html += array[i].nickname + "</td>";
	            }
	            html += "</tr></table>";
	            document.getElementById('friends').innerHTML = html;
	        } else {
		        alert('Error :' + response.errorMessage);
		    }

	    }