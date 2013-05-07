/**
 * Slider improvements
 */
$(document).ready(function () {
  $(function () {
    var select = $('.value-select .form-item select');
    select.each(function (e) {
      var slider = $("<div id='slider-" + e + "'><span class='left'></span><span class='right'></span></div>").insertAfter($(this)).slider({
        min:1,
        max:3,
        range:2,
        value:select[e].selectedIndex + 1,
        slide:function (event, ui) {
          select[e].selectedIndex = ui.value - 1;
        }
      });
    });
    select.change(function () {
      $(this).next().slider("value", this.selectedIndex + 1);
    });
  });
});

/**
 * $ Form Reset Extension
 */
$.fn.reset = function () {
  $(this).each(function () {
    this.reset();
  });
}

///////////////// Argument form togglers

/**
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

/**
 * Show/Hide the Argument Form
 */
$('h6#add-arg').live('click', function () {
  argument_form_toggle($(this));
  var area = $('#analytics-area');
  if (area.hasClass('visible_deb')) {
    area.removeClass('visible_deb').addClass('hidden_deb').slideUp();
    $('h6#deb-ana').removeClass('expanded');
  }
});

/**
 * Function to toggle element
 */
function element_toggle(element) {
  if (element.hasClass('hidden')) {
    element.removeClass('hidden').addClass('visible').slideDown(400);
  } else {
    element.removeClass('visible').addClass('hidden').slideUp(400);
  }
}

/**
 * To change support value
 */
$('.yn').live('click', function (e) {
  e.preventDefault();
  var el = $(this).closest('.position-question').find('.reply-comment');
  element_toggle(el);
  if ($(this).hasClass('agree')) {
    el.find('input[name=support]').val('1');
  } else {
    el.find('input[name=support]').val('0');
  }
});

/**
 * Show (Click yes/no to leave support/oppose comment.)
 */
$('.yn').live('click', function () {
  $('.reply_wrapper legend a').parents('ul.argument_box').find('strong.motivat').css('display', 'block');
});

////////////// YN Callbacks

/**
 * Change the Yes/No votes number
 */
function votes_update(content_type, content_id, agree, count) {
  var selector = '#yn-' + content_type + '-' + content_id + ' .yn-' + (agree ? 'a' : 'd') + ' span';
  var el = $('#yn-' + content_type + '-' + content_id);
//  console.log(el);
  var el_a = el.children('.yn-' + (agree ? 'a' : 'd'))
//  console.log(el_a);
  var count_before = $(selector);
  var el_span = el_a.children('span');
  count_before = el_span;
  console.log(el_span);
  if (!count_before) {
    return;
  }
  count_before = count_before.html().replace(/[\(\)]/g, '');
  count_before = parseInt(count_before);
  if (count == null) {
    count = count_before + 1;
  }
  if (count != count_before) {
    $(selector).fadeOut(1000, function () {
      $(this).html('(' + count + ')').fadeIn(1000);
    });
  }
}

/**
 * Change the size of the debate vote sum count
 *
 * @element  - element to recalculate for
 * @count    - vote count
 */
function circle_update(element, count) {
  var size = Math.abs(count) > 100 ? 'large' : ( Math.abs(count) > 10 ? 'middle' : 'small' );
  var color = count > 0 ? 'positive' : ( count < 0 ? 'negative' : 'null' );
  element.find('span.sum')
    .removeClass('small middle large')
    .addClass(size);
  element.find('span.sum span')
    .html(count)
    .removeClass('null positive negative')
    .addClass(color);
}

/**
 * Success event on YN callback
 */
function yn_success(el, data) {
  var parent = el.closest('.comment-agree');
  // update circle
  circle_update(el.parents('.one-forum'), data.pvote_sum);
  // update the vote counts
  votes_update(data.content_type, data.content_id, true, data.vote_up);
  votes_update(data.content_type, data.content_id, false, data.vote_dn);
  // update parent vote count
  if (data.parent_id != data.content_id) {
    votes_update('node', data.parent_id, true, data.pvote_up);
    votes_update('node', data.parent_id, false, data.pvote_dn);
  }
  parent.children('.yn').attr({'title':'You have rated this!'}).removeClass('yn-a yn-d');

  // update strenght chart
  charts_update();
}

/**
 * Resource text -- remove http://
 */
$('#url').focusin(function () {
  if ($(this).val() == $(this).prop('defaultValue')) {
    $(this).val('');
  }
});
$('#url').focusout(function () {
  if ($(this).val() == '') {
    $(this).val($(this).prop('defaultValue'));
  }
});

/**
 * Reply Form Submit
 */
$('.arg-reply-form').live('submit', function (e) {
  e.preventDefault();
  var form = $(this);
  if (form.find('textarea').val().length < 2) {
    // TODO text translate
    $.hrd.noty({'type':'error', 'text':'Please enter your reply'});
    return;
  }
  // hide submit button
  form.find('input[type=submit]').hide();
  // show sub loader
  form.find('#sub_loader').show();
  // get parent
  var parent = form.closest('.one-forum');
  var parent_id = parent.attr('name');

  $.ajax({
    type:'POST',
    dataType:'json',
    url:form.attr('action'),
    data:form.serialize(),
    success:function (response) {
      if (!response.status) {
        $.hrd.noty({text:response.message, type:'error'});
        return false;
      }
      // show message
      $.hrd.noty({text:response.message, type:'success'});
      // reset form
      form.reset();
      // add the comment to the list
      parent.find('#all_replybox_' + parent_id).prepend(response.content);
      // toggle replybox
      element_toggle(parent.find('.reply-comment'));
      // update reply count
      var replycount = parent.find('.replies legend span.replycount');
      replycount.fadeOut(1000, function () {
        replycount.html(parseInt(replycount.html()) + 1);
        replycount.fadeIn(1000);
      });
      // add the translate to the new comment
      translate();
    },
    complete:function () {
      // show submit button
      form.find('input[type=submit]').show();
      // hide sub loader
      form.find('#sub_loader').hide();
    }
  });
});

/**
 * Argument Delete
 */
$('.argument-delete').live('click', function (e) {
  e.preventDefault();
  var el = $(this);

  $.hrd.noty({
    'layout':'center',
    'type':'alert',
    // TODO text translate
    'text':'Are you sure you want to delete?',
    'modal':true,
    'timeout':false,
    'buttons':[
      {
        addClass:'btn btn-primary',
        // TODO text translate
        text:'Delete!',
        onClick:function ($noty) {
          $.ajax({
            type:'POST',
            dataType:'json',
            url:'/argument/delete/' + el.attr('name'),
            data:{},
            success:function (response) {
              if (!response.status) {
                $.hrd.noty({text:response.message, type:'error'});
                return false;
              }
              // show message
              $.hrd.noty({text:response.message, type:'success'});
              // delete content from page
              var params = el.attr('name').split('/');
              var container = false;
              switch (params[0]) { // by content_type
                case 'node' :
                  container = el.closest('.one-forum');
                  break;
                case 'comment' :
                  container = el.closest('.one_reply');
                  break;
              }
              if (container) {
                container.slideUp(400, function () {
                  container.remove();
                });
              }
            }
          });
          $noty.close();
        }
      },
      {
        addClass:'btn btn-danger',
        // TODO text translate
        text:'Cancel',
        onClick:function ($noty) {
          $noty.close();
        }
      }
    ]
  });
});

/**
 * Google translate
 */
Drupal.behaviors.translate = function (context) {
  translate();

  if (typeof tipsy_attach == 'function') {
    tipsy_attach();
  }

  if (typeof toggle_resources == 'function') {
    toggle_resources();
  }

}

/**
 * Tabs Recent/Supported/Old
 */
$(document).ready(function () {
  $("#debate_list_area").tabs({
    cache:false,
    load:function (event, ui) {
      Drupal.attachBehaviors();
    }
  });
});

/**
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

/**
 * Switch between Debate/Resource forms
 */
$(document).ready(function () {
  $('.reference-form').hide();

  $('.add_button .argument-form a').click(function () {
    $('.reference-form').show();
    $('.argument-form').hide();
    $('#argument_type').val(2);
//    TODO text translate
    $('#add_argument').val($('#linkbox').html() == '' ? 'Attach' : 'Add');
    $(this).parents('.add_button').addClass('reduce');
    return false;
  });

  $('.add_button .reference-form a').click(function () {
    $('.reference-form').hide();
    $('.argument-form').show();
    $('#argument_type').val(1);
//    TODO text translate
    $('#add_argument').val('Add');
    $(this).parents('.add_button').removeClass('reduce');
    return false;
  });

});

/**
 * Show/Hide the Analytics Form
 */
$(document).ready(function () {
  $('h6#deb-ana').click(function () {
    var area = $('#leave_comment_area');
    if (area.hasClass('visible_ar')) {
      area.removeClass('visible_ar').addClass('hidden_ar').slideUp();
      $('h6#add-arg').removeClass('expanded');
    }
    analytics_form_toggle($(this));
  });
});

/**
 *
 * @param url
 * @return {*}
 */
function url_prepare(url) {
  var regex1 = /^www\./, regex2 = /^http:\/\//;
  if (regex1.test(url) || !regex2.test(url)) {
    return 'http://' + url;
  }
  return url;
}

/**
 * Validate URL
 */
function url_validate(url) {
  // var objRE = /^http:\/\/(www\.)?[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
  var objRE = /^(http[s]?:\/\/){0,1}(www\.){0,1}[a-zA-Z0-9\.\-]+\.[a-zA-Z]{2,5}[\.]{0,1}/;
  return objRE.test(url);
}

/**
 * New Argument Form
 */
$('#argument-add-form').live('submit', function (e) {
  e.preventDefault();

  var form = $('#argument-add-form');

  // type = 1/2 = debate/resource
  var type = $('#argument_type').val();
  // debate title
  var title = $('#deb_title').val();
  // debate flags
  var flag_set = false;
  var choices_count = Drupal.settings.argument_form.count;
  for (var i = 0; i < choices_count; i++) {
    if ($('#sup_' + i).val() != 0) {
      flag_set = true;
      break;
    }
  }
  // resource link & regexp
  var nlink = url_prepare($('#url').val());
  // resource linkbox
  var linkbox = $('#linkbox').html();

  // check errors
  var error = false;
  if (title.length < 2 && type == 1) {
    error = 'Please let us know what you think.';
  } else if (!flag_set && type == 1) {
    error = 'You must choose at least one suppose or oppose.';
  } else if (!url_validate(nlink) && type == 2) {
    error = 'Please enter a valid URL. ' + nlink;
  } else if (linkbox == '' && type == 2) {
    var callback_url = '/argument/preview/resource';
    var lbox = $('#linkbox');
    lbox.slideDown('slow');
    // todo translate string
    lbox.html("<span class='load'>Loading...</span>");

    $.ajax({
      type:'POST',
      dataType:'json',
      url:callback_url,
      data:{ url:nlink },
      success:function (response) {
        if (!response.status) {
          output = false;
          lbox.slideUp('slow', function () {
            lbox.html('')
          });
          $.hrd.noty({
            type:'error',
            text:'Sorry, your URL cannot be attached'
          });
          return false;
        }
        lbox.html(response.message);

        $.hrd.noty({
          type:'success',
          // translate
          text:'You can now submit your resource'
        });
        // todo translate
        $('#add_argument').val('Add');
      }
    });

    return false;
  }
  if (error) {
    $.hrd.noty({
      type:'error',
      text:error
    });
    return false;
  }

  // hide submit button
  $('#add_argument').hide();
  // show sub loader
  $('#sub_loader').show();
  // image
  form.find('input[name=image]').val($('input[name=uimg]').val());

  // without errors submit form
  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/argument/create',
    data:form.serialize(),
    success:function (response) {
      // close form
      argument_form_toggle($('h6#add-arg'));
      // work with response
      if (response.success) {
        // success message
        $.hrd.noty({
          type:'success',
          text:response.message
        });
        // reset form
        form.reset();
        // reset linkbox
        $('#linkbox').html('');
        // reset the chicces
        for (var i = 0; i < choices_count; i++) {
          $('#sup_' + i + ' option').removeAttr('selected');
          $('#slider-' + i).slider({value:2});
          $('#sup_' + i + ' :nth-child(2)').attr("selected", "selected");
        }
        // refresh the opened tab
        var selected = $("#debate_list_area").tabs("option", "selected");
        $('#debate_list_area').tabs("load", selected);
      } else {
        $.hrd.noty({
          type:'error',
          text:response.message
        });
      }
    },
    complete:function () {
      // hide sub loader
      $('#sub_loader').hide();
      // show submit button
      $('#add_argument').show();
      // recalculate
      var ct = $('.' + (type == 1 ? 'arg' : 'res') + 'count');
      ct.fadeOut(1000, function () {
        var count = parseInt(ct.html()) + 1;
        ct.html(count);
        ct.fadeIn(1000);
      });
    }
  });
  return false;
});

/**
 * Image selector buttons
 */
$(document).ready(function () {
  var noimage = $('#no_thumbnail');
  var selectors = $('.img-select');

  // image selectors
  selectors.live('click', function () {
    var images = $('.img-selector').find('img');
    var images_count = images.length;
    var image_src = $('input[name="uimg"]');
    var imgid = $('#img_count');

    // new index
    var image_index = $('input[name="uimg_index"]');
    var image_index_new = Number(image_index.val()) + ($(this).hasClass('prev') ? -1 : 1);
    var next = $('.img-select.next');
    var prev = $('.img-select.prev');

    // new image
    var selected = $('#cur_img_' + image_index_new);
    image_src.val(selected.attr('src'));
    image_index.val(image_index_new);
    imgid.html(image_index_new + 1);
    images.hide();
    selected.show();

    // next button
    if (image_index_new >= images_count - 1) {
      next.hide();
    } else {
      next.show();
    }
    // prev button
    if (image_index_new <= 0) {
      prev.hide();
    } else {
      prev.show();
    }
  });

  // no image behaviour
  noimage.live('click', function () {
    var selectors = $('.img_controls');
    var image_src = $('input[name="uimg"]');
    var images = $('.img-selector').find('img');
    var counter = $('.img_counter');
    if ($(this).attr('checked')) {
      selectors.hide();
      image_src.val('');
      images.hide();
      counter.hide();
    } else {
      selectors.show();
      images.show();
      counter.show();
      var image_index = $('input[name="uimg_index"]');
      // new image
      image_src.val(images[image_index]);
    }
  });
});

/**
 * Show popup
 */
$(document).ready(function () {

  // filters
  $('.popup a').click(function () {
    var e = $(this).attr('class');
    var id = $(this).parents('dl').attr('name');
    var el = $('#debate_list_area');
    var nid = Drupal.settings.node.nid;
    var url = '/argument/tab/' + nid + '/';

    el.tabs("url", 0, url + 0 + '/0?class=' + e + '&chorder=' + id);
    el.tabs("url", 1, url + 1 + '/0?class=' + e + '&chorder=' + id);
    el.tabs("url", 2, url + 2 + '/0?class=' + e + '&chorder=' + id);

    var selected = el.tabs("option", "selected");
    el.tabs("load", selected);
    el.tabs("select", selected);

    var filter = $(this).parents('.show_only').find('.popup');
    filter.removeClass('visible').addClass('hidden');
    $('#debate_list_area .show_only span.button').removeClass('active');
    return false;
  });

  // reset filters
  $('#filter_content .reset').live('click', function () {
    var el = $('#debate_list_area');
    var nid = Drupal.settings.node.nid;
    var url = '/argument/tab/' + nid + '/';
    el.tabs("url", 0, url + 0 + '/0');
    el.tabs("url", 1, url + 1 + '/0');
    el.tabs("url", 2, url + 2 + '/0');
    var selected = el.tabs("option", "selected");
    el.tabs("load", selected);
    el.tabs("select", selected);
  })
});