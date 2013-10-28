STEP 1: RETRIEVE ACTUAL ISO COUTRIES LIST

From http://www.geonames.org/countries/
Put it to the location_get_iso3166_list() function in location.inc (location module)

STEP 2: RETRIEVE ACTUAL ISO REGIONS LIST

From http://www.geonames.org/countries/ go to countries' pages and visit Administrative Division section. 
Parse all similar pages to get file: regions.txt

Initial state of pages in "iso-regions (init)" dir
Preparsed state of pages in "iso-regions (preparsed)" dir

Remove "supported" directory from location module
Create the functions with regions lists

STEP 3: GET THE LIST OF CITIES

Using 
- regions.txt List of iso to geonameid relations
- cities5000.txt List of cities with population >5000
- code2gid.txt List of region codes (from cities5000) to geonameid
