/**
 * This file contains custom js behaviours on site
 */

// YN module related js-events

/*
 * Change the Yes/No votes number
 */
function votes_update(content_type, content_id, agree, count) {
  var selector = '#yn-'+content_type+'-'+content_id+' .yn-'+(agree?'a':'d')+' span';
  var count_before = jQuery(selector).html().replace(/[\(\)]/g,'');
  count_before = parseInt(count_before);
  if( count == null ) {
    count = count_before + 1;
  }
  if( count != count_before ) {
    jQuery(selector).fadeOut(1000, function(){ $(this).html('('+count+')').fadeIn(1000); });
  }
}

/*
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

$(document).ready(function(){
  $('.yn').live('click', function(e){
    e.preventDefault();
    var el = $(this).closest('.position-question').find('.reply-comment');
    element_toggle(el);
    if ($(this).hasClass('agree')) {
      el.find('input[name=str_wk]').val('1');
    } else {
      el.find('input[name=str_wk]').val('0');
    }
  });
});

/*
 * Success event on YN callback
 */
function yn_success(el, data) {
  var parent = el.closest('.comment-agree');

  console.log(parent);
  console.log(el);
  console.log(data);
  // update circle
  circle_update(el.parents('.one-forum'), data.pvote_sum);
  // update the vote counts
  votes_update(data.content_type, data.content_id, true, data.vote_up);
  votes_update(data.content_type, data.content_id, false, data.vote_dn);
  // update parent vote count
  if( data.parent_id != data.content_id ) {
    votes_update('node', data.parent_id, true, data.pvote_up);
    votes_update('node', data.parent_id, false, data.pvote_dn);
  }
  parent.children('.yn').attr({'title':'You have rated this!'}).removeClass('yn-a yn-d');
}