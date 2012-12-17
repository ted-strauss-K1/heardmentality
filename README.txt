1. Enable Modules

	1. Poll, Forum
	2. Content, Content Copy, Text, Option Widgets
	3. Administration menu
	4. Fieldgroup, Node Reference, Number

2. Disable Modules

	1. Color, Database Logging, Help

3. Enable Modules

	1. Contact, Content Translation, Locale, Path, Profile
	2. JQuery Update: /admin/settings/jquery_update (setup)
	3. Location, Node Locations: /admin/content/node-type/poll (setup: http://pix.am/z3b8/)
	4. Translation modules: http://pix.am/HwrO/

4. Setup Translation modules:

	1. Add languages: 
	2. /admin/settings/language/configure Set "Path prefix with language fallback"
	3. /admin/settings/language/i18n Set "Hide translation links"

5. Setup polls:

	1. /admin/content/node-type/poll Comment Settings >> Default >> Disabled
	2. /admin/content/node-type/forum/fields Add field http://pix.am/HXxv/ http://pix.am/PEaG/
	3. /admin/content/node-type/poll Rename http://pix.am/uaa0/

6. Setup forums:

	1. /admin/content/node-type/forum/fields Add fields

		1. http://pix.am/q7U8/ http://pix.am/AXIz/
		2. http://pix.am/d3P6/ http://pix.am/cvq6/
		3. http://pix.am/keCO/ http://pix.am/FVcv/
		4. http://pix.am/ooYh/ http://pix.am/HGFH/
		5. http://pix.am/Fpf5/ http://pix.am/EZKz/
		6. http://pix.am/kf4U/ 


7. Enable Modules

	1. Corresponding node references: /admin/settings/corresponding_node_references/references (setup)
	2. Language Detection Fix, Poll Choice Suggestions, Poll Fix, Poll Choices Characteristics, Poll Extension
	3. Ranks, Userpoints, Userpoints Extension: import 
	4. Donations, Paypal API: setup /admin/settings/donations, /admin/settings/paypal_api
	5. Userpoints Invite, Token, Invite, Invite Statistics: setup /admin/user/invite/settings
	6. Flag, Flag Note, Flag Button, Views
	7. Yes/No Voting, Voting API
	8. Follow Button, UR-API
	9. UR-Invite, UR-Rules, UR-UI, Rules: setup /admin/user/relationships/add http://pix.am/AKUb/
	10. Contact Forms, Alter: setup /admin/build/contact/add http://pix.am/yn6e/ and /admin/build/contact/settings http://pix.am/POYO/

8. Delete content types Story, Page on /admin/content/types/list
9. ------------------------ hm-clean-2012-12-04-15-00
10. Enable Modules

	1. 
		1. Poll Translation, Content Translation, Microsoft Translate: setup /admin/settings/mstapi


11. ------------------------ hm-clean-2012-12-04-17-00
12. Add role "administrator" on /admin/user/roles
13. Enable modules:

	1. Email Registration
	2. Feedback: setup /admin/user/permissions http://pix.am/AVJ6/
	3. Pathauto: setup /admin/build/path/pathauto http://pix.am/Ezeb/
	4. Rules Administration UI

14. Install and enable rubik theme: /admin/build/themes
15. Set rubik as default admin theme: /admin/settings/admin
16. Create Page content type on /admin/content/types/add
17. Create nodes of type Page for 403 and 404 errors
18. Set 403 & 404 pages /admin/settings/error-reporting
19. Enable module

	1. Avatar Selection, User Login Modal, Profile Complete Percentage, Profile Privacy
	2. Setup: 

20. Enable Module 

	1. Event Stream

21. Put the Front Events to Front Page Content region on /admin/build/block
22. Uncheck require email verification on /admin/user/settings http://pix.am/yLjG/
23. Enable module 

	1. Geonames, Heatmap

24. Put the Heatmap to Front Page Heatmap region on /admin/build/block
25. Put the Language Switcher to Multilanguage region on /admin/build/block
26. Set Up Gigya on /admin/settings/gigya http://pix.am/uriG/ http://pix.am/Etf5/
27. Put the User Profile Complete Percent (Bottom) to Footer Inner region on /admin/build/block
28. Set up geonames: /admin/settings/geonames - name "jnavanephp", url "http://api.geonames.org"
29. x


























