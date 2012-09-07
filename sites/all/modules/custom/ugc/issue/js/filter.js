/*
 * Short Messages
 *
 * @element  - element id where to put the message
 * @message  - message text
 * @delayTimeout    - timeout
 * @slideTimeout    - timeout for slideup
 */








/**Rallydev:530**/
$(document).ready(function(){
  imageUrl = Drupal.settings.base_url +'/sites/all/themes/heardmentalitylight/images/ui-bg_diagonals40x40_red.png';
  if($('.error').html() != null ) {
    $('.top-message').css('background-image', 'url(' + imageUrl + ')');
    $('.error').css('border','none');
    $('.error').css('background','none');
  }
  if($('.warning').html() != null ) { 
    $('.top-message').css('background-image', 'url(' + imageUrl + ')');
    $('.warning').css('border','none');
    $('.warning').css('background','none');
  }  
});
/**************/

/**
 * @author gobinath.m
 */





function search_iss_trig(){
  $('#subject').trigger('change');
  setTimeout(subcatSet,3000);
  $('#s_country').trigger('change');
  setTimeout(substate,3000);
}
function subcatSet(){
  $('#area').trigger('change');
}
function substate(){
  $('#s_state').trigger('change');
}


$(document).ready(function() {

  // hide / show suggest answer
  $('.wait').live('click', function(){
    $('.sugg-hide').slideToggle('slow');
  });

  //trigger search filters
  search_iss_trig();


  $('#analytics-area').slideUp(3000);
  $('#res-analytics-area').slideUp(3000);

  $('#show-analytics').click(function(){
    $('#filter-area').slideUp('fast');
    $('#analytics-area').slideToggle('slow'); 
  })
  $('#show-filter').click(function(){
    $('#analytics-area').slideUp('fast');
    $('#filter-area').slideToggle('slow');
  })

  // resource tab
  $('#show-res-statistics').click(function(){
    $('#res-analytics-area').slideToggle('fast');
    $('#res-filter-area').slideUp('slow');
    $('#add-resource-area').slideUp('slow');
  })
  $('#show-res-filter').click(function(){
    $('#res-analytics-area').slideUp('fast');
    $('#res-filter-area').slideToggle('slow');
    $('#add-resource-area').slideUp('slow');
  })


  $('#addnew_reference').click(function(){
    $('#res-analytics-area').hide('fast');
    $('#res-filter-area').hide('fast');
    $('#add-resource-area').slideToggle('slow');
  });

});




// open suggest answer form
$('#sugg-btn').live('click',function(){
  $('#sugg-form').slideToggle('fast');
});

$('#canc').live('click', function() {
  $('#sugg-form').slideUp('fast');
});

// open add new debate form
$('#addnew_debate').live('click',function(){
  $('#submitted-msg').html('');
  $('#deb-err').html('');
  $('#add_debate_wrapper').slideToggle('slow');
       
});

$.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({
    opacity: 'toggle', 
    height: 'toggle'
  }, speed, easing, callback);
};









// from debate module - code cleanup
$(document).ready(function() {



  var selObj = $('#rtype');
  $('#div1,#div2,#div3,#media,#media_div').hide();
  selObj.bind('change', function(e) {

    var vDiv1 = $('#div1');
    var vDiv2 = $('#div2');
    var vDiv3 = $('#div3');
    var medDiv1 =$('#media');
    var medDiv2 = $('#media_div');
    $('#div1,#div2,#div3,#media,#media_div,#linkbox').hide();
    var selIndex = selObj.selectedIndex;
    var value = selObj.val();

    if(value==1)
    {
      vDiv1.slideDown();
      $('#linkbox').show();
    }
    if(value==2)
    {
      vDiv2.slideDown();

    }
    if(value==3)
    {
      vDiv1.slideDown();
      $('#linkbox').show();
    }

  });

  var selObjmed = $('#mtype');
  var medDiv1 = $('#media');
  var medDiv2 = $('#media_div');
  $('#media,#media_div').hide();
  selObjmed.bind('change', function(emed) {
    $('#media,#media_div').hide();
    var valuemed = selObjmed.val();
    //  $(medDiv1,medDiv2).hide();
    //alert(valuemed);
    if(valuemed==1)
    {
      medDiv1.slideDown();
    }else
    if(valuemed==2)
    {
      medDiv2.slideDown();
    }


  });


  $('#myForm').submit(function() {

    var cat1 = $('#rtype').val();
    var nlink = $('#nlink').val();
    var mtype =$('#mtype').val();
    var membed = $('#membed').val();
    var docpath = $('#docpath').val();
    var err = '';
    var trig_ref = '';
    var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
    if (cat1==0)
      err += '<li>Please Select Type !</li>';
    if (cat1==1) {
      trig_ref = '#ref_innews';
      if (!tomatch.test(nlink))
        err += '<li>Please Enter Link </li>';
    }
    if (cat1==2) {
      trig_ref = '#ref_multimedia';
      if (mtype==0)
        err += '<li>Please Select Media Type !</li>';

      if (mtype==1)
      {

        if (!tomatch.test(membed))
          err += '<li>Please Enter YouTube Link </li>';
        if (tomatch.test(membed)) {
          var el = $('#err').hide();
        }
      }
      else
      {
        if ( $.trim(docpath).length < 1) {
          err += '<li>Please Select Document !</li>';
        }

      }
    }
    if (cat1==3)
    {
      trig_ref = '#ref_facts';

      if (!tomatch.test(nlink))
        err += '<li>Please Enter  Fact Link</li>';

    }
    var el =  $('#refer-err');

    if ($.trim(err).length > 1) {
      el.html(err);
      el.addClass('error-msg');
      return false;
    }	else{
      el.hide();
    }

    //$('input[type="submit"]').attr('disabled',true);
    $(this).find('#add-new-res').hide();
    $(this).find('#sub_loader').show();
    // e.preventDefault();

    $.post( $(this).attr('action'), $(this).serialize(),
      function(data){
        el.removeClass('error');
        $( "form" )[ 0 ].reset();
        $('#uscrap').empty();
        $("#linkbox").html('');
        $('#nlink').val('http://');


        //$( "form" )[ 0 ].clearForm();
        // clearForm($(this));
        //el.html(data);
        //$(data).prependTo('#load-resource');
        $(trig_ref).trigger('click');
        $('#add-resource-area').slideUp();
        $('#sub_loader').hide();
        $('#add-new-res').show();
        // el.delay(400).slideDown(400).delay(3000).slideUp(400);
        // $.growlUI('', data);
        $('input[type="submit"]').removeAttr('disabled');
      });

    return false;
  });
});






// in your app create uploader as soon as the DOM is ready
// don't wait for the window to load




$.fn.clearForm = function() {
  return this.each(function() {
    var type = this.type, tag = this.tagName.toLowerCase();
    if (tag == 'form')
      return $(':input',this).clearForm();
    if (type == 'text' || type == 'password' || tag == 'textarea')
      this.value = '';
    else if (type == 'checkbox' || type == 'radio')
      this.checked = false;
    else if (tag == 'select')
      this.selectedIndex = -1;
  });
};

function clearForm(form) {
  // iterate over all of the inputs for the form
  // element that was passed in
  $(':input', form).each(function() {
    var type = this.type;
    var tag = this.tagName.toLowerCase(); // normalize case
    // it's ok to reset the value attr of text inputs,
    // password inputs, and textareas
    if (type == 'text' || type == 'password' || tag == 'textarea')
      this.value = "";
    // checkboxes and radios need to have their checked state cleared
    // but should *not* have their 'value' changed
    else if (type == 'checkbox' || type == 'radio')
      this.checked = false;
    // select elements need to have their 'selectedIndex' property set to -1
    // (this works for both single and multiple select elements)
    else if (tag == 'select')
      this.selectedIndex = -1;
  });
};


// resources image selector
$(document).ready(function() {


  $('#re-sel-next').live('click',function() {
    var curr = $("#cur_id_val").val();
    var next= Number(curr)+Number(1);
    var imgcount = Number(next)+Number(1);
    var end = $('#end_image').val();
    end = Number(end)-Number(1);
    var imgid = '#cur_img_';
    var src = $(imgid+next).attr("src");
    $(imgid+curr).hide();
    $(imgid+next).show();
    $('#cur_id_val').val(next);
    $('#img_count').html(imgcount);
    if($('#no_thumbnail').attr('checked')){
      $('#final_uimage').val('');
    }
    else{
      $('#final_uimage').val(src);
    }

    if(curr >= end){
      //$('#re-sel-next').bind('click', disableLink);
      //$('#re-sel-next').fadeTo('fast', 0.2);
      $('#re-sel-next').hide();
    }
    if(curr >= 0){
      //$('#re-sel-pre').unbind();
      //$('#re-sel-pre').fadeTo('fast', 1);
      $('#re-sel-pre').show();
    }
  });
  $('#re-sel-pre').live('click',function() {
    var curr = $("#cur_id_val").val();
    var pre= Number(curr)-Number(1);
    var imgcount = Number(pre)+Number(1);
    var end = $('#end_image').val();
    end = Number(end)+Number(1);
    var imgid = '#cur_img_';
    var src = $(imgid+pre).attr("src");

    $(imgid+curr).hide();
    $(imgid+pre).show();
    $('#cur_id_val').val(pre);
    $('#img_count').html(imgcount);
    if($('#no_thumbnail').attr('checked')){
      $('#final_uimage').val('');
    }
    else{
      $('#final_uimage').val(src);
    }

    if(curr<end){
      //$('#re-sel-next').unbind();
      //$('#re-sel-next').fadeTo('fast', 1);
      $('#re-sel-next').show();
    }

    if(pre == 0){
      //$('#re-sel-pre').bind('click', disableLink);
      //$('#re-sel-pre').fadeTo('fast', 0.2);
      $('#re-sel-pre').hide();
    }
  });

  $('#no_thumbnail').live('click', function() {
    var curr = $("#cur_id_val").val();
    var imgid = '#cur_img_';
    var src = $(imgid+curr).attr("src");
    if($('#no_thumbnail').attr('checked')){
      $('#final_uimage').val('');
    }else{
      $('#final_uimage').val(src);
    }
  });

})

function disableLink(e) {
  // cancels the event
  e.preventDefault();

  return false;
}


// open resource subtab types


function resOpenReplyBox(rid){
  var boxid = '#reply-box-'+rid;
  $(boxid).slideToggle('slow');
}
function resOpenReplies(rid){
  var boxid = '#all_replybox_'+rid;
  $(boxid).slideToggle('slow');
}




///////// ########## from preload.js code cleanup ########## /////


function loadflagquestion(url,title)
{


  //$.nyroModalSettings({ title:'Flag Posts'});

  //$.nyroModalManual({
  // url: url,width:550,height:450,title:'Flag Posts'
  //  });

  var options = 'sameBox:true width:50% height:60% caption:' +
  '`Flag Posts`';
  parent.fb.start(url, options);


}
function loadflagresdeb(url,title)
{


  //$.nyroModalSettings({ title:'Flag Posts'});

  //$.nyroModalManual({
  // url: url,width:550,height:450,title:'Flag Posts'
  //  });

  var options = 'newBox:true width:50% height:60% caption:' +
  '`Flag Posts`';
  parent.fb.start(url, options);


}
function loadeditquestion(url,title)
{


  //$.nyroModalSettings({ title:'Flag Posts'});

  //$.nyroModalManual({
  // url: url,width:550,height:450,title:'Flag Posts'
  //  });

  var options = 'sameBox:true width:78% height:90% caption:' +
  '`Edit Profile`';
  parent.fb.start(url, options);


}



$(document).ready(function () {

  //twitter like alert
  if($('#twitMsg').text().length>2){
    $('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
  }
  //loading status for ajax
  //    $("#loading").ajaxStart(function () {
  //        $(this).fadeIn();
  //    });
  //
  //    $("#loading").ajaxStop(function () {
  //
  //        $(this).fadeOut();
  //        fb.activateElements();
  //    });
  $("#loading").ajaxError(function() {
    $(this).hide();
    $('#twitMsg').empty().html('Sorry Error Occurs Please Reload the Page and Try Again!');
    $('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
  });





});








// add / edit vote ajax submission
$('#issue_edit_form_stream').live('submit', function(){
  if($('#check_login').val()==0){
    $('#dialog').dialog('open');
    return false;
  }
  var thisForm = $(this);
  var data = thisForm.serialize();
  var vote_type = thisForm.find('#vote_type').val();
  var but_val = '';
  if(vote_type == 'edit'){
    but_val = 'Changing...';
  }else if(vote_type == 'add'){
    but_val = 'Voting...';
  }
  thisForm.find('#edit-change').val(but_val);
  var choice = thisForm.find('input:radio[name=choice]:checked').val();

  $.ajax({
    type: 'POST',
    dataType: 'json',
    url: Drupal.settings.basePath + 'issue/vote/ajax/submit/'+vote_type,
    data: data,
    success: function(msg){
      var nid_val = thisForm.find('#nid_val').val();
      //alert(msg.message);
      $('#vote-msg-alert-'+nid_val).html(msg.message);
      if(msg.success == 1){
        var def_vote = thisForm.find('#def_vote').val();
        var newchoicediv = '#'+nid_val+'-chorder-'+choice;
        var oldchoicediv = '#'+nid_val+'-chorder-'+def_vote;

        var oldchoice = $(oldchoicediv).html();
        var newchoice = $(newchoicediv).html();
        if(vote_type == 'edit'){
          thisForm.find('#def_vote').val(choice);
          //$('#voting-pane-'+nid_val).html(msg.content);
          $(oldchoicediv).html(Number(oldchoice)-Number(1));
          $(newchoicediv).html(Number(newchoice)+Number(1));
        }else{
          $(oldchoicediv).html(Number(oldchoice)-Number(1));
          $(newchoicediv).html(Number(newchoice)+Number(1));
          var totcount = $('#tot-count-'+nid_val).html();
          $('#tot-count-'+nid_val).html(Number(totcount)+Number(1));
                      
          $('#vote-count-poll-'+nid_val).show();
          thisForm.find('#vote_type').val('edit');
          thisForm.find('#def_vote').val(choice);
        }
        thisForm.find('#edit-change').val('Change Vote');
      }else {
        if(vote_type == 'edit'){
          thisForm.find('#edit-change').val('Change Vote');
        }else{
          thisForm.find('#edit-change').val('Vote');
        }
      }
    }
  });
  return false;
    
})
// VALIDATE FLAG ISSUE FORM
$('#abuse-report-form').live('submit', function(e){
  e.preventDefault();
  if($(this).find('input:radio[name=reason]:checked').length == 0){
    $(this).find('#flag-error').html('Please select your flag reason');
    return false;
  }
  var data=$(this).serialize();
  $.ajax({
    type: 'post',
    url: $(this).attr('action'),
    data: data,
    success: function(data){
      $('#abuse-report-form').html(data);

    }
  });
});

$('.openlogin_box').live('click', function(){
  $('#dialog').tabs();
  $('#dialog').dialog('open');
  return false;
})



/**Rallydev:526**/
$(document).ready(function(){
  $('#new-ellipse').click(function(){
    $('#extended-issue-description').show();
    $(this).remove();
  });
});
/**************/


$(document).ready(function(){
  $('.popup a').click(function(){
    var e = $(this).attr('class');
    var id = $(this).parents('dl').attr('name');
    nid = Drupal.settings.nid;
    var url = Drupal.settings.base_url + '/arguments/tabs/' + nid +'/';
    $('#debate_list_area').tabs("url", 0 , url+0+'/0?class='+e +'&chorder='+id);
    $('#debate_list_area').tabs("url", 1 , url+1+'/0?class='+e +'&chorder='+id);
    $('#debate_list_area').tabs("url", 2 , url+2+'/0?class='+e +'&chorder='+id);

    var selected = $("#debate_list_area").tabs( "option", "selected" );
    $('#debate_list_area').tabs("load", selected);
    $('#debate_list_area').tabs("select", selected);
    
    var filter = $(this).parents('.show_only').find('.popup');
    filter.removeClass('visible').addClass('hidden');
    $('#debate_list_area .show_only span.button').removeClass('active');
    return false;
  })
});