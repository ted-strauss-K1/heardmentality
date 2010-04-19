function validate_profile(){
    var facebook = $('edit-facebook').value;
    var twitter = $('edit-twitter').value;

    var RegExp = /^(([\w]+:)?\/\/)?(([\d\w]|%[a-fA-f\d]{2,2})+(:([\d\w]|%[a-fA-f\d]{2,2})+)?@)?([\d\w][-\d\w]{0,253}[\d\w]\.)+[\w]{2,4}(:[\d]+)?(\/([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)*(\?(&?([-+_~.\d\w]|%[a-fA-f\d]{2,2})=?)*)?(#([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)?$/;
	if(facebook !=''){
    if(!(RegExp.test(facebook))){
		alert('Please enter the valid URL format for Facebook');
        return false;
    }
	}
	if(twitter !=''){
    if(!(RegExp.test(twitter))){
		alert('Please enter the valid URL format for Twitter');
        return false;
    }

	}
    return true;
    
}

