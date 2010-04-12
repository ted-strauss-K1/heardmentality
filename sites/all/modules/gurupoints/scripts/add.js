// JavaScript Document
function add_ans(){

    var ans_cnt = $('votepts').value;
	
	var tab=$('votepts'+ans_cnt).get('tabindex');
	
	tab=tab+1;
	
	//validate prev ans is empty
	if($('votepts'+ans_cnt).value.length>1){
		
		 ans_cnts = ++ans_cnt;
		 
		 if(ans_cnt>=1){
		
		$('del_ans').fade('in');
	}
		
    if (ans_cnt < 11) {
        $('votepts').set('value', ans_cnts);
        //	$('add_more').set('html','  <p>&nbsp;</p>');
        var firstElem = new Element("input", {
            name: "votepts'+ans_cnt+'"
        });
        //$('add_more').adopt(firstElem);
        // var slot = new Element('input');
        // slot.inject($('add_more'));
        //var tem=$('add_more').innerHTML ;
        new Element('p').inject($('add_more'));
        
   
    //  wrapper.appendText('[Remove]');

        
        var ele = new Element('input', {
            id: 'votepts' + ans_cnts,
            name: 'votepts' + ans_cnts,
			tabindex:tab,
            // styles: {    'font-weight': 700,    color: 'green'  }
            size: '40',    events: { 
     'keyup': function(){
          $('Add').disabled = 0;
    }

    
    }
        }).inject($('add_more'));
        
         
        //wrapper.wraps(ele);
        
        $('add_more').getLast().highlight('#F1F1F1', '#6DB6DB');
		$('add_more').getLast().focus();
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
	
        
        el.setStyle('display', 'block');

		el.highlight('#FF0000', '#6DB6DB');
		
	
	
	}
   
    
}
