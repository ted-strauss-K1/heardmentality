/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
jQuery(document).ready(function() {
load_list(1);
init_pagecon();
});

 var current='';

function init_pagecon() {
   jQuery('.page-n2 li a').bind('click', function() {

        load_list(jQuery(this).attr('name'));
        return false;
    });

  jQuery('#pundit-prev').bind('click', function() {
    load_previous(jQuery(this));

    });
jQuery('#pundit-next').bind('click', function() {
load_next(jQuery(this));
    });
}

function load_previous(){

	new_page = parseInt($('a.reputation-score').attr('name')) - 3;
	//if there is an item before the current active link run the function
	if($('a.reputation-score').parent().prev('.page_link').length==true){
		load_list(new_page);
	}

}

function load_next(el){
	new_page = parseInt($('a.reputation-score').attr('name')) + 3;
	//if there is an item after the current active link run the function
	if($('a.reputation-score').parent().next('.page_link').length==true){
		load_list(new_page);
	}
        
}





function load_list(first){
   
    var last=first+3;
    if(first==current)
      return false;

    if(first>1)
        jQuery('#pundit-prev').show();
    else
        jQuery('#pundit-prev').hide();
    if(jQuery("li.page_link:last a").attr('name')==first)
            jQuery("#pundit-next").hide();
        else
             jQuery("#pundit-next").show();
    
    var url=gSitePath+'pundit/ajax';
        jQuery.ajax({
            type: "POST",
            url: url,
            cache:false,
            data: {
             'first': first,
             'last' :last,
             'cid'  :jQuery('#tcat').val(),
             'scid':jQuery('#tscat').val()
            },
            success: function(msg){
                 current=first;
                jQuery('#pundits').html(msg);
                jQuery(".page-n2 li a[class*='reputation-score']").removeAttr("class");
jQuery(".page-n2 li a[name='"+first+"']").attr("class","reputation-score");
            }
        });
}