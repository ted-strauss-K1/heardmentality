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
  <?php   $mbl=4;$min=0;
            foreach ($secondary_links as $linksm): $min++;?>
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
  <div class="fbWrapper" style="display: none; visibility: visible;"><select onchange="fb.translate(fb.fbContent, this.options[this.selectedIndex].value)" style="display: block;" class="jq-translate-ui" id="boxSelect"><option value="">Translate to...</option><option value="af">Afrikaans</option><option value="sq">Albanian</option><option value="ar">Arabic</option><option value="be">Belarusian</option><option value="bg">Bulgarian</option><option value="ca">Catalan</option><option value="zh-CN">Chinese (Simplified)</option><option value="zh-TW">Chinese (Traditional)</option><option value="hr">Croatian</option><option value="cs">Czech</option><option value="da">Danish</option><option value="nl">Dutch</option><option value="en">English</option><option value="et">Estonian</option><option value="tl">Filipino</option><option value="fi">Finnish</option><option value="fr">French</option><option value="gl">Galician</option><option value="de">German</option><option value="el">Greek</option><option value="iw">Hebrew</option><option value="hi">Hindi</option><option value="hu">Hungarian</option><option value="is">Icelandic</option><option value="id">Indonesian</option><option value="ga">Irish</option><option value="it">Italian</option><option value="ja">Japanese</option><option value="ko">Korean</option><option value="lv">Latvian</option><option value="lt">Lithuanian</option><option value="mk">Macedonian</option><option value="ms">Malay</option><option value="mt">Maltese</option><option value="no">Norwegian</option><option value="fa">Persian</option><option value="pl">Polish</option><option value="pt">Portuguese</option><option value="ro">Romanian</option><option value="ru">Russian</option><option value="sr">Serbian</option><option value="sk">Slovak</option><option value="sl">Slovenian</option><option value="es">Spanish</option><option value="sw">Swahili</option><option value="sv">Swedish</option><option value="th">Thai</option><option value="tr">Turkish</option><option value="uk">Ukrainian</option><option value="vi">Vietnamese</option><option value="cy">Welsh</option><option value="yi">Yiddish</option></select></div>
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
<?php print $closure; ?>
</body>
</html>
