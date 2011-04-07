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
         
          jQuery(".quesbg").load(jQuery(this).attr('href'), function(response, status, xhr) {

        
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
});


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
    $$('.check-me').each(function(e){
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
