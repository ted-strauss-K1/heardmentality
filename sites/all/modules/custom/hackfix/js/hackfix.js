Drupal.hackfix = {
  'field': ' field is required.',
  'term': 'You must agree with the Terms of use and Privacy Policy to get an account.'
}

Drupal.behaviors.hackfix = function (context) {
  $('form#user-register').submit(function () {
    var errors = {},
        hasError = false;

    // @TODO: replace this by smth beautiful
    if ($('#edit-mail', this).val() == '') {
      $('#edit-mail', this).addClass('error');
      errors['mail'] = 'E-Mail' + Drupal.hackfix.field;
      hasError = true;
    } else {
      $('#edit-mail', this).removeClass('error');
    }

    if ($('#edit-pass-pass1', this).val() == '') {
      $('#edit-pass-pass1', this).addClass('error');
      errors['pass1'] = 'Password' + Drupal.hackfix.field;
      hasError = true;
    } else {
      $('#edit-pass-pass1', this).removeClass('error');
    }

    if ($('#edit-pass-pass2', this).val() == '') {
      $('#edit-pass-pass2', this).addClass('error');
      errors['pass2'] = 'Confirmation' + Drupal.hackfix.field;
      hasError = true;
    } else {
      $('#edit-pass-pass2', this).removeClass('error');
    }

    var $term = $('#edit-terms', this);
    if (!$term.is(':checked')) {
      errors['term'] = Drupal.hackfix.term;
      hasError = true;
    }

    if (hasError) {
      setErrors(this, errors);
      return false;
    }
  });

  function setErrors(form, errors) {
    var $messages = $('div.messages.error');
    if ($messages) {
      $messages.remove();
    }
    
    $messages = $('<div></div>')
                  .addClass('messages')
                  .addClass('error');
    var $ul = $('<ul></ul>');
    for (var i in errors) {
      $('<li></li>').html(errors[i]).appendTo($ul);
    }
    $messages.append($ul);
    $(form).prepend($messages);
  }
}