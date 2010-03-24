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
		    
		        var el=$('err');
		el.setStyle('background-color', '#eeeeee');
        el.setStyle('height', '20px');
		el.setStyle('padding','10px');
        el.setStyle('color', 'red');
        el.setStyle('border', '3px solid #dd97a1');
        el.setStyle('list-style', 'none');
        
        el.setStyle('display', 'block');
		el.set('html',' Upto 10 Answers only allowed!');
		el.highlight('#FF0000', '#6DB6DB');
		        $('Add').disabled = 1;
		        $('add_more').getLast().highlight('#FF0000', '#6DB6DB');
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

	var ans_cnt = $('ans_cnt').value;
	if (ans_cnt > 2) {
	
		if (ans_cnt == 3) {
		
			$('del_ans').fade('out');
		}
		$('q_ans' + ans_cnt).fade('out');
		
		$('q_ans' + ans_cnt).destroy();
		$('ans_cnt').set('value', ans_cnt - 1);
		
	}
}
/*	function add_ans(){
 
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

