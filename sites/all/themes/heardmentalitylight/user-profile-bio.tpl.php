<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<a class="button light <?php print $follow_status['fclass']; ?>" href="<?php print $follow_status['href']; ?>"><?php print $follow_status['status']; ?></a>
        <h2 class="din"><span class="no-white-space"><?php print $getuser->name; ?></span></h2>
        <div class="user-info">
                <p><?php print $ranking; ?></p>
                <p class="bio">
                        <?php print $settings['bio']; ?>
                </p>
                 <?php if($settings['mywebsite']): ?>
                <span class="URL"><?php print t('Web'); ?>: <a href="<?php print $settings['mywebsite']; ?>" target="_blank"><?php print $settings['mywebsite']; ?></a></span>,
                <?php endif; ?>
                <?php if($settings['email']): ?>
                <span class="URL"><?php print t('Email'); ?>: <?php print $settings['email']; ?></span>,
                <?php endif; ?>
                <?php if($settings['twitter']): ?>
                <span class="URL"><?php print t('Twitter'); ?>: <a href="<?php print $settings['twitter']; ?>" target="_blank"><?php print $settings['twitter']; ?></a></span>,
                <?php endif; ?>
                <?php if($settings['facebook']): ?>
                <span class="URL"><?php print t('Facebook'); ?>: <a href="<?php print $settings['facebook']; ?>" target="_blank"><?php print $settings['facebook']; ?></a></span>
                <?php endif; ?>
                <?php if($settings['other_links']):
                    foreach($settings['other_links'] as $name => $url) {?>
                    <span class="URL"><?php print ucwords(t($name)); ?>: <a href="<?php print $url; ?>" target="_blank"><?php print $url; ?></a></span>
                    <?php }?>
                <?php endif; ?>
        </div>