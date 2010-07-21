// JavaScript Document
function tabactive(pmID, pmPath,id)
{
	jQuery('#tabIn').removeClass('active');
	jQuery('#tabM').removeClass('active');
	jQuery('#tabF').removeClass('active');
	
	jQuery('#tab'+pmID).addClass('active');
		if(pmID == 'In')
		vPath=pmPath+"qlite/innews/"+id
	else if(pmID == 'M')
		vPath=pmPath+"qlite/media/"+id
	else if(pmID == 'F')
		vPath=pmPath+"qlite/facts/"+id

	jQuery.ajax({
  url: vPath,
  cache: false,
  success: function(response){
	  
  jQuery('#rcontents').html(response);
  }
});
}



function loadReport(pmID, pmPath,id)
{
	jQuery('#tab1').removeClass('active');
	jQuery('#tab2').removeClass('active');
	jQuery('#tab3').removeClass('active');
	
	jQuery('#tab'+pmID).addClass('active');
	if(pmID == 1)
		vPath=pmPath+"qlite/percent/"+id
	else if(pmID == 2)
		vPath=pmPath+"qlite/graph/"+id
	else if(pmID == 3)
		vPath=pmPath+"qlite/map/"+id
	
		jQuery('#frmGoogle').attr('src',vPath);

	/*
jQuery.ajax({
  url: vPath,
  cache: false,
  success: function(response){
  jQuery('#contents').html(response);
  }
});*/
}


function loadresource(url,title)
{
	

	jQuery.nyroModalSettings({ title:'Add Resources'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450,title:'Add Resources'
  });

		
}

function loadsuggest(url,title){
	
	jQuery.nyroModalSettings({ title:'Suggest an Answer'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450, padding:40,title:'Suggest an Answer'
  });

}
function load_invite(url,title){
	
	jQuery.nyroModalSettings({ title:'Flag this question'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450, padding:40,title:'Flag this question'
  });
}


function loadtag(url,title)
{
	
jQuery.nyroModalSettings({ title:'Retag this question'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450, padding:40,title:'Retag this question'
  });	
	
	
}


function likethis(action, wid, like, ele){

    el = jQuery(ele);
    
    el.empty();
    //var myVerticalSlide = new Fx.Slide('likelink');
    
    
    //	myVerticalSlide.slideOut();
    // el.fade('out');
    //$('likelink').set('slide', {duration: 'long', transition: 'bounce:out'});
    //$('likelink').slide('in');
    //el.slide('hide').slide('in');
   // el.slideDown();
    // $('likelink').empty();
    
    var url = spath + 'question/forum/savecmt';
 
    jQuery('#waveerr').html('<b>Saving your like..!</b>');
         // jQuery('#waveerr').slideDown().slideUp();
    		jQuery.ajax({
   type: "POST",
   url: url,
   dataType:'xhr',
  data: {
            action: action,
            like: like,
            nodeid: wid
        },
   success: function(msg){
    el.html(msg);
	jQuery('#waveerr').slideUp();
   }
 });	
    
    //$('waveerr').set('html','<b>Thanks for your like!</b>');

}



