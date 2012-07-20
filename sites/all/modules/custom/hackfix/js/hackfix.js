Drupal.hackfix = {
  'field': ' field is required.',
  'term': 'You must agree with the Terms of use and Privacy Policy to get an account.'
}

Drupal.behaviors.hackfix = function (context) {
  // ajax validating of login form
  $('form#user-login', context).submit(function() {
    var credentials = {
          'name': {
            'title': 'E-mail' + Drupal.hackfix.field,
            'field': $('#edit-name', this)
          },
          'pass': {
            'title': 'Password' + Drupal.hackfix.field,
            'field': $('#edit-pass', this)
          }
        };

    var status = checkInputValues(credentials);
    if (status.hasError) {
      setErrors(this, status.errors);
    } else {
      // do ajax validation of credentials
      var data = {},
          url = Drupal.settings.basePath + 'login/validate/ajax';
      for (var i in credentials) {
        data[i] = credentials[i].field.val();
      }
      var $form = $(this);
      $form.throbberStart();
      $.ajax({
        type: "POST",
        url: url,
        data: data,
        dataType: 'json',
        success: function(response) {
          if (response.hasError) {
            setErrors($form, response.errors);
            $form.throbberStop();
          } else {
            window.location.href = Drupal.settings.basePath;
          }
        }
      });
    }
    
    return false;
  });

  // ajax validating of registration form
  $('form#user-register', context).submit(function() {
    var inputs = {
          'mail': {
            'title': 'E-mail' + Drupal.hackfix.field,
            'field': $('#edit-mail', this)
          },
          'pass1': {
            'title': 'Password' + Drupal.hackfix.field,
            'field': $('#edit-pass-pass1', this)
          },
          'pass2': {
            'title': 'Confirmation' + Drupal.hackfix.field,
            'field': $('#edit-pass-pass2', this)
          }
        };
    var status = checkInputValues(inputs);

    var $term = $('#edit-terms', this);
    if (!$term.is(':checked')) {
      status.errors['term'] = Drupal.hackfix.term;
      status.hasError = true;
    }

    if (status.hasError) {
      setErrors(this, status.errors);
      return false;
    }
    return true;
  });

  /**
   * Set errors messages to given form
   */
  function setErrors(form, errors) {
    var $messages = $('div.messages.error', form);
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

  /**
   * Check input values to be not empty
   */
  function checkInputValues(inputs) {
    var errors = {},
        hasError = false;

    for (var i in inputs) {
      if (inputs[i].field.val() == '') {
        inputs[i].field.addClass('error');
        errors[i] = inputs[i].title;
        hasError = true;
      } else {
        inputs[i].field.removeClass('error');
      }
    }

    return {
      hasError: hasError,
      errors: errors
    };
  }
}