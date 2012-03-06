// $Id: $

if (Drupal.settings.gigya_sharebar){
  var conf = Drupal.settings.gigya.conf;
  // Step 1: Construct a UserAction object and fill it with data.
  var ua = new gigya.services.socialize.UserAction();
  ua.setUserMessage(Drupal.settings.gigya_sharebar.userMessage);
  ua.setLinkBack(Drupal.settings.gigya_sharebar.linkBack);
  ua.setTitle(Drupal.settings.gigya_sharebar.title);
  ua.addActionLink(Drupal.settings.gigya_sharebar.actionLinkTitle, Drupal.settings.gigya_sharebar.actionLinkHREF);
  //ua.setDescription(description);

  // Step 2: Define the Share Bar Plugin's params object.
  var params ={
      userAction:ua,
      shareButtons: Drupal.settings.gigya_sharebar.shareButtons,
      showCounts: Drupal.settings.gigya_sharebar.showCounts,
      containerID: 'gigya-sharebar',
      cid:''
  };

  if (typeof Drupal.settings.gigya_sharebar.facebookLikeButton != 'undefined') {
      params.facebookLikeButton =  Drupal.settings.gigya_sharebar.facebookLikeButton;
    }

  // Step 3: Load the Share Bar Plugin.
  gigya.services.socialize.showShareBarUI(conf,params);
}
