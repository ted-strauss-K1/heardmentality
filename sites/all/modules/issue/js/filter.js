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
function get_filter_option(type) {
  var url=Drupal.settings.base_url+'qlite/ajax?action=filter';
  $('#fopt').html('');
  $.ajax({
    type: "POST",
    url: url,
    data: {
      type: type
    },
    success: function(msg){
      $('#fopt').html(msg);
    }
  });		
}


function MM_jumpMenuGo(){ 
  document.form1.submit();
}

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
  //for IE
  // setTimeout(resetFields,3000);
  //  $('#subject').change();
  //   $('#subject').val("3");
  //sendEvent($('#subject'),'change');//assuming there is a select element
  //$('#subject').fireEvent("onchange");

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

function sendEvent(ele,e){
  try{// every browser except IE8 and below works here
    var evt = document.createEvent("HTMLEvents");
    evt.initEvent(e, true, true);
    ele.dispatchEvent(evt);
  }
  catch(err){
    ele.fireEvent('on'+e);
  }
}


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



// forum reply

function open_replybox(id){
  var spl = id.split("_");
  var open_id = '#reply_box_'+spl[2];
  var msgid = '#reply-msg-'+spl[2];
  $(msgid).html('');
  $(open_id).slideToggle('slow');
}

function show_replies(id){
  var spl = id.split("_");
  var open_id = '#all_replybox_'+spl[2];
  $(open_id).slideToggle('slow');
}



$('.arg-reply-form').live('submit', function(e){
  e.preventDefault();

  var cont = $(this);
  var debid = cont.find('#ded_tnid').val();
  var norep = "#no_rply_"+debid;
  if(cont.find('textarea').val().length<2){
    cont.find('#reply_err').html('<span>Please enter your reply.</span>');
  }else{
    cont.find('#add_reply').hide();
    cont.find('#sub_loader').show();
    var data = cont.serialize();
    var ded_tnid = cont.find('#deb_tnid').val();
    var box_id = '#reply_box_'+ded_tnid;
    var open_id = '#all_replybox_'+ded_tnid;
    $.ajax({
      type: 'POST',
      dataType: 'json',
      url: cont.attr('action'),
      data: data,
      success: function(msg){
        cont.find('textarea').val('');
        $(box_id).slideUp('slow');
        $(norep).remove();
        $(msg.content).prependTo(open_id);
        $(open_id).slideDown('slow');
        cont.find('#reply_err').html('');
        $('#reply-msg-'+ded_tnid).html(msg.message);
      },
      complete: function(){
        cont.find('#add_reply').show();
        cont.find('#sub_loader').hide();
        cont.find('#reply_err').html('');
      }
    });
  }
  return false;
});


function delete_thread(id, type){
  var spl = id.split("_");
  var fid  = spl[2];
  var dtype = spl[1];
  //var msgid = '#reply-msg-'+fid;
  var url = Drupal.settings.base_url + '/issue/thread/delete/'+dtype+'/'+fid+'/'+type;
  if(confirm("Are you sure to delete this argument?")){
    $.ajax({
      type: 'post',
      url: url,
      success: function(msg){
          
      },
      complete: function(){
        var bid = '#'+dtype+'-block-'+fid;
        $(bid).remove();
      }
    });
    return true;
  }
  else{
    return false;
  }
}


// insight view

function insight_view(nid){

  var url = Drupal.settings.base_url + '/issue/ajax/insightview/'+nid;
  $.ajax({
    type: 'get',
    url: url,
    success:function(msg){
      $('#insight-view').html(msg);
    }
  });

}


// load debate statistics
function loadDebateStatistic() {
  var nid = $('#curr_nid').val();
  $.getJSON(Drupal.settings.base_url + '/debate/ajax/'+ nid +'/'+ '?action=analysis', function(data) {
    var chart;
    chart = new Highcharts.Chart({
      chart: {
        renderTo: 'container',
        defaultSeriesType: 'column',
        style: {
          fontFamily: 'Arial',
          color: '#4c4c4c',
          fontSize: '12px'
        },
        plotBorderColor: '#fff',
        plotBorderWidth: 0,
        borderColor: '#fff',
        borderRadius: 0,
        borderWidth: 0,
        marginTop: 10,
        marginRight: 20,
        marginBottom: 80,
        marginLeft: 30,
        ignoreHiddenSeries: true
      },
      title: {
        text: null
      },
	  
      xAxis: {
        categories: data.categories,
        title: {
          text: null
        },
        lineColor: '#ccc',
        lineWidth: 1,
        endOnTick: false,
        tickColor: '#ccc',
        tickWidth: 1,
        tickLength: 5,
        gridLineColor: '#ccc',
        tickmarkPlacement: 'on',
        startOnTick: false,
        labels: {
          style: {
            color: '#4c4c4c',
            font: '12px Aial, sans-serif'	
          }
        }
      },
	  
      yAxis:{ 
        tickInterval: 1,
        title: {
          text: null
        },
        endOnTick: false,
        maxPadding: 0.01,
        lineWidth: 1,
        lineColor: '#ccc',
        tickmarkPlacement: 'on',
        tickColor: '#ccc',
        tickWidth: 1,
        tickLength: 5
      },
					
      legend: {
        enabled: false
      },
	
      tooltip: {
        formatter: function() {
          return ''+
          this.series.name +': '+ this.y +'';
        },
        shadow: false,
        style: {
          color: '#4c4c4c',
          font: '12px Aial, sans-serif'
        },
        borderRadius: 3
      },
	  
      plotOptions: {
        column: {
          dataLabels: {
            enabled: false
          },
          borderColor: '#fff',
          borderWidth: 0,
          shadow: false,
          groupPadding: 0.15,
          pointPadding: 0
        }
      },
	  
      credits: {
        enabled: false
      },
      series: [{
        name: 'Strength',
        data: data.data
      }]
    });
  });
}

$('#deb-ana').live('click', function(){
  var nid = $('#curr_nid').val();
  var url = Drupal.settings.base_url + '/issue/ajax/debate_statistics/'+ nid;
  $('#deb-ana-load-txt').html('Loading...');
  $.ajax({
    type: 'get',
    url: url,
    success:function(msg){
      $('#load-deb-statics').html(msg);
    },
    complete:function(){
      loadDebateStatistic();
      $('#deb-ana-load-txt').html('');
    }
  });
});

// load reference statistics
$('#res-ana').live('click', function(){
  var nid = $('#curr_nid').val();
  var url = Drupal.settings.base_url + 'issue/ajax/resource_statistics/'+nid;
  $('#res-ana-load-txt').html('Loading...');
  $.ajax({
    type: 'get',
    url: url,
    success:function(msg){
      $('#load-res-statics').html(msg);
    },
    complete:function(){
      $('#res-ana-load-txt').html('');
    }
  });
});


// from debate module - code cleanup

$(document).ready(function() {
  $("#lattach").click(function() {
    var url = $('#edit-ref-title').val();
    //var objRE = /(^http?:\/\/)?[a-z0-9~_\-\.]+\.[a-z]{2,9}(\/|:|\?[!-~]*)?$/i;
    var objRE = /http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
    //  var url= content.match(urlRegex);
    if (objRE.test(url) == false) {
      $('#deb-err').html('<span>Please enter a valid URL.</span>');
      return false;
    }
    else {
      var purl=Drupal.settings.base_url+'/debate/ajax';
      $(this).attr('disabled',true);
      $("#linkbox").slideDown('show');
      $("#linkbox").html("<span class='load'>Loading...</span>");
      $.get(purl+"?action=url&url="+url,function(response)
      {
        $("#linkbox").html(response);
        $("#lattach").removeAttr('disabled');
        if($('#cur_id_val').val() == $('#end_image').val()){
          $('#re-sel-next').hide();
          $('#re-sel-prev').hide();
        }

        $('#re-sel-pre').hide();
      });
      
    }
    return false;
  });


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
    //var el =  $('#twitMsg', top.document);
    var el =  $('#refer-err');

    if ($.trim(err).length > 1) {
      el.html(err);
      el.addClass('error-msg');
      //$('#twitMsg', top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
      return false;
    }	else{
      el.hide();
    }

    //$('input[type="submit"]').attr('disabled',true);
    $(this).find('#add-new-res').hide();
    $(this).find('#sub_loader_res').show();
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
        $('#sub_loader_res').hide();
        $('#add-new-res').show();
        // el.delay(400).slideDown(400).delay(3000).slideUp(400);
        // $.growlUI('', data);
        $('input[type="submit"]').removeAttr('disabled');
      });

    return false;
  });
});

function startload(){
// initialize();
//createUploader();
}


function createUploader(){
  var uploader = new qq.FileUploader({
    element: document.getElementById('file-uploader-demo1'),
    action: Drupal.settings.base_url+'upload_document.php',
    debug: true,
    // url of the server-side upload script, should be on the same domain
    // additional data to send, name-value pairs
    //params: {},

    // validation
    // ex. ['jpg', 'jpeg', 'png', 'gif'] or []
    allowedExtensions: ["doc","docx","ppt","pdf"],
    // each file size limit in bytes
    // this option isn't supported in all browsers
    sizeLimit: 1000000, // max size
    minSizeLimit: 1, // min size
    multipleFileUpload:false,
    onSubmit: function(id, fileName){
      $.growlUI('','File uploading please wait!');
    },
    onProgress: function(id, fileName, loaded, total){
      $.growlUI('','File uploading please wait!');
    },
    onComplete: function(id, fileName, responseJSON){
      $('#docpath').val(responseJSON.filename);
      $.growlUI('','File uploaded successfully!');
    },
    showMessage: function(message){

      $.growlUI('',message);
    }

  });
}

// in your app create uploader as soon as the DOM is ready
// don't wait for the window to load
//window.onload = createUploader;
window.onload=startload;


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
function res_type_tab(id,tab,nid){
  var divid;

  // url sort get values
  var sup = $('#sup').val();
  var ans = $('#ans').val();
  var sort = $('#sort').val();

  $('#load-resource').prepend('Loading...');
  var url = Drupal.settings.base_url+'issues/load_resources/'+nid+'/'+id+'/'+sup+'/'+ans+'/'+sort;
  $.ajax({
    type: 'post',
    url: url,
    success: function(msg){
      $('#load-resource').html('');
      $('#load-resource').html(msg);
    }
  });
}

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

  $(".innerbox li a").live('click', function(e) {

    });



});

function load_issue(url){

  $('#qajax').load(url, function(response, status, xhr) {
    if (status == "success") {
      reset_tabs();

    }else{
      var msg = "Sorry but there was an error: ";
      $("#qajax").html(msg + xhr.status + " " + xhr.statusText);
    }
  });

}

function check_popup_login(){
  $(document).ready(function() {

    $('#twitMsg').html("Please Login to do this!");
    $('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
  });
}

function close_notify_message(dcount, mid, uid){

  $(document).ready(function() {

    var divid = 'not-id-'+dcount;
    var url = gSitePath+'question/ajax';
    $.ajax({
      type: "GET",
      url: url,
      data: 'mid='+mid+'&uid='+uid+'&notupdate=1',
      success: function(msg)
      {
        if(msg){
          $('#'+divid+'').hide();
        }else{
          return false;
        }
      }
    });
  });

}

function show_inotify(data){

  $('#twitMsg',top.document).html(data);
  $('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);

}

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

// open flag for arguments
function open_flag_box(oid, type){
  var divId;
  if(type == 'node'){
    divId = '#flag-arg-'+oid;
  }else if(type == 'comment'){
    divId = '#flag-comm-'+oid;
  }
  $(divId).dialog('open');
  $(divId).html('Please Wait...');
  $.ajax({
    type: 'get',
    data: {
      'flag_type': type
    },
    url: Drupal.settings.base_url + '/issue/ajax/getForumFlagForm/'+oid,
    success: function(form){
      $(divId).html(form);
    }
  });
  return false;
}

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
    nid = $('#curr_nid').val();
    var url = Drupal.settings.base_url + '/issue/' + nid +'/tab_content/1/';
    $('#debate_list_area').tabs("url", 0 , url+0+'?class='+e +'&chorder='+id);
    $('#debate_list_area').tabs("url", 1 , url+1+'?class='+e +'&chorder='+id);
    $('#debate_list_area').tabs("url", 2 , url+2+'?class='+e +'&chorder='+id);
    var selected = $("#debate_list_area").tabs( "option", "selected" );
    $('#debate_list_area').tabs("load", selected);
    $('#debate_list_area').tabs("select", selected);
    
    var filter = $(this).parents('.show_only').find('.popup');
    filter.removeClass('visible').addClass('hidden');
    $('#debate_list_area .show_only span.button').removeClass('active');
    return false;
  })
});