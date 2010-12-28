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
function wave_form(ths){
    //Prevents the default submit event from loading a new page.
    //e.stop();
    
    var wt=jQuery('#newwavediv').find('#wtitle');
    var wc=jQuery('#newwavediv').find('#wcon');
    var wtitle=wt.val();
    var post=wc.val();
    var formwave=jQuery('#newwaveform');

    if(jQuery.trim(wtitle).length<2||wtitle=='Title'){

        wt.css("border-color","red");
		
        return false;
    }else{

        wt.css("border-color","");
    }

		
    if(jQuery.trim(post).length<8||post=='Enter text here'){
		
        wc.css("border-color","red");
  
        return false;
    }else{
			
       wt.css("border-color","");
    }
    
   var lent = formwave.find('select option:selected[value="0"]').length;
 
  if(lent<1)
      {
          alert('atleast one option should be netural!!');
          return false;
      }else{
           jQuery.post(formwave.attr('action'),formwave.serialize(),
        function(data){
            jQuery('#qwave').html(data);
            wt.attr('value','');
              jQuery(ths).fadeIn();
              formwave.clearForm();
              wt.val('Title');
              wc.val('Enter text here');
              jQuery('form#newwaveform select').val('0');
	fb.end();

        });
      }

 
	
    
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
	
    var options = 'sameBox:true width:700 height:90% caption:' +
    '`Forum Posts`';
    parent.fb.start(url, options);
//jQuery.nyroModalSettings({title:'Forum Posts'});
//jQuery.nyroModalManual({
// url: url,width:550,height:450,title:'Forum Posts'
// });
//return hs.htmlExpand(url, { outlineType: 'rounded-white',wrapperClassName: 'draggable-header', objectType: 'iframe' } );
}
function loadrforum(url,title){
	
    //jQuery.nyroModalSettings({title:'Forum Posts'});

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


jQuery(document).ready(function(){
    $('#vmaintabs1 #com').click(function() {
        $("#maintabs #in").removeClass("current");
        $("#maintabs #par2").removeClass("current");
        $('#maintabs #par1').addClass("current");
    });

    $('#vmaintabs2 #com2').click(function() {
        $("#maintabs #in").removeClass("current");
        $("#maintabs #par1").removeClass("current");
        $('#maintabs #par2').addClass("current");
    });

    jQuery('.debate-links').live('click',function(e){
       e.preventDefault();
        e.stopPropagation();
         parent.fb.start(jQuery(this).attr('href'), {
     type:'ajax',
    width: '90%',
    height: '90%',
    caption:'DEBATE SUMMARY'
   // afterItemStart:'`fb$("fbCaption").append("DEBATE SUMMARY");fb.translate(\'eat a peach\', \'fr\', function(result) { alert(result.responseData.translatedText); }); `',
  //controlsPos:'tr', captionPos:'tc',caption:'#boxSelect',
	//afterItemEnd:'`fb$("boxSelect").selectedIndex = 0;`'
  });

$.getScript("test.js", function(){
   alert("Script loaded and executed.");
 });
    });




});



//        $("li.y").click(function(){
//    $("li.x").removeClass("xshown").addClass("xhidden");
//    $(this).addClass("yshown");
//});