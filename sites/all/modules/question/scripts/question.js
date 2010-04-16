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
    
    return true;
    
}

function add_ans(){

    var ans_cnt = $('ans_cnt').value;
	
	var tab=$('q_ans'+ans_cnt).get('tabindex');
	
	tab=tab+1;
	
	//validate prev ans is empty
	if($('q_ans'+ans_cnt).value.length>1){
		
		 ans_cnts = ++ans_cnt;
		 
		 if(ans_cnt>=3){
		
		$('del_ans').fade('in');
	}
		
    if (ans_cnt < 11) {
        $('ans_cnt').set('value', ans_cnts);
        //	$('add_more').set('html','  <p>&nbsp;</p>');
        var firstElem = new Element("input", {
            name: "q_ans'+ans_cnt+'"
        });
        //$('add_more').adopt(firstElem);
        // var slot = new Element('input');
        // slot.inject($('add_more'));
        //var tem=$('add_more').innerHTML ;
      
        
   
    //  wrapper.appendText('[Remove]');

        
        var ele = new Element('input', {
            id: 'q_ans' + ans_cnts,
            name: 'q_ans' + ans_cnts,
			tabindex:tab,
            // styles: {    'font-weight': 700,    color: 'green'  }
            size: '40',    events: { 
     'keyup': function(){
          $('Add').disabled = 0;
    }
	
    
    }
        }).inject($('add_more'));
        
           new Element('p').inject($('add_more'));
        //wrapper.wraps(ele);
        
        $('add_more').getLast('input').highlight('#F1F1F1', '#6DB6DB');
		$('add_more').getLast('input').focus();
		$('err').empty();
        
    }
		    else {
		    
		     var el=$('add_more').getLast('p');
  		 el.set('html',' Upto 10 Answers only allowed!');
		
		        $('Add').disabled = 1;
		       el.highlight('#FF0000', '#6DB6DB');
		    }
	}else{
		
		
		var el=$('err');
		el.setStyle('background-color', '#eeeeee');
        el.setStyle('height', '20px');
		el.setStyle('padding','10px');
        el.setStyle('color', 'red');
        el.setStyle('border', '3px solid #dd97a1');
        el.setStyle('list-style', 'none');
        
        el.setStyle('display', 'block');
		el.set('html','  Answer should not be empty!');
		el.highlight('#FF0000', '#6DB6DB');
		
	
	 if(ans_cnt>=3){
	 	 $('Add').disabled = 1;
	 $('add_more').getLast().highlight('#FF0000', '#6DB6DB');
	 }
	}
   
    
}

function del_ans(){
		 $('Add').disabled = 0;
	var ans_cnt = $('ans_cnt').value;
	if (ans_cnt > 2) {
	
		if (ans_cnt == 3) {
		
			$('del_ans').fade('out');
		}
		if(ans_cnt==10){
			
			 var el=$('add_more').getLast('p').empty();
			  $('Add').disabled = 0;
		}	
		
		
		$('q_ans' + ans_cnt).fade('out');
		
		$('q_ans' + ans_cnt).destroy();
		 $('add_more').getLast('p').destroy();
		$('ans_cnt').set('value', ans_cnt - 1);
		
	}
}


window.addEvent('domready', function() {
	
	 var selObj = $('q_context');
  selObj.addEvent('change',function()
  {
 get_tag_cat('','');
  }); 	
	 
	
});

function get_tag_cat(ids,level){
	var text = $('q_context').get('value');
	var qns=$('q_quest').get('value');
	var ids=$('cat1').get('value');
	var scat=$('cat2').get('value');
	var sscat=$('cat3').get('value');
	var url = spath+'question/ajax';
									var req = new Request({    
											method: 'get'
											,url: url
											,data: { 'action':level,'cat1':ids,'cat2':scat,'cat3':sscat,'tag':text,'qns':qns},
											onRequest: function() { },
											onComplete: function(response) {
													 $('sug_div').set('html', response);
											}
									}).send();
	setTimeout(bind_event,5000);
	
}





window.addEvent('domready', function() {
	
	bind_event();
	
	
	
	
});

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

function tag_add_input(val){
	
	var context=$('tagging-widget-input-1').get('value');
	
	if(context.length>0){
		var etarget=$('tagdiv');
	//set the tag
	 var ele = new Element('div',{ id : 'tagset','onclick':'tag_delq(this);return false;'
	 	 
	 }).inject(etarget);
			ele.addClass('tagging-tag');
			ele.addClass('inp');
			ele.set('text',context);
	}
	$('tagging-widget-input-1').set('value','');
	insert_tag();
}

function tag_add(val,el){
	
	
	var context=el.get('text');
	el.destroy();
	var elements =$$('div.tagging-curtags-wrapper');
	var etarget=$('tagdiv');
	
	//set the tag
	 var ele = new Element('div',{ id : 'tagset','onclick':'tag_delq(this);return false;'
	 	 
	 }).inject(etarget);
			ele.addClass('tagging-tag');
			ele.set('text',context);
	
	insert_tag();		
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
	
function tag_delq(val){
	
	var result = val.hasClass('inp');

	if (!result) {
	
		var context = val.get('text');
		val.destroy();
		
		var etarget = $('sug_div');
		
		//set the tag
		var ele = new Element('div', {
			id: 'stag'
		
		}).inject(etarget);
		
		ele.addClass('tagging-suggest-tag');
		ele.set('text', context);
		bind_event();
		
	}else {
		
		val.destroy();
	}	
				
	insert_tag();			
}


