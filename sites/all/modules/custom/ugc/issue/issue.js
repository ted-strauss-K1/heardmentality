/*
 * Count letters on issue create form
 */
$(function() {
  var maxChar = 140;
  limitChars = function(){
    var text = $("#q_quest").val();
    if (text.length > maxChar) {
      text = text.substring(0, maxChar);
      $("#q_quest").val(text);
    }
  }
});

/*
 * Override ahah.success
 *
 * @warning -- This is very important. Do not modify.
 *
 * @see http://drupal.org/node/1005598
 */
$(function(){
  //override ahah success to fire a custom javascript function, if it's in the response object
  Drupal.ahah.prototype.success = function (response, status){
    var customCallback = function(){
      if(!!response.js){ //fire custom javascript callback after AHAH has done its thing
        eval(response.js['func']+'('+(!!response.js['params'] ? response.js['params'] : '')+');');
      }
    };
    var wrapper = $(this.wrapper);
    var form = $(this.element).parents('form');
    var new_content = $('<div></div>').html(response.data);
    form.attr('action', this.form_action);
    this.form_target ? form.attr('target', this.form_target) : form.removeAttr('target');
    this.form_encattr ? form.attr('target', this.form_encattr) : form.removeAttr('encattr');
    if(this.progress.element){$(this.progress.element).remove();}
    if(this.progress.object){this.progress.object.stopMonitoring();}
    $(this.element).removeClass('progress-disabled').attr('disabled', false);
   // Drupal.freezeHeight();
    if(this.method == 'replace'){wrapper.empty().append(new_content);}
    else{wrapper[this.method](new_content);}
    if(this.showEffect!='show'){new_content.hide();}
    if(($.browser.safari && $("tr.ahah-new-content", new_content).size()>0)){new_content.show();customCallback();}
    else if($('.ahah-new-content', new_content).size()>0){
      $('.ahah-new-content', new_content).hide();
      new_content.show();
      $(".ahah-new-content", new_content)[this.showEffect](this.showSpeed, customCallback);
    }
    else if(this.showEffect != 'show'){new_content[this.showEffect](this.showSpeed, customCallback);}
    if(new_content.parents('html').length > 0){Drupal.attachBehaviors(new_content);}
    //Drupal.unfreezeHeight();
  };
});

/*
 * This function runs every time we exceed the limit of possible answers
 */
function issue_create_ahah_answer_error() {
  $.hrd.noty({
    'type'   : 'error',
    'text'   : 'Maximum fields exceeded'
  });
}


$(document).ready(function(){
  /*
   * Regular and Suggested choices
   */
  var s1 = '.choices.regular input[type="radio"]';
  var s2 = '.choices.suggested input[type="radio"]';
  function choices(s1,s2) {
    $(s1).change(function() {
      $(s1).parents('div.form-item').removeClass('staygreen');
      $(s1+':checked').parents('div.form-item').addClass('staygreen');
      $(s2).each(function(i,e) {
        $(e).removeAttr("checked")
        $(e).parents('div.form-item').removeClass('staygreen');
      });
    });
    $(s1+':checked').each(function(i,e){
      $(e).parents('div.form-item').addClass('staygreen');
    });
  }
  choices(s1,s2);
  choices(s2,s1);

  /*
   * Toggle resources
   */
  $('#inc_ref').change(function(){
    $('.resources').toggle();
  });


});




