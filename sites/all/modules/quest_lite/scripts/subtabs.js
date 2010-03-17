function subtab(){
 var elOneM = $('contentone');
       var elTwoM = $('contenttwo');
       var elThreeM = $('contentthree');
    var elFourM = $('contentfour');
	  var elFiveM = $('contentfive');
	   var elsixM = $('contentsix');

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
      
       $('one').addEvent('click', showFunction.bind(elOneM));
       $('two').addEvent('click', showFunction.bind(elTwoM));
       $('three').addEvent('click', showFunction.bind(elThreeM));
        $('four').addEvent('click', showFunction.bind(elFourM));
		 $('five').addEvent('click', showFunction.bind(elFiveM));
		 	 $('six').addEvent('click', showFunction.bind(elsixM));
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
                                       'height': [0, 100]
                               }
               });
}

