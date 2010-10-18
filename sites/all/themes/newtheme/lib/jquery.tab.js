
var tabarray=['#tabs,#tabs-container','#maintabs,#tabcontent','#tabmenu,#rcontents'];
$(document).ready(function(){
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

});

function loadTab(tabObj,containerId){

    if(!tabObj || !tabObj.length){
        return;
    }
    $(containerId).addClass('loading');
    $(containerId).fadeOut('fast');
    
    $(containerId).load(tabObj.attr('href'), function(response){
        $(containerId).removeClass('loading');
        $(containerId).fadeIn('fast');
  setTimeout("setbub()",3000) ;
    });

}


          function setbub(){
    jQuery("#tabcontent").find("a").each(function(){
             if( jQuery(this).attr("rel").length>0){

                                jQuery(this).SetBubblePopup({
                                    innerHtml: jQuery(this).attr("rel"),
                                    color:"grey",
                                    imageFolder: "/images/bp_images"

                                });
                            }


        }); }