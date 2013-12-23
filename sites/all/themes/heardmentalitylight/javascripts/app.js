/* 
 * Skeleton V1.0.3
 * Copyright 2011, Dave Gamache
 * www.getskeleton.com
 * Free to use under the MIT license.
 * http://www.opensource.org/licenses/mit-license.php
 * 7/17/2011
 */

$(document).ready(function () {

  $('#effect').delay(5000).fadeOut(1000);
//  $('#effect').fadeOut(1000);
  /* Tabs Activiation
   ================================================== */
  var tabs = $('ul.tabs');

  tabs.each(function (i) {
    //Get all tabs
    var tab = $(this).find('> li > a');
    tab.click(function (e) {

      //Get Location of tab's content
      var contentLocation = $(this).attr('href') + "Tab";

      //Let go if not a hashed one
      if (contentLocation.charAt(0) == "#") {

        e.preventDefault();

        //Make Tab Active
        tab.removeClass('active');
        $(this).addClass('active');

        //Show Tab Content & add active class
        $(contentLocation).show().addClass('active').siblings().hide().removeClass('active');

      }
    });
  });

});

$(function () {

  // Accordion
  $("#accordion").accordion({
    header: "h3"
  });

  // Tabs
  $('#tabs').tabs();

  // Datepicker
  $('#datepicker').datepicker({
    inline: true
  });

  // Slider
  $('#slider').slider({
    range : true,
    values: [17, 67]
  });

  // Progressbar
  $("#progressbar").progressbar({
    value: 20
  });

  //hover states on the static widgets
  $('#dialog_link, ul#icons li').hover(
    function () {
      $(this).addClass('ui-state-hover');
    },
    function () {
      $(this).removeClass('ui-state-hover');
    }
  );

});

$(".expanding").collapse({
  show: function () {
    this.animate({
      opacity: 'toggle',
      height : 'toggle'
    }, 300);
  },
  hide: function () {

    this.animate({
      opacity: 'toggle',
      height : 'toggle'
    }, 300);
  }
});

$(function () {

  // Accordion
  $("#accordion").accordion({
    header: "h3"
  });

  // Tabs
//  $('#tabs').tabs();

  // Datepicker
  $('#datepicker').datepicker({
    inline: true
  });

  // Slider
  $('#slider').slider({
    range : true,
    values: [17, 67]
  });

  // Progressbar
  $("#progressbar").progressbar({
    value: 20
  });

  //hover states on the static widgets
  $('#dialog_link, ul#icons li').hover(
    function () {
      $(this).addClass('ui-state-hover');
    },
    function () {
      $(this).removeClass('ui-state-hover');
    }
  );

});

/**
 * FADES
 */


$(document).ready(function () {
  $(".comments.expanding h6, a.facebook, a.twitter").fadeTo("fast", 0.5); // This sets the opacity of the thumbs to fade down to 30% when the page loads
  $(".comments.expanding h6, a.facebook, a.twitter").hover(function () {
    $(this).fadeTo("fast", 1.0); // This should set the opacity to 100% on hover
  }, function () {
    $(this).fadeTo("fast", 0.5); // This should set the opacity back to 30% on mouseout
  });
});

$(document).ready(function () {
  $(".comments.expanding h6#reply").fadeTo("fast", 0.9); // This sets the opacity of the thumbs to fade down to 30% when the page loads
  $(".comments.expanding h6#reply").hover(function () {
    $(this).fadeTo("fast", 1.0); // This should set the opacity to 100% on hover
  }, function () {
    $(this).fadeTo("fast", 0.9); // This should set the opacity back to 30% on mouseout
  });
});

/**
 * JQUERY UI STUFF
 */


$(function () {

  // Accordion
  $("#accordion").accordion({
    header: "h3"
  });

  // Tabs
  // $('#tabs').tabs();

  // Dialog
  $('#dialog').dialog({
    autoOpen : false,
    modal    : true,
    minWidth : 320,
    resizable: true
  });

  // Dialog Link
  $('#dialog_link2').click(function () {
    $('#dialog2').dialog('open');
    return false;
  });

  // Dialog			
  $('#dialog-flag').dialog({
    autoOpen : false,
    modal    : true,
    minWidth : 320,
    resizable: false
  });

  // Dialog Link
  $('#dialog_link-flag').click(function () {
    $('#dialog-flag').dialog('open');
    return false;
  });

  // Dialog			
  $('#dialog-profile-pic').dialog({
    autoOpen : false,
    modal    : true,
    minWidth : 320,
    resizable: false
  });

  // Dialog Link
  $('#dialog_link-pic').click(function () {
    $('#dialog-profile-pic').dialog('open');
    return false;
  });

  // Toggler hide

  $(function () {
    // run the currently selected effect
    function runEffect() {
      $("#effect").hide("fade", 500);
    };
    // set effect from select menu value
    $("#button").click(function () {
      runEffect();
      return false;
    });
  });

  // Toggler show

  $(function () {
    // run the currently selected effect
    function runEffect() {
      // run the effect
      $("#effect2").show("blind", 500);
    };
    // set effect from select menu value
    $("#button2").click(function () {
      runEffect();
      return false;
    });

    $("#effect2").hide();
  });

  // Datepicker
  $('#datepicker').datepicker({
    inline: true
  });

  // Slider
  $('#slider').slider({
    range : true,
    values: [17, 67]
  });

  // Progressbar
  $("#progressbar").progressbar({
    value: 20
  });

  //hover states on the static widgets
  $('#dialog_link, ul#icons li').hover(
    function () {
      $(this).addClass('ui-state-hover');
    },
    function () {
      $(this).removeClass('ui-state-hover');
    }
  );

});

$(function () {

});

/*
 * Functions to hide/show the reply form
 */

Drupal.behaviors.add_reply = function (context) {
  $('ul.argument_box > li > .position-question a.agree').click(function () {

    if ($(this).parents('ul.argument_box > li > .position-question').find('a.disagree').hasClass('collapsed')) {
      $(this).parents('ul.argument_box > li > .position-question').find('a.disagree').removeClass('collapsed');
    }

    var agree = $(this).parents('ul.argument_box > li > .position-question').find('#reply-comment');

    if (agree.hasClass('hidden')) {
      $(this).addClass('collapsed');
    }
    else {
      $(this).removeClass('collapsed');
    }
    element_toggle(agree);

    $(this).parents('ul.argument_box > li > .position-question').find('input[name=str_wk]:radio:even').attr('checked', true);

  });

  $('ul.argument_box > li > .position-question a.disagree').click(function () {

    if ($(this).parents('ul.argument_box > li > .position-question').find('a.agree').hasClass('collapsed')) {
      $(this).parents('ul.argument_box > li > .position-question').find('a.agree').removeClass('collapsed');
    }

    var disagree = $(this).parents('ul.argument_box > li > .position-question').find('#reply-comment');

    if (disagree.hasClass('hidden')) {
      $(this).addClass('collapsed');
    }
    else {
      $(this).removeClass('collapsed');
    }
    element_toggle(disagree);

    $(this).parents('ul.argument_box > li > .position-question').find('input[name=str_wk]:radio:odd').attr('checked', true);

  });

};
