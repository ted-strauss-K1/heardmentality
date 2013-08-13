<?php

/**
 * Implementation of hook_menu()
 *
 * @return array
 */
function badges_pages_menu()
{
  $menu = array();

  $menu['badges'] = array(
    'title' => t('Badges'),
    'page callback' => 'theme',
    'page arguments' => array('badges_list'),
    'access callback' => TRUE,
  );
  $menu['badges/users'] = array(
    'title' => t('Badges'),
    'page callback' => 'theme',
    'page arguments' => array('badges_list_users'),
    'access callback' => TRUE,
  );

  return $menu;
}

/**
 * Implementation of hook_theme()
 *
 * @return array
 */
function badges_theme()
{
  $theme = array();

  $theme['badges_list'] = array(
    'arguments' => array('sort' => 0),
  );
  $theme['badges_list_users'] = array(
    'arguments' => array(),
  );

  return $theme;
}

/**
 * Theme for badges list
 *
 * @code sort 0 -- by count DESC
 * @code sort 1 -- by count ASC
 * @code sort 2 -- by name DESC, count DESC
 * @code sort 3 -- by name ASC, count DESC
 *
 * @return string
 */
function theme_badges_list($sort = 2)
{
//  $output = '<div class="badges">';
  $output = '<div id="about_us_page_content"><div id="badges">
    <table border="0" cellspacing="0" cellpadding="0" id="badgeslist">
      <thead>
        <tr>
          <th class="small">' . t('Type') . '/' . t('Count') . '</th>
          <th class="medium">' . t('Name') . '</th>
          <th class="large">' . t('Description') . '</th>
        </tr>
      </thead>
      <tbody>';

  $query = "SELECT badge name, COUNT(*) count FROM {badges} GROUP BY badge ";

//  $sort = 2;
  switch ($sort) {
    case 0:
      $query .= "ORDER BY COUNT(*) DESC";
      break;
    case 1:
      $query .= "ORDER BY COUNT(*) ASC";
      break;
    case 2:
    case 3:
      $keys = array_keys(badges_types());
      $keys = array_flip($keys);
      $query .= 'ORDER BY (CASE badge WHEN 0 THEN 0 ';
      $i = -1;

      foreach (badges_list() as $name => $info) {
        $i++;
        $query .= sprintf("WHEN '%s' THEN %d ", $name, ($sort == 2 ? -1 : 1) * $keys[$info['type']]);
      }
      $query .= 'ELSE ' . $i . ' END) ASC, COUNT(*) DESC';
      break;
  }

  $badges = badges_list();
  $result = db_query($query);
  while ($badge = db_fetch_object($result)) {
    $badge_item = $badges[$badge->name];
    if (!$badge_item) {
      continue;
    }
    $output .= sprintf('
        <tr>
          <td><span class="%s medal3" title="%s">&nbsp;</span> x %d</td>
          <td>%s</td>
          <td>%s</td>
        </tr>
      ', $badge_item['type'], t(badges_types($badge_item['type']) . ' Medal'), $badge->count - 1, $badge_item['name'], $badge_item['info']
    );
  }
//  $output .= '</div>';
  $output .= '</tbody></table></div></div>';
  return $output;
}

/**
 * Theme for badges list for users
 *
 * @return string
 */
function theme_badges_list_users()
{
  $output = '<div id="badges_list_userbadges"><ul>';

  $badges_userbadges = badges_userbadges(FALSE);

//  var_dump($badges_userbadges);

  foreach ($badges_userbadges as $uid => $data) {
    $output .= '<li><a href="/user/profile/view/' . $uid . '">' . $data['#name'] . '</a>:&nbsp;';

    foreach ($data['#list'] as $name => $info) {
      $output .= sprintf('<span class="selected-item %s">%s<span class="count-item">x</span><span class="number-item">%d</span></span>',
        $info['type'], $info['name'], $info['#count']
      );
    }

    $output .= '</li>';
  }

  $output .= '</ul></div>';
  return $output;
}