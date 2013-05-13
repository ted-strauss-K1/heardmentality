<?php

/**
 * @file
 *  Functions related to Apache Solr indexing operations.
 */

/**
 * Index issues
 */
function issue_search_index_issues() {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');

  $env_id = apachesolr_default_environment();
  $limit = variable_get('apachesolr_cron_limit', 50);
  apachesolr_index_entities($env_id, $limit);
}

/**
 * Returns array containing information about fields that should be indexed.
 *
 * @param string $entity_type
 *  Entity type.
 *
 * @return array
 *  Additional Fields.
 */
function issue_search_additional_fields($entity_type = 'node')
{
  $fields[$entity_type] = array();

  $mappings = module_invoke_all('apachesolr_field_mappings');
  foreach (array_keys($mappings) as $key) {

    // Set all values with defaults.
    $defaults = array(
      'dependency plugins' => array('bundle', 'role'),
      'map callback' => FALSE,
      'name callback' => '',
      'hierarchy callback' => FALSE,
      'indexing_callback' => '',
      'index_type' => 'string',
      'facets' => FALSE,
      'facet missing allowed' => FALSE,
      'facet mincount allowed' => FALSE,
      'multiple' => TRUE,
    );
    if ($key !== 'per-field') {
      $mappings[$key] += $defaults;
    } else {
      foreach (array_keys($mappings[$key]) as $field_key) {
        $mappings[$key][$field_key] += $defaults;
      }
    }
  }

  // Allow other modules to add or alter mappings.
  drupal_alter('apachesolr_field_mappings', $mappings, $entity_type);

  // Construct pseudo-field for locations.
  $field = $mappings['locations'];
  $field['name'] = 'locations';
  $field['module_name'] = 'location';
  $field['display_name'] = t('Location');
  $field['bundles'] = array('poll');
  $field['multiple'] = TRUE;
  $field['field'] = array();
  $field['field']['field_name'] = 'locations';
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  // Construct pseudo-field for node having votes check.
  $field = $mappings['has_votes'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  // Construct pseudo-field for registering node's voters.
  $field = $mappings['user_votes'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  // Construct pseudo-field for node votes count.
  $field = $mappings['votes_count'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  // Construct pseudo-field for node views count.
  $field = $mappings['views_count'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  // Construct pseudo-field for node views count.
  $field = $mappings['languages'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }

  return $fields[$entity_type];
}

/**
 * Takes the values from the location field and tells the module where to put them.
 *
 * @param object $entity
 *   An object containing the entity that will get indexed.
 * @param string $field_name
 *   A string containing the name of the location field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return array
 *   An array containing all the fields that need to be indexed.
 */
function issue_search_locations_indexing_callback($entity, $field_name, $index_key, $field_info)
{
  $fields = array();
  if (!empty($entity->$field_name)) {
    $field_location = $entity->$field_name;
    if (!empty($field_location)) {
      foreach ($field_location as $delta => $item) {

        // Latitude / Longitude.
        if (isset($item['latitude']) && isset($item['longitude'])) {
          $fields[] = array(
            'key' => $index_key,
            'value' => implode(',', array($item['latitude'], $item['longitude'])),
          );
        }

        // Postal Code.
        if (!empty($item['postal_code'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'postal_code');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['postal_code'],
          );
        }

        // Country Code.
        if (!empty($item['country'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'country');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country'],
          );
        }

        // Country Name.
        if (!empty($item['country_name'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'country_name');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country_name'],
          );
        }

        // Province Code.
        if (!empty($item['province'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'province');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['province'],
          );
        }

        // Province Name.
        if (!empty($item['province_name'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'province_name');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['province_name'],
          );
        }

        // Country-Province code.
        if ((!empty($item['country'])) && (!empty($item['province']))) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'country_province');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country'] . '_' . $item['province'],
          );
        }

        // City Code.
        if (!empty($item['city_code'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'city_code');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['city'],
          );
        }

        // City Name.
        if (!empty($item['city'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'city');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['city'],
          );
        }
      }
    }
  }

  return $fields;
}

/**
 * Takes extra node values, tells the module where to put them.
 *
 * @param object $entity
 *   An object containing the entity that will get indexed.
 * @param string $field_name
 *   A string containing the name of the location field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return array
 *   An array containing all the fields that need to be indexed.
 */
function issue_search_extra_fields_indexing_callback($entity, $field_name, $index_key, $field_info)
{
  $fields = array();

  switch ($field_name) {
    case 'has_votes':
      $fields[] = array(
        'key' => $index_key,
        'value' => issue_search_extra_fields_indexing_has_votes($entity, $field_name, $index_key, $field_info),
      );
      break;

    case 'user_votes':
      $fields = issue_search_extra_fields_indexing_user_votes($entity, $field_name, $index_key, $field_info);
      break;

    case 'votes_count':
      $fields[] = array(
        'key' => $index_key,
        'value' => issue_search_extra_fields_indexing_votes_count($entity, $field_name, $index_key, $field_info)
      );
      break;

    case 'views_count':
      $fields[] = array(
        'key' => $index_key,
        'value' => issue_search_extra_fields_indexing_views_count($entity, $field_name, $index_key, $field_info)
      );
      break;

    case 'languages':
      $fields = issue_search_extra_fields_indexing_languages($entity, $field_name, $index_key, $field_info);
      break;

    default:
      break;
  }

  return $fields;
}

/**
 * Checks if $node has votes or not.
 *
 * @param object $node
 *   An object containing the node that will get indexed.
 * @param string $field_name
 *   A string containing the name of field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return boolean
 *      FALSE if no votes, TRUE otherwise.
 */
function issue_search_extra_fields_indexing_has_votes($node, $field_name, $index_key, $field_info)
{
  $list = issue_get_vote_status($node->nid);
  $result = (isset($list['u']) && !empty($list['u'])) ? TRUE : FALSE;

  return $result;
}

/**
 * Lists users voted on the issue.
 *
 * @param object $node
 *   An object containing the node that will get indexed.
 * @param string $field_name
 *   A string containing the name of field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return array
 *  An array of fields with user IDs of users voted.
 */
function issue_search_extra_fields_indexing_user_votes($node, $field_name, $index_key, $field_info)
{
  $fields = array();

  $list = issue_get_vote_status($node->nid);
  $uids = (isset($list['u']) && !empty($list['u'])) ? array_keys($list['u']) : array();
  foreach ($uids as $uid) {
    $fields[] = array(
      'key' => $index_key,
      'value' => $uid,
    );
  }

  return $fields;
}

/**
 * Votes amount indexer.
 *
 * @param object $node
 *   An object containing the node that will get indexed.
 * @param string $field_name
 *   A string containing the name of field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return integer
 *  Votes amount info.
 */
function issue_search_extra_fields_indexing_votes_count($node, $field_name, $index_key, $field_info)
{
  $list = issue_get_vote_status($node->nid);
  $uids = (isset($list['u']) && !empty($list['u'])) ? array_keys($list['u']) : array();

  $value = count($uids);

  return $value;
}

/**
 * Views amount indexer.
 *
 * @param object $node
 *   An object containing the node that will get indexed.
 * @param string $field_name
 *   A string containing the name of field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return integer
 *  Views amount info.
 */
function issue_search_extra_fields_indexing_views_count($node, $field_name, $index_key, $field_info)
{
  $value = (int)db_result(db_query('SELECT t.totalcount AS views FROM {node_counter} t WHERE t.nid = %d LIMIT 1', $node->nid));

  return $value;
}

/**
 * Lists languages of the issue.
 *
 * @param object $node
 *   An object containing the node that will get indexed.
 * @param string $field_name
 *   A string containing the name of field.
 * @param string $index_key
 *   A string containing the solr index field name.
 * @param array $field_info
 *   Field information.
 *
 * @return array
 *  An array of fields with language codes of the node.
 */
function issue_search_extra_fields_indexing_languages($node, $field_name, $index_key, $field_info)
{
  $fields = array();

  $languages = array();
  $query = db_query("SELECT ct.language AS langcode FROM {content_translate} ct WHERE ct.content_id = %d", $node->nid);
  while ($record = db_fetch_object($query)) {
    $languages[] = $record->langcode;
  }
  $languages[] = ($node->language == '') ? 'und' : $node->language;
  $languages = array_unique($languages);

  foreach ($languages as $language) {
    $fields[] = array(
      'key' => $index_key,
      'value' => $language,
    );
  }

  return $fields;
}