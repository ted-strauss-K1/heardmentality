<?php

/**
 * Project:     RSSParser: A library for parsing RSS feeds
 * File:        RSSParser.class.php
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @link http://www.phpinsider.com/php/code/RSSParser/
 * @copyright 2004-2005 New Digital Group, Inc.
 * @author Monte Ohrt <monte at newdigitalgroup dot com>
 * @package RSSParser
 * @version 1.0-dev
 */

require_once(dirname(__FILE__).'/XMLParser.class.php');

class RSSParser extends XMLParser{
    
    /**#@-*/
    /**
     * The class constructor.
     */
   function RSSParser() { }
  
    /**
     * parse the XML file (or URL)
     *
     * @param string $path the XML file path, or URL
     */
    function parse($path){
           
        // parse the XML content      
        parent::parse($path);
        //print_r($this->output);
        if(empty($this->output)||$this->output[0]['name']=='HTML')
           return ""; //return array();

        // detect the format        
        switch(strtoupper($this->output[0]['name'])) {
            case 'RDF:RDF':
                return $this->parse_rdf();                
                break;   
            case 'RSS':
                return $this->parse_rss();
                break;
            default:
                trigger_error('unknown XML format');
                break;
        }
    }

    function parse_rss() {
        // get RSS header items
        $_output['ATTRS'] = $this->output[0]['attrs'];
        // get channel content
        foreach($this->output[0]['child'][0]['child'] as $_channel_element) {
            switch(strtoupper($_channel_element['name'])) {
                case 'ITEM':
                    $_item = array();
                    foreach($_channel_element['child'] as $_item_element) {
                        $_item[$_item_element['name']] = $_item_element['content'];
                    }
                    $_output['ITEM'][] = $_item;
                    break;
                case 'IMAGE':
                    foreach($_channel_element['child'] as $_image_element) {
                        $_image[$_image_element['name']] = $_image_element['content'];
                    }
                    $_output['CHANNEL']['IMAGE'] = $_image;
                    break;
                case 'TEXTINPUT':
                    foreach($_channel_element['child'] as $_textinput_element) {
                        $_textinput[$_textinput_element['name']] = $_textinput_element['content'];
                    }
                    $_output['CHANNEL']['TEXTINPUT'] = $_textinput;
                    break;
                default:
                    $_output[$_channel_element['name']] = isset($_channel_element['content']) ? $_channel_element['content'] : null;
                    break;   
            }   

        }
        return $_output;
    }

    function parse_rdf() {
        
        // get RDF header items
        $_output['ATTRS'] = $this->output[0]['attrs'];
        $_output['CHANNEL']['ATTRS'] = $this->output[0]['child'][0]['attrs'];
        // get channel content
        foreach($this->output[0]['child'] as $_rdf_element) {
        
            switch(strtoupper($_rdf_element['name'])) {
            
                case 'CHANNEL':
                    $_output['CHANNEL']['ATTRS'] = $_rdf_element['attrs'];
                    foreach($_rdf_element['child'] as $_channel_element) {
                        switch(strtoupper($_channel_element['name'])) {
                            case 'ITEMS':
                                foreach($_channel_element['child'][0]['child'] as $_items_element) {
                                    $_items[] = $_items_element['attrs']['RDF:RESOURCE'];
                                }                    
                                $_output['CHANNEL']['ITEMS'] = $_items;
                                break;
                            case 'IMAGE':
                                $_output['CHANNEL']['IMAGE']['ATTRS'] = $_channel_element['attrs'];
                                break;
                            case 'TEXTINPUT':
                                $_output['CHANNEL']['TEXTINPUT']['ATTRS'] = $_channel_element['attrs'];
                                break;
                                break;
                            default:
                                $_output['CHANNEL'][$_channel_element['name']] = $_channel_element['content'];
                                break;   
                        }   

                    }
                    break;
                case 'ITEM':
                    foreach($_rdf_element['child'] as $_item_element) {
                        $_item[$_item_element['name']] = $_item_element['content'];
                    }
                    $_output['ITEM'][] = $_item;
                    break;
            }
        
        }
        return $_output;
    }
    
       
}


?>
