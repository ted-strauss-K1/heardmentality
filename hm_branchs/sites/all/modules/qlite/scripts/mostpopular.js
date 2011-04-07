// $Id$
/**
 * @file Adds javascript actions to the most popular block.
 * 
 * @author Andrew Marcus
 * @since Dec 18, 2009
 */
if (Drupal.jsEnabled) { 
jQuery(document).ready(function(){

    // Get the configuration options
    var options = {'hideContent' : function(content) {
      content.fadeTo(200, 0.5);
    },
    'showContent' : function(content, html) {
      content.html(html).fadeTo(200, 1.0);
    },
    'showThrobber' : true,
    'blockSelector' : '.mostpopular--widget',
    'servicesSelector' : 'ul.mostpopular--services li',
    'intervalsSelector' : 'ul.mostpopular--intervals li',
    'contentSelector' : 'div.mostpopular--content',
    'selectedClass' : 'selected',
    'default_sid' : '4',
    'default_iid' :'2'
};
    
    // Keep track of the tab we're currently looking at
    var selected = {'sid' : options.sid, 'iid' : options.iid};

    // Attach to all the most popular blocks on the page
    var parent = jQuery('.mostpopular');
    parent.each(function() {
      var serviceTabs = parent.find(options.servicesSelector);
      var intervalTabs = parent.find(options.intervalsSelector);


      // Create a content container
      var content = parent.find(options.contentSelector);
      var wrapper = content.wrap("<div />").parent()
      .css({
        position : 'relative'
      });

      // Create a throbber image
     if (options.showThrobber) {
        var throbber = jQuery('.ahah-progress')
        .css({
          position : 'absolute',
          zIndex : 100
        }).appendTo(wrapper).hide();

        // Redefine the show function for the throbber to center it
        throbber.centerAndShow = function() {
          var top = parseInt((wrapper.outerHeight({margin: true}) - throbber.height()) / 2);
          var left = parseInt((wrapper.outerWidth({margin: true}) - throbber.width()) / 2);
          throbber.css({
            top : top,
            left : left
          }).show();
        };
      }

      // -----------------------------------------------------
      // Bind all the links to services
      serviceTabs.find("a").each(function() {
        var link = $(this).data('service', true);
        
        // If the service ID is not already declared, extract it from the URL.
        if (!link.attr('sid')) {
          var parts = parseLink(link.attr('href'));
          link.attr('sid', parts.sid);
        }

        // Update the selected tab
        link.bind('select', function() {
          selected.sid = link.attr('sid');
          serviceTabs.removeClass(options.selectedClass);
          link.parent().addClass(options.selectedClass);
          return false;
        });
        
        // Update the selected tab and reload the content
        link.bind('click', function() {
          link.trigger('select');
          reload();
          return false;
        });
      });

      // -----------------------------------------------------
      // Bind all the links to intervals
      intervalTabs.find("a").each(function() {
        var link = $(this).data('interval', true);
       
        // If the interval ID is not already declared, extract it from the URL.
        if (!link.attr('iid')) {
          var parts = parseLink(link.attr('href'));
          link.attr('iid', parts.iid);
        }
        
        // Update the selected tab
        link.bind('select', function() {
          selected.iid = link.attr('iid');
          intervalTabs.removeClass(options.selectedClass);
          link.parent().addClass(options.selectedClass);
          return false;
        });
        
        // Update the selected tab and reload the content
        link.bind('click', function() {
          link.trigger('select');
          reload();
          return false;
        });
      });

      // -----------------------------------------------------
      // If nothing has been selected, probably because Authcache is enabled,
      // use the cookie or defaults to select a tab and load its content.
      if (!selected.sid || !selected.iid) {
        
        // If there is a cookie already, use its values
        var cookie = $.cookie('mostpopular');
        var p = /(\d+)\/(\d+)/;
        var match = p.exec(cookie);
        if (match) {
          selected = {'sid': match[1], 'iid': match[2]};
        }
        // Otherwise, use the default values
        else {
          selected = {'sid': options.default_sid, 'iid': options.default_iid};
        }
          
        // Find the current links and select them.
        var service = serviceTabs.find('a[sid=' + selected.sid + ']');
        var interval = intervalTabs.find('a[iid=' + selected.iid + ']');
        
        // Trigger a refresh on the selected interval link.
        service.trigger('select');
        interval.trigger('click');
      }
      
      /**
       * Parses a URL to a mostpopular/items/%/% page and returns the
       * service and interval ids.
       * 
       * @return An array containing:
       *   - prefix: The site prefix (the basepath after the domain name).
       *   - sid: The service ID.
       *   - iid: The interval ID.
       */
      function parseLink(url) {
         
        var p = /(.*)\/qlite\/tophot\/(\d+)\/(\d+)/;
        var match = p.exec(url);
        
        if (match.length == 4) {
          return {
            'prefix' : match[1],
            'sid' : match[2],
            'iid' : match[3]
          };
        }
        return {};
      }

      /**
       * This function is called whenever a service or interval tab is clicked.
       * It loads the new most popular items via AJAX rather than the link's 
       * default URL.
       */
      function reload() {
        startReload();
         
        // Construct the appropriate URL to use
        var url = Drupal.settings.basePath + 
          "qlite/tophot/" + selected.sid + "/" + selected.iid;

        // Fetch the content via AJAX
        $.get(url, function(data) {
          var response = Drupal.parseJson(data);
          finishReload(response);
          return false;
        });
        return false;
      }

      /**
       * Starts the process of reloading the most popular items, by hiding
       * the existing content and showing the throbber, if necessary.
       * 
       * The hideContent() method defined in the options will be called.
       */
      function startReload() {
        // Show the throbber and dim the content
        if (throbber) {
          throbber.centerAndShow();
        }
        options.hideContent(content);
      }

      /**
       * Finishes the process of reloading the most popular items, by showing
       * the new content and hiding the throbber, if necessary.
       * 
       * The showContent() method defined in the options will be called.
       * 
       * @param response
       *   A JSON response from Drupal.  It contains one key, 'data', whose
       *   value is an HTML string to render.
       */
      function finishReload(response) {
        // Replace the content, fade it back in and hide the throbber
        options.showContent(content, response.data);
        if (throbber) {
          throbber.hide();
        }
  jQuery('.mostpopular--content li a').each(function()
                        {
                            if( jQuery(this).attr("title").length>0){
                          
                                jQuery(this).SetBubblePopup({
                                    innerHtml: jQuery(this).attr("title"),
                                    color:'grey',
                                    imageFolder: '/heardmentality/sites/all/themes/newtheme/images/bp_images'

                                });
                            }
                        });
      }
    });
  });

  /**
   * Defines the default options. Override these options in
   * Drupal.settings.mostpopular.
   */
  

  /**
   * Provides a default theme for the throbber that appears when content is
   * reloading.   You can override this in your own theme.
   * 
   * @return An HTML string to render the throbber.
   */
 
}