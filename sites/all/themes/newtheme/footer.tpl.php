  </div>
  </div>
  <div class="clr"></div>
  <div class="bott"></div>
  <div class="footer">
  <div class="copy"> <a href="http://creativecommons.org/licenses/by-sa/2.5/" title="creativecommons">
  <img border="0" alt="cc" align="absmiddle"  hspace="2" src="<?php echo $directory;?>/images/cc.png"/></a> &nbsp; 2010 Heardmentality.org
   </div>
 <div class="menu">
  <ul>
  <?php   $mbl=4;$min=0; foreach ($secondary_links as $linksm): $min++;?>
         <li class="listnone"><a href="<?php print($gSitePath.$linksm['href']);?>" <?php if($linksm['title'] == 'Contact Us'||($linksm['title'] == 'Privacy & Policy')||($linksm['title'] == 'User Agreement')):?> rel="width:850,height:570" class="advanced<?php echo $mbl++; ?>" title="<?php print($linksm['title']);?>"<?php endif;?>><?php print($linksm['title']);?></a></li><?php $min++;?> 
          <?php endforeach; ?>
          </ul>
               </div>
       <!--    <div class="footer-icon-outer">
          <a href="http://www.opensource.org/" title="opensource"><img border="0" alt="opensource" src="<?php echo $directory;?>/images/icon1.png"/></a>
          <a href="http://drupal.org/" title="drupal"><img border="0" alt="drupal" src="<?php echo $directory;?>/images/icon2.png"/></a>
          <a href="http://www.govtrack.us/" title="govtrack"><img border="0" alt="govtrack" src="<?php echo $directory;?>/images/icon3.png"/></a>
     
          </div> -->
  </div>
<!--main div close-->

<script type="text/javascript">
jQuery(function() {
  function preloadImg(image) {
    var img = new Image();
    img.src = image;
  }

  preloadImg('<?php echo $directory;?>/img/ajaxLoader.gif');
  preloadImg('<?php echo $directory;?>/img/prev.gif');
  preloadImg('<?php echo $directory;?>/img/next.gif');
});


function translateTo( destLang ){ 

  jQuery('body').translate(
      'english', 
      destLang, 
      {not: '#menu, pre, .jq-translate-ui', fromOriginal:true,
	  start:        function(){jQuery('#loading').fadeIn();},
      complete:     function(){jQuery('#loading').fadeOut();}
  
	  }
      )
	jQuery(".jq-translate-ui").val(destLang).attr("selected", "selected");
  jQuery(".jq-translate-ui option:contains("+destLang+")").val();
jQuery(".jq-translate-ui option[text=" + destLang +"]").attr("selected","selected") ;

}

jQuery(document).ready(function(){

  /*--- snip ---*/

  //when the Google Language API is loaded
  jQuery.translate(function(){ 
    // clear the loading gif
    jQuery('#lang').empty();
    //generate dropdown
    jQuery.translate.ui('select', 'option') 
    // when selecting another language
    .change(function(){
      var lang =jQuery(this).val();
      translateTo(lang);
      jQuery.cookie('destLang', lang, {path:'/'});
      })
    .val('English') //select English as default
    .appendTo('#lang'); //insert the dropdown to the page

    //insert Google's logo after the dropdown:
//jQuery.translate.getBranding().appendTo(jQuery('#lang'));

    //get previously translated language      
    var destLang = jQuery.cookie('destLang'); 
    if (destLang && destLang != 'English') {
    jQuery('.jq-translate-ui').val(destLang);
    translateTo( destLang );
    }else{
       jQuery('.jq-translate-ui').val('en');
    }
  });
  
   
});

</script>
     <!-- Tour created with Amberjack wizard: http://amberjack.org -->
<!-- Tour created with Amberjack wizard: http://amberjack.org -->
<div class="ajTourDef" id="MyTour" style="display:none"
 title="http://216.139.157.254/openwave/hm/tour/home/donate">
  <div title="http://216.139.157.254/openwave/hm/tour/home/home">
    Login with any of your favourite social network
  </div>
  <div title="http://216.139.157.254/openwave/hm/tour/home/question">
     Post your day by day issues
  </div>
  <div title="http://216.139.157.254/openwave/hm/tour/home/donate">
     Make a donate
  </div>
  <div title="http://216.139.157.254/openwave/hm/"></div>
</div>

<script type="text/javascript" src="http://amberjack.org/src/stable/amberjack.pack.js">
</script>

<script type="text/javascript" defer="true">
  Amberjack.open();
</script>
                    <!-- Tour created with Amberjack wizard: http://amberjack.org -->
</body>
</html>
