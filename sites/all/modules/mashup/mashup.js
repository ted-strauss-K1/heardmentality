//on dom ready...

function loadWidgetMootools(pmAPIKey,pmDivId)
{
    surl="http://216.139.157.254/openwave/hm/mashup/xml/"+pmAPIKey;
	/* ajax alert */
	var req = new Request({
		method: 'post',
		url: surl,
		data: { 'id' :  pmAPIKey},
		headers: {'X-Request': 'XML'},
		onComplete: function(response) { 
			//$(pmDivId).set("html",response)
			response=ffLoadXMLBrowser(response)
			vContent=contentWidjet(response)
			$(pmDivId).set("html",vContent)
		}
	}).send();
}
function loadWidgetJquery(pmAPIKey,pmDivId)
{
surl="http://216.139.157.254/openwave/hm/mashup/xml/"+pmAPIKey;
	vParam	= 'id='+pmAPIKey;
	/* ajax alert */
	jQuery.get({
		url: surl,
		data: vParam,
		type: 'POST',
		dataType: 'xml',
		success:function( response ){
                    alert(response);
			vContent=contentWidjet(response)
			jQuery("#"+pmDivId).html(vContent)
		}
	});
}
function contentWidjet(response)
{
	oQuest=ntag( response, 'question' )
	vQuestion=vtag(oQuest[0],'value')
	vQuestColor=vtag(oQuest[0],'color')
	vQuestSize=vtag(oQuest[0],'size')
	oAns=ntag( response, 'answer' )
	aAns=vtag(oAns[0],'value').split("||");
	vAnsColor=vtag(oAns[0],'color')
	vAnsSize=vtag(oAns[0],'size')
	oWidth=ntag( response, 'width' )
	vWidth=vtag(oWidth[0],'value')
	oHeight=ntag( response, 'height' )
	vHeight=vtag(oHeight[0],'value')
	oBorder=ntag( response, 'border' )
	vBorder=vtag(oBorder[0],'value')
	
	vContent='<div style="width:'+vWidth+'px;height:'+vHeight+'px;overflow:scroll;border:1px solid #'+vBorder+';"><table><tr><td style="font:normal '+vQuestSize+'px Arial, Helvetica, sans-serif; color:#'+vQuestColor+';">'+vQuestion+'</td></tr><tr><td><table>';
				for(i=0;i<aAns.length;i++)
				{
					vContent =vContent+'<tr><td style="font:normal '+vAnsSize+'px Arial, Helvetica, sans-serif; color:#'+vAnsColor+';">'+aAns[i]+'</td></tr>';				
				}
	vContent =vContent+'</table></td></tr></table></div>';
	return vContent;
}
function ffLoadXMLBrowser(strXML) 
{ 
  if(document.implementation && document.implementation.createDocument)  
  { 
		 xmlParser = new DOMParser(); 
	   xmlDocum = xmlParser.parseFromString( strXML, 'text/xml'); 
	   xmlSerializer = new XMLSerializer(); 
	   
  } 
  else if(window.ActiveXObject) { 
	   // IE 
	   xmlDocum = new ActiveXObject("Microsoft.XMLDOM"); 
	   xmlDocum.async=false; 
	   xmlDocum.loadXML( strXML); 
  } 
  //alert(xmlDocum.xml); 
  return xmlDocum; 
}
function ntag( xml, tag )
{
	return xml.getElementsByTagName(tag);
}

function vtag( xml, tag )
{
	var node = xml.getElementsByTagName(tag);

	if( node.length > 0 && node[0].firstChild != null )
	{
		return node[0].firstChild.nodeValue;
	}
	else
		return '';
}