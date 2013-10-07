(function(d){

  var id = 'hm-embed', a = "data-issue", l = 'http://dev.heardmentality.org', w, i;
  if ((w = document.getElementById(id)) && (i = w.getAttribute(a))) {

    // easyxdm
    var js;
    js = d.createElement('script');
    js.async = true;
    js.src = l + '/sites/all/libraries/easyxdm/easyXDM.debug.js';
    js.onreadystatechange= function () {
      if (this.readyState == 'complete') embed();
    }
    js.onload = embed;
    document.getElementsByTagName('body')[0].appendChild(js);

    // actual embed using easyxdm
    function embed() {
      new easyXDM.Socket({
        remote: l + "/embedder/" + i,
        container: w,
        onMessage: function(message, origin){
          this.container.getElementsByTagName("iframe")[0].style.height = message + "px";
        }
      });
    }
  }
}(document));


