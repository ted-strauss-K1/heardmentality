


jQuery(document).ready(function() {

jQuery("#lattach").click(function()
{
var content=jQuery('#nlink').val();
var urlRegex = /(\b(https?|ftp|file):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|])/ig;
jQuery(this).attr('disabled',true);
var url= content.match(urlRegex);
var purl=spath+'debate/ajax';

if(url.length>0)
{

$("#linkbox").slideDown('show');
$("#linkbox").html("Loading.....");
$.get(purl+"?action=url&url="+url,function(response)
{
jQuery("#linkbox").html(response);
jQuery("#lattach").removeAttr('disabled');
});

}
return false;
});


    var selObj = jQuery('#rtype');
    jQuery('#div1,#div2,#div3,#media,#media_div').hide();
    selObj.bind('change', function(e) {
        
        var vDiv1 = jQuery('#div1');
        var vDiv2 = jQuery('#div2');
        var vDiv3 = jQuery('#div3');
        var medDiv1 =jQuery('#media');
        var medDiv2 = jQuery('#media_div');
        jQuery('#div1,#div2,#div3,#media,#media_div,#linkbox').hide();
        var selIndex = selObj.selectedIndex;
        var value = selObj.val();
              
        if(value==1)
        {
            vDiv1.slideDown();
		jQuery('#linkbox').show();
        }
        if(value==2)
        {
            vDiv2.slideDown();
					   
        }
        if(value==3)
        {
            vDiv1.slideDown();
            jQuery('#linkbox').show();
        }
              
    });
	   
    var selObjmed = jQuery('#mtype');
    var medDiv1 = jQuery('#media');
    var medDiv2 = jQuery('#media_div');
    jQuery('#media,#media_div').hide();
    selObjmed.bind('change', function(emed) {
         jQuery('#media,#media_div').hide();
        var valuemed = selObjmed.val();
      //  jQuery(medDiv1,medDiv2).hide();
        //alert(valuemed);
        if(valuemed==1)
        {
            medDiv1.slideDown();
        }else
        if(valuemed==2)
        {
            medDiv2.slideDown();
        }
                     
       
    });


    jQuery('#myForm').submit(function() {
        
        var cat1 = jQuery('#rtype').val();
        var nlink = jQuery('#nlink').val();
        var mtype =jQuery('#mtype').val();
        var membed = jQuery('#membed').val();
        var docpath = jQuery('#docpath').val();
        var err = '';
        var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
        if (cat1==0)
            err += '<li>Please Select Type !</li>';
        if (cat1==1)
        {

            if (!tomatch.test(nlink))
                err += '<li>Please Enter Link </li>';

        }
        if (cat1==2)
        {
            if (mtype==0)
                err += '<li>Please Select Media Type !</li>';

            if (mtype==1)
            {

                if (!tomatch.test(membed))
                    err += '<li>Please Enter YouTube Link </li>';
                if (tomatch.test(membed))
                {
                    var el = jQuery('#err').hide();
                   
                }
            }
            else
            {
                if ( jQuery.trim(docpath).length < 1)
                {
                    err += '<li>Please Select Document !</li>';
                }
                if (jQuery.trim(docpath).length > 1)
                {
                    var el = jQuery('err').hide();
                }
            }
        }
        if (cat1==3)
        {

            if (!tomatch.test(nlink))
                err += '<li>Please Enter  Fact Link</li>';

        }
        var el =jQuery('#err');
        
        if (jQuery.trim(err).length > 1) {
          el.html(err);
          el.addClass('error');
            el.show();
            return false;
        }	else{
            el.hide();
        }

       // e.preventDefault();
      
        jQuery.post( jQuery(this).attr('action'), jQuery(this).serialize(),
            function(data){
                el.removeClass('error');
                jQuery( "form" )[ 0 ].reset();
                jQuery('#uscrap').empty();
                jQuery("#linkbox").html('');
             //jQuery( "form" )[ 0 ].clearForm();
            // clearForm(jQuery(this));
            el.slideDown().fadeOut(4000);
                 el.html(data);
                //  jQuery.unblockUI();
               // jQuery.growlUI('', data);
            });

        return false;
    });
	   
});




function createUploader(){
    var uploader = new qq.FileUploader({
        element: document.getElementById('file-uploader-demo1'),
        action: spath+'upload_document.php',
        debug: true,
        // url of the server-side upload script, should be on the same domain
        // additional data to send, name-value pairs
        //params: {},

        // validation
        // ex. ['jpg', 'jpeg', 'png', 'gif'] or []
        allowedExtensions: ["doc","docx","ppt","pdf"],
        // each file size limit in bytes
        // this option isn't supported in all browsers
        sizeLimit: 1000000, // max size
        minSizeLimit: 1, // min size
        multipleFileUpload:false,
        onSubmit: function(id, fileName){jQuery.growlUI('','File uploading please wait!');},
        onProgress: function(id, fileName, loaded, total){jQuery.growlUI('','File uploading please wait!');},
        onComplete: function(id, fileName, responseJSON){jQuery('#docpath').val(responseJSON.filename);jQuery.growlUI('','File uploaded successfully!');},
        showMessage: function(message){
            jQuery.growlUI('',message);
        }

    });
}

// in your app create uploader as soon as the DOM is ready
// don't wait for the window to load
window.onload = createUploader;


 jQuery.fn.clearForm = function() {
  return this.each(function() {
 var type = this.type, tag = this.tagName.toLowerCase();
 if (tag == 'form')
   return $(':input',this).clearForm();
 if (type == 'text' || type == 'password' || tag == 'textarea')
   this.value = '';
 else if (type == 'checkbox' || type == 'radio')
   this.checked = false;
 else if (tag == 'select')
   this.selectedIndex = -1;
  });
};

function clearForm(form) {
  // iterate over all of the inputs for the form
  // element that was passed in
  $(':input', form).each(function() {
 var type = this.type;
 var tag = this.tagName.toLowerCase(); // normalize case
 // it's ok to reset the value attr of text inputs,
 // password inputs, and textareas
 if (type == 'text' || type == 'password' || tag == 'textarea')
   this.value = "";
 // checkboxes and radios need to have their checked state cleared
 // but should *not* have their 'value' changed
 else if (type == 'checkbox' || type == 'radio')
   this.checked = false;
 // select elements need to have their 'selectedIndex' property set to -1
 // (this works for both single and multiple select elements)
 else if (tag == 'select')
   this.selectedIndex = -1;
  });
};