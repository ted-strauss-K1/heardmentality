
function showhidem(id){


    if (document.getElementById){
        obj = document.getElementById(id);
       
		
        if (obj.style.display == "none"){
            obj.style.display = "inline";
			
      
        } else {
            obj.style.display = "none";
         
        }
		
		
    }
	

}
	