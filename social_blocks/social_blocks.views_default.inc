<?php
/**
 * @file
 * social_blocks.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function social_blocks_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'social';
  $view->description = 'Contains blocks with most recent item from each social media source';
  $view->tag = 'default';
  $view->base_table = 'social';
  $view->human_name = 'ISU Social';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'social_block';
  /* Field: Social Media Entity: Internal, numeric social media entity ID */
  $handler->display->display_options['fields']['smid']['id'] = 'smid';
  $handler->display->display_options['fields']['smid']['table'] = 'social';
  $handler->display->display_options['fields']['smid']['field'] = 'smid';
  /* Field: Social Media Entity: Published */
  $handler->display->display_options['fields']['field_yt_published']['id'] = 'field_yt_published';
  $handler->display->display_options['fields']['field_yt_published']['table'] = 'field_data_field_yt_published';
  $handler->display->display_options['fields']['field_yt_published']['field'] = 'field_yt_published';
  $handler->display->display_options['fields']['field_yt_published']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Sort criterion: Social Media Entity: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'social';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'facebook' => 'facebook',
  );

  /* Display: YouTube Block */
  $handler = $view->new_display('block', 'YouTube Block', 'block');
  $handler->display->display_options['display_description'] = 'Single most recent YouTube video block';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'social_block';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Published (field_yt_published) */
  $handler->display->display_options['sorts']['field_yt_published_value']['id'] = 'field_yt_published_value';
  $handler->display->display_options['sorts']['field_yt_published_value']['table'] = 'field_data_field_yt_published';
  $handler->display->display_options['sorts']['field_yt_published_value']['field'] = 'field_yt_published_value';
  $handler->display->display_options['sorts']['field_yt_published_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'youtube' => 'youtube',
  );

  /* Display: Facebook Block */
  $handler = $view->new_display('block', 'Facebook Block', 'block_1');
  $handler->display->display_options['display_description'] = 'Single most recent Facebook post block';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'social_block';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Updated (field_fb_updated) */
  $handler->display->display_options['sorts']['field_fb_updated_value']['id'] = 'field_fb_updated_value';
  $handler->display->display_options['sorts']['field_fb_updated_value']['table'] = 'field_data_field_fb_updated';
  $handler->display->display_options['sorts']['field_fb_updated_value']['field'] = 'field_fb_updated_value';
  $handler->display->display_options['sorts']['field_fb_updated_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'facebook' => 'facebook',
  );
  /* Filter criterion: Social Media Entity: Message (field_fb_message) */
  $handler->display->display_options['filters']['field_fb_message_value']['id'] = 'field_fb_message_value';
  $handler->display->display_options['filters']['field_fb_message_value']['table'] = 'field_data_field_fb_message';
  $handler->display->display_options['filters']['field_fb_message_value']['field'] = 'field_fb_message_value';
  $handler->display->display_options['filters']['field_fb_message_value']['operator'] = 'not empty';

  /* Display: Pinterest Block */
  $handler = $view->new_display('block', 'Pinterest Block', 'block_2');
  $handler->display->display_options['display_description'] = 'Single most recent Pinterest pin block';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Published (field_pin_published) */
  $handler->display->display_options['sorts']['field_pin_published_value']['id'] = 'field_pin_published_value';
  $handler->display->display_options['sorts']['field_pin_published_value']['table'] = 'field_data_field_pin_published';
  $handler->display->display_options['sorts']['field_pin_published_value']['field'] = 'field_pin_published_value';
  $handler->display->display_options['sorts']['field_pin_published_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'pinterest' => 'pinterest',
  );

  /* Display: Twitter Block */
  $handler = $view->new_display('block', 'Twitter Block', 'block_3');
  $handler->display->display_options['display_description'] = 'Single most recent tweet block';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Created (field_tw_created) */
  $handler->display->display_options['sorts']['field_tw_created_value']['id'] = 'field_tw_created_value';
  $handler->display->display_options['sorts']['field_tw_created_value']['table'] = 'field_data_field_tw_created';
  $handler->display->display_options['sorts']['field_tw_created_value']['field'] = 'field_tw_created_value';
  $handler->display->display_options['sorts']['field_tw_created_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'twitter' => 'twitter',
  );

  /* Display: Social pane */
  $handler = $view->new_display('panel_pane', 'Social pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'all' => 'all',
    'instagram' => 'instagram',
    'facebook' => 'facebook',
    'pinterest' => 'pinterest',
    'twitter' => 'twitter',
    'youtube' => 'youtube',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );

  /* Display: Facebook pane */
  $handler = $view->new_display('panel_pane', 'Facebook pane', 'panel_pane_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent Facebook social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Updated (field_fb_updated) */
  $handler->display->display_options['sorts']['field_fb_updated_value']['id'] = 'field_fb_updated_value';
  $handler->display->display_options['sorts']['field_fb_updated_value']['table'] = 'field_data_field_fb_updated';
  $handler->display->display_options['sorts']['field_fb_updated_value']['field'] = 'field_fb_updated_value';
  $handler->display->display_options['sorts']['field_fb_updated_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'facebook' => 'facebook',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );

  /* Display: Twitter pane */
  $handler = $view->new_display('panel_pane', 'Twitter pane', 'panel_pane_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent Twitter social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Created (field_tw_created) */
  $handler->display->display_options['sorts']['field_tw_created_value']['id'] = 'field_tw_created_value';
  $handler->display->display_options['sorts']['field_tw_created_value']['table'] = 'field_data_field_tw_created';
  $handler->display->display_options['sorts']['field_tw_created_value']['field'] = 'field_tw_created_value';
  $handler->display->display_options['sorts']['field_tw_created_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'twitter' => 'twitter',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );

  /* Display: YouTube pane */
  $handler = $view->new_display('panel_pane', 'YouTube pane', 'panel_pane_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent YouTube social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Updated (field_yt_updated) */
  $handler->display->display_options['sorts']['field_yt_updated_value']['id'] = 'field_yt_updated_value';
  $handler->display->display_options['sorts']['field_yt_updated_value']['table'] = 'field_data_field_yt_updated';
  $handler->display->display_options['sorts']['field_yt_updated_value']['field'] = 'field_yt_updated_value';
  $handler->display->display_options['sorts']['field_yt_updated_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'youtube' => 'youtube',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );

  /* Display: Pinterest pane */
  $handler = $view->new_display('panel_pane', 'Pinterest pane', 'panel_pane_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent Pinterest social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Published (field_pin_published) */
  $handler->display->display_options['sorts']['field_pin_published_value']['id'] = 'field_pin_published_value';
  $handler->display->display_options['sorts']['field_pin_published_value']['table'] = 'field_data_field_pin_published';
  $handler->display->display_options['sorts']['field_pin_published_value']['field'] = 'field_pin_published_value';
  $handler->display->display_options['sorts']['field_pin_published_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'pinterest' => 'pinterest',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );

  /* Display: Instagram Block */
  $handler = $view->new_display('block', 'Instagram Block', 'block_4');
  $handler->display->display_options['display_description'] = 'Single most recent Instagram post block';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'social_block';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Created (field_instagram_created) */
  $handler->display->display_options['sorts']['field_instagram_created_value']['id'] = 'field_instagram_created_value';
  $handler->display->display_options['sorts']['field_instagram_created_value']['table'] = 'field_data_field_instagram_created';
  $handler->display->display_options['sorts']['field_instagram_created_value']['field'] = 'field_instagram_created_value';
  $handler->display->display_options['sorts']['field_instagram_created_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'instagram' => 'instagram',
  );

  /* Display: Instagram pane */
  $handler = $view->new_display('panel_pane', 'Instagram pane', 'panel_pane_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'ISU Social';
  $handler->display->display_options['display_description'] = 'Displays most recent Instagram social items';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Social Media Entity: Created (field_instagram_created) */
  $handler->display->display_options['sorts']['field_instagram_created_value']['id'] = 'field_instagram_created_value';
  $handler->display->display_options['sorts']['field_instagram_created_value']['table'] = 'field_data_field_instagram_created';
  $handler->display->display_options['sorts']['field_instagram_created_value']['field'] = 'field_instagram_created_value';
  $handler->display->display_options['sorts']['field_instagram_created_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Topics (field_tags) */
  $handler->display->display_options['arguments']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['arguments']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['arguments']['field_tags_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_tags_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags_tid']['validate']['type'] = 'panels_term_reference';
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags_tid']['validate_options']['type'] = 'tids';
  $handler->display->display_options['arguments']['field_tags_tid']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Social Media Entity: Social_type */
  $handler->display->display_options['filters']['social_type']['id'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['table'] = 'social';
  $handler->display->display_options['filters']['social_type']['field'] = 'social_type';
  $handler->display->display_options['filters']['social_type']['value'] = array(
    'instagram' => 'instagram',
  );
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_tags_tid' => array(
      'type' => 'context',
      'context' => 'entity:node.field_tags',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field: Topic/s (field_tags)',
    ),
  );
  $export['social'] = $view;

  return $export;
}
