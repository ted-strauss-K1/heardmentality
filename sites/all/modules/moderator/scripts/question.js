// JavaScript Document
jQuery(document).ready( function() {



  // check duplicate before submit
  jQuery('#save_issue').click(function() {
    if(jQuery('#dupe-issue-area').length>0){
      var dupeCount = jQuery("#dupe_count").val();
      if(dupeCount != 0){
        jQuery('#twitMsg').html("Duplicate issues exist! Please verify your issue with duplication");
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
        return false;
      }else{
        return true;
      }
    }
  });

});




function validate_question(){

  var quest = jQuery('#q_quest').val();
  var ans1 = jQuery('#q_ans0').val();
  var ans2 = jQuery('#q_ans1').val();
  // var cat1 = jQuery('#cat1').val();
  var cat1 = jQuery('#q_cat :selected').val();

  var check = jQuery('#exist_check').val();

  var err = '';
  var errmsg = '';

  jQuery('#err').html('');
  if (jQuery.trim(quest).length) {

    if (jQuery('#inside_content').length&&check=='invalid')
      err += '<li>Please re-check your Issue from our Dupe List, We consider this as Duplicate Issue</li>';

    if (jQuery.trim(ans1).length < 1||jQuery.trim(ans2).length < 1)
      err += '<li>Minimum 2 answers required</li>';
    if (jQuery.trim(cat1).length < 1){
      jQuery('#q_cat').css('border','1px solid red');
      err += '<li>Please Provide Main Cateogry of the Issue!</li>';
    }
      
    jQuery("#add_more input").each(function(){
      jQuery(this).css('border','1px solid #838381');
    });
    jQuery('#add_more input:text[value=""]').each(function(){
      jQuery(this).css('border','1px solid red');
    });

  }
  else{
    err += '<li>Please Provide Proper Issue!</li>';
  }


  if (jQuery.trim(err).length > 1) {
    show_inotify(err);
    // jQuery('#err').html(err);
    // jQuery('#err').addClass('error');
    return false;
  }
  else{
    return true;
  }
  return false;
}





function bind_event(){
  var elements = $$('div.tagging-suggest-tag');
  var el = $('tagging-widget-container').getElements('a');
  /*

	//alert(elements);
	elements.addEvent('click', tag_add.bindWithEvent(this,elements));
	//elements.addLiveEvent('click', 'a', function(e){ alert('This is a live event'); });

*/
  for(var i = 0 ; i < el.length ; i = i + 1)
  {


    el[i].set('href','#');
  }

  elements.each(function(element,index){

    element.addEvent('click', tag_add.bindWithEvent(this,element));
  });

  var addbut=$$('a.tagging-button-container');

  addbut.addEvent('click',tag_add_input.bindWithEvent(this));
}


function bind_event_added(){
  var elements = $('tagdiv').getElements('div');

  elements.each(function(element,index){

    element.addEvent('click', tag_delq.bindWithEvent(this,element));
  });


}

function tag_add_input(val){

  var context=$('tagging-widget-input-1').get('value');

  if(context.length>0){
    var etarget=$('tagdiv');
    //set the tag
    var ele = new Element('div',{
      id : 'tagset'

    }).inject(etarget);
    ele.addClass('tagging-tag');
    ele.addClass('inp');
    ele.set('text',context);
  }
  $('tagging-widget-input-1').set('value','');
  bind_event_added();
  insert_tag();
}

function tag_add(val,el){


  var context=el.get('text').trim();
  el.destroy();
  var elements =$$('div.tagging-curtags-wrapper');
  var etarget=$('tagdiv');
  if (context != '') {
    //set the tag
    var ele = new Element('div', {
      id: 'tagset'

    }).inject(etarget);
    ele.addClass('tagging-tag');
    ele.set('text', context);
    bind_event_added();
    insert_tag();
  }

}

function insert_tag(){

  var myArray=new Array();
  var elements =$$('div.tagging-tag');

  elements.each(function(element,index){

    myArray.extend([element.get('text').trim()]);

  });


  var rtag=myArray.join(',');
  rtag.clean();
  $('q_tag').set('value',rtag);
}

function tag_delq(val,el){

  var result = el.hasClass('inp');

  if (!result) {

    var context =el.get('text');

    el.destroy();
    if(context!=''){
      var etarget = $('sug_div');

      //set the tag
      var ele = new Element('div', {
        id: 'stag'

      }).inject(etarget);

      ele.addClass('tagging-suggest-tag');
      ele.set('text', context);
      bind_event();
      return false;
    }

  }else {

    el.destroy();
  }

  insert_tag();
}

