/**
 * @author gobinath.m
 */
function get_toplist(sid,level){
	cid=jQuery('#tcat').val();
	if(level==2){
	scid=sid;
	}else{
		
		scid='';
	}

		var url = gSitePath+'qmini/ajax';
									
			jQuery.ajax({
   type: "POST",
   url: url,
   data: { action:level,cid:cid,scid:scid},
   success: function(msg){
     jQuery('#res_top').html(msg);
     load_list(1);
init_pagecon();
   }
 });						
									
	
	if(level==1&&sid!=''){
	
	jQuery.ajax({
   type: "POST",
   url: url,
   data: { action:5,cid:cid},
   success: function(msg){
     jQuery('#res_scat').html(msg);
   }
	 });	
	}else if(level==1&&sid==''){
		var ins='<select name="" disabled="disabled"><option>selecct a sub-category</option></select>';
		 jQuery('#res_scat').html(ins);
	}


        
 }

