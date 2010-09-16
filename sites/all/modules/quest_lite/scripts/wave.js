/**
 * @author admin
 */
/*
window.addEvent('domready', function() {
	
	
	$('newwavebut').addEvent('click', function(){
    
	$('newwavediv').fadeIn('in');
	
});

	
	

});

*/
	function wave_form(){
		//Prevents the default submit event from loading a new page.
		//e.stop();
		var wt=jQuery('#newwavediv').find('.textArea');
		var post=wt.val();
		var formwave=jQuery('#newwaveform');
		
		if(jQuery.trim(post).length<8){
		
			wt.css("border-color","#EF2C2C");
			wt.attr('id','wtitlerror');
			return false;
		}else{
			
	wt.attr('id','wtitle');	
		}
jQuery.post(formwave.attr('action'),formwave.serialize(),
   function(data){
    jQuery('#qwave').html(data);
   });
				jQuery('#qwave').fadeOut('slow');
				jQuery('#qwave').empty();
			
				jQuery('#qwave').fadeIn('slow');
				wt.attr('value','');
		
			jQuery('#newwavediv').fadeOut('slow');
}

function toggle(){
	
	//var mySlide = new Fx.Slide('newwavediv');

	
		//mySlide.toggle();
	jQuery('#newwavediv').focus();
jQuery('.textArea').focus();
	jQuery('#newwavediv').toggle();
	//$('newwavediv').fade('out');
	
}

function loadwave(qid,wid){
	
	url= gSitePath+'question/forum/?qid='+qid+'&wid='+wid;
	jQuery.nyroModalSettings({ title:'Forum Posts'});

	//jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Forum Posts'
 // });
return hs.htmlExpand(url, { outlineType: 'rounded-white',wrapperClassName: 'draggable-header', objectType: 'iframe' } );
}


function loadrforum(url,title){
	
	jQuery.nyroModalSettings({ title:'Forum Posts'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450,title:'Forum Posts'
  });

	
}

function loadflagquestion(url,title)
{
	
	
	jQuery.nyroModalSettings({ title:'Flag Posts'});

	jQuery.nyroModalManual({
    url: url,width:550,height:450,title:'Flag Posts'
  });

	
	
	
}