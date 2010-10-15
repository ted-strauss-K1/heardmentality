// JavaScript Document



function validate_question(){

    var quest = $('q_quest').value;
    var ans1 = $('q_ans1').value;
    var ans2 = $('q_ans2').value;
    
    var cat1 = $('cat1').value;
    var err = '';
    
    if (quest.trim().length < 1) 
        err += '<li>Please Provide Proper Question!</li>';
    
    if (ans1.trim().length < 1) 
        err += '<li>Please Provide Answer 1!</li>';
    
    if (ans2.trim().length < 1) 
        err += '<li>Please Provide Answer 2!</li>';
    
    
    if (cat1.trim().length < 1) 
        err += '<li>Please Provide Main Cateogry of the Question!</li>';
    
    
    if (err.trim().length > 1) {
        var el = $('err');
        el.setStyle('background-color', '#eeeeee');
        el.setStyle('height', 'auto');
        el.setStyle('color', 'red');
        el.setStyle('border', '3px solid #dd97a1');
        el.setStyle('list-style', 'none');
        
        el.setStyle('display', 'block');
        el.set('html', err);
        el.highlight("#EBCC22");
        
        return false;
    }

    $('qform').fade('out');
    $$('div.facttop').set('html','Please wait till processing...!')
    return true;
    
}

function add_ans(){

    var ans_cnt = jQuery('#ans_cnt').val();
   //jQuery('#Add').attr('disabled',true);
    var tab=jQuery('#q_ans'+ans_cnt).attr('tabindex');
	
    tab=tab+1;
	    //validate prev ans is empty
    if(jQuery('#q_ans'+ans_cnt).val().length>1){
		
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
		
		alert('ss');

        var el=jQuery("#err");
        alert('sss');
        el.css('display', 'block');
        el.html('Answer should not be empty!');
           jQuery('#add_more input:empty').css('border',red);
      //  el.highlight('#FF0000', '#6DB6DB');
		
	
        if(ans_cnt>=3){
            jQuery('#Add').attr('disabled',true);
         //  jQuery('#add_more input:last').('input').highlight('#F1F1F1', '#6DB6DB');
        }
    }
   
    
}

function del_ans(){
    jQuery('#Add').attr('disabled',false);
    var ans_cnt = $('ans_cnt').value;
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


