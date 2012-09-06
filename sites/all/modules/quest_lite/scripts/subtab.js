// JavaScript Document


function loaded()
{
    swfobject.embedSWF("myContent.swf", "rcontents", "300", "120", "9.0.0");
}


function loadReport(pmID, pmPath,id)
{
    jQuery('#tab1').parent('li').removeClass('current');
    jQuery('#tab2').parent('li').removeClass('current');
    jQuery('#tab3').parent('li').removeClass('current');
    jQuery('#tab'+pmID).parent('li').addClass('current');
    if(pmID == 1)
        vPath=pmPath+"issue/report/percent/"+id
    else if(pmID == 2)
        vPath=pmPath+"issue/report/graph/"+id
    else if(pmID == 3)
        vPath=pmPath+"issue/report/map/"+id
	
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
	

    //jQuery.nyroModalSettings({ title:'Add Resources'});

    //jQuery.nyroModalManual({
    //  url: url,width:550,height:450,title:'Add Resources'
    // });
    var options = 'sameBox:true width:50% height:60% caption:' +
    '`Add Resources`';
    parent.fb.start(url, options);
		
}

function loadsuggest(url,title){
	
    //jQuery.nyroModalSettings({ title:'Suggest an Answer'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450, padding:40,title:'Suggest an Answer'
    // });
    var options = 'sameBox:true width:50% height:60% caption:' +
    '`Suggest an Answer`';
    parent.fb.start(url, options);
}
function load_invite(url,title){
	
    //jQuery.nyroModalSettings({ title:'Flag this question'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450, padding:40,title:'Flag this question'
    //});
    var options = 'sameBox:true width:50% height:70% caption:' +
    '`Invite your Facebook Friends`';
    parent.fb.start(url, options);
}


function loadtag(url,title)
{
	
    //jQuery.nyroModalSettings({ title:'Retag this question'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450, padding:40,title:'Retag this question'
    // });

    var options = 'sameBox:true width:50% height:70% caption:' +
    '`Retag This Question`';
    parent.fb.start(url, options);
	
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



