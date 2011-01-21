function validate_reg()
{
var err='';
//alert("llll");

	if (document.getElementById("rname").value=='')
	{

	err=err+"<li>User name should not be  blank!</li>";

	}

         var ck_uname = /^[A-Za-z0-9_]{5,20}$/;
    if(!jQuery('#rname').val().match(ck_uname)){

       err=err+"Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ";
    }

    if (document.getElementById("fname").value=='')
	{
	
	err=err+"<li>First Name should not be blank!</li>";
	
	}



	if (document.getElementById("lname").value=='')
	{
	
	err=err+"<li>Last Name should not be blank!</li>";
	
	}

    
	if (document.getElementById("edit-mail").value=='')
	{
	
	err=err+"<li>Email Id must not blank!</li>";
	
	}
	
	if (!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(document.getElementById("edit-mail").value)))
	{
	
	err=err+"<li>Please Enter the Valid Email Id!</li>";
	
	} 
	
        if (document.getElementById("dob").value!='')
	{
            
        if(!(/^[0-9]{4}$/.test(document.getElementById("dob").value)))
        {
	
	err=err+"<li>Date Of Birth must be valid format YYYY-[1986]!</li>";
	
	}}

        var zip=jQuery('#edit-zip').val();

        if(zip.length>0){
            var zstate=jQuery('input[name="state"]').val();;
            if(jQuery.trim(zstate).length<1)
                err=err+"<li>Please re-check the zip code you have entered check space if needed </li>";
        }

            var pic=jQuery('input:radio[name=pic_avt]:checked').val();
   // if(pic==1&&jQuery('#edit-file-upload').val().length<2){
     //  err=err+"<li>Please upload Image for your profile or pick an avatar below! </li>";

   // }

    if(pic==2&&jQuery("input[name=select_avatar]:checked").length<1){
       err=err+"<li>Please pick any avatar or upload an image above </li>";

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
        err=err+"<li>Please provide proper url format Ex: http://www."+host1+".com/username </li>";
    }else if(host1!=host2)
   err=err+"<li>Please provide "+host1+" link for "+host1+" field </li>";
    }

} );

        if(err.length>0){
            window.scrollTo(0,0);
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

function UriParser(uri){
//define class (for use with prototype.js) to do URI parsing
//modified from FlogUriParser found at http://www.flog.co.nz/index.php/journal/prototype-uri-parser-class/
this._regExp = /^((\w+):\/\/\/?)?((\w+):?(\w+)?@)?([^\/\?:]+):?(\d+)?(\/?[^\?#;\|]+)?([;\|])?([^\?#]+)?\??([^#]+)?#?(\w*)/;
this.username = "";
this.password = "";
this.port = "";
this.protocol = "";
this.host = "";
this.pathname = "";
this.url = "";
this.urlparamseparator = "";
this.urlparam = "";
this.querystring = {};
this.fragment = "";
this.results = null;

this._getVal = function(r, i) {
if(!r) return null;
return (typeof(r[i]) == 'undefined' ? "" : r[i]);
};

this.parse = function(uri) {
var r = this._regExp.exec(uri);
this.results = r;
this.url = this._getVal(r,0);
this.protocol = this._getVal(r,2);
this.username = this._getVal(r,4);
this.password = this._getVal(r,5);
this.host = this._getVal(r,6);
this.port = this._getVal(r,7);
this.pathname = this._getVal(r,8);
this.urlparamseparator = this._getVal(r,9);
this.urlparam = this._getVal(r,10);
this.querystring = this._getVal(r,11);
this.fragment = this._getVal(r,12);
return r;
}
if(uri) this.parse(uri);
}
 function onLoad() {
	        // get user info
	        gigya.services.socialize.getUserInfo(conf, {callback: renderUI});

	        // register for connect status changes
	        gigya.services.socialize.addEventHandlers(conf,
	                  {onConnectionAdded: renderUI, onConnectionRemoved: renderUI});

	    }


                function renderUI(res) {

	    }

	    // Get the user's friends
	    function getFriends() {
	        gigya.services.socialize.getFriendsInfo(conf, {callback: getFriends_callback});
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