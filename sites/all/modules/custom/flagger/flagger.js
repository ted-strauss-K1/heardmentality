function flagger_exec(flagger) {
    var url = Drupal.settings.base_url + '/flagger/' + flagger.attr('name')
    $.ajax({
        type: "POST",
        dataType: 'json',
        url: url,
        data: {},
        success: function(response){
            $.hrd.noty({
                'layout' : 'center',
                'type'   : 'alert',
                'text'   : response.text,
                'modal'  : true,
                'timeout': false,
                'buttons': [
                    {
                        addClass : 'btn btn-primary',
                        text     : 'Flag!',
                        onClick  : function($noty) {
                            $('#flagger-form').submit();
                            $noty.close();
                            $.hrd.noty({
                                'layout' : 'center',
                                'type'   : 'success',
                                'text'   : 'Thank you for helping us keep this place in order',
                                'modal'  : true
                            });
                        }
                    },
                    {
                        addClass: 'btn btn-danger',
                        text: 'Cancel',
                        onClick: function($noty) {
                            $noty.close();
                        }
                    }
                ]
            });
            $('#flagger-form').ajaxForm({
                // target: '#output'
            });
        }
    });
}


$(document).ready(function() {
  $('.flagger').live('click',function(e) {
    e.preventDefault();
    var flagger = $(this);
    flagger_exec(flagger);
    return false;
  });
});
