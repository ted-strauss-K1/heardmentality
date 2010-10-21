function mycarousel_initCallback(carousel) {
    /*  jQuery('.jcarousel-control a').bind('click', function() {
        carousel.scroll(jQuery.jcarousel.intval(jQuery(this).text()));
        return false;
    });

    jQuery('.jcarousel-scroll select').bind('change', function() {
        carousel.options.scroll = jQuery.jcarousel.intval(this.options[this.selectedIndex].value);
        return false;
    });
*/
    jQuery('#mycarousel-next').bind('click', function() {
        carousel.next();
        return false;
    });

    jQuery('#mycarousel-prev').bind('click', function() {
        carousel.prev();
        return false;
    });
};

// Ride the carousel...
/*
jQuery(document).ready(function() {
    jQuery("#mycarousel").jcarousel({
        scroll: 5,
        initCallback: mycarousel_initCallback,
        // This tells jCarousel NOT to autobuild prev/next buttons
        buttonNextHTML: null,
        buttonPrevHTML: null
    });
});
*/

function mycarousel_itemLoadCallback(carousel, state)
{
    // Check if the requested items already exist
    if (carousel.has(carousel.first, carousel.last)) {
        return;
    }
    var url=gSitePath+'pundit/ajax';
    jQuery.getJSON(
        url,
        {
            first: carousel.first,
            last: carousel.last
        },
        function(xml) {
            // mycarousel_itemAddCallback(carousel, carousel.first, carousel.last, xml);
            var mycarousel_itemList = xml;

            for (var i = carousel.first; i <= carousel.last; i++) {
                
                if (carousel.has(i)) {alert('ss'+i);
                    continue;
                }

                if (i > mycarousel_itemList.length) {
                    alert(i);
                   break;
                }
            
                // Create an object from HTML
              var item = jQuery(mycarousel_getItemHTML(mycarousel_itemList[i-1])).get(0);
              //var item=mycarousel_getItemHTML(mycarousel_itemList[i-1]);
                // Apply thickbox
                // tb_init(item);

                carousel.add(i, item);
            }


        }
        );



};


function mycarousel_getItemHTML(item)
{
    // var url_m = item.url.replace(/_s.jpg/g, '_m.jpg');
    //var html=item.rel.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
    var html='';
    return '<a  href="' + item.url + '" title="' + item.title + '">'+item.image+'</a>';
};


jQuery(document).ready(function() {
    jQuery('#mycarousel').jcarousel({
        initCallback: mycarousel_initCallback,
       // Uncomment the following option if you want items
        // which are outside the visible range to be removed
        // from the DOM.
        // Useful for carousels with MANY items.

        // itemVisibleOutCallback: {onAfterAnimation: function(carousel, item, i, state, evt) { carousel.remove(i); }},
        itemLoadCallback: mycarousel_itemLoadCallback
    });
});
