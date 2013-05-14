<?php

/**
 * @file
 * Home of the FeedsHTTPFetcher and related classes.
 */

feeds_include_library('PuSHSubscriber.inc', 'PuSHSubscriber');


/**
 * Result of FeedsHTTPFetcher::fetch().
 */
class InstagramFetcherResult extends FeedsHTTPFetcherResult {

  /**
   * Constructor.
   */
  public function __construct($id = NULL, $username = NULL) {
    $this->id = $id;
    $this->username = $username;
    parent::__construct('');
  }

  /**
   * Overrides FeedsFetcherResult::getRaw();
   */
  public function getRaw() {

    module_load_include('lib.php', 'instagram_import');

    $access_token = variable_get('instagram_import_access_token', '');
    $instagram = new Instagram($this->username, $access_token);

    $items = $instagram->user_recent($this->id);

    return $this->sanitizeRaw($items);

  }

}

/**
 * Fetches data via HTTP.
 */
class InstagramFetcher extends FeedsHTTPFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    if ($this->config['use_pubsubhubbub'] && ($raw = $this->subscriber($source->feed_nid)->receive())) {
      return new FeedsFetcherResult($raw);
    }
    $fetcher_result = new InstagramFetcherResult($source_config['source'], $source_config['username']);
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

    $client_id = variable_get('instagram_import_client_id', '');
    $client_secret = variable_get('instagram_import_client_secret', '');

    if ($client_id == '' || $client_secret == '') {
      drupal_set_message(t('Please <a href="@url">configure your Instagram client id and secret</a>.', array('@url' => 'admin/config/services/instagram-import')), 'error');
    }

    $access_token = variable_get('instagram_import_access_token', '');

    if (empty($access_token)) {

      drupal_set_message(t('Before you can setup your Instagram importer, you must first retrieve an access token from Instagram. To do so, select the "Import" button below. By selecting "Import", you will be redirected to Instagram to grant access to this site and then you will be returned to this form to setup your importer.'), 'status', FALSE);

      $username = isset($source_config['username']) ? $source_config['username'] : '';
      $form['username'] = array(
        '#type' => 'textfield',
        '#title' => t('Instagram username'),
        '#default_value' => $username,
        '#maxlength' => NULL,
        '#required' => TRUE,
        '#disabled' => TRUE,
      );
      $source = isset($source_config['source']) ? $source_config['source'] : '';
      $form['source'] = array(
        '#markup' => '<h4>' . t('This importer is set to import the feed from the user ID:') . '</h4><div><em>' . $source . '</em></div>',
      );

    }
    else {

      $username = isset($source_config['username']) ? $source_config['username'] : '';
      $form['username'] = array(
        '#type' => 'textfield',
        '#title' => t('Instagram username'),
        '#default_value' => $username,
        '#maxlength' => NULL,
        '#required' => TRUE,
      );
      $source = isset($source_config['source']) ? $source_config['source'] : '';
      $form['source'] = array(
        '#markup' => '<h4>' . t('This importer is set to import the feed from the user ID:') . '</h4><div><em>' . $source . '</em></div>',
      );

    }

    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {

    global $user;

    module_load_include('lib.php', 'oauth_common');
    module_load_include('lib.php', 'instagram_import');

    $client_id = variable_get('instagram_import_client_id', '');
    $client_secret = variable_get('instagram_import_client_secret', '');

    if ($client_id == '' || $client_secret == '') {
      form_set_error('', t('Please configure your Instagram client id and secret.'));
    }

    $access_token = variable_get('instagram_import_access_token', '');

    if (empty($access_token)) {

      $callback_uri = url('instagram-import/oauth', array('absolute' => TRUE));

      $instagram = new InstagramOAuth($client_id, $client_secret);

      $_SESSION['instagram_import_oauth']['account'] = $user->uid;
      $_SESSION['instagram_import_oauth']['destination'] = $_GET['q'];

      drupal_goto($instagram->get_authorize_url($callback_uri));

    }
    else {

      // Ideally it would be nice to check if the access token is valid right
      // here. Instagram api doesn't seem to have a simple way of doing this.
      // For now, we'll just have to fallback to request errors to handle
      // invalid access tokens.

      $instagram = new Instagram($values['username'], $access_token);

      $instagram_user = $instagram->user_lookup($values['username'], array('!count' => 1));

      if ($values['username'] == $instagram_user[0]->username) {

        $values['source'] = $instagram_user[0]->id;

      }
      else {

        form_set_error('username', t('The Instagram username you entered does not match any Instagram users. Please double-check that it is correct and try again.'));

      }

    }

  }

}
