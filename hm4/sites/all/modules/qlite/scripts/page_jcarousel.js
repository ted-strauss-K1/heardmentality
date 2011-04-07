function mycarousel_initCallback(carousel) {
   jQuery('.jcarousel-control a').bind('click', function() {
        carousel.scroll(jQuery.jcarousel.intval(jQuery(this).attr('name')));
        return false;
    });

    jQuery('.jcarousel-scroll select').bind('change', function() {
        carousel.options.scroll = jQuery.jcarousel.intval(this.options[this.selectedIndex].value);
        return false;
    });

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
if (carousel.prevFirst != null) {
        // Remove the last visible items to keep the list small
        for (var i = carousel.prevFirst; i <= carousel.prevLast; i++) {
            // jCarousel takes care not to remove visible items
            carousel.remove(i);
        }
    }


    var per_page = carousel.last - carousel.first + 1;
    var currPage = 0;
    var f,l;
    var cr = carousel;

    for (var i = carousel.first; i <= carousel.last; i++) {
        var page = Math.ceil(i / per_page);

        if (currPage != page) {
            currPage = page;

            f = ((page - 1) * per_page) + 1;
            l = f + per_page - 1;

            f = f < carousel.first ? carousel.first : f;
            l = l > carousel.last ? carousel.last : l;

            if (carousel.has(f, l)) {
                continue;
            }
        } }

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
  carousel.unlock();
  carousel.size(mycarousel_itemList[0].total);

 var per_page = carousel.last - carousel.first + 1;
            for (var i = carousel.first; i <= carousel.last; i++) {
                          
             var pos = i - 1;
        var idx = Math.round(((pos / per_page) - Math.floor(pos / per_page)) * per_page);
        if (i>carousel.size()) {
        break;
    }
                      // Create an object from HTML
              var item = jQuery(mycarousel_getItemHTML(mycarousel_itemList[idx])).get(0);
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
     if(item){
      var html='';
    return '<a  href="' + item.url + '" title="' + item.title + '">'+item.image+'</a>';
     }else{
         return '';
     }
   
};


jQuery(document).ready(function() {
    jQuery('#mycarousel').jcarousel({
        initCallback: mycarousel_initCallback,
      visible: 4,
       itemLastInCallback:   mycarousel_itemLastInCallback,
         buttonNextCallback:   mycarousel_buttonNextCallback,
        buttonPrevCallback:   mycarousel_buttonPrevCallback,
       // Uncomment the following option if you want items
        // which are outside the visible range to be removed
        // from the DOM.
        // Useful for carousels with MANY items.

        // itemVisibleOutCallback: {onAfterAnimation: function(carousel, item, i, state, evt) { carousel.remove(i); }},
        itemLoadCallback: mycarousel_itemLoadCallback
    });
});


// it will append class="selected" into <a>
// <a href="#">1</a> to <a href="#" class="selected">1</a>
function highlight(carousel, obejctli,liindex,listate){
 ii++;
};
// it will remove last selected slide from <a>
// <a href="#" class="selected">1</a> to <a href="#">1</a>
function removehighlight(carousel, obejctli,liindex,listate){
   
     jQuery('.jcarousel-control a:nth-child('+ liindex +')').removeAttr("class","selected");
};

function mycarousel_itemLastInCallback(carousel, item, idx, state) {
jQuery(".jcarousel-control a[class*='reputation-score']").removeAttr("class");
jQuery(".jcarousel-control a[name*='"+idx+"']").prev().attr("class","reputation-score");

};


function mycarousel_buttonNextCallback(carousel, button, enabled) {
    if(enabled){

        jQuery('#mycarousel-next').show();
    }else{
         jQuery('#mycarousel-next').hide();
    }
};

/**
 * This is the callback function which receives notification
 * about the state of the prev button.
 */
function mycarousel_buttonPrevCallback(carousel, button, enabled) {
    if(enabled){

        jQuery('#mycarousel-prev').show();
    }else{
         jQuery('#mycarousel-prev').hide();
    }
};