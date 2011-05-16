
var tabarray=['#tabs,#tabs-container','#maintabs,#tabcontent','#tabmenu,#rcontents'];
$(document).ready(function(){
    // Preload tab on page load
    jQuery.each(tabarray,function(){
       // e.preventDefault();
        var arr=this.split(",");
       
        var tabsId = arr[0];
        var containerId = arr[1];
        

        if($(tabsId + ' LI.current A').length > 0){
            loadTab($(tabsId + ' LI.current A'),containerId);
        }

        $(tabsId + ' A').click(function(e){
                if($(this).attr('href')=='#') {
                  e.preventDefault();
                     e.stopPropagation();
                     return false;
                     }
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


function set_tab_active(id){

  loadTab(jQuery(id),'#tabcontent');
  $('#maintabs LI.current').removeClass('current');
  jQuery(id).parent().addClass('current');
}

function loadTab(tabObj,containerId){

    if(!tabObj || !tabObj.length){
        return;
    }
    jQuery("#loading").fadeIn();
    $(containerId).html('Loading...');
    $(containerId).fadeOut('fast');
    
    $(containerId).load(tabObj.attr('href'), function(response){
      jQuery("#loading").fadeOut();
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


        });}