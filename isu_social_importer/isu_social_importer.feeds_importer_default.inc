<?php
/**
 * @file
 * isu_social_importer.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function isu_social_importer_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'isu_facebook';
  $feeds_importer->config = array(
    'name' => 'ISU Facebook',
    'description' => 'Imports ISU Facebook page feed',
    'fetcher' => array(
      'plugin_key' => 'FacebookPageFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FacebookPageParser',
      'config' => array(
        'context' => '$.data.*',
        'sources' => array(
          'jsonpath_parser:0' => '$.id',
          'jsonpath_parser:1' => '$.comments.count',
          'jsonpath_parser:2' => '$.likes.count',
          'jsonpath_parser:3' => '$.shares.count',
          'jsonpath_parser:4' => '$.type',
          'jsonpath_parser:5' => '$.message',
          'jsonpath_parser:6' => '$.created_time',
          'jsonpath_parser:7' => '$.updated_time',
          'jsonpath_parser:8' => '$.picture',
          'jsonpath_parser:9' => '$.from.id',
          'jsonpath_parser:12' => '$.id',
          'jsonpath_parser:13' => '$.from.name',
          'jsonpath_parser:14' => '$.post_url',
          'jsonpath_parser:15' => '$.page_username',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:12' => 0,
            'jsonpath_parser:13' => 0,
            'jsonpath_parser:14' => 0,
            'jsonpath_parser:15' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'SocialProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => TRUE,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'iid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'field_fb_comments',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_fb_likes',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_fb_shares',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_fb_type',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_fb_message',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_fb_created:start',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_fb_updated:start',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_fb_photo',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_fb_page_id',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'guid',
            'unique' => 1,
          ),
          11 => array(
            'source' => 'jsonpath_parser:13',
            'target' => 'field_fb_page_name',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:14',
            'target' => 'field_fb_post_url:url',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'jsonpath_parser:15',
            'target' => 'field_fb_page_username',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'facebook',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['isu_facebook'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'isu_instagram';
  $feeds_importer->config = array(
    'name' => 'ISU Instagram',
    'description' => 'Imports ISU Instagram photos.',
    'fetcher' => array(
      'plugin_key' => 'InstragramFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'InstagramParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'SocialProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => TRUE,
        'mappings' => array(
          0 => array(
            'source' => 'user_name',
            'target' => 'field_instagram_username',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'full_name',
            'target' => 'field_instagram_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'item_link',
            'target' => 'field_instagram_item_link:url',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'global_id',
            'target' => 'guid',
            'unique' => 1,
          ),
          4 => array(
            'source' => 'created',
            'target' => 'field_instagram_created:start',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'image',
            'target' => 'field_instagram_image',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'caption',
            'target' => 'field_instagram_caption',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'comments',
            'target' => 'field_instagram_comments',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'likes',
            'target' => 'field_instagram_likes',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'item_id',
            'target' => 'iid',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'instagram',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['isu_instagram'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'isu_pinterest';
  $feeds_importer->config = array(
    'name' => 'ISU Pinterest',
    'description' => 'Imports ISU Pinterest feed.',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'PinterestFeedParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'SocialProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => TRUE,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'field_pin_title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'description',
            'target' => 'field_pin_description',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'url',
            'target' => 'field_pin_link:url',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'title',
            'target' => 'field_pin_link:title',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          5 => array(
            'source' => 'url',
            'target' => 'url',
            'unique' => 1,
          ),
          6 => array(
            'source' => 'guid',
            'target' => 'iid',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'image',
            'target' => 'field_pin_image',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'timestamp',
            'target' => 'field_pin_published:start',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'username',
            'target' => 'field_pin_account_link:title',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'account_link',
            'target' => 'field_pin_account_link:url',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'filtered_html',
        'skip_hash_check' => 0,
        'bundle' => 'pinterest',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['isu_pinterest'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'isu_youtube';
  $feeds_importer->config = array(
    'name' => 'ISU YouTube',
    'description' => 'Imports ISU YouTube feed.',
    'fetcher' => array(
      'plugin_key' => 'YouTubeFeedFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'YouTubeFeedParser',
      'config' => array(
        'context' => '$.feed.entry.*',
        'sources' => array(
          'jsonpath_parser:0' => '$.id.$t',
          'jsonpath_parser:1' => '$.title.$t',
          'jsonpath_parser:2' => '$.content.$t',
          'jsonpath_parser:3' => '$.author[0].name.$t',
          'jsonpath_parser:4' => '$.title.$t',
          'jsonpath_parser:5' => '$.link[0].href',
          'jsonpath_parser:6' => '$.yt$statistics.favoriteCount',
          'jsonpath_parser:7' => '$.yt$statistics.viewCount',
          'jsonpath_parser:8' => '$.media$group.media$thumbnail[0].url',
          'jsonpath_parser:9' => '$.link[0].href',
          'jsonpath_parser:10' => '$.published.$t',
          'jsonpath_parser:11' => '$.updated.$t',
          'jsonpath_parser:12' => '$.id.$t',
          'jsonpath_parser:13' => '$.link[0].href',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:10' => 0,
            'jsonpath_parser:11' => 0,
            'jsonpath_parser:12' => 0,
            'jsonpath_parser:13' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'SocialProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => TRUE,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'iid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'field_yt_title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_yt_description',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_yt_author',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_yt_link:title',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_yt_link:url',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_yt_favorites',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_yt_views',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_yt_thumbnail',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_yt_video',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:10',
            'target' => 'field_yt_published:start',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'jsonpath_parser:11',
            'target' => 'field_yt_updated:start',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'guid',
            'unique' => 1,
          ),
          13 => array(
            'source' => 'jsonpath_parser:13',
            'target' => 'url',
            'unique' => 1,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'youtube',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['isu_youtube'] = $feeds_importer;

  return $export;
}
