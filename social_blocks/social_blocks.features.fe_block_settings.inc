<?php
/**
 * @file
 * social_blocks.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function social_blocks_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['social_blocks-isu-mobile'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'isu-mobile',
    'module' => 'social_blocks',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'isu_primary' => array(
        'region' => 'footer_3',
        'status' => '1',
        'theme' => 'isu_primary',
        'weight' => '-32',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['social_blocks-social-links'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'social-links',
    'module' => 'social_blocks',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'isu_primary' => array(
        'region' => 'footer_4',
        'status' => '1',
        'theme' => 'isu_primary',
        'weight' => '-32',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  return $export;
}
