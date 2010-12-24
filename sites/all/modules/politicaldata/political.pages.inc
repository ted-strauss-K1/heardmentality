<?php
function political_api() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $strReturn = '';
    drupal_add_css(drupal_get_path('module', 'category').'/styles/jquery.treeview.css');
    require ('XMLParser.class.php');
    $case = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $xml = new XMLParser();
    $limit = 6;
    set_time_limit(0);
    $i = 0;
    switch ($case) {
        
        case 'people':
            $output = $xml->parse('http://www.govtrack.us/data/us/111/people.xml');
            foreach ($output as $valuesresult) {
            
            }
            
            foreach ($valuesresult as $opkt) {
                if ($i > 5)
                    break;
                foreach ($opkt as $result) {
                    echo $i;
                    if ($i > 5)
                        break;
                    
                    echo $result['name'];
                    foreach ($result as $final) {
                        
                        if ($i > 5)
                            break;

                        
                        $count = db_result(db_query("SELECT COUNT(*) FROM {user} where political_user='1' AND political_id='".$final['ID']."' group by uid"));
                        if (! empty($final['ID']) && $final['ID'] > 0 && $count == 0) {
                            
                            $insert = "insert into {users} (name,pass,mail,provider,created,access,login,status,Identity,political_user,political_id)values('".mysql_escape_string($final['FIRSTNAME'].$final['ID'])."','','','Political','".time()."','".time()."','".time()."','1','','1','".$final['ID']."') ";
                            $insersult = db_query($insert);
                            $lid = mysql_insert_id();
                            $insert_profile = "insert into user_profile (uid,real_name,first_name,last_name,gender,zip,state,facebook,twitter,dob,image_url,provider)values('".$lid."','".mysql_escape_string($final['FIRSTNAME'].''.$final['FIRSTNAME'])."','".$final['FIRSTNAME']."' ,'".$final['LASTNAME']."' ,'".$final['GENDER']."','','".$final['STATE']."','','','".$final['BIRTHDAY']."','','') ";
                            
                            $insersult = db_query($insert_profile);
                        
                        }

                    
                    }
                    $i++;
                
                }
            }
            
            break;
        case 'question':
            
          $output = $xml->parse('http://www.govtrack.us/data/us/111/bills.index.xml');
           // $output = $xml->parse('http://192.9.200.13/design/heardmentality/bills.index.xml');
            
            /*
             $ch = curl_init();
             // set URL and other appropriate options
             curl_setopt($ch, CURLOPT_URL, "http://www.govtrack.us/data/us/111/bills.index.xml");
             curl_setopt($ch, CURLOPT_HEADER, false);
             // grab URL and pass it to the browser
             curl_exec($ch);
             // close CURL resource, and free up system resources
             curl_close($ch);
             exit;
             
             */


            foreach ($output as $valuesresult) {
            
            }
            $congress = $valuesresult['attrs']['SESSION'];
            foreach ($valuesresult as $opkt) {
                
                if ($i > 15)
                    break;
                foreach ($opkt as $result) {
                    
                    if ($i > 15)
                        break;
                    
                    foreach ($result as $final) {
                        
                        if (strlen($final['TITLE']) > 5) {
                            $dst = clean_url(myTruncate($final['TITLE'], 100, ' '));
                            $result = db_query("INSERT INTO {question} set uid='1',question='".$final['TITLE']."',context='".$final['OFFICIAL-TITLE']."',is_political='1',billid='".$final['NUMBER']."',billtype='".$final['TYPE']."',congress='$congress',cid='1',year='".$final['TYPE']."',url='$dst',country='United States' ");
                            
                            $ins_id = db_last_insert_id('question', 'qid');
                            //values are + (aye), - (nay), 0 (absent), P (present), X (other)
                            $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Aye');
                            $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Nay');
                            //  $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Absent');
                            $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Present');
                            $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Not Voting');
                            //url alias
                              db_query("insert into {question_cat} set qid='$ins_id',cat='1'");
                            $url = 'qlite/view/'.$ins_id;
                            
                            $urlins = db_query("insert INTO {url_alias} set src='".$url."',dst='".$dst."'");
                        }
                    
                    }
                    $i++;
                
                }
            }
            
            echo "Data updated successfully!";
            break;
        case 'votes':
            
			   $query = "SELECT * from {political_vote_links} where status='0' LIMIT 0,10";
    $list = ExecuteQuery($query, "select");	
					
						
            foreach($list as $for) {
                
                $url = $for['url']; 
                $output = $xml->parse($url);
                
             
                foreach ($output as $valuesresult) {
                
                }
                foreach ($valuesresult as $result) {
                
                }
				foreach ($result as $result2) {
				//	print_r($result2);
				 $billcase=$result2['name'];
				
             switch($billcase){
             	
				case 'BILL':
					$billid=$result2['attrs']['NUMBER'];
				break;
				case 'VOTER':
					
					$vote=$result2['attrs']['VOTE'];
					$vid=$result2['attrs']['ID'];
					$value=$result2['attrs']['VALUE'];
					$urlid=$for['urlid'];
					update_vote($billid,$vote,$vid,$value,$urlid);
					break;
				
             }
			 
			 
			 
                }
            	
            }

            
            break;
		case 'votelinks':
			political_vote_links();
				break;	
        default:
            echo "No Action Found";
            break;

    
    }

    
    //return $strReturn;


}

function update_vote($bid="",$vote="",$vid="",$value="",$urlid=""){
	$pr=func_get_args();

	
db_query("update {political_vote_links} set status='1' where urlid='$urlid'");
	
	if(!empty($bid)&&!empty($vid)){
		$query="select uid from {user} where political_user='1' AND political_id='$vid'";
		$uid=db_result(db_query($query));
		
		$query="select qid from {question} where is_political='1' AND billid='$bid'";
		$qid=db_result(db_query($query));
		
		switch($value){
			case 'Yea':
				$aid=db_result(db_query("select paid from {possible_answer} where qid='$qid' AND answer='Aye'"));
					break;
			case 'Nay':
				$aid=db_result(db_query("select paid from {possible_answer} where qid='$qid' AND answer='Nay'"));
					break;
			case 'Present':
				$aid=db_result(db_query("select paid from {possible_answer} where qid='$qid' AND answer='Present'"));
					break;	
			default:
				$aid=db_result(db_query("select paid from {possible_answer} where qid='$qid' AND answer='Not Voting'"));			
			break;
		}//switch ends
		if(!empty($qid)&&!empty($uid)&&!empty($aid)){
			
			db_query("insert into {possible_answer_vote} set qid='$qid',uid='$uid',panswer_id='$aid'");	
		}
	
		
		
	}

	
}

function political_vote_links(){
	

$target_url = "http://www.govtrack.us/data/us/111/rolls/";


// make the cURL request to $target_url
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL,$target_url);
curl_setopt($ch, CURLOPT_FAILONERROR, true);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
curl_setopt($ch, CURLOPT_AUTOREFERER, true);
curl_setopt($ch, CURLOPT_RETURNTRANSFER,true);
curl_setopt($ch, CURLOPT_TIMEOUT, 10);
$html= curl_exec($ch);
if (!$html) {
	echo "<br />cURL error number:" .curl_errno($ch);
	echo "<br />cURL error:" . curl_error($ch);
	exit;
}

// parse the html into a DOMDocument
$dom = new DOMDocument();
@$dom->loadHTML($html);

// grab all the on the page
$xpath = new DOMXPath($dom);
$hrefs = $xpath->evaluate("/html/body//a");

for ($i = 0; $i < $hrefs->length; $i++) {
	$href = $hrefs->item($i);
	 $url = $href->getAttribute('href');
	
	storeLink($url,$target_url);
	
}

	
	
	
}

	
	function storeLink($url="",$target="") {
		
		 $final=$target.$url;
		 if(preg_match('/^.*\.(xml)$/i', $final)){
		 	$query = "INSERT INTO {political_vote_links} (url) VALUES ('$final')";
	db_query($query) or die('Error, insert query failed');
		 }
	echo "Votes Updated Successfully!";
		
	
}
