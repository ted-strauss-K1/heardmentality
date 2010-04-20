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
        new Element('p').inject($('add_more'));
        
   
    //  wrapper.appendText('[Remove]');

        
        var ele = new Element('input', {
            id: 'q_ans' + ans_cnts,
            name: 'q_ans' + ans_cnts,
            // styles: {    'font-weight': 700,    color: 'green'  }
            size: '40',    events: { 
     'keyup': function(){
          $('Add').disabled = 0;
    }

    
    }
        }).inject($('add_more'));
        
         
        //wrapper.wraps(ele);
        
        $('add_more').getLast().highlight('#F1F1F1', '#6DB6DB');
		
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
				
				
}


/*	
function tag_del(val,el){
	
	
	var context=el.get('text');
	el.destroy();
	
	var etarget=$('sug_div');
	
	//set the tag
	 var ele = new Element('div',{ id : 'stag'
	 	 
	 }).inject(etarget);
	 
			ele.addClass('tagging-suggest-tag');
			ele.set('text',context);
	
	bind_event();	
}





 Element.implement({
    addLiveEvent: function(event, selector, fn){
        this.addEvent(event, function(e){
            var t = $(e.target);

            if (!t.match(selector)) return false;
                fn.apply(t, [e]);
        }.bindWithEvent(this, selector, fn));
    }
});



$$('div').addLiveEvent('click', 'a', function(e){ alert('This is a live event'); });


 function add_ans(){
 
 var ans_cnt=$('ans_cnt').value;
 ans_cnts=++ans_cnt;
 if(ans_cnt<11){
 $('ans_cnt').set('value',ans_cnts);
 //	$('add_more').set('html','  <p>&nbsp;</p>');
 var firstElem  = new Element("input", {name: "q_ans'+ans_cnt+'"});
 //$('add_more').adopt(firstElem);
 // var slot = new Element('input');
 // slot.inject($('add_more'));
 
 
 $('add_more').innerHTML += '  <p>&nbsp;</p> <div><input name="q_ans'+ans_cnts+'" type="text" id="q_ans'+ans_cnts+'" size="40" /></div>';
 $('add_more').getLast().highlight('#FF0000', '#6DB6DB');
 }else{
 $('add_more').innerHTML += '  <p>&nbsp;</p> <div>Only Upto 10 Answers are allowed!</div>';
 $('add_more').getLast().highlight('#FF0000', '#6DB6DB');
 }
 }
 
 
 function get_subcat(sid,divid,level){
 
 var foo = [];
 $(sid).getSelected().each(function(number,i){
 if(number.value!=''){
 foo[i] =number.value;
 }
 });
 var foo = foo.filter(function(item, index){
 return item > 0;
 });
 var ids = foo.toString();
 
 
 if(ids.length>0){
 
 
 var url = "'.$gSitePath.'question/ajax";
 var req = new Request({
 method: 'get'
 ,url: url
 ,data: { 'action':level,'ids':ids},
 onRequest: function() { },
 onComplete: function(response) {
 $(divid).set('html', response);
 }
 }).send();
 
 }else{
 $(divid).set('html','No Subcategory');
 }
 }	*/

