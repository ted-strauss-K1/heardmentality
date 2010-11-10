
 //  var jQuery= jQuery.noConflict();


jQuery(document).ready(function(){
		
	// first example
	
	jQuery("#navigation").treeview({
		animated: "slow",
		collapsed: true,
		unique: true,
		persist: "cookie",
		toggle: function() {
			window.console && console.log("%o was toggled", this);
		}
	});

	

});

function loadAddCategory(pmUrl){
	alert('sss');
MochaUI.slideshareWindow = function(){
new MochaUI.Window({
id: 'slideshare',
title: 'Add Category',
loadMethod: 'iframe',
contentURL: pmUrl,
width: 415,
height: 355,
resizeLimit: {'x': [330, 2500], 'y': [250, 2000]},
contentBgColor: '#000'
});
}
}

