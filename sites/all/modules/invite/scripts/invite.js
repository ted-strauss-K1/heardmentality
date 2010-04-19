

  
  
  
  
  function addJavascript(jsname,pos) {
var th = document.getElementsByTagName(pos)[0];
var s = document.createElement('script');
s.setAttribute('type','text/javascript');
s.setAttribute('src',jsname);
th.appendChild(s);
} 


addJavascript('http://www.plaxo.com/css/m/js/util.js','head'); 
addJavascript('http://www.plaxo.com/css/m/js/basic.js','head'); 
addJavascript('http://www.plaxo.com/css/m/js/abc_launcher.js','head'); 