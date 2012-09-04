/*
 * Jquery Form Reset Extension
 */
$.fn.reset = function () {
  $(this).each(function() {
    this.reset();
  });
}

/*
 * Toggle Argument Add Form
 */
function argument_form_toggle(invoker) {
  var area = $('#leave_comment_area');
  if (area.hasClass('hidden_ar')) {
    invoker.addClass('expanded');
    area.removeClass('hidden_ar').addClass('visible_ar').slideDown(400);
  } else {
    invoker.removeClass('expanded');
    area.addClass('hidden_ar').removeClass('visible_ar').slideUp(400);
  }
}

/*
 * Toggle Analytics Form
 */
function analytics_form_toggle(invoker) {
  var area = $('#analytics-area');
  if (area.hasClass('hidden_deb')) {
    area.removeClass('hidden_deb').addClass('visible_deb').slideDown(400);
    invoker.addClass('expanded');
  } else {
    area.removeClass('visible_deb').addClass('hidden_deb').slideUp(400);
    invoker.removeClass('expanded');
  }
}

$(document).ready(function() {

  /*
   * Switch between Debate/Resource forms
   */
  $('.reference-form').hide();
  $('#link_arg-wrapper a').click(function(){
    $('.reference-form').show();
    $('.argument-form').hide();
    $('#argument_type').val(0);
    return false;
  });
  $('#link_ref-wrapper a').click(function(){
    $('.reference-form').hide();
    $('.argument-form').show();
    $('#argument_type').val(1);
    return false;
  });

  /*
   * Show/Hide the Argument Form
   */
  $('h6#add-arg').click(function() {
    argument_form_toggle($(this));
    var area = $('#analytics-area');
    if (area.hasClass('visible_deb')) {
      area.removeClass('visible_deb').addClass('hidden_deb').slideUp();
      $('h6#deb-ana').removeClass('expanded');
    }
  });

  /*
   * Show/Hide the Analytics Form
   */
  $('h6#deb-ana').click(function() {
    var area = $('#leave_comment_area');
    if (area.hasClass('visible_ar')) {
      area.removeClass('visible_ar').addClass('hidden_ar').slideUp();
      $('h6#add-arg').removeClass('expanded');
    }
    analytics_form_toggle($(this));
  });

  /*
   * Change the height of the form
   */
  $('.add_button .argument-form a, .add_button .reference-form a').click(function() {
    if ($('#leave_comment_area table .reference-form').css('display') == 'block'){
      $('#leave_comment_area .add_button').addClass('reduce');
    } else {
      $('#leave_comment_area .add_button').removeClass('reduce');
    }
  });

  /*
   * New Argument Form
   */
  $('#argument-add-form').on('submit', function(e){
    e.preventDefault();

    var form = $('#argument-add-form');

    // type = 1/0 = debate/resource
    var type = $('#argument_type').val();
    // debate title
    var title = $('#deb_title').val();
    // debate flags
    var flag_set = false;
    var choices_count = Drupal.settings.arguments_form.count;
    for(var i=0; i<choices_count; i++) {
      if(jQuery('#sup_'+i).val() != 0) {
        flag_set = true;
        break;
      }
    }
    // resource link & regexp
    var nlink = $('#url').val();
    // resource linkbox
    var linkbox = $('#linkbox').html();

    // check errors
    var error = false;
    if(title.length < 2 && type == 1){
      error = 'Please let us know what you think.';
    } else if(!flag_set && type == 1) {
      error = 'You must choose at least one suppose or oppose.';
    } else if(!url_validate(nlink) && type == 0) {
      error = 'Please enter a valid URL.';
    } else if(linkbox == '' && type == 0) {
      error = 'Please press Attach before adding.';
    }
    if( error ) {
      $.hrd.noty({
        type  : 'error',
        text  :  error
      });
      return false;
    }

    // hide submit button
    $('#add_argument').hide();
    // show sub loader
    $('#sub_loader').show();

    // without errors submit form
    $.ajax({
      type      : 'POST',
      dataType  : 'json',
      url       : form.attr('action'),
      data      : form.serialize(),
      success   : function(response) {
        // close form
        argument_form_toggle($('h6#add-arg'));
        // work with response
        if (response.success) {
          // success message
          $.hrd.noty({
            type  : 'success',
            text  :  response.message
          });
          // reset form
          form.reset();
          // reset linkbox
          $('#linkbox').html('');
          // reset the chicces
          for(var i=0; i<choices_count; i++) {
            $('#sup_'+i+' option').removeAttr('selected');
            $('#slider-'+i).slider({value:2});
            $('#sup_'+i+' :nth-child(2)').attr("selected", "selected");
          }
          // refresh the opened tab
          var selected = $("#debate_list_area").tabs( "option", "selected" );
          $('#debate_list_area').tabs("load", selected);
        } else {
          $.hrd.noty({
            type  : 'error',
            text  :  response.message
          });
        }
      },
      complete: function(){
        // hide sub loader
        $('#sub_loader').hide();
        // show submit button
        $('#add_argument').show();
        // recalculate
        var ct = $('.'+(type==1?'arg':'res')+'count');
        ct.fadeOut(1000, function(){
          var count = parseInt(ct.html())+1;
          ct.html(count);
          ct.fadeIn(1000);
        });
      }
    });
    return false;
  });


});
