/**
 * @author gobinath.m
 */
//window.addEvent('domready', function(){
//
//
//
//
//});





//function get_Reply(make){
//    var vals = [];
////    $$('.check-me').each(function(e){
////		if(e.getProperty('checked')){
////
////			  vals.push(e.value);
////		}
////
////    });
//
//
//
//
//
//	 //if (vals.length > 0) {
//        if($(":checkbox:checked").length) {
//
//
//    var report = $('cmt_txt').get('value');
//
//    if ($("#showbox_cmt").css("display") == 'none') {
//
//           $("#showbox_cmt").css('display','block');
//
//        $('showbox_cmt').setStyle('display', 'block');
//        $('showbox_cmt').slide('hide').slide('in');
//        $('showbox_cmt').focus();
//        return false;
//    }
//    if (report.trim().length < 5) {
//        $('cmt_txt').setStyle('border-color', '#EF2C2C');
//        return false;
//    }else{
//		 $('cmt_txt').setStyle('border-color', '');
//
//	}
//
//            $('action').set('value', make);
//
//            $('cmtform').set('send', {
//                onComplete: function(response){
//                    var log = $('clist').empty().addClass('ajax-loading');
//                    log.set('html', response);
//
//                }
//            });
//            //Send the form.
//            $('cmtform').send();
//
//        }
//            else {
//
//                alert('select atleast one user To send message !');
//                return false;
//            }
//
//
//}


jQuery(document).ready(function(){

    $('.facttext .menu a').click(function() {
        //$('#box1').css("background","#9f9");
        $(".facttext .menu a").css('color', '#DD6600');
        $(this).css('color', '#4170A0');
        
});

    jQuery(".contarea a[href*='?ajax=1']").each(function(){
   
        jQuery(this).click(function () {
         
          jQuery(".hm-cen").load(jQuery(this).attr('href'), function(response, status, xhr) {

        
  if (status == "success") {
reset_tabs();
}
});

            return false;
        });
       
    });

    jQuery('div.facttext > ul.menu > li a').click(function(){
        alert('clicked');
        return false;
    });

    //heartbeat function

    jQuery('div.more-link a').live('click',function(e){
         jQuery("body").css({'opacity': 0.5});
         var more=jQuery(this);
        e.preventDefault();
        load_stream(more,'more');
    });



});


// happening now slide down
//setTimeout(slidestream, 5000);

  (function(a){
    jQuery.browser.mobile=/android.+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od|ad)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|e\-|e\/|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(di|rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|xda(\-|2|g)|yas\-|your|zeto|zte\-/i.test(a.substr(0,4))
    })(navigator.userAgent||navigator.vendor||window.opera);

 //var duration = 2000;
function slidestream(){
var delay = 0;
jQuery(jQuery('#uactivity div.activity-stream:hidden').get().reverse()).each(function(){
    jQuery(this).delay(delay).slideDown('slow', function() {
	if (jQuery.browser.mobile == false) {
		var settings = {
			scrollbarWidth:20, 
			scrollbarMargin:0, 
			showArrows:true
		};
		
		var pane = $('.container .nine .grey-box .uactivity');
		pane.jScrollPane(settings);
		var api = pane.data('jsp');
		
		jQuery(window).resize(function () {
			api.reinitialise();

		});
    }
	});
    delay +=2000;
});
}



function load_stream(more,action){

            var firstid=jQuery('#uactivity div:first').attr('id');
            if (!firstid) {
              return;
            }
           var firstmid=firstid.split('-');
            var timestamp = Number(new Date());
            var url = window.location.toString();
            var query_string = url.split("?");
            //pass filter value along with url
        var urr=more.attr('href')+more.attr('id')+'?'+query_string[1];

        jQuery.ajax({
          type: 'GET',
          dataType: 'json',
          url: urr,
          data: {'time': timestamp,'action':action,'firstid':firstmid[1]},
          success: function(data){
              var cnt=data.count;
              // jQuery.unblockUI();
            if(data.error){
            if(action=='more'){
                 jQuery('#uactivity').append('<div class="warning"><small>No More User Activity!</small></div>');
                 jQuery('div.more-link').fadeOut('slow');
            }
             // alert('error occurs please try to reload!!')
            }else{
                if(action=='more'){
                      more.attr('id',data.start);
              jQuery('#uactivity').append(data.content);
              if(!data.more){
                   jQuery('div.more-link').fadeOut('slow');
                   jQuery('#uactivity').append('<div class="warning"><small>There are no more posts to show right now.!</small></div>');
              }

                }
              if(action=='new'){
                more.attr('id',data.start);
              jQuery('#uactivity').prepend(data.content);
                }
            }
            jQuery("body").css({'opacity':''});
          },
          complete: function(){
              slidestream();
          }
        });




// jQuery.getJSON(urr,
//        {
//            'time': timestamp,'action':action,'firstid':firstmid[1]
//        },
//        function(data) {
//
//            var cnt=data.count;
//           // jQuery.unblockUI();
//            if(data.error){
//            if(action=='more'){
//                 jQuery('#uactivity').append('<div class="warning"><small>No More User Activity!</small></div>');
//                 jQuery('div.more-link').fadeOut('slow');
//            }
//             // alert('error occurs please try to reload!!')
//            }else{
//                if(action=='more'){
//                      more.attr('id',data.start);
//              jQuery('#uactivity').append(data.content);
//              if(!data.more){
//                   jQuery('div.more-link').fadeOut('slow');
//                   jQuery('#uactivity').append('<div class="warning"><small>There are no more posts to show right now.!</small></div>');
//              }
//
//                }
//              if(action=='new'){
//                more.attr('id',data.start);
//              jQuery('#uactivity').prepend(data.content);
//                }
//            }
//        jQuery("body").css({'opacity':''});
//        }).complete(function() { alert("complete"); });



}
function reset_tabs(){
var tabarray=['#maintabs,#tabcontent'];

      // Preload tab on page load
    jQuery.each(tabarray,function(e){
        var arr=this.split(",");

        var tabsId = arr[0];
        var containerId = arr[1];


        if($(tabsId + ' LI.current A').length > 0){
            loadTab($(tabsId + ' LI.current A'),containerId);
        }

        $(tabsId + ' A').click(function(){
            if($(this).parent().hasClass('current')){
                return false;
            }

            $(tabsId + ' LI.current').removeClass('current');
            $(this).parent().addClass('current');

            loadTab($(this),containerId);
            return false;
        });





    });



}


function get_Reply(make){

    if($(":checkbox:checked").length) {
        if ($("#showbox_cmt").css("display") == 'none') {

            $("#showbox_cmt").css('display','block');
        }
        if($("#showbox_cmt").click())
        {
            var myLength = $("#cmt_txt").val().length;
            if(myLength>5)
            {
                document.cmtform.submit();
            }
                    

                   
        }
    }
}


function get_votes(){

    var vals = [];
    $('.check-me').each(function(e){
        if(e.getProperty('checked')){
            vals.push(e.value);
        }
      
    });
    $('showbox_cmt').setStyle('display', 'none');
   
   
    $('action').set('value', make);
            
    $('cmtform').set('send', {
        onComplete: function(response){
            var log = $('clist').empty().addClass('ajax-loading');
            log.set('html', response);
                   
        }
    });
    //Send the form.
    $('cmtform').send();
}
function loadwave(qid,wid){
    url= gSitePath+'question/forum/?qid='+qid+'&wid='+wid;
    jQuery.nyroModalSettings({
        title:'Forum Posts'
    });
    var options = 'sameBox:true width:70% height:90% caption:' +
    '`Forum Posts`';
    parent.fb.start(url, options);
//jQuery.nyroModalManual({
// url: url,width:550,height:450,title:'Forum Posts'
// });
//return hs.htmlExpand(url, { outlineType: 'rounded-white',wrapperClassName: 'draggable-header', objectType: 'iframe' } );
}
