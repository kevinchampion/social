<?php
/**
 * @file
 * social_importer.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function social_importer_user_default_permissions() {
  $permissions = array();

  // Exported permission: access own authorizations.
  $permissions['access own authorizations'] = array(
    'name' => 'access own authorizations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: access own consumers.
  $permissions['access own consumers'] = array(
    'name' => 'access own consumers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: add authenticated twitter accounts.
  $permissions['add authenticated twitter accounts'] = array(
    'name' => 'add authenticated twitter accounts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'twitter',
  );

  // Exported permission: add twitter accounts.
  $permissions['add twitter accounts'] = array(
    'name' => 'add twitter accounts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'twitter',
  );

  // Exported permission: administer consumers.
  $permissions['administer consumers'] = array(
    'name' => 'administer consumers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: administer facebook import.
  $permissions['administer facebook import'] = array(
    'name' => 'administer facebook import',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'facebook_import',
  );

  // Exported permission: administer oauth.
  $permissions['administer oauth'] = array(
    'name' => 'administer oauth',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: administer social types.
  $permissions['administer social types'] = array(
    'name' => 'administer social types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'social',
  );

  // Exported permission: administer socials.
  $permissions['administer socials'] = array(
    'name' => 'administer socials',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'social',
  );

  // Exported permission: administer twitter accounts.
  $permissions['administer twitter accounts'] = array(
    'name' => 'administer twitter accounts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'twitter',
  );

  // Exported permission: clear isu_facebook feeds.
  $permissions['clear isu_facebook feeds'] = array(
    'name' => 'clear isu_facebook feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: clear isu_instagram feeds.
  $permissions['clear isu_instagram feeds'] = array(
    'name' => 'clear isu_instagram feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: clear isu_pinterest feeds.
  $permissions['clear isu_pinterest feeds'] = array(
    'name' => 'clear isu_pinterest feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: clear isu_youtube feeds.
  $permissions['clear isu_youtube feeds'] = array(
    'name' => 'clear isu_youtube feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: create social types.
  $permissions['create social types'] = array(
    'name' => 'create social types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'social',
  );

  // Exported permission: edit any facebook social.
  $permissions['edit any facebook social'] = array(
    'name' => 'edit any facebook social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: edit any instagram social.
  $permissions['edit any instagram social'] = array(
    'name' => 'edit any instagram social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: edit any pinterest social.
  $permissions['edit any pinterest social'] = array(
    'name' => 'edit any pinterest social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: edit any twitter social.
  $permissions['edit any twitter social'] = array(
    'name' => 'edit any twitter social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: edit any youtube social.
  $permissions['edit any youtube social'] = array(
    'name' => 'edit any youtube social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: import isu_facebook feeds.
  $permissions['import isu_facebook feeds'] = array(
    'name' => 'import isu_facebook feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: import isu_instagram feeds.
  $permissions['import isu_instagram feeds'] = array(
    'name' => 'import isu_instagram feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: import isu_pinterest feeds.
  $permissions['import isu_pinterest feeds'] = array(
    'name' => 'import isu_pinterest feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: import isu_youtube feeds.
  $permissions['import isu_youtube feeds'] = array(
    'name' => 'import isu_youtube feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: oauth authorize any consumers.
  $permissions['oauth authorize any consumers'] = array(
    'name' => 'oauth authorize any consumers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: oauth register any consumers.
  $permissions['oauth register any consumers'] = array(
    'name' => 'oauth register any consumers',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'oauth_common',
  );

  // Exported permission: unlock isu_facebook feeds.
  $permissions['unlock isu_facebook feeds'] = array(
    'name' => 'unlock isu_facebook feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: unlock isu_instagram feeds.
  $permissions['unlock isu_instagram feeds'] = array(
    'name' => 'unlock isu_instagram feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: unlock isu_pinterest feeds.
  $permissions['unlock isu_pinterest feeds'] = array(
    'name' => 'unlock isu_pinterest feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: unlock isu_youtube feeds.
  $permissions['unlock isu_youtube feeds'] = array(
    'name' => 'unlock isu_youtube feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: view any facebook social.
  $permissions['view any facebook social'] = array(
    'name' => 'view any facebook social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: view any instagram social.
  $permissions['view any instagram social'] = array(
    'name' => 'view any instagram social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: view any pinterest social.
  $permissions['view any pinterest social'] = array(
    'name' => 'view any pinterest social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: view any twitter social.
  $permissions['view any twitter social'] = array(
    'name' => 'view any twitter social',
    'roles' => array(),
    'module' => 'social',
  );

  // Exported permission: view any youtube social.
  $permissions['view any youtube social'] = array(
    'name' => 'view any youtube social',
    'roles' => array(),
    'module' => 'social',
  );

  return $permissions;
}
