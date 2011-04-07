IsIE = (document.all && navigator.userAgent.search(/MSIE/i) != -1)|| false;

function getPageSize ()

{

	var vXscroll,vYscroll;

	if(window.innerHeight && window.scrollMaxY)

	{

		vXscroll = document.body.scrollWidth;

		vYscroll = window.innerHeight + window.scrollMaxY;

	}

	else if(document.body.scrollHeight > document.body.offsetHeight)

	{

		vXscroll = document.body.scrollWidth;

		vYscroll = document.body.scrollHeight;

	}

	else

	{

		vXscroll = document.body.offsetWidth;

		vYscroll = document.body.offsetHeight;

	}

	

	var vWindowWidth,vWindowHeight;

	if(self.innerHeight)

	{

		vWindowWidth = self.innerWidth;

		vWindowHeight = self.innerHeight;

	}

	else if(document.documentElement && document.documentElement.clientHeight)

	{

		vWindowWidth  = document.documentElement.clientWidth;

		vWindowHeight = document.documentElement.clientHeight;

	}

	else if(document.body)

	{

		vWindowWidth  = document.body.clientWidth;

		vWindowHeight = document.body.clientHeight;

	}

	var vPageHeight,vPageWidth;

	

	if(vYscroll < vWindowHeight) vPageHeight = vWindowHeight;

	else vPageHeight = vYscroll;

	

	if(vXscroll < vWindowWidth) vPageWidth = vWindowWidth;

	else vPageWidth = vXscroll;

	return {vPageWidth:vPageWidth, vPageHeight:vPageHeight, vWindowWidth:vWindowWidth, vWindowHeight:vWindowHeight};

}

function loadPopupWindow(pmTitle,pmHeight,pmWidth,vSrc)

{

	vWidth=pmWidth.split("px");

	vheight=pmHeight.split("px");

		vW=vWidth[0]-10

		vH=vheight[0]-30

	vBackground = document.createElement('div');

	vBackground.id ='divParentPSO'

	vPageSize = getPageSize();

	vWdt=vPageSize.vPageWidth+35

	//vBackground.style.width 	= vWdt+"px"; 
    vBackground.style.width ="100%";

	vBackground.style.height 	= vPageSize.vPageHeight+"px"; 

	vBackground.style.left 	= "0px"; 

	vBackground.style.top 	= "0px"; 	

	vBackground.style.position 	= "absolute"; 	

	vBackground.style.opacity 	= ".5"; 	

	vBackground.style.backgroundColor 	= "#000000"; 	

	vBackground.style.filter 	= "alpha(opacity=50)"; 

	//vBackground.className 	= "popupBackgroundSafariIframe";

	

	vPosx	= (vPageSize.vWindowWidth/2)-(vWidth[0]/2)

	vPosy	= (vPageSize.vWindowHeight/2)-(vheight[0]/2)

	vPosx 	= vPosx+'px'; 

	vPosy 	= vPosy+'px';



	vPanel = document.createElement('div');

	vPanel.id ='divPanel'

	vPanel.style.width 	= pmWidth; 

	vPanel.style.height = pmHeight; 

	vPanel.style.left 	= vPosx; 

	vPanel.style.top 	= vPosy;

	vPanel.style.position='absolute'

	

	vPanel.innerHTML	= '<div class="mybgcolor" id="divPopupdiv" style="height:pmHeight; width:pmWidth; top:vPosy; left:vPosx; position:fixed;" align="center">'+getPopupWindowHeader( vWidth[0],vheight[0],pmTitle )+'<div id="loadIframe" align="center" ><iframe src="'+vSrc+'" frameborder="0" height="'+vH+'" width="'+vW+'"></iframe></div>'+getPopupWindowBottom()+'</div>'

	hideallTags()

	document.body.appendChild(vBackground);

	setTimeout(function (){document.body.appendChild(vPanel)},1000);

}

function closePopupWindow()

{

	if(document.getElementById('divPanel'))

	{

		document.body.removeChild(document.getElementById('divPanel'));

	}

	if(document.getElementById('divParentPSO'))

	{

		document.body.removeChild(document.getElementById('divParentPSO'));

	}

	showAllTages();

}

function getPopupWindowHeader( pmWidth,pmHeight,pmTitle ){

	var aHtml = [];

	aHtml.push('<table width="'+pmWidth+'" height="'+pmHeight+'" border="0" cellspacing="0" cellpadding="0" >');

	aHtml.push('<tr>')

	aHtml.push('<td align="left" valign="top" style="background-color:#000;"><table width="100%" border="0" cellspacing="0" cellpadding="0">')

	aHtml.push('<tr>')

	aHtml.push('<td align="left" valign="top" height="25"></td>')

	aHtml.push('<td width="100%" align="left" valign="middle" ><table width="100%" border="0" cellspacing="0" cellpadding="0">')

	aHtml.push('<tr>')

	aHtml.push('<td width="4%">&nbsp;</td>')

	aHtml.push('<td width="87%" align="left" style="font-family: Arial, Helvetica, sans-serif;font-size: 12px;font-weight: bold;color: #fff;">'+pmTitle+'</td>')

	aHtml.push('<td width="7%" align="right" valign="middle"><a href="javascript:void(0)" onClick="closePopupWindow()">X</a></td>')

	aHtml.push('</tr>')

	aHtml.push('</table></td>')

	aHtml.push('<td align="left" valign="top"></td>')

	aHtml.push('</tr>')

	aHtml.push('<tr>')

	aHtml.push('<td align="left" valign="top" style="background-color:#000;" >&nbsp;</td>')

	aHtml.push('<td align="left" height="100%" valign="top" style="background-color: #FFFFFF;">')

	return aHtml.join('');

}

function getPopupWindowBottom(){

	var aHtml = [];

	aHtml.push('</td>')

	aHtml.push('<td align="left" valign="top" style="background-color:#000;" >&nbsp;</td>')

	aHtml.push('</tr>')

	aHtml.push('<tr>')

	aHtml.push('<td align="left" valign="top" height="5"></td>')

	aHtml.push('<td align="left" valign="top" >&nbsp;</td>')

	aHtml.push('<td align="left" valign="top" height="5"></td>')

	aHtml.push('</tr>')

	aHtml.push('</table></td>')

	aHtml.push('</tr>')

	aHtml.push('</table>')

	return aHtml.join('');

}

function hideallTags()

{

	aDiv=document.getElementsByTagName('div')

	for(i=0;i<aDiv.length;i++)

	{

		if(aDiv[i].id=='orderbutt')

			aDiv[i].style.display='none';

	}

	aSelect=document.getElementsByTagName('select')

	for(i=0;i<aSelect.length;i++)

	{

			aSelect[i].style.visibility='hidden';

	}

}

function showAllTages()

{

	aDiv=document.getElementsByTagName('div')

	for(i=0;i<aDiv.length;i++)

	{

		if(aDiv[i].id=='orderbutt')

			aDiv[i].style.display='block';

	}

	aSelect=document.getElementsByTagName('select')

	for(i=0;i<aSelect.length;i++)

	{

		aSelect[i].style.visibility='visible';

	}

}

