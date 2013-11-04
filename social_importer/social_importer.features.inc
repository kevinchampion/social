<?php
/**
 * @file
 * social_importer.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function social_importer_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_social_type().
 */
function social_importer_default_social_type() {
  $items = array();
  $items['facebook'] = entity_import('social_type', '{
    "type" : "facebook",
    "label" : "Facebook",
    "weight" : "0",
    "data" : { "sample_data" : 0 },
    "rdf_mapping" : []
  }');
  $items['instagram'] = entity_import('social_type', '{
    "type" : "instagram",
    "label" : "Instagram",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  $items['pinterest'] = entity_import('social_type', '{
    "type" : "pinterest",
    "label" : "Pinterest",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  $items['twitter'] = entity_import('social_type', '{
    "type" : "twitter",
    "label" : "Twitter",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  $items['youtube'] = entity_import('social_type', '{
    "type" : "youtube",
    "label" : "YouTube",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  return $items;
}
