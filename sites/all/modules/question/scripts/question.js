// JavaScript Document
jQuery(document).ready( function() {
    jQuery('#q_cat').multiSelect();
    setDefaultCountry(cncode);
    get_state(cncode);
                get_city(setstate);
});
/*
		(function($) {
  $(document).ready(function() {
    $(\'input.tagging-widget-input\').tagging();
  });
})(jQuery);
*/
//	window.setTimeout("setDefaultCountry()", 1000);
/*	jQuery(function() {
		jQuery("#q_edate").datepicker({
			changeMonth: true,
			changeYear: true,minDate: \'1d\', dateFormat: \'yy-mm-dd\'
		});


	});*/

function setDefaultCountry(cn) {
    if(cn.length>0){

        var countrySelect = document.getElementById("q_country");

        for (i=0;i< countrySelect.length;i++) {
            // the javascript geonamesData.js contains the countrycode
            // of the userIp in the variable \'geonamesUserIpCountryCode\'
            if (countrySelect[i].value == cn) {
                // set the country selectionfield
                countrySelect.selectedIndex = i;
                
            }
        }



        var stateSelect = document.getElementById("q_state");
        for (i=0;i< stateSelect.length;i++) {
            if (stateSelect[i].value == ustate) {
               
                // set the country selectionfield
                stateSelect.selectedIndex = i;
                get_city(setstate);

            }
        }



    }
}



function get_state(code){
    var url = spath+"question/ajax";
 
    jQuery.ajax({
        type: "GET",
        url: url,
        data: {
            'action': 1,
            'code' :code,
             'select':1
        },
        success: function(msg){
            jQuery('#chg_state').html(msg);
            
            if(setstate.length>1){
             
          //jQuery("#q_state option").each(function(){jQuery(this).text(escape(jQuery(this).text()));});
                    //jQuery("#q_state option:contains('tamil nadu')").attr("selected","selected") ;
                        //jQuery(this).text().toLowerCase()
            }
        }
    });



    jQuery('#chg_city').html('');
    jQuery('#chg_city').fadeOut('slow');
}
function get_city(code){
    jQuery('#chg_city').fadeIn('slow');
    var url = spath+"question/ajax";

    jQuery.ajax({
        type: "GET",
        url: url,
        data: {
            'action': 2,
            'code' :code,
            'select':1
        },
        success: function(msg){
            jQuery('#chg_city').html(msg);
        }
    });

}

jQuery("input[name='q_cat[]']").live("change", function(event) {

    var values = new Array();
    jQuery.each(jQuery("input[name='q_cat[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');

    get_subcat('q_cat','chg_scat',1,ids);
});

jQuery("input[name='q_scat[]']").live("change", function(event) {

    var values = new Array();
    jQuery.each(jQuery("input[name='q_scat[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');

    get_subcat('q_scat','chg_sscat',2,ids);
});


function get_subcat(sid,divid,level,ids){

   

    if(level==1){
        jQuery('#cat1').val(ids);
        jQuery('#chg_sscat').fadeOut('slow');
    }

    if(level==2){

        jQuery('#cat2').val(ids);
        jQuery('#chg_sscat').fadeIn('slow');
    }
    if(level==3)
        jQuery('#cat3').val(ids);

    if(ids.length>0){

        if(level<3){

            var url = spath+"question/ajax";

            jQuery.ajax({
                type: "POST",
                url: url,
                data: {
                    'action': level,
                    'ids' :ids
                },
                success: function(msg){
                    jQuery('#'+divid).html(msg);
                    if(sid=='q_cat')
                        window.setTimeout("jQuery('#q_scat').multiSelect()", 500);
                    else if(sid=='q_scat')
                        window.setTimeout("jQuery('#q_sscat').multiSelect()", 500);
                // jQuery('#'+divid+'input:select').multiSelect();
                }
            });


        //get_tag_cat(ids,level);
        }
    }else{
        jQuery('#'+divid).html('No Subcategory');
    }
}





function validate_question(){

    var quest = jQuery('#q_quest').val();
    var ans1 = jQuery('#q_ans1').val();
    var ans2 = jQuery('#q_ans2').val();
    
    var cat1 = jQuery('#cat1').val();
    var err = '';
 
    if (jQuery.trim(quest).length < 1)
        err += '<li>Please Provide Proper Question!</li>';
    
    if (jQuery.trim(ans1).length < 1||jQuery.trim(ans2).length < 1)
        err += '<li>Minimum 2 answers required</li>';
 
    if (jQuery.trim(cat1).length < 1) 
        err += '<li>Please Provide Main Cateogry of the Question!</li>';
    
    jQuery("#add_more input").each(function(){
        jQuery(this).css('border','1px solid #838381');
    });
    jQuery('#add_more input:text[value=""]').each(function(){
        jQuery(this).css('border','1px solid red');
    });
    if (jQuery.trim(err).length > 1) {
        jQuery('#err').html(err);
        jQuery('#err').addClass('error');
        return false;
    }

    jQuery('#question').slideUp('slow');
    jQuery('div.do-intop').html('Please wait till processing...!');
    return true;
    
}

function add_ans(){

    var ans_cnt = jQuery('#ans_cnt').val();
    //jQuery('#Add').attr('disabled',true);
    var tab=jQuery('#q_ans'+ans_cnt).attr('tabindex');
	
    tab=tab+1;
    //validate prev ans is empty
    if(jQuery('#q_ans'+ans_cnt).val().length>1){
        jQuery("#add_more input").each(function(){
            jQuery(this).css('border','1px solid #838381')
        });
        ans_cnts = ++ans_cnt;
		 
        if(ans_cnt>=3){
		
            jQuery('#del_ans').fadeIn('slow');
        }
		
        if (ans_cnt < 11) {
            jQuery('#ans_cnt').val(ans_cnts);
            //	$('add_more').set('html','  <p>&nbsp;</p>');
            var firstElem='<li><label><span class="span1">Answer</span></label><span><input name="q_ans'+ans_cnt+'" id="q_ans'+ans_cnts+'" onkeyup="jQuery(\'#Add\').attr(\'disabled\',false);" /></span></li>';
                   
            jQuery("#add_more").append(firstElem);
            // $('add_more').getLast('input').highlight('#F1F1F1', '#6DB6DB');
            //  $('add_more').getLast('input').focus();
            jQuery('#err').empty();
        
        }
        else {
		    
            jQuery('#add_more').append('<li><span class="red"> Upto 10 Answers only allowed!</span></li>').slideIn('slow');
           		
            jQuery('#Add').attr('disabled',true);
        // el.highlight('#FF0000', '#6DB6DB');
        }
    }else{
		
		

        var el=jQuery("#err");
   
        el.css('display', 'block');
        el.html('Some of the fields are still empty !');
        jQuery('#err').addClass('error');
        jQuery('#add_more input').each(function(){
            jQuery(this).css('border','1px solid #838381')
        });
        jQuery('#add_more input:text[value=""]').each(function(){
            jQuery(this).css('border','1px solid red')
        });
        //  el.highlight('#FF0000', '#6DB6DB');
		
	
        if(ans_cnt>=3){
            jQuery('#Add').attr('disabled',true);
        //  jQuery('#add_more input:last').('input').highlight('#F1F1F1', '#6DB6DB');
        }
    }
   
    
}

function del_ans(){
    jQuery('#Add').attr('disabled',false);
    var ans_cnt = jQuery('#ans_cnt').val();
    if (ans_cnt > 2) {

        if (ans_cnt == 3) {
		
            jQuery('#del_ans').fadeOut('slow');
        }
        if(ans_cnt==10){
			
            jQuery('#add_more li:last').remove();
            jQuery('#Add').attr('disabled',false);
        }
		
		
        jQuery('#q_ans' + ans_cnt).fadeOut('slow');
		
        jQuery('#q_ans' + ans_cnt).remove();
        jQuery('#add_more li:last').remove();
        jQuery('#ans_cnt').val(ans_cnt - 1);
		
    }
}

/*
window.addEvent('domready', function() {
	
	 var selObj = $('q_context');
  selObj.addEvent('change',function()
  {
 get_tag_cat('','');
  }); 	
//tagging
bind_event();

	bind_event_added();
});
*/
function get_tag_cat(ids,level){
    var text = $('q_context').get('value');
    var qns=$('q_quest').get('value');
    var ids=$('cat1').get('value');
    var scat=$('cat2').get('value');
    var sscat=$('cat3').get('value');
    var url = spath+'question/ajax';
    var req = new Request({
        method: 'get'
        ,
        url: url
        ,
        data: {
            'action':level,
            'cat1':ids,
            'cat2':scat,
            'cat3':sscat,
            'tag':text,
            'qns':qns
        },
        onRequest: function() { },
        onComplete: function(response) {
            $('sug_div').set('html', response);
        }
    }).send();
    setTimeout(bind_event,2000);
	
}



function bind_event(){
    var elements = $$('div.tagging-suggest-tag');
    var el = $('tagging-widget-container').getElements('a');
    /*
	
	//alert(elements);
	elements.addEvent('click', tag_add.bindWithEvent(this,elements)); 
	//elements.addLiveEvent('click', 'a', function(e){ alert('This is a live event'); });
	
*/
    for(var i = 0 ; i < el.length ; i = i + 1)
    {
 
  
        el[i].set('href','#');
    }

    elements.each(function(element,index){
 		
        element.addEvent('click', tag_add.bindWithEvent(this,element));
    });
	
    var addbut=$$('a.tagging-button-container');
	
    addbut.addEvent('click',tag_add_input.bindWithEvent(this));
}


function bind_event_added(){
    var elements = $('tagdiv').getElements('div');
	
    elements.each(function(element,index){
 		
        element.addEvent('click', tag_delq.bindWithEvent(this,element));
    });
	

}

function tag_add_input(val){
	
    var context=$('tagging-widget-input-1').get('value');
	
    if(context.length>0){
        var etarget=$('tagdiv');
        //set the tag
        var ele = new Element('div',{
            id : 'tagset'
	 	 
        }).inject(etarget);
        ele.addClass('tagging-tag');
        ele.addClass('inp');
        ele.set('text',context);
    }
    $('tagging-widget-input-1').set('value','');
    bind_event_added();
    insert_tag();
}

function tag_add(val,el){
	
	
    var context=el.get('text').trim();
    el.destroy();
    var elements =$$('div.tagging-curtags-wrapper');
    var etarget=$('tagdiv');
    if (context != '') {
        //set the tag
        var ele = new Element('div', {
            id: 'tagset'
							
        }).inject(etarget);
        ele.addClass('tagging-tag');
        ele.set('text', context);
        bind_event_added();
        insert_tag();
    }
			
}
	
function insert_tag(){
		
    var myArray=new Array();
    var elements =$$('div.tagging-tag');
		
    elements.each(function(element,index){
 		
        myArray.extend([element.get('text').trim()]);
	
    });
		
		
    var rtag=myArray.join(',');
    rtag.clean();
    $('q_tag').set('value',rtag);
}
	
function tag_delq(val,el){

    var result = el.hasClass('inp');

    if (!result) {
	
        var context =el.get('text');
		
        el.destroy();
        if(context!=''){
            var etarget = $('sug_div');
		
            //set the tag
            var ele = new Element('div', {
                id: 'stag'
		
            }).inject(etarget);
		
            ele.addClass('tagging-suggest-tag');
            ele.set('text', context);
            bind_event();
            return false;
        }
		
    }else {
		
        el.destroy();
    }
				
    insert_tag();
}


 /*
  jQuery(document).ready(function() {
    var selected = new Array();

   jQuery('select').mouseover(function() {
      if (this.multiple == true) {
        for (var i=0,a=0;i<this.options.length;i++) {
          if (this.options[i].selected == true) {
            selected[a] = this.options[i].value;
            a++;
          }
        }
      }
    });

    safe them when you click the mouse
    jQuery('select').click(function() {
      // make sure it's a multiple select
      if (this.multiple == true) {
        for(var i=0;i<selected.length;i++) {
          for(var a=0;a<this.options.length;a++){
            if (selected[i] == this.options[a].value && this.options[a].selected == true) {
              this.options[a].selected = false;
              selected.splice(i,1);
            } else if (selected[i] == this.options[a].value) {
              this.options[a].selected = true;
            }
          }
        }
      }

      // load all selected options in array when the mouse pointer hovers the select box
      if (this.multiple == true) {
        for (var i=0,a=0;i<this.options.length;i++) {
          if (this.options[i].selected == true) {
            selected[a] = this.options[i].value;
            a++;
          }
        }
      }

    });
  });
*/