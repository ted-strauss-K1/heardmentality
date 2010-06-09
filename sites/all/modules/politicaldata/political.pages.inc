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
                  
                    if ($i > 5)
                        break;
                    
                   
                    foreach ($result as $final) {
                        
                        if ($i > 5)
                            break;
                        
                                           
						$count = db_result(db_query("SELECT COUNT(*) FROM {user} where political_user='1' AND political_id='".$final['ID']."' group by uid"));
                        if (! empty($final['ID']) && $final['ID'] > 0 && $count==0) {
                            
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
			 echo "Data updated successfully!";
            break;
        case 'question':
            
            $output = $xml->parse('http://www.govtrack.us/data/us/111/bills.index.xml');
            
            foreach ($output as $valuesresult) {
            
            }
            
            foreach ($valuesresult as $opkt) {
                if ($i > 5)
                    break;
                foreach ($opkt as $result) {
                    
                    if ($i > 5)
                        break;
                   
                    foreach ($result as $final) {
                        
                    	 $dst = clean_url(myTruncate($final['TITLE'], 100, ' '));
                        $result = db_query("INSERT INTO {question} set uid='1',question='".$final['TITLE']."',context='".$final['OFFICIAL-TITLE']."',cid='1',country='US' ");
                        
                        $ins_id = db_last_insert_id('question', 'qid');
                        
                        $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Yay');
                        $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, 'Nay');
                    
                    }
                    $i++;
                
                }
            }

             echo "Data updated successfully!";
            break;
        
        default:
            echo "No Action Found";
            break;

    
    }

   
    //return $strReturn;


}
