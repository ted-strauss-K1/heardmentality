function subtab(){
 var elOneM = $('contentone');
       var elTwoM = $('contenttwo');
       var elThreeM = $('contentthree');
    var elFourM = $('contentfour');
	  var elFiveM = $('contentfive');
	   var elsixM = $('contentsix');
	    var elseven = $('contentseven');
   var eleight = $('contenteight');
    var elnine = $('contentnine');
       //creat morph object
       elOneM = new Fx.Morph(elOneM, {
               link: 'cancel'
       });
       elTwoM = new Fx.Morph(elTwoM, {
               link: 'cancel'
       });
       elThreeM = new Fx.Morph(elThreeM, {
               link: 'cancel'
       });
	    elFourM = new Fx.Morph(elFourM, {
               link: 'cancel'
       });
		
		 elFiveM = new Fx.Morph(elFiveM, {
               link: 'cancel'
       });
		  elsixM = new Fx.Morph(elsixM, {
               link: 'cancel'
       });
		    elseven = new Fx.Morph(elseven, {
               link: 'cancel'
       });
			
			  eleight = new Fx.Morph(eleight, {
               link: 'cancel'
       });
			  
			    elnine = new Fx.Morph(elnine, {
               link: 'cancel'
       });
				
      
       $('one').addEvent('click', showFunction.bind(elOneM));
       $('two').addEvent('click', showFunction.bind(elTwoM));
       $('three').addEvent('click', showFunction.bind(elThreeM));
        $('four').addEvent('click', showFunction.bind(elFourM));
		 $('five').addEvent('click', showFunction.bind(elFiveM));
		 	 $('six').addEvent('click', showFunction.bind(elsixM));
			  $('seven').addEvent('click', showFunctionSub.bind(elseven));
			   $('eight').addEvent('click', showFunctionSub.bind(eleight));
			    $('nine').addEvent('click', showFunctionSub.bind(elnine));
		elOneM.start({
               'display': 'block',
               'opacity': 1
			   });
}

var showFunction = function() {
       
       $$('.hidden').setStyles({
               'display': 'none',
               'opacity': 0,
               'background-color': '#fff',
               'font-size': '16px'
       });
       this.start({
               'display': 'block',
               'opacity': 1
			   });
               var changeEffect = new Fx.Elements($('container'), {duration: 1000, transition: Fx.Transitions.Bounce.easeIn});
                       changeEffect.start({
                       '0': {
                                       'height': [0, 200]
                               }
               });
}
var showFunctionSub = function() {
       $$('.hiddens').setStyles({
               'display': 'none',
               'opacity': 0,
               'background-color': '#fff',
               'font-size': '16px'
       });
       this.start({
               'display': 'block',
               'opacity': 1
			   });
               var changeEffect = new Fx.Elements($('container'), {duration: 1000, transition: Fx.Transitions.Bounce.easeIn});
                       changeEffect.start({
                       '0': {
                                       'height': [0, 350]
                               }
               });
}

