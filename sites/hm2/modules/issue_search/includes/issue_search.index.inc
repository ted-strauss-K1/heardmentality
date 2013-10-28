<?php

/**
 * @param $nid
 */
function issue_search_index_node($nid)
{
  @db_query("UPDATE {apachesolr_index_entities_node} SET changed = %d WHERE entity_id = %d", time(), $nid);
  issue_search_index_issues();
}

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
 * Implementation of hook_apachesolr_field_mappings().
 * Add index mappings for Field API types. The default mappings array handles just list fields and taxonomy term reference fields.
 *
 * @return array
 *  An associative array of mappings as defined by modules that implement hook_apachesolr_field_mappings().
 */
function issue_search_apachesolr_field_mappings()
{
  $mappings['locations'] = array(
    'indexing_callback' => 'issue_search_locations_indexing_callback',
    'multiple' => TRUE,
  );
  $mappings['user_votes'] = array(
    'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
    'index_type' => 'integer',
    'multiple' => TRUE,
    'name' => 'user_votes',
    'module_name' => 'issue',
    'display_name' => t('User Votes'),
    'bundles' => array('issue'),
    'field' => array(
      'field_name' => 'user_votes'
    ),
  );
  $mappings['votes_count'] = array(
    'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
    'index_type' => 'integer',
    'multiple' => FALSE,
    'name' => 'votes_count',
    'module_name' => 'issue',
    'display_name' => t('Votes Amount'),
    'bundles' => array('issue'),
    'field' => array(
      'field_name' => 'votes_count'
    ),
  );
  $mappings['views_count'] = array(
    'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
    'index_type' => 'integer',
    'multiple' => FALSE,
    'name' => 'views_count',
    'module_name' => 'issue',
    'display_name' => t('Views Amount'),
    'bundles' => array('issue'),
    'field' => array(
      'field_name' => 'views_count'
    ),
  );
  $mappings['languages'] = array(
    'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
    'index_type' => 'string',
    'multiple' => TRUE,
    'name' => 'languages',
    'module_name' => 'issue',
    'display_name' => t('Node Languages'),
    'bundles' => array('issue'),
    'field' => array(
      'field_name' => 'languages'
    ),
  );

  return $mappings;
}

/**
 * Implementation of hook_apachesolr_field_mappings_alter().
 * Add or alter index mappings for Field API types. The default mappings array handles just list fields and taxonomy term reference fields, in the same way as documented in hook_apachesolr_field_mappings.
 *
 * @param array $mappings
 *  An associative array of mappings as defined by modules that implement hook_apachesolr_field_mappings().
 * @param string $entity_type
 *  Entity type.
 */
function issue_search_apachesolr_field_mappings_alter(&$mappings, $entity_type)
{
  //
}

/**
 * Implementation of hook_apachesolr_field_name_map_alter().
 *  Assigns a readable name to your custom solr field.
 *
 * @param array $map
 *  Fields map.
 */
function issue_search_apachesolr_field_name_map_alter(&$map)
{
  $map['sm_location_codes'] = t('Location Codes');
  $map['sm_latitude_longitude'] = t('Latitude / Longitude');
  $map['sm_postal_code'] = t('Postal Code');
  $map['sm_country'] = t('Country Code');
  $map['sm_country_name'] = t('Country Name');
  $map['sm_province'] = t('Province Code');
  $map['sm_province_name'] = t('Province Name');
  $map['sm_city'] = t('City Code');
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
  $field['bundles'] = array('issue');
  $field['multiple'] = TRUE;
  $field['field'] = array();
  $field['field']['field_name'] = 'locations';
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

  /*
  // Construct pseudo-field for node having votes check.
  $field = $mappings['has_votes'];
  if (!empty($field['bundles'])) {
    $fields[$entity_type][apachesolr_index_key($field)] = array($field);
  }


  */

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

        if (isset($item['name'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'location_codes',
          );
          $field_index_key = apachesolr_index_key($field);

          $codes = explode('_', $item['name'], 3);
          $code = '';
          for ($i=0; $i<count($codes); $i++) {
            $code .= (0!=$i ? '_' : '') . $codes[$i];
            $fields[] = array(
              'key' => $field_index_key,
              'value' => $code,
            );
          }
        }

        // Latitude / Longitude.
        if (isset($item['latitude']) && isset($item['longitude'])) {
          if (0 != $item['latitude'] || 0 != $item['longitude']) {
            $field = array(
              'index_type' => $field_info['index_type'],
              'multiple' => $field_info['multiple'],
              'name' => 'latitude_longitude',
            );
            $field_index_key = apachesolr_index_key($field);
            $fields[] = array(
              'key' => $field_index_key,
              'value' => implode(',', array($item['latitude'], $item['longitude'])),
            );
          }
        }

        // Postal Code.
        if (!empty($item['postal_code'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'postal_code'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['postal_code'],
          );
        }

        // Country Code.
        if (!empty($item['country'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'country'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country'],
          );
        }

        // Country Name.
        if (!empty($item['country_name'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'country_name'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country_name'],
          );
        }

        // Province Code.
        if (!empty($item['province'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'province'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country'] . '_' . $item['province'],
          );
        }

        // Province Name.
        if (!empty($item['province_name'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'province_name'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['province_name'],
          );
        }

        // City Code.
        if (!empty($item['city'])) {
          $field = array(
            'index_type' => $field_info['index_type'],
            'multiple' => $field_info['multiple'],
            'name' => 'city'
          );
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['country'] . '_' . $item['province'] . '_' . $item['city'],
          );
        }

        // City Name.
        // todo city name indexing
        /*
        if (!empty($item['city'])) {
          $field = array('index_type' => $field_info['index_type'], 'multiple' => $field_info['multiple'], 'name' => 'city');
          $field_index_key = apachesolr_index_key($field);
          $fields[] = array(
            'key' => $field_index_key,
            'value' => $item['city'],
          );
        }
        */


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

  if ($choices = cpoll_load_choices($node->nid)) {
    foreach ($choices as $choice) {
      foreach ($choice['uids'] as $uid) {
        $fields[] = array(
          'key' => $index_key,
          'value' => $uid,
        );
      }
    }
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
  $votes = 0;

  if ($choices = cpoll_load_choices($node->nid)) {
    foreach ($choices as $choice) {
      $votes += $choice['votes'];
    }
  }

  return $votes;
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
  $query = db_query("SELECT ct.language AS langcode FROM {content_translate} ct WHERE ct.content_type = 'node' AND ct.content_id = %d", $node->nid);
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

/**
 * Implementation of hook_apachesolr_index_document_build().
 * Build the documents before sending them to Solr. The function is the follow-up for apachesolr_update_index.
 *
 * @param ApacheSolrDocument $document
 *  Document object: maps fields and values.
 * @param object $entity
 *  An object containing the entity that will get indexed.
 * @param string $entity_type
 *  Entity type.
 * @param string $env_id
 *  Environment ID.
 */
function issue_search_apachesolr_index_document_build(ApacheSolrDocument $document, $entity, $entity_type, $env_id)
{
  $fields = array();

  // Get fields for indexing.
  $indexed_fields = issue_search_additional_fields($entity_type);
  foreach ($indexed_fields as $index_key => $nodefields) {
    if (!empty($nodefields)) {
      foreach ($nodefields as $field_info) {
        if (is_array($field_info['field'])) {
          $field_name = $field_info['field']['field_name'];
        }

        $function = $field_info['indexing_callback'];
        if ($function && function_exists($function) && in_array($entity->type, $field_info['bundles'])) {

          // NOTE: This function should always return an array. One entity field may be indexed to multiple Solr fields.
          $fields = array_merge($fields, $function($entity, $field_name, $index_key, $field_info));
        }
      }
    }
  }

  foreach ($fields as $field) {
    $document->addField($field['key'], $field['value']);
  }
}

/**
 * Implementation of hook_apachesolr_index_documents_alter().
 * Alter the prepared documents from one entity before sending them to Solr.
 *
 * @todo better way to index translations
 *
 * @param array $documents
 *  An array of already built documents.
 * @param object $entity
 *  An object containing the entity that will get indexed.
 * @param string $entity_type
 *  Entity type.
 * @param string $env_id
 *  Environment ID.
 */
function issue_search_apachesolr_index_documents_alter(array &$documents, $entity, $entity_type, $env_id)
{

  // Add translated fields to the document's content.
  foreach ($documents as $document) {

    // Skip unnecessary content.
    if (($entity_type != 'node') || ($entity->type != 'issue') || ($document->entity_id != $entity->nid)) {
      continue;
    }

    // Get existing content.
    $content = $document->content;

    // Get translations to add.
    $fields = array();
    $query = db_query("SELECT ct.text AS text FROM {content_translate} ct WHERE ct.content_id = %d", $entity->nid);
    while ($record = db_fetch_object($query)) {
      $fields[] = $record->text;
    }

    // Extend content.
    foreach ($fields as $field) {
      $content .= ' ' . $field;
    }

    // Set new content.
    $document->content = $content;
  }
}