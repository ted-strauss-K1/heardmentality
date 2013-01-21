<?php
// root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<div id="stream-<?php print $nid; ?>">
<li>
        <?php print $issue; ?>?
        <a href="<?php print $sitelink.'moderator/issues/edit/'.$nid; ?>" title="Moderate"><input type="button" value="Moderate" class="remove" /></a>
        <input type="button" onclick="mod_hide_issue('<?php print $nid; ?>')" value="hide" class="remove" />
        <div class="clear"></div>
</li>
</div>