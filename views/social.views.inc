<?php

/**
 * @file
 * Providing extra functionality for the Social UI via views.
 */


/**
 * Implements hook_views_data()
 */
function social_views_data_alter(&$data) {
  $data['social']['link_social'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the social.'),
      'handler' => 'social_handler_link_field',
    ),
  );
  $data['social']['edit_social'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the social.'),
      'handler' => 'social_handler_edit_link_field',
    ),
  );
  $data['social']['delete_social'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the social.'),
      'handler' => 'social_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows socials/social/%social_id/op
  $data['social']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this social.'),
      'handler' => 'social_handler_social_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function social_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'socials';
  $view->description = 'A list of all socials';
  $view->tag = 'socials';
  $view->base_table = 'social';
  $view->human_name = 'Socials';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Social';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any social_type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'smid' => 'smid',
    'iid' => 'iid',
    'social_type' => 'social_type',
    'changed' => 'changed',
    'link_social' => 'link_social',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = 'smid';
  $handler->display->display_options['style_options']['info'] = array(
    'smid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'iid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'social_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'link_social' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['content'] = 'No socials have been created yet';
  /* Field: Social Media Entity: Internal, numeric social media entity ID */
  $handler->display->display_options['fields']['smid']['id'] = 'smid';
  $handler->display->display_options['fields']['smid']['table'] = 'social';
  $handler->display->display_options['fields']['smid']['field'] = 'smid';
  $handler->display->display_options['fields']['smid']['label'] = 'Internal ID';
  $handler->display->display_options['fields']['smid']['separator'] = '';
  /* Field: Social Media Entity: Iid */
  $handler->display->display_options['fields']['iid']['id'] = 'iid';
  $handler->display->display_options['fields']['iid']['table'] = 'social';
  $handler->display->display_options['fields']['iid']['field'] = 'iid';
  $handler->display->display_options['fields']['iid']['label'] = 'Social media item ID';
  /* Field: Social Media Entity: Social_type */
  $handler->display->display_options['fields']['social_type']['id'] = 'social_type';
  $handler->display->display_options['fields']['social_type']['table'] = 'social';
  $handler->display->display_options['fields']['social_type']['field'] = 'social_type';
  $handler->display->display_options['fields']['social_type']['label'] = 'Social type';
  /* Field: Social Media Entity: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'social';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['separator'] = '';
  /* Field: Social Media Entity: Link */
  $handler->display->display_options['fields']['link_social']['id'] = 'link_social';
  $handler->display->display_options['fields']['link_social']['table'] = 'social';
  $handler->display->display_options['fields']['link_social']['field'] = 'link_social';
  $handler->display->display_options['fields']['link_social']['label'] = 'View';
  /* Field: Social Media Entity: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'social';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['social_type']['expose']['operator_id'] = 'social_type_op';
  $handler->display->display_options['filters']['social_type']['expose']['label'] = 'Social type';
  $handler->display->display_options['filters']['social_type']['expose']['operator'] = 'social_type_op';
  $handler->display->display_options['filters']['social_type']['expose']['identifier'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'socials_admin_page');
  $handler->display->display_options['path'] = 'admin/content/socials/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Social';
  $handler->display->display_options['tab_options']['description'] = 'Manage social';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  $views[] = $view;
  return $views;

}
