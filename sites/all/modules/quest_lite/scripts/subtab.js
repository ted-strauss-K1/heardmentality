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