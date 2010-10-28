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
                var wt=jQuery('#newwavediv').find('#wtitle');
		var wc=jQuery('#newwavediv').find('#wcon');
                var wtitle=wt.val();
		var post=wc.val();
		var formwave=jQuery('#newwaveform');

           if(jQuery.trim(wtitle).length<2){

			wt.css("border-color","red");
		
			return false;
		}else{

	wt.css("border-color","");
		}

		
		if(jQuery.trim(post).length<8){
		
			wc.css("border-color","red");
		wc.removeClass('txtare');
			return false;
		}else{
			
	wc.addClass('txtare');
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
	jQuery.nyroModalSettings({title:'Forum Posts'});
  var options = 'sameBox:true width:700 height:90% caption:' +
  '`Forum Posts`';
  parent.fb.start(url, options);
            //jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Forum Posts'
 // });
//return hs.htmlExpand(url, { outlineType: 'rounded-white',wrapperClassName: 'draggable-header', objectType: 'iframe' } );
}


function loadrforum(url,title){
	
	jQuery.nyroModalSettings({title:'Forum Posts'});

	//jQuery.nyroModalManual({
  //  url: url,width:550,height:450,title:'Forum Posts'
 // });
  var options = 'sameBox:true width:700 height:90% caption:' +
  '`Forum Posts`';
  parent.fb.start(url, options);
	
}

function loadflagquestion(url,title)
{
	
	
	//jQuery.nyroModalSettings({ title:'Flag Posts'});

	//jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Flag Posts'
//  });

	  var options = 'sameBox:true width:70% height:90% caption:' +
  '`Flag Posts`';
  parent.fb.start(url, options);
	
	
}