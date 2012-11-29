<?php

/**
 * Microsoft Translator API - AccessTokenAuthentication
 *
 * @see http://msdn.microsoft.com/en-us/library/ff512434.aspx#phpexample
 */
class AccessTokenAuthentication
{
  /**
   * Get the access token.
   *
   * @param $grantType      Grant type
   * @param $scopeUrl       Application Scope URL
   * @param $clientID       Application client ID
   * @param $clientSecret   Application client ID
   * @param $authUrl        Oauth Url
   * @return mixed
   * @throws Exception
   */
  function getTokens($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl)
  {
    try {
      //Initialize the Curl Session.
      $ch = curl_init();
      //Create the request Array.
      $paramArr = array(
        'grant_type' => $grantType,
        'scope' => $scopeUrl,
        'client_id' => $clientID,
        'client_secret' => $clientSecret
      );
      //Create an Http Query.//
      $paramArr = http_build_query($paramArr);
      //Set the Curl URL.
      curl_setopt($ch, CURLOPT_URL, $authUrl);
      //Set HTTP POST Request.
      curl_setopt($ch, CURLOPT_POST, TRUE);
      //Set data to POST in HTTP "POST" Operation.
      curl_setopt($ch, CURLOPT_POSTFIELDS, $paramArr);
      //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
      //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
      curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
      //Execute the  cURL session.
      $strResponse = curl_exec($ch);
      //Get the Error Code returned by Curl.
      $curlErrno = curl_errno($ch);
      if ($curlErrno) {
        $curlError = curl_error($ch);
        throw new Exception($curlError);
      }
      //Close the Curl Session.
      curl_close($ch);
      //Decode the returned JSON string.
      $objResponse = json_decode($strResponse);

      if ($objResponse->error) {
        throw new Exception($objResponse->error_description);
      }
      return $objResponse->access_token;
    } catch (Exception $e) {
//      echo "Exception-" . $e->getMessage();
      return false;
    }
  }
}

/**
 * Microsoft Translator API - SOAPMicrosoftTranslator
 *
 * Class:AccessTokenAuthentication
 *
 * Create SOAP Object
 *
 * @see http://msdn.microsoft.com/en-us/library/ff512434.aspx#phpexample
 */
class SOAPMicrosoftTranslator
{

  /**
   * Soap Object
   *
   * @var SoapClient
   */
  public $objSoap;

  /**
   * Create the SAOP object
   *
   * @param $accessToken  Access Token string
   * @param $wsdlUrl      WSDL string
   */
  public function __construct($accessToken, $wsdlUrl)
  {
    try {
      //Authorization header string.
      $authHeader = "Authorization: Bearer " . $accessToken;
      $contextArr = array(
        'http' => array(
          'header' => $authHeader
        )
      );
      //Create a streams context.
      $objContext = stream_context_create($contextArr);
      $optionsArr = array(
        'soap_version' => 'SOAP_1_2',
        'encoding' => 'UTF-8',
        'exceptions' => true,
        'trace' => true,
        'cache_wsdl' => 'WSDL_CACHE_NONE',
        'stream_context' => $objContext,
        'user_agent' => 'PHP-SOAP/' . PHP_VERSION . "\r\n" . $authHeader
      );
      //Call Soap Client.
      $this->objSoap = new SoapClient($wsdlUrl, $optionsArr);
    } catch (Exception $e) {
//      echo "<h2>Exception Error!</h2>";
//      echo $e->getMessage();
      $this->objSoap = false;
    }
  }
}


/**
 *
 */
class MicrosoftTranslate
{
  /**
   * Soap WSDL Url
   */
  protected $_wsdlUrl = "http://api.microsofttranslator.com/V2/Soap.svc";

  /**
   * Client ID of the application
   *
   * To be set by user
   */
  protected $_clientID = "";

  /**
   * Client Secret key of the application
   *
   * To be set by user
   */
  protected $_clientSecret = "";

  /**
   * OAuth Url
   */
  protected $_authUrl = "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/";

  /**
   * Application Scope Url
   */
  protected $_scopeUrl = "http://api.microsofttranslator.com";

  /**
   * Application grant type
   */
  protected $_grantType = "client_credentials";

  /**
   * Store queue for translations
   *
   * @var array
   */
  protected $_queue = array();

  /**
   * Construct object for translation
   *
   * @param $clientID
   * @param $clientSecret
   */
  public function __construct($clientID, $clientSecret)
  {
    $this->_clientID = $clientID;
    $this->_clientSecret = $clientSecret;
  }

  /**
   * Add the string to queue
   *
   * @param $string
   */
  public function queue($string)
  {
    $this->_queue[$string] = '';
  }

  /**
   * Remove the string from queue or clear it
   *
   * @param bool $string
   */
  public function dequeue($string = false)
  {
    if ($string === false) {
      $this->_queue = array();
    } else {
      unset($this->_queue);
    }
  }

  /**
   * Run translation
   *
   * @param $lang_from
   * @param $lang_to
   * @return array
   */
  public function exec($lang_from, $lang_to)
  {
    // Create the Authentication object
    $authObj = new AccessTokenAuthentication();
    // Get the Access token
    $accessToken = $authObj->getTokens($this->_grantType, $this->_scopeUrl, $this->_clientID, $this->_clientSecret, $this->_authUrl);
    if ($accessToken === false) {
      return false;
    }
    // Create soap translator Object
    $soapTranslator = new SOAPMicrosoftTranslator($accessToken, $this->_wsdlUrl);
    if ($soapTranslator->objSoap === false) {
      return false;
    }
    // Create Option Array.
    $optionArg = array(
      'Category' => "general",
      'ContentType' => "text/plain",
      'Uri' => null,
      'User' => 'TestUser'
    );
    // Input text Array.
    $inputStrArr = array_keys($this->_queue);
    // Request argument list.
    $requestArg = array(
      'appId' => '', // no longer used, but pass it anyway
      'texts' => $inputStrArr,
      'from' => 'de',
      'to' => 'en',
      'maxTranslations' => 5,
      'options' => $optionArg
    );
    try {
      $responseObj = $soapTranslator->objSoap->GetTranslationsArray($requestArg);
      $responseTranslation = $responseObj->GetTranslationsArrayResult->GetTranslationsResponse;
      $i = 0;
      foreach ($responseTranslation as $translationArr) {
        $translationMatchArr = $translationArr->Translations->TranslationMatch;
        echo "Get Translation For <b>$inputStrArr[$i]</b>";
        echo "<table border ='2px'>";
        echo "<tr><td><b>Count</b></td><td><b>MatchDegree</b></td>
        <td><b>Rating</b></td><td><b>TranslatedText</b></td></tr>";
        foreach ($translationMatchArr as $translationMatch) {
          echo "<tr><td>$translationMatch->Count</td><td>$translationMatch->MatchDegree</td><td>$translationMatch->Rating</td>
            <td>$translationMatch->TranslatedText</td></tr>";
        }
        echo "</table></br>";
        $i++;
      }
    } catch (Exception $e) {
//      echo "Exception: " . $e->getMessage() . "<br/>";
      return false;
    }
    return $this->_queue;
  }

}
