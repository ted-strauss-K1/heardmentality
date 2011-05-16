function validate_reg()
{
    var err='';
    //alert("llll");

    if (document.getElementById("rname").value=='')
    {

        err=err+"User name should not be  blank! ";

    }

    var ck_uname = /^[A-Za-z0-9_]{5,20}$/;
    if(!jQuery('#rname').val().match(ck_uname)){

        err=err+" Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ";
        load_notify(err);
        return false;
    }

    if (document.getElementById("fname").value=='')
    {
	
        err=err+"First Name should not be blank! ";
	
    }



    if (document.getElementById("lname").value=='')
    {
	
        err=err+" Last Name should not be blank!";
        load_notify(err);
        return false;
    }

    
    if (document.getElementById("edit-mail").value=='')
    {
	
        err=err+" Email Id must not blank! ";
	
    }
	
    if (!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(document.getElementById("edit-mail").value)))
    {
	
        err=err+" Please Enter the Valid Email Id!";
        load_notify(err);
        return false;
    }
	
    if (document.getElementById("dob").value!='')
    {
            
        if(!(/^[0-9]{4}$/.test(document.getElementById("dob").value)))
        {
	
            err=err+" Date Of Birth must be valid format YYYY-[1986]! ";
            load_notify(err);
            return false;
        }
    }

var zip=jQuery('#edit-zip').val();

if(zip.length>0){
    var zstate=jQuery('input[name="state"]').val();
  
    if(jQuery.trim(zstate).length<1){
       err=err+" Please re-check the zip code you have entered check space if needed  ";
    load_notify(err);
    return false;
    }
       
}

var pic=jQuery('input:radio[name=pic_avt]:checked').val();
// if(pic==1&&jQuery('#edit-file-upload').val().length<2){
//  err=err+"<li>Please upload Image for your profile or pick an avatar below! </li>";

// }

if(pic==2&&jQuery("input[name=select_avatar]:checked").length<1){
    err=err+" Please pick any avatar or upload an image above  ";
load_notify(err);
    return false;
}

jQuery('div.social-rite input').each( function(){

    var uid=jQuery(this).attr('id');
    var url=jQuery(this).val();
    var patt= /^http:\/\/(www.)*([a-zA-Z0-9]*)*(.)*/;
    if(url.length>0){
        //edit-follow-links-facebook-url
        var npt=uid.split('-');
        var host1=npt[3];

        url.match(patt);
        var host2=RegExp.$2;
        if(!patt.test(url)){
            err=err+"<small> Please provide proper url format Ex: http://www."+host1+".com/username,  </small>";
        }else if(host1!=host2){
             err=err+" <small> Please provide "+host1+" link for "+host1+" field,<small>  ";
           
        }
           
    }

} );

if(err.length>0){
   // window.scrollTo(0,0);
    // err=err.wrap('<ul></ul>');
   // jQuery('#twitMsg',top.document).html(err);
  //  jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
   load_notify(err);
    return false;
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

function load_notify(err){

    window.scrollTo(0,0);
    // err=err.wrap('<ul></ul>');
    jQuery('#twitMsg',top.document).html(err);
    jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);

}
function onLoad() {
    // get user info
    gigya.services.socialize.getUserInfo(conf, {
        callback: renderUI
    });

    // register for connect status changes
    gigya.services.socialize.addEventHandlers(conf,
    {
        onConnectionAdded: renderUI,
        onConnectionRemoved: renderUI
    });

}


function renderUI(res) {

}

// Get the user's friends
function getFriends() {
    gigya.services.socialize.getFriendsInfo(conf, {
        callback: getFriends_callback
    });
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

 jQuery(document).ready(function(){

        if(jQuery('#err_div').html().length>2){
            jQuery('#twitMsg',top.document).html(jQuery('#err_div').html());
         jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
     }

    });