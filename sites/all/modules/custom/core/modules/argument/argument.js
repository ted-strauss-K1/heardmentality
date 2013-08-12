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
  var el_a = el.children('.yn-' + (agree ? 'a' : 'd'))
  var count_before = el_a.find('span');
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

$('body').on('yn', function(e, el, data) {
  var body = $('body');

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
  body.trigger('cpoll_update', true);

  // badges
  if (1 == data['vote_value']) {
    if ('comment' == data['content_type']) {
      body.trigger('badge.comment_yn_voteup', [data['content_uid']]);
    }
    if ('node' == data['content_type']) {
      body.trigger('badge.'+data['node_type'] + '_yn_voteup', [data['content_uid']]);
    }
    body.trigger('badge.yn_voteup', [Drupal.settings.user.uid]);
    body.trigger('badge.yn_predict', [data['first_voter']]);
  }
});

/**
 * Resource text -- remove http://
 */
$('#url').focusin(function () {
  if ($(this).val() == $(this).prop('defaultValue')) {
    $(this).val('');
  }
}).focusout(function () {
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
    $.hrd.noty({'type':'error', 'text':'Please enter your reply'}); // todo translate
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

      var body = $('body');
      body.trigger('events', ['reply', {
        'cid'           : response.cid,
        'content_type'  : 'comment',
        'content_id'    : response.cid
      }])

      // badges
      body.trigger('badge.debate_create', [Drupal.settings.node.uid]);
      body.trigger('badge.comment_create', [Drupal.settings.user.uid]);

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

  var name = el.attr('name');

  $.hrd.noty({
    'layout':'center',
    'type':'alert',
    'text':'Are you sure you want to delete?', // todo translate
    'modal':true,
    'timeout':false,
    'buttons':[
      {
        addClass:'btn btn-primary',
        text:'Delete!', // todo translate
        onClick:function ($noty) {
          $.ajax({
            type:'POST',
            dataType:'json',
            url:'/argument/delete/' + name,
            data:{},
            success:function (response) {
              if (!response.status) {
                $.hrd.noty({text:response.message, type:'error'});
                return false;
              }
              // show message
              $.hrd.noty({text:response.message, type:'success'});
              // delete content from page
              var params = name.split('/');
              var container = false;
              switch (params[0]) { // by content_type
                case 'node' :
                  container = el.closest('.one-forum');
                  counter = container.hasClass('argument') ? $('.argcount') : $('.rescount');
                  break;
                case 'comment' :
                  container = el.closest('.one_reply');
                  counter = container.parents('div.replies').find('.replycount');
                break;
              }
              if (container) {
                counter.html( parseInt(counter.html()) - 1 );
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
        text:'Cancel', // todo translate
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

  expander();
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
    $('#argument_type').val('resource');
    // $('#add_argument').val($('#linkbox').html() == '' ? 'Attach' : 'Add'); // todo translate
    $(this).parents('.add_button').addClass('reduce');
    return false;
  });

  $('.add_button .reference-form a').click(function () {
    $('.reference-form').hide();
    $('.argument-form').show();
    $('#argument_type').val('argument');
    $('#add_argument').val('Add'); // todo translate
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
  var type = $('#argument_type').val();

  var
    error = false,
    data = {},
    choices_count = Drupal.settings.argument_form.count;

  data['nid'] = form.find('[name=nid]').val();
  data['type'] = type;

  // argument posting
  if ('argument' == type) {
    // title
    var title = $('#deb_title').val();
    if (title.length < 2) {
      error = 'Please let us know what you think'; // todo translate
    }

    // flags
    var flag_set = false;
    data['options'] = {};
    form.find('input[name^="chorder_"]').each(function (i,e) {
      var
        chid = $(e).val(),
        val = form.find('[name="option_'+chid+'"]').val();
      data['options'][chid] = val;
      if (0 != val) {
        flag_set = true;
      }
    });
    if (!flag_set) {
      error = 'You must choose at least one suppose or oppose'; // todo translate
    }

    // data collect
    data['text'] = form.find('textarea').val();
  }

  var ifnull = function(text) {
    return 'null' == text || !text ? '' : text;
  }

  // resource posting
  if ('resource' == type) {
    var embedly = form.find('.embedly');
    var preview = embedly.data('preview');
    if (preview['url']) {
      data['url'] = preview['url'];
      data['title'] = ifnull(preview['title']);
      data['description'] = ifnull(preview['description']);
      data['image'] = ifnull(preview['thumbnail_url']);
    } else {
      error = 'The URL you entered was not processed. Try pasiting it again.'; // todo translate
    }
  }

  // handle errors
  if (error) {
    $.hrd.noty({
      type:'error',
      text:error
    });
    return false;
  }

  // hide submit button and show loader
  $('#add_argument').hide();
  $('#sub_loader').show();

  // submit form
  // without errors submit form
  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : '/argument/create',
    data      : data,
    success   : function (response) {
      // close form
      argument_form_toggle($('h6#add-arg'));
      // work with response
      if (response.success) {
        // success message
        $.hrd.noty({
          type  : 'success',
          text  : response.message
        });
        // reset form
        form.reset();
        // reset choices
        for (var i = 0; i < choices_count; i++) {
          $('#sup_' + i + ' option').removeAttr('selected');
          $('#slider-' + i).slider({value:2});
          $('#sup_' + i + ' :nth-child(2)').attr("selected", "selected");
        }
        // reset embedly
        $('.embedly-wrapper').html('');
        // refresh the opened tab
        var debate_area = $("#debate_list_area");
        var selected = debate_area.tabs("option", "selected");
        debate_area.tabs("load", selected);

        // event
        var body = $('body');
        body.trigger('events', ['debate', {
          'nid'           : response.nid,
          'content_type'  : 'node',
          'content_id'    : response.nid
        }]);

        // badges
        body.trigger('badge.debate_create', [Drupal.settings.node.uid]);

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


  // todo check below


  // debate title


  // resource link & regexp
  var nlink = url_prepare($('#url').val());
  // resource linkbox
  var linkbox = $('#linkbox').html();

  // check errors

  if (title.length < 2 && type == 'argument') {
    error = 'Please let us know what you think.';
  } else if (!flag_set && type == 'argument') {
    error = 'You must choose at least one suppose or oppose.';
  } else if (!url_validate(nlink) && type == 'resource') {
    error = 'Please enter a valid URL. ' + nlink;
  } else if (linkbox == '' && type == 'resource') {
    var callback_url = '/argument/preview/resource';
    var lbox = $('#linkbox');
    lbox.slideDown('slow');
    lbox.html("<span class='load'>Loading...</span>"); // todo translate string

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
            text:'Sorry, your URL cannot be attached' // todo translate
          });
          return false;
        }
        lbox.html(response.message);



        $.hrd.noty({
          type:'success',
          text:'You can now submit your resource' // todo translate
        });
        $('#add_argument').val('Add'); // todo translate
      }
    });

    return false;
  }

  // image
  form.find('input[name=image]').val($('input[name=uimg]').val());


  return false;
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

function toggle_resources() {
  if ($('#inc_check').attr('checked')) {
    $('.resource').show();
  } else {
    $('.resource').hide();
  }
}

$(document).ready(function () {
  /*
   * Toggle resources
   */
  $('#inc_check').change(function () {
    toggle_resources();
  });

});

/**
 *
 */
$('a.permalink').live('click', function (e) {
  e.preventDefault();
//  var link = window.location.href.replace(/#.*/, '') + '#' + $(this).parents('.one-forum').attr('id');
  var link = $(this).attr('name');
  $.hrd.noty({
    'layout':'center',
    'type':'alert',
    'text':'<a href="' + link + '">' + link + '</a>',
    'modal':true,
    'timeout':false,
    'closeWith':['button']
  });
});