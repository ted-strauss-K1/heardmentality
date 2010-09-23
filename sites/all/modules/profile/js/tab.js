function loadtab(url,title)
{
	

	//jQuery.nyroModalSettings({ title:'Add Resources'});

	//jQuery.nyroModalManual({
  //  url: url,width:550,height:450,title:'Add Resources'
 // });
 var options = 'sameBox:true width:50% height:70% caption:' +title;
  parent.fb.start(url, options);
		
}