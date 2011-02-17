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
    var err= jQuery('#twitMsg');
      
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
    
   var lent = formwave.find('select option:selected[value="1"],select option:selected[value="2"]').length;
 
  if(lent<1)
      {
        
           err.html('Atleast one option should be either oppose or support!!');
                err.delay(400).slideDown(400).delay(3000).slideUp(400);
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
               err.html('Your argument has been added');
                err.delay(400).slideDown(400).delay(3000).slideUp(400);
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

    var options = 'sameBox:true width:50% height:40% caption:' +
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
    width: '70%',
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


jQuery('#dfilt-sup,#dfilt-ans,#dfilt-sort').live('change',function(){
var qid=jQuery('input[name="mid"]').val();
var gurl=spath+'debate/ajax/'+qid;
var sup=jQuery('#dfilt-sup').val();
var ans=jQuery('#dfilt-ans').val();
var sort=jQuery('#dfilt-sort').val();
 jQuery.ajax({
                type: "GET",
                url: gurl,
                data: {
                    'action': 'filter',
                    'sup': sup,
                    'ans': ans,
                    'sort':sort
                },
                success: function(msg){
                 jQuery('#qwave').html(msg);
                }
            });

});

jQuery('#rfilt-sup,#rfilt-ans,#rfilt-sort').live('change',function(){
var qid=jQuery('input[name="mid"]').val();
var gurl=spath+'debate/ajax/'+qid;
var sup=jQuery('#rfilt-sup').val();
var ans=jQuery('#rfilt-ans').val();
var sort=jQuery('#rfilt-sort').val();
var type=jQuery('#rtype').val();
 jQuery.ajax({
                type: "GET",
                url: gurl,
                data: {
                    'action': 'resfilter',
                    'sup': sup,
                    'ans': ans,
                    'sort':sort,
                    'type':type
                },
                success: function(msg){
                 jQuery('#resfilter').html(msg);
                }
            });

});



});



//        $("li.y").click(function(){
//    $("li.x").removeClass("xshown").addClass("xhidden");
//    $(this).addClass("yshown");
//});