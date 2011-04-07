/* - - - Custom Theme - - - */

/* Logo */
h1 a {
	background-image:url('../images/wflogo.png'); 
	min-height:0;
	height:40px;
}
* html h1 a {/* IE6 png Support */
	background-image: none;
	filter: progid:DXImageTransform.Microsoft.AlphaImageLoader(src="/images/wflogo.png", sizingMethod="crop");
}

/* Backgrounds */
html{
	background-image:none;
	background-color:#ffff99;
}
h1{
	background-image:none;
	background-color:#99cc66;
}
#container, html.embed{
	background-color:#FFFFFF;
}
.wufoo input.text, .wufoo textarea.textarea, .wufoo input.file{
	background:#FFFFFF url(/images/fieldbg.gif) repeat-x top;
}
.safari .wufoo input.file{
	background:none;
}
.wufoo li.focused{
	background-color:#FFF7C0;
}
.wufoo .instruct{
	background-color:#F5F5F5;
}

/* Borders */
#container{
	border:0 solid #cccccc;
}
.wufoo .info_head, .wufoo .paging-context{
	border-bottom:1px dotted #CCCCCC;
}
.wufoo .section, .wufoo .captcha{
	border-top:1px dotted #CCCCCC;
}
.wufoo input.text, .wufoo textarea.textarea{
	border:;
}
.wufoo .instruct{
	border:1px solid #E6E6E6;
}
.fixed .info_head{
	border-bottom:none;
}

/* Typography */
.wufoo .info_head h2{
	font-size:160%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#000000;
}
.wufoo .info_head div{
	font-size:95%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#444444;
}
.wufoo .section h3{
	font-size:110%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#000000;
}
.wufoo .section div{
	font-size:85%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#444444;
}

.wufoo .graph h3{
	color:#000000;
}
.wufoo .footer h4{
	color:#000000;
}
.wufoo .footer span{
	color:#444444;
}

.wufoo label.desc{
	font-size:95%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#444444;
}
.wufoo label.choice{
	font-size:100%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#444444;
}
.wufoo input.text, .wufoo textarea.textarea, .wufoo select.select, .wufoo input.file{
	font-size:100%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#333333;
}
.wufoo li div, .wufoo li span, .wufoo li div label, .wufoo li span label{
	font-family:inherit;
	color:#444444;
}
.safari .wufoo input.file{ /* Webkit */
	font-size:100%;
	font-family:inherit;
	color:#444444;
}
.wufoo .instruct small{
	font-size:80%;
	font-family:inherit;
	font-weight:;
	font-style:;
	color:#444444;
}
.altInstruct .instruct, .wufoo li.leftHalf .instruct, .wufoo li.rightHalf .instruct{
	background:none;
	border:none;
}
.altInstruct .instruct small, .wufoo li.leftHalf .instruct small, .wufoo li.rightHalf .instruct small{
	color:#444444;
	background:none;
	border:none;
}
.wufoo input.btTxt{
	font-size:;
	font-family:;
	font-weight:;
	font-style:;
	color:;
}

.wufoo li.focused label.desc,
.wufoo li.focused div, .wufoo li.focused span, .wufoo li.focused div label, .wufoo li.focused span label,
.safari .wufoo li.focused input.file{ 
	color:#000000;
}


.confirm h2{
	font-family:inherit;
	color:#444444;
}
a.power{
	background-color:#99cc66 !important;
	border-color:#7aa352 !important;
	color:#000000 !important;
}
.embed a.power{
	background-color:#e6e6e6 !important;
	border-color:#cccccc !important;
	color:#000000 !important;
}

/* Pagination */

.pg1 var, .pg2 var, .pg2 em, .page1 .pg2 var, .pg1 b, .wufoo .buttons .marker{
	font-family:inherit;
	color:#444444;
}

.pg1 var{
	border:1px solid #cccccc;
}
.pg1 .done var{
	background:#e6e6e6;
}

.pg1 .selected var, .pg2 var, .pg2 var em{
	background:#FFF7C0;
	color:#000000;
}
.pg1 .selected var, .pg2 td{
	border:1px solid #e6dead;
}

/* Likert Backgrounds */

.likert table{
	background-color:#FFFFFF;
}
.likert thead td, .likert thead th{
	background-color:#e6e6e6;
}
.likert tbody tr.alt td, .likert tbody tr.alt th{
	background-color:#f5f5f5;
}

/* Likert Borders */

.likert table, .likert th, .likert td{
	border-color:#dedede;
}
.likert td{
	border-left:1px solid #cccccc;
}

/* Likert Typography */

.likert caption, .likert thead td, .likert tbody th label{
	color:#444444;
	font-family:inherit;
}
.likert tbody td label{
	color:#575757;
	font-family:inherit;
}
.likert caption, .likert tbody th label{
	font-size:95%;
}

/* Likert Hover */

.likert tbody tr:hover td, .likert tbody tr:hover th, .likert tbody tr:hover label{
	background-color:#FFF7C0;
	color:#000000;
}
.likert tbody tr:hover td{
	border-left:1px solid #ccc69a;
}

/* Big Number */

.number{
	background-color:#f5f5f5;
	border-color:#e6e6e6;
}
.number strong, .number em{
	color:#000000;
}

/* ----- Field Chart Border and Background Colors ----- */

#widget{
	background:#FFFFFF;
}
.fcNav a.show{
	background-color:#FFFFFF;
	border-color:#cccccc;
}
.fc table{
	border-left:1px solid #dedede;	
}
.fc thead th, .fc .more th{
	background-color:#dedede;
	border-right:1px solid #cccccc;
}
.fc tbody td, .fc tbody th, .fc tfoot th, .fc tfoot td{
	background-color:#FFFFFF;
	border-right:1px solid #dedede;
	border-bottom:1px solid #e6e6e6;
}
.fc tbody tr.alt td, .fc tbody tr.alt th, .fc tbody td.alt{
	background-color:#f5f5f5;
}

/* ----- Field Chart Typography Colors ----- */

.fc caption, .fc tfoot,
.fc thead th, .fcNav, .fcNav a{
	color:#000000;
}
.fc tbody th div, 
.fc tbody td.count, .fc .cards tbody td a, .fc td.percent var,
.fc .timestamp span{
	color:#444444;
}
.fc .indent .count{
	color:#4b4b4b;
}
.fc .cards tbody td a span{
	color:#7d7d7d;
}

/* ----- Field Chart Hover ----- */

.fc .choices tbody tr:hover td, .fc .choices tbody tr:hover th,
.fc .data tbody tr:hover td, .fc .data tbody tr:hover th,
.fc .cards tbody td:hover{
	background-color:#FFF7C0;
}
.fc tbody tr:hover th div,
.fc tbody tr:hover td,
.fc tbody tr:hover var{
	color:#000000;
}

/* ----- Payments ----- */

.invoice thead th, 
.invoice tbody th, .invoice tbody td,
.invoice tfoot th,
.invoice .total,
.invoice tfoot .last th, .invoice tfoot .last td,
.invoice tfoot th, .invoice tfoot td{
	border-color:#dedede;
}
.invoice thead th{
	background:#f5f5f5;
}
.invoice th, .invoice td{
	color:#000000;
}
#ppSection, #ccSection{
	border-bottom:1px dotted #CCCCCC;
}
#shipSection, #invoiceSection{
	border-top:1px dotted #CCCCCC;
}

/* Drop Shadows */
#top, #bottom{
	visibility:visible;
}
