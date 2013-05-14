<?php
/**
 * @file
 * isu_social_importer.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function isu_social_importer_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_social_type().
 */
function isu_social_importer_default_social_type() {
  $items = array();
  $items['facebook'] = entity_import('social_type', '{
    "type" : "facebook",
    "label" : "Facebook",
    "weight" : "0",
    "data" : { "sample_data" : 0 }
  }');
  $items['instagram'] = entity_import('social_type', '{
    "type" : "instagram",
    "label" : "Instagram",
    "weight" : "0",
    "data" : ""
  }');
  $items['pinterest'] = entity_import('social_type', '{
    "type" : "pinterest",
    "label" : "Pinterest",
    "weight" : "0",
    "data" : ""
  }');
  $items['twitter'] = entity_import('social_type', '{ "type" : "twitter", "label" : "Twitter", "weight" : "0", "data" : "" }');
  $items['youtube'] = entity_import('social_type', '{ "type" : "youtube", "label" : "YouTube", "weight" : "0", "data" : "" }');
  return $items;
}
