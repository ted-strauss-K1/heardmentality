<script type="text/javascript">
function loadTempPath(pmPath)
{
	window.parent.document.getElementById("docpath").value=pmPath;
	
}
</script>
<?PHP
echo $gSitePath;
if($_FILES)
{
	 $vTempPath=$_FILES["fileupload"]['tmp_name'];
	$vDate=date("d-m-y",time());
	$vDir="mediadoc/".$vDate."/";
	if(!is_dir($vDir))
	{
	
		mkdir($vDir,0777);
	}
	 $vFile=$vDir.rand().$_FILES["fileupload"]['name'];
	
	copy($vTempPath,$vFile);
	?>
		<script type="text/javascript">
			loadTempPath('<?php echo($vFile);?>')
		</script>
	<?php
}
?>
<style type="text/css">
body{
margin-left:0px;
margin-top:0px;
}
input.hide
	{
		position:absolute;
		left:-135px;
		-moz-opacity:0 ;
		filter:alpha(opacity: 0);
		opacity: 0;
		z-index: 2;/**/
		top:0px;
		border:thin solid #0000CC;
	}

input.red
	{
		background-image:url(buttons/b-upload-menu.jpg);
		z-index:1;
		left:0px;
		top:0px;
	}
</style>

<script type="text/javascript">
function buttonPush ()
{
	var x = document.getElementsByTagName('input');
	for (var i=0;i<x.length;i++) 
	{
		if (x[i].type != 'file') continue;
		x[i].onchange = function () {
			if(this.value != '')
			{
				vPath=this.value;
				vLen=vPath.length;
				vPos=vPath.indexOf(".")
				vSubStr=vPath.substring(vPos,vLen);
				if(vSubStr != ".pdf" && vSubStr != ".doc" && vSubStr != ".docx" && vSubStr != ".ppt"  && vSubStr != ".ppts")
				{
					alert("Please upload PDF, DOC, PPT file.")
					return false;
				}
				else
				{
					document.frmUploader.submit();
				}
			}
		}
	}
}
</script>
<form action="" name="frmUploader" id="frmUploader" method="post" enctype="multipart/form-data" onSubmit="return false;">
<input type="file" class="hide" type="file" name="fileupload" style="cursor:pointer;" />
<input type="submit" class="red" id="pseudobutton" value="Upload Document" onClick="return false;" style="cursor:pointer;">
 
</form>
<script type="text/javascript">
buttonPush ()
</script>