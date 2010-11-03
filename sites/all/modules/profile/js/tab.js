function loadtab(url,title)
{
	

	//jQuery.nyroModalSettings({ title:'Add Resources'});

	//jQuery.nyroModalManual({
  //  url: url,width:550,height:450,title:'Add Resources'
 // });
 var options = 'sameBox:true width:50% height:70% caption:' +'`'+title+'`';
  parent.fb.start(url, options);
		
}

jQuery(document).ready(function(){
	 $('.fa-item a').click(function() {
        //$('#box1').css("background","#9f9");
        $(".fa-item a").css('color', '#996600');
        $(this).css('color', '#4170A0');

        });
        });