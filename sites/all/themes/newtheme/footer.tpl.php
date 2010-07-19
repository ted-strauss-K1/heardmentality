  </div>
  </div>
  <div class="clr"></div>
  <div class="bott"></div>
  <div id="footer"><div class="footerleft">Copyright <a href="http://creativecommons.org/licenses/by-sa/2.5/" title="creativecommons"><img border="0" alt="cc" src="<?php echo $directory;?>/images/cc.jpg"/></a> 2010 Heardmentality.org </div>
  <div class="footerright">  <?php   $mbl=4;$min=0; foreach ($secondary_links as $linksm): $min++;?>
         <a href="<?php print($gSitePath.$linksm['href']);?>" <?php if($linksm['title'] == 'Contact Us'||($linksm['title'] == 'Privacy & Policy')||($linksm['title'] == 'User Agreement')):?> rel="width:850,height:570" class="advanced<?php echo $mbl++; ?>" title="<?php print($linksm['title']);?>"<?php endif;?>><?php print($linksm['title']);?></a><?php if((count($secondary_links))>=$min){ echo " - ";}$min++;?> 
          <?php endforeach; ?>
          <a href="http://www.opensource.org/" title="opensource"><img border="0" alt="opensource" src="<?php echo $directory;?>/images/icon1.png"/></a><a href="http://drupal.org/" title="drupal"><img border="0" alt="drupal" src="<?php echo $directory;?>/images/icon2.png"/></a><a href="http://www.govtrack.us/" title="govtrack"><img border="0" alt="govtrack" src="<?php echo $directory;?>/images/icon3.png"/></a></div>
  </div>
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
    }
  });
  
   
});

</script>

</body>
</html>
