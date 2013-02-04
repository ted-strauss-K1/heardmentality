<?php

/**
 * @file
 *
 * Apachesolr API implementations.
 */

/**
 * Implementation of hook_apachesolr_field_mappings().
 *
 * @return array
 *   $mappings is an array containing all the field mappings.
 */
function issue_search_apachesolr_field_mappings() {
    $mappings['locations'] = array(
        'indexing_callback' => 'issue_search_locations_indexing_callback',
        'multiple' => TRUE,
    );
    $mappings['has_votes'] = array(
        'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
        'index_type' => 'boolean',
        'multiple' => TRUE,
    );

    return $mappings;
}

/**
 * Implementation of hook_apachesolr_field_mappings_alter().
 *
 * @param type $mappings
 * @param type $entity_type
 */
function issue_search_apachesolr_field_mappings_alter(&$mappings, $entity_type) {

}

/**
 * Implementation of hook_apachesolr_field_name_map_alter().
 *
 * @param array $map
 */
function issue_search_apachesolr_field_name_map_alter(&$map) {
    $map['sm_locations'] = t('Latitude / Longitude');
    $map['sm_postal_code'] = t('Postal Code');
    $map['sm_country'] = t('Country Code');
    $map['sm_country_name'] = t('Country Name');
    $map['sm_province'] = t('Province Code');
    $map['sm_province_name'] = t('Province Name');
    $map['sm_city_code'] = t('City Code');
    $map['sm_city'] = t('City Name');
}

/**
 * Implementation of hook_apachesolr_index_document_build().
 *
 * @param ApacheSolrDocument $document
 * @param type $entity
 * @param type $entity_type
 * @param type $env_id
 */
function issue_search_apachesolr_index_document_build(ApacheSolrDocument $document, $entity, $entity_type, $env_id) {
    module_load_include('inc', 'issue_search', 'includes/issue_search.index');

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
                if ($function && function_exists($function)) {

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
 *
 * @param array $documents
 * @param type $entity
 * @param type $entity_type
 * @param type $env_id
 */
function issue_search_apachesolr_index_documents_alter(array &$documents, $entity, $entity_type, $env_id) {

}

/**
 * Implementation of hook_apachesolr_query_prepare().
 *
 * @param type $query
 */
function issue_search_apachesolr_query_prepare($query) {
    // Add a sort on the node ID.
    $query->setAvailableSort('entity_id', array(
        'title' => t('Node ID'),
        'default' => 'asc',
    ));
}

/**
 * Implementation of hook_apachesolr_query_alter().
 *
 * @param type $query
 */
function issue_search_apachesolr_query_alter($query) {
    // todo
    $sort = 0;
    switch ($sort) {
        case 2 : //

        case 'Votes':
            $query->setSolrsort('itm_field_votes_count', 'desc');
            break;
        case 'Latest':
            $query->setSolrsort('ds_created', 'desc');
            break;
        case 'Views':
            $query->setSolrsort('itm_field_visits_count', 'desc');
            break;

        default:
            $query->setSolrsort('itm_field_votes_count', 'desc');
            break;
    }
}

/**
 * Implementation of hook_apachesolr_process_results().
 *
 * @param type $results
 * @param DrupalSolrQueryInterface $query
 */
function issue_search_apachesolr_process_results(&$results, DrupalSolrQueryInterface $query) {

}

/**
 * Implementation of hook_apachesolr_search_result_alter().
 *
 * @param type $document
 * @param type $extra
 * @param DrupalSolrQueryInterface $query
 */
function issue_search_apachesolr_search_result_alter($document, &$extra, DrupalSolrQueryInterface $query) {

}
