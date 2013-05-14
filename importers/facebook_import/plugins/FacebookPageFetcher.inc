<?php

/**
 * @file
 * Home of the FeedsHTTPFetcher and related classes.
 */

feeds_include_library('PuSHSubscriber.inc', 'PuSHSubscriber');

/**
 * Result of FeedsHTTPFetcher::fetch().
 */
class FacebookPageFetcherResult extends FeedsHTTPFetcherResult {

  /**
   * Overrides FeedsFetcherResult::getRaw();
   */
  public function getRaw() {
    feeds_include_library('http_request.inc', 'http_request');
    $result = http_request_get($this->url, NULL, NULL, NULL, $this->timeout);
    if (!in_array($result->code, array(200, 201, 202, 203, 204, 205, 206))) {
      throw new Exception(t('Download of @url failed with code !code.', array('@url' => $this->url, '!code' => $result->code)));
    }
    return $this->sanitizeRaw($result->data);
  }

}

/**
 * Fetches data via HTTP.
 */
class FacebookPageFetcher extends FeedsHTTPFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    if ($this->config['use_pubsubhubbub'] && ($raw = $this->subscriber($source->feed_nid)->receive())) {
      return new FeedsFetcherResult($raw);
    }
    $fetcher_result = new FacebookPageFetcherResult($source_config['source']);
    // When request_timeout is empty, the global value is used.
    $fetcher_result->setTimeout($this->config['request_timeout']);
    return $fetcher_result;
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'auto_detect_feeds' => FALSE,
      'use_pubsubhubbub' => FALSE,
      'designated_hub' => '',
      'request_timeout' => NULL,
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    $form['auto_detect_feeds'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto detect feeds'),
      '#description' => t('If the supplied URL does not point to a feed but an HTML document, attempt to extract a feed URL from the document.'),
      '#default_value' => $this->config['auto_detect_feeds'],
    );
    $form['use_pubsubhubbub'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use PubSubHubbub'),
      '#description' => t('Attempt to use a <a href="http://en.wikipedia.org/wiki/PubSubHubbub">PubSubHubbub</a> subscription if available.'),
      '#default_value' => $this->config['use_pubsubhubbub'],
    );
    $form['designated_hub'] = array(
      '#type' => 'textfield',
      '#title' => t('Designated hub'),
      '#description' => t('Enter the URL of a designated PubSubHubbub hub (e. g. superfeedr.com). If given, this hub will be used instead of the hub specified in the actual feed.'),
      '#default_value' => $this->config['designated_hub'],
      '#dependency' => array(
        'edit-use-pubsubhubbub' => array(1),
      ),
    );
   // Per importer override of global http request timeout setting.
   $form['request_timeout'] = array(
     '#type' => 'textfield',
     '#title' => t('Request timeout'),
     '#description' => t('Timeout in seconds to wait for an HTTP get request to finish.</br>' .
                         '<b>Note:</b> this setting will override the global setting.</br>' .
                         'When left empty, the global value is used.'),
     '#default_value' => $this->config['request_timeout'],
     '#element_validate' => array('element_validate_integer_positive'),
     '#maxlength' => 3,
     '#size'=> 30,
   );
    return $form;
  }

  /**
   * Expose source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['fb_page'] = array(
      '#type' => 'textfield',
      '#title' => t('Facebook page name'),
      '#description' => t('The user or account name. This is the name appended to the url of the facebook page: http://www.facebook.com/[name]'),
      '#default_value' => isset($source_config['fb_page']) ? $source_config['fb_page'] : '',
      '#maxlength' => NULL,
      '#required' => TRUE,
    );
    $source = isset($source_config['source']) ? $source_config['source'] : '';
    $form['source'] = array(
      '#markup' => '<h4>' . t('The Facebook page url including a properly configured access token:') . '</h4><div>' . $source . '</div>',
    );
    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {

    $page_id = FALSE;

    if (!empty($values['fb_page'])) {

      $page_id = facebook_import_retrieve_page_id($values['fb_page']);

    }

    $app_id = variable_get('facebook_import_app_id', '');
    $app_secret = variable_get('facebook_import_app_secret', '');

    if (!empty($app_id) && !empty($app_secret)) {
      if ($page_id) {
        $values['fb_id'] = $page_id;
        $access_token = facebook_import_access_token($app_id, $app_secret);
        if ($access_token) {
          $query = array(
            'access_token' => $access_token,
            'date_format' => 'U',
            // 'since' => 1364144400,
          );
          $feed_url = url('https://graph.facebook.com/' . $page_id . '/feed', array('absolute' => TRUE, 'query' => $query));
          $values['source'] = $feed_url;
        }
        else {
          form_set_error('', t('A Facebook access token was unable to be generated. This is most likely because the Facebook App ID and Facebook App Secret are either not set or invalid. Check your <a href="@url">Facebook Import settings</a>.', array('@url' => url('admin/config/services/facebook_import'))));
        }
      }
      else {
        form_set_error('source', t('The Facebook page %page is invalid.', array('%page' => $values['source'])));
      }
    }
    else {
      form_set_error('', t('Retrieving a Facebook feed requires a Facebook App ID and Facebook App Secret. One or both are not configured properly. Check your <a href="@url">Facebook Import settings</a>.', array('@url' => url('admin/config/services/facebook_import'))));
    }

  }

}
