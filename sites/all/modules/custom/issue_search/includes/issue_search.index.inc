<?php

/**
 * @file
 *
 * Functions related to Apache Solr indexing operations.
 */

/**
 * Returns array containing information about fields that should be indexed.
 *
 * @param type $env_id
 * @param type $entity_type
 *
 * @return array
 */
function issue_search_additional_fields($entity_type = 'node') {
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
    $field['name'] = 'has_votes';
    $field['module_name'] = 'apachesolr';
    $field['display_name'] = t('Has Votes');
    $field['bundles'] = array('poll');
    $field['multiple'] = FALSE;
    $field['field'] = array();
    $field['field']['field_name'] = 'has_votes';
    if (!empty($field['bundles'])) {
        $fields[$entity_type][apachesolr_index_key($field)] = array($field);
    }

    // Construct pseudo-field for node having votes check.
    $field = $mappings['has_votes'];
    $field['name'] = 'has_votes';
    $field['module_name'] = 'apachesolr';
    $field['display_name'] = t('User Votes');
    $field['bundles'] = array('poll');
    $field['multiple'] = FALSE;
    $field['field'] = array();
    $field['field']['field_name'] = 'user_votes';
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
 *   Array.
 *
 * @return array
 *   An array containing all the fields that needs to be indexed.
 */
function issue_search_locations_indexing_callback($entity, $field_name, $index_key, $field_info) {
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
 * Takes extra node values tells the module where to put them.
 *
 * @param string $field_name
 *   A string containing the name of the field.
 * @param string $index_key
 *   A string containing the solr index field name.
 *
 * @return array
 *   An array containing all the fields that needs to be indexed.
 */
function issue_search_extra_fields_indexing_callback($entity, $field_name, $index_key, $field_info) {
    $fields = array();

    switch ($field_name) {
        case 'has_votes':
            $fields[] = array(
                'key' => $index_key,
                'value' => issue_search_extra_fields_indexing_has_votes($entity, $field_info),
            );
            break;

        case 'has_votes':
            $fields[] = array(
                'key' => $index_key,
                'value' => issue_search_extra_fields_indexing_user_votes($entity, $field_info),
            );
            break;

        default:
            break;
    }

    return $fields;
}

/**
 * Checks if $node has votes or not.
 *
 * @param type $node
 * @param type $field_info
 *
 * @return boolean
 *      FALSE if no votes, TRUE otherwise
 */
function issue_search_extra_fields_indexing_has_votes($node, $field_name, $index_key, $field_info) {
    return FALSE;
}

/**
 * Lists users voted on the issue.
 *
 * @param type $node
 * @param type $field_info
 *
 * @return array
 *      An array of fields with user IDs of users voted.
 */
function issue_search_extra_fields_indexing_user_votes($node, $field_name, $index_key, $field_info) {
    $fields = array();

    return $fields;
}