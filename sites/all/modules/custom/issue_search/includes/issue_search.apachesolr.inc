<?php

/**
 * @file
 *  Apachesolr hooks implementations.
 */

/**
 * Implementation of hook_apachesolr_field_mappings().
 * Add index mappings for Field API types. The default mappings array handles just list fields and taxonomy term reference fields.
 * 
 * @return array
 *  An associative array of mappings as defined by modules that implement hook_apachesolr_field_mappings().
 */
function issue_search_apachesolr_field_mappings() {
    $mappings['locations'] = array(
        'indexing_callback' => 'issue_search_locations_indexing_callback',
        'multiple' => TRUE,
    );
    $mappings['has_votes'] = array(
        'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
        'index_type' => 'boolean',
        'multiple' => FALSE,
        'name' => 'has_votes',
        'module_name' => 'issue',
        'display_name' => t('Has Votes'),
        'bundles' => array('poll'),
        'field' => array(
            'field_name' => 'has_votes'
        ),
    );
    $mappings['user_votes'] = array(
        'indexing_callback' => 'issue_search_extra_fields_indexing_callback',
        'index_type' => 'integer',
        'multiple' => TRUE,
        'name' => 'user_votes',
        'module_name' => 'issue',
        'display_name' => t('User Votes'),
        'bundles' => array('poll'),
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
        'bundles' => array('poll'),
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
        'bundles' => array('poll'),
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
        'bundles' => array('poll'),
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
 * 
 * @todo
 *  Alter mappings if necessary.
 */
function issue_search_apachesolr_field_mappings_alter(&$mappings, $entity_type) {
    // TODO: alter mappings if necessary.
}

/**
 * Implementation of hook_apachesolr_field_name_map_alter().
 *  Assigns a readable name to your custom solr field.
 * 
 * @param array $map
 *  Fields map.
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
 * @param array $documents
 *  An array of already built documents.
 * @param object $entity
 *  An object containing the entity that will get indexed.
 * @param string $entity_type
 *  Entity type.
 * @param string $env_id
 *  Environment ID.
 */
function issue_search_apachesolr_index_documents_alter(array &$documents, $entity, $entity_type, $env_id) {
    
    // Add translated fields to the document's content.
    foreach ($documents as $document) {
        
        // Skip unnecessary content.
        if (($entity_type != 'node') || ($entity->type != 'poll') || ($document->entity_id != $entity->nid)) {
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

/**
 * Implementation of hook_apachesolr_query_prepare().
 * Prepare the query by adding parameters, sorts, etc.
 * This hook is invoked before the query is cached. The cached query is used after the search such as for building facet and sort blocks, so parameters added during this hook may be visible to end users.
 * This is otherwise the same as HOOK_apachesolr_query_alter(), but runs before it.
 *
 * @param DrupalSolrQueryInterface $query
 *  An object implementing DrupalSolrQueryInterface.
 */
function issue_search_apachesolr_query_prepare(DrupalSolrQueryInterface $query) {
    global $language;

    // Params.
    $query->addParam('fl', 'im_field_arguments');
    $query->addParam('fl', 'sm_field_description');
    $query->addParam('fl', 'sm_country_name');
    $query->addParam('fl', 'sm_province_name');
    $query->addParam('fl', 'sm_country_name');
    $query->addParam('fl', 'sm_city_name');
    $query->replaceParam('rows', db_result(db_query('SELECT COUNT(*) FROM {node}')));

    // Sort.
    $query->setAvailableSort('ds_created', array('title' => t('Updated'), 'default' => 'desc'));
    $query->setAvailableSort('is_views_count', array('title' => t('Views Amount'), 'default' => 'desc'));
    $query->setAvailableSort('is_votes_count', array('title' => t('Votes Amount'), 'default' => 'desc'));
    $query->setSolrsort($_POST['solrsort'], $_POST['direction']);

    // Filters.
    $query->addFilter('entity_type', 'node');
    $query->addFilter('bundle', 'poll');
    $query->addFilter('bundle_name', 'Issue');
    if ($_POST['my_language'] == 'true') {
        $subquery = apachesolr_drupal_query('apachesolr');
        $subquery->addFilter('sm_languages', $language->language);
        $subquery->addFilter('sm_languages', 'und');
        $query->addFilterSubQuery($subquery, 'OR', 'AND');
    }
}

/**
 * Implementation of hook_apachesolr_query_alter().
 * Alter the query after it's prepared and cached.
 * Any module performing a search should call drupal_alter('apachesolr_query', $query). That function then invokes this hook. It allows modules to modify the query object and its parameters.
 * A module implementing HOOK_apachesolr_query_alter() may set $query->abort_search to TRUE to flag the query to be aborted.
 * 
 * @param DrupalSolrQueryInterface $query
 *  An object implementing DrupalSolrQueryInterface
 */
function issue_search_apachesolr_query_alter(DrupalSolrQueryInterface $query) {
    global $_issue_search_user;

    // Taxonomy.
    if ($_POST['taxonomy']) {
        $subquery = apachesolr_drupal_query('apachesolr');
        $values = explode(';', $_POST['taxonomy']);
        foreach ($values as $value) {
            $subquery->addFilter('tid', $value);
        }
        $query->addFilterSubQuery($subquery, 'OR', 'AND');
    }

    // Location.
    if ($_POST['my_region'] == 'true') {
        $value = $_issue_search_user->profile_country;
        $query->addFilter('sm_country', $value);
    } else {
        if ($_POST['countrycodes']) {
            $subquery = apachesolr_drupal_query('apachesolr');
            $values = explode(';', $_POST['countrycodes']);
            foreach ($values as $value) {
                $subquery->addFilter('sm_country', $value);
            }
            $query->addFilterSubQuery($subquery, 'OR', 'AND');
        }
        if ($_POST['provincecodes']) {
            $subquery = apachesolr_drupal_query('apachesolr');
            $values = explode(';', $_POST['provincecodes']);
            foreach ($values as $value) {
                $subquery->addFilter('sm_country_province', $value);
            }
            $query->addFilterSubQuery($subquery, 'OR', 'AND');
        }
        if ($_POST['citycodes']) {
            $subquery = apachesolr_drupal_query('apachesolr');
            $values = explode(';', $_POST['citycodes']);
            foreach ($values as $value) {
                $subquery->addFilter('sm_city', $value);
            }
            $query->addFilterSubQuery($subquery, 'OR', 'AND');
        }
    }
    
    // Date.
    switch ($_POST['interval']) {
        case 'week':
            $query->addFilter('ds_created', '[' . apachesolr_date_iso(strtotime("-1 week")) . ' TO ' . apachesolr_date_iso(time()) . ']');
            break;
        case 'month':
            $query->addFilter('ds_created', '[' . apachesolr_date_iso(strtotime("-4 week")) . ' TO ' . apachesolr_date_iso(time()) . ']');
            break;
        case 'all':
        default:
            break;
    }
    
    // Votes.
    if ($_POST['not_voted'] == 'true') {
        $query->addFilter('im_user_votes', $_issue_search_user->uid, TRUE);
    }
}

/**
 * Implementation of hook_apachesolr_process_results().
 * This is invoked by apachesolr_search.module for the whole resultset returned in a search.
 *
 * @param type $results
 *  Resultset.
 * @param DrupalSolrQueryInterface $query
 *  Query.
 */
function issue_search_apachesolr_process_results(&$results, DrupalSolrQueryInterface $query) {
    // TODO: Process all resultset if necessary.
}