


window.addEvent('domready',function()
{
       var selObj = $('rtype');
       var vDiv1 = new Fx.Slide('div1').hide()
       var vDiv2 = new Fx.Slide('div2').hide()
       var vDiv3 = new Fx.Slide('div3').hide()
       selObj.addEvent('change',function(e)
       {
               var vDiv1 = new Fx.Slide('div1').hide()
               var vDiv2 = new Fx.Slide('div2').hide()
               var vDiv3 = new Fx.Slide('div3').hide()
			     var medDiv1 = new Fx.Slide('media').hide()
               var medDiv2 = new Fx.Slide('media_div').hide()
               var selIndex = selObj.selectedIndex;
               var value = selObj.options[selIndex].value
               e = new Event(e);
               if(value==1)
               {
                       vDiv1.toggle();
					   
               }
               if(value==2)
               {
                       vDiv2.toggle();
					   
               }  
               if(value==3)
               {
                       vDiv3.toggle();
               }                
               e.stop();
       });
	   
	  var selObjmed = $('mtype');
		 var medDiv1 = new Fx.Slide('media').hide()
               var medDiv2 = new Fx.Slide('media_div').hide()
     
		 selObjmed.addEvent('change',function(emed)
       {
               var medDiv1 = new Fx.Slide('media').hide()
               var medDiv2 = new Fx.Slide('media_div').hide()
              
               var selIndexmedia = selObjmed.selectedIndex;
               var valuemed = selObjmed.options[selIndexmedia].value
               emed = new Event(emed);
			  // alert(valuemed);
               if(valuemed==1)
               {
                       medDiv1.toggle();
               }
               if(valuemed==2)
               {
                       medDiv2.toggle();
               }  
                     
               emed.stop();
       });


var formvalid = $('myForm');
    
       formvalid.addEvent('submit',function()
       {


             
             
			   
       });






	   
	   
});




  
