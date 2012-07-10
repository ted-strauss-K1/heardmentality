

var scrollOnValidateError = true;


function clear_validate_messages()
{
  var allMessages = jQuery('div.validate-error');
  allMessages.each(
    function ()
    {
      if (!$(this).hasClass('validate-ajax'))
      {
        jQuery(this).remove();
      }
    });
}

function add_validate_message(elem, message, addClass)
{
  var elemParent = jQuery(elem).parent().parent();
  if (elemParent.find('div.validate-error').length == 0)
  {
    if (typeof addClass == 'undefined')
    {
      addClass = 'validate-error';
    }
    jQuery(elem).parent().after('<div class="' + addClass + '" style="display:none"><span>' + message + '</span></div>');
    elemParent.find('div.validate-error').slideDown();
  } else {
    var validateMessage = elemParent.find('div.validate-error span');
    validateMessage.html(message);
  }
}

function getDomain(url) {
  var arUrl =  url
    .replace('http://www.','')
    .replace('https://www.','')
    .replace('http://','')
    .replace('https://','')
    .replace('www.','')
    .split(/[/?#]/);
  var result = '';
  if (arUrl.length > 0)
  {
    result = arUrl[0];
  }
  return result;
}
function validate_reg()
{
  // return true;

  /*
   * validate classes
   *
   *   validate
   *
   *   validate-name
   *   validate-not-empty
   *   validate-email
   *   validate-date-year
   *   validate-zip
   *   validate-url
   *   validate-url-username
   *
   *
   *   error block
   *
   *   <div class="validate-error">
   *     <span>text</span>
   *   <div>
   *
   * */

  var validateElements = jQuery('input.validate, textarea.validate');
  clear_validate_messages();

  var errorCount = 0;

  validateElements.each(
    function ()
    {
      var ielem = $(this);
      var ielemVal = ielem.val();

      if (ielem.hasClass('validate-not-empty'))
      {
        if ((ielemVal == '') || ( (ielemVal == ielem.attr('blurtext'))))
        {
          add_validate_message(this, 'Field should not be blank!');
          errorCount++;
        }
      }


      if (ielem.hasClass('validate-username'))
      {
        if(!(/^[A-Za-z0-9_]{5,20}$/.test(ielemVal)))
        {
          add_validate_message(ielem, 'Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ');
          errorCount++;
        }
        /*
         if(!chk_uname(ielem, false))
         {

         }  */
      }

      if (ielem.hasClass('validate-name'))
      {
        if(!(/^([a-zA-Z]+ ){1,2}[a-zA-Z]+$/i.test(ielemVal)))
        {
          add_validate_message(this, 'Full Name should be Alpha Ex : Kevin kumar');
          errorCount++;
        }
      }


      if (ielem.hasClass('validate-email'))
      {
        if(!(/^[a-z0-9\.\-\_]+\@[a-z0-9\.\-]+\.[a-z0-9]{2,4}$/.test(ielemVal)))
        {
          add_validate_message(this, 'Please Enter the Valid Email Id!');
          errorCount++;
        }
      }

      if (ielem.hasClass('validate-date-year'))
      {
        if(!(/^[0-9]{4}$/.test(ielemVal)))
        {
          add_validate_message(this, 'Date Of Birth must be valid format YYYY-[1986]!');
          errorCount++;
        }
      }

      if (ielem.hasClass('validate-zip'))
      {
        if (!get_zip_city(ielem, false))
        {
          errorCount++;
        }
      }

      var patt= /^http:\/\/(www.)*([a-zA-Z0-9]*)*(.)*/;
      var host = ielem.attr('name');

      if (ielem.hasClass('validate-url-username') && (ielemVal != ''))
      {
        var hostVal = getDomain(ielemVal);
        if(!patt.test(ielemVal)) {
          add_validate_message(this, 'Please provide proper url format Ex: http://www.'+ host +'.com/username');
          errorCount++;
        } else if(host + '.com' != hostVal){
          add_validate_message(this, 'Please provide '+host+' link for '+host+' field');
          errorCount++;
        }
      }

      if (ielem.hasClass('validate-url') && (ielemVal != ''))
      {
        if(!patt.test(ielemVal)){
          add_validate_message(this, 'Please provide proper url format im My website Ex: http://www.'+host+'.com');
          errorCount++;
        }
      }

    });


  errorCount = $('div.validate-error').length;
  if (errorCount > 0)
  {
    if (scrollOnValidateError)
    {
      var destination = $('div.validate-error:first').offset().top - 30;
      jQuery("html,body").animate({scrollTop: destination}, 400);
    }
    scrollOnValidateError = false;
    return false;
  }


  /*

   jQuery('select.socials-name').each( function(ind,el){


   var host1=jQuery(this).val();
   //var ele=jQuery(this).nextAll('input:eq(0)');
   var url=jQuery('.socials-val:eq('+ind+')').val();


   if(url.length>0){
   //edit-follow-links-facebook-url
   var re = new RegExp("http:\/\/(www.)([a-zA-Z0-9]+)(.)","ig");
   var arr = re.exec(url);
   //url.match(patt);
   var host2=RegExp.$2;

   if(!patt.test(url)){
   err=err+"Please provide proper url format Ex: http://www."+host1+".com/username,";
   }else if(host1!=host2){
   err=err+"  Please provide "+host1+" link for "+host1+" field ,  ";

   }

   }

   } );
   */
  return true;
}



jQuery('#edit-file-upload').live('change', function() {
  jQuery('input:radio[name=pic_avt]:first').attr('checked',true);
  var $avatar = jQuery("div.form-item img").hasClass("avatar-select");
  if ($avatar) {
    $avatar.removeClass('avatar-select');
  }
});


jQuery('div.form-item img').live('click', function() {

  jQuery('input:radio[name=pic_avt]:nth(1)').attr('checked',true);
});


jQuery('div.avatar-selection-pager-nav a').live('click', function() {
  setTimeout('chk_avatar()',1000);

});

function load_notify(err){

//    window.scrollTo(0,0);
//
//    jQuery('#twitMsg',top.document).html(err);
//    jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
  jQuery('.toggler').html(err);
  jQuery('.toggler').show('slow');

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

//jQuery(document).ready(function(){
//
//    if(jQuery('.messages').html().length>2){
//        jQuery('#twitMsg',top.document).html(jQuery('.messages').html());
//        jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
//    }
//
//});

// disable submit button when entering zipcode
jQuery(document).ready(function(){

  jQuery('#zip, #dob').keydown(function(e)
  {
    var key = e.charCode || e.keyCode || 0;
    return (
      key == 8 ||
        key == 9 ||
        key == 13 ||
        key == 46 ||
        (key >= 37 && key <= 40) ||
        (key >= 48 && key <= 57) ||
        (key >= 96 && key <= 105));
  });

  $('#zip').keypress(function() {
    get_zip_city($(this), true);
  });

  chk_uname($('#username'), true);
  $('#username').keyup(function() {
    chk_uname($(this), true);
  });


  // Blur for input and textarea

  var elemBlur = $('input[blurtext], textarea[blurtext]');

  elemBlur.each(function () {
    if($(this).attr("value") == "") {
      $(this).attr("value", $(this).attr("blurtext"));
    }
  });


  elemBlur.focus(function() {
    if($(this).attr("value").toLowerCase() == $(this).attr("blurtext").toLowerCase()) {
      $(this).attr("value", "");
    }
  });

  elemBlur.blur(function() {
    if($(this).attr("value") == "") {
      $(this).attr("value", $(this).attr("blurtext"));
    }
  });
});


