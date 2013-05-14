<?php

/**
 * @file
 * Classes to implement the full Instagram API.
 *
 * Cribbed almost entirely from the drupagram module:
 * @see  http://www.drupal.org/project/drupagram
 */

/**
 * Class InstagramImportConf
 *
 * Singleton which stores common configuration
 * @see http://php.net/manual/en/language.oop5.patterns.php
 */
class InstagramImportConf {

  private static $instance;
  private $attributes = array(
    'apibase' => 'https://api.instagram.com',
    'apiurl' => 'https://api.instagram.com/v1',
    'tiny_url' => 'tinyurl.com',
  );

  private function __construct() {

  }

  public static function instance() {
    if (!isset(self::$instance)) {
      $className = __CLASS__;
      self::$instance = new $className;
    }
    return self::$instance;
  }

  /**
   * Generic getter
   *
   * @param $attribute
   *   string attribute name to return
   * @return
   *   mixed value or NULL
   */
  public function get($attribute) {
    if (array_key_exists($attribute, $this->attributes)) {
      return $this->attributes[$attribute];
    }
  }

  /**
   * Generic setter
   * @param $attribute
   *   string attribute name to be set
   * @param $value
   *   mixed value
   */
  public function set($attribute, $value) {
    if (array_key_exists($attribute, $this->attributes)) {
      $this->attributes[$attribute] = $value;
    }
  }

}

/**
 * Primary Instagram API implementation class
 * Supports the full REST API for instgram.
 */
class Instagram {
  /**
   * The name of the GET param that holds the authentication code
   * @var string
   */

  const RESPONSE_CODE_PARAM = 'code';

  /**
   * @var $format API format to use: can be json or xml
   */
  protected $format = 'json';

  /**
   * @var $source the instagram api 'source'
   */
  protected $source = 'drupal';

  /**
   * @var $username Instagram username to use for authenticated requests
   */
  protected $username;

  /**
   * @var $password Instagram password to use for authenticated requests
   */
  protected $password;

  /**
   * JSON encoded OAuth token
   * @var string
   */
  protected $oauth_token = NULL;

  /**
   * Decoded plain access token
   * @var string
   */
  protected $access_token = NULL;

  /**
   * OAuth user object
   * @var object
   */
  protected $current_user = NULL;
  protected $endpoints = array(
    'authorize' => 'oauth/authorize/?client_id=!client_id&redirect_uri=!redirect_uri&response_type=!response_type',
    'access_token' => 'oauth/access_token',
    'user' => 'v1/users/!user_id/?access_token=!access_token',
    'user_feed' => 'v1/users/self/feed?access_token=!access_token&min_id=!min_id',
    'user_recent' => 'v1/users/!user_id/media/recent/?access_token=!access_token&max_id=!max_id&min_id=!min_id&max_timestamp=!max_timestamp&min_timestamp=!min_timestamp',
    'user_search' => 'v1/users/search?q=!q&access_token=!access_token',
    'user_follows' => 'v1/users/!user_id/follows?access_token=!access_token',
    'user_followed_by' => 'v1/users/!user_id/followed-by?access_token=!access_token',
    'user_requested_by' => 'v1/users/self/requested-by?access_token=!access_token',
    'user_relationship' => 'v1/users/!user_id/relationship?access_token=!access_token',
    'modify_user_relationship' => 'v1/users/!user_id/relationship?action=%s&access_token=!access_token',
    'media' => 'v1/media/!user_id?access_token=!access_token',
    'media_search' => 'v1/media/search?lat=%s&lng=%s&max_timestamp=%d&min_timestamp=%d&distance=%d&access_token=!access_token',
    'media_popular' => 'v1/media/popular?access_token=!access_token',
    'media_comments' => 'v1/media/%d/comments?access_token=!access_token',
    'post_media_comment' => 'v1/media/%d/comments?access_token=!access_token',
    'delete_media_comment' => 'v1/media/%d/comments?comment_id=%d&access_token=!access_token',
    'likes' => 'v1/media/%d/likes?access_token=!access_token',
    'post_like' => 'v1/media/%d/likes',
    'remove_like' => 'v1/media/%d/likes?access_token=!access_token',
    'tags' => 'v1/tags/%s?access_token=!access_token',
    'tags_recent' => 'v1/tags/%s/media/recent?max_id=%d&min_id=%d&access_token=!access_token',
    'tags_search' => 'v1/tags/search?q=%s&access_token=!access_token',
    'locations' => 'v1/locations/%d?access_token=!access_token',
    'locations_recent' => 'v1/locations/%d/media/recent/?max_id=%d&min_id=%d&max_timestamp=%d&min_timestamp=%d&access_token=!access_token',
    'locations_search' => 'v1/locations/search?lat=%s&lng=%s&foursquare_id=%d&distance=%d&access_token=!access_token',
    'geographies' => 'v1/geographies/%d/media/recent?access_token=!access_token',
  );

  /**
   * Constructor for the Instagram class
   */
  public function __construct($username = NULL, $access_token = NULL) {
    if (!empty($username) || !empty($access_token)) {
      $this->set_auth($username, $access_token);
    }
  }

  /**
   * Set the username and password
   */
  public function set_auth($username, $access_token) {
    $this->username = $username;
    $this->access_token = $access_token;
  }

  /**
   * Get an array of Instagram objects from an API endpoint
   */
  protected function fetch($key, $params = array(), $use_auth = TRUE) {
    $results = array();

    if (array_key_exists($key, $this->endpoints)) {
      $path = $this->endpoints[$key];
    }
    else {
      watchdog('instagram_import', 'Endpoint key not found: !key', array('!key' => $key), WATCHDOG_ERROR);
      return FALSE;
    }

    $response = $this->call($path, $params, 'GET', $use_auth);

    // Determine the right class to use when returning the results for this key
    switch ($key) {
      case 'user':
      case 'user_search':
      case 'user_follows':
      case 'user_followed_by':
        $class = 'InstagramUser';
        break;
      default:
        $class = 'InstagramMedia';
        break;
    }
    if (isset($response) && is_array($response)) {
      $response = array_filter($response);
    }

    // Check on successfull call
    if (!empty($response)) {
      foreach ($response as $key => $item) {
        if ($key != 'data') {
          continue;
        }
        elseif (!empty($item) && isset($item[0])) {
          foreach ($item as $object) {
            $results[] = new $class($object);
          }
        }
        else {
          $results[] = new $class($item);
        }
      }
    }

    // Call might return FALSE , e.g. on failed authentication but an exection
    // will be raised, no need for us to do anything special here.
    return $results;
  }

  /**
   * Fetch a user's feed
   */
  public function user_feed($id = 'self', $params = array(), $use_auth = TRUE) {
    $params['!user_id'] = $id;
    $result = $this->fetch('user_feed', $params, $use_auth);

    return $result;
  }

  /**
   * Get basic information about a user.
   */
  public function user_info($id = 'self', $params = array(), $use_auth = TRUE) {
    if (is_numeric($id)) {
      $params['!user_id'] = $id;
    }
    elseif ($id != 'self') {
      return $this->user_lookup($id);
    }
    $result = $this->fetch('user', $params, $use_auth);

    return $result;
  }

  public function user_lookup($username, $params = array(), $use_auth = TRUE) {
    $params['!q'] = $username;
    $result = $this->fetch('user_search', $params, $use_auth);

    return $result;
  }

  /**
   * See the authenticated user's feed.
   * GET /users/self/feed
   *
   * PARAMETERS
   * access_token A valid access token.
   * max_id Return media earlier than this max_id
   * min_id Return media later than this min_id
   * count  Count of media to return
   *
   * @example https://api.instagram.com/v1/users/self/feed?access_token=10920197.f59def8.6670c891a5b4477084ecf66a5aa8e67b
   */
  public function self_feed($params = array(), $use_auth = TRUE) {
    return $this->fetch('user_feed', $params, $use_auth);
  }

  /**
   * Get the most recent media published by a user.
   * GET /users/{user-id}/media/recent
   *
   * PARAMETERS
   * access_token A valid access token.
   * max_id Return media earlier than this max_id
   * min_id Return media later than this min_id
   * count  Count of media to return
   * min_timestamp  Return media after this UNIX timestamp
   * max_timestamp  Return media before this UNIX timestamp
   *
   * @example: https://api.instagram.com/v1/users/3/media/recent/?access_token=10920197.f59def8.6670c891a5b4477084ecf66a5aa8e67b
   */
  public function user_recent($id = NULL, $params = array(), $use_auth = TRUE) {
    if (empty($id)) {
      $params['!user_id'] = 'self';
    }
    elseif (is_numeric($id)) {
      $params['!user_id'] = $id;
    }
    else {
      $username = $id;
      // $params['username'] = $username;
      $account = $this->user_lookup($username);
      $params['!user_id'] = $account->id;
    }

    return $this->fetch('user_recent', $params, $use_auth);
  }

  /**
   * Retrieve popular media.
   *
   * @param array $params
   * @param boolean $use_auth
   * @return InstagramMedia object.
   */
  public function media_popular($params = array(), $use_auth = TRUE) {
    return $this->fetch('media_popular', $params, $use_auth);
  }

  /**
   * See the authenticated user's list of media they've liked. Note that this
   * list is ordered by the order in which the user liked the media. Private
   * media is returned as long as the authenticated user has permission to view
   * that media. Liked media lists are only available for the currently
   * authenticated user.
   * GET /users/self/media/liked
   *
   * PARAMETERS
   * access_token A valid access token.
   * max_like_id  Return media liked before this id
   * count  Count of media to return
   */
  public function self_liked($params = array(), $use_auth = TRUE) {
    $params['user-id'] = 'self';

    return $this->fetch('users/{user-id}/media/recent', $params, $use_auth);
  }

  /**
   * Search for a user by name.
   * GET /users/search
   *
   * PARAMETERS
   * q  A query string.
   * count  Number of users to return
   *
   * @example: https://api.instagram.com/v1/users/search?q=jack&access_token=10920197.f59def8.6670c891a5b4477084ecf66a5aa8e67b
   */
  public function user_search($q, $params = array(), $use_auth = TRUE) {
    $params['!q'] = $q;
    return $this->fetch('user_search', $params, $use_auth);
  }

  /**
   * Method for calling any instagram api resource
   */
  public function call($path, $params = array(), $method = 'GET', $use_auth = FALSE) {
    $url = $this->create_url($path, '');

    try {
      if ($use_auth) {
        $response = $this->auth_request($url, $params, $method);
      }
      else {
        $response = $this->request($url, $params, $method);
      }
    }
    catch (Exception $e) {
      watchdog('instagram_import', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }

    if (!$response) {
      return FALSE;
    }

    return $this->parse_response($response);
  }

  /**
   * Perform an authentication required request.
   */
  protected function auth_request($path, $params = array(), $method = 'GET') {
    $params['!access_token'] = $this->access_token;
    return $this->request($path, $params, $method, TRUE);
  }

  /**
   * Perform a request
   *
   * @param string $url
   * @param array $params
   * @param string $method. Can be one of: GET, POST, DELETE or PUT.
   * @param bool $use_auth
   * @return type
   */
  protected function request($url, $params = array(), $method = 'GET', $use_auth = FALSE) {
    // @TODO: GET requests could potentially be cached.
    $data = '';

    if (!is_array($params)) {
      $params = (array) $params;
    }
    if (count($params) > 0) {
      if ($method == 'GET') {
        if (is_array($params) && !empty($params)) {
          $url = format_string($url, $params);
        }
        $url = preg_replace('/&?[a-z_]*=![a-z_]*/', '', $url, -1);
      }
      else {
        $data = http_build_query($params, '', '&');
      }
    }

    $headers = array();
    // @TODO: implement headers when $use_auth == TRUE

    $response = drupal_http_request($url, array(
      'headers' => $headers,
      'method' => $method,
      'data' => $data,
      ));

    if (!isset($response->error)) {
      return $response->data;
    }
    else {
      throw new Exception($response->error);
    }
  }

  protected function parse_response($response, $format = NULL) {
    if (empty($format)) {
      $format = $this->format;
    }

    switch ($format) {
      case 'json':
        // http://drupal.org/node/985544 - json_decode large integer issue
        // $length = strlen(PHP_INT_MAX);
        // $response = preg_replace('/"(id|in_reply_to_status_id)":(\d{' . $length . ',})/', '"\1":"\2"', $response);
        return json_decode($response, TRUE);
    }
  }

  protected function create_url($path, $format = NULL) {
    if (is_null($format)) {
      $format = $this->format;
    }
    $conf = InstagramImportConf::instance();
    $url = $conf->get('apibase') . '/' . $path;
    if (!empty($format)) {
      $url .= '.' . $this->format;
    }
    return $url;
  }

}

/**
 * A class to provide OAuth enabled access to the Instagram API
 */
class InstagramOAuth extends Instagram {

  protected $client_id;
  protected $client_secret;
  protected $redirect_uri;
  protected $token;
  protected $access_token = NULL;
  protected $auth_user = array();

  /**
   * Constructor for the InstagramOAuth class
   */
  public function __construct($client_id = NULL, $client_secret = NULL, $redirect_uri = NULL, $access_token = NULL) {
    if (empty($client_id) || empty($client_secret)) {
      throw new InstagramException(t('You need to configure your Client ID and/or Client Secret keys.'));
    }
    $this->client_id = $client_id;
    $this->client_secret = $client_secret;
    if (isset($redirect_uri)) {
      $this->redirect_uri = $redirect_uri;
    }
    if (isset($access_token)) {
      $this->access_token = $access_token;
    }
  }

  /**
   * Returns the properly formatted authorization url.
   *
   * @param string $redirect_uri. URI to redirect the user to after authorization
   * @param array $scope. Items can be: 'basic', 'comments', 'relationships' and 'likes'
   * @param string $response_type. Currently only 'code' is supported
   * @return string. Propertly formatted authorization url.
   */
  public function get_authorize_url($redirect_uri = NULL, $scope = array('basic', 'comments', 'relationships', 'likes'), $response_type = 'code') {

    $url = $this->create_url('oauth/authorize', '');
    $url .= '?client_id=' . $this->client_id;
    $url .= '&response_type=' . $response_type;
    if (isset($redirect_uri)) {
      $url .= '&redirect_uri=' . $redirect_uri;
    }
    if (isset($scope)) {
      $url .= '&scope=' . implode('+', $scope);
    }

    return $url;
  }

  /**
   * Returns the properly formatted authentication url
   */
  public function get_authenticate_url() {
    $url = $this->create_url('oauth/authenticate', '');
    if (!empty($this->token)) {
      $url .= '?access_token=' . $this->token['access_token'];
    }

    return $url;
  }

  /**
   * Retrieves the access token.
   *
   * @param string $code
   * @param string $redirect_uri
   * @param string $grant_type
   * @return type
   */
  public function get_access_token($code, $redirect_uri, $grant_type = 'authorization_code') {
    if ($this->access_token !== NULL) {
      return $this->access_token;
    }

    $url = $this->create_url('oauth/access_token', '');
    $params = array(
      'client_id' => $this->client_id,
      'client_secret' => $this->client_secret,
      'grant_type' => $grant_type,
      'redirect_uri' => $redirect_uri,
      'code' => $code,
    );
    try {
      $response = $this->auth_request($url, $params, 'POST', FALSE);
    }
    catch (Exception $e) {
      watchdog('instagram_import', '!message', array('!message' => $e->__toString()), WATCHDOG_ERROR);
      return FALSE;
    }
    $token = json_decode($response, TRUE);
    $this->token = $token;
    $this->access_token = $token['access_token'];
    // $token['user']['oauth_token'] = $token['access_token'];
    // $this->auth_user = new InstagramUser($token['user']);

    return $token;
  }

  public function auth_request($url, $params = array(), $method = 'POST', $use_auth = TRUE) {
    return $this->request($url, $params, $method, $use_auth);
  }

}

/**
 * Instagram search is not used in this module yet
 */
class InstagramSearch extends Instagram {

  public function search($params = array()) {

  }

}

/**
 * Class for containing an individual Instagram posts.
 */
class InstagramMedia {

  public $id;
  public $user;
  public $type;
  public $images;
  public $location;
  public $comments;
  public $caption;
  public $link;
  public $likes;
  public $filter;
  public $created_time;

  /**
   * Constructor for InstagramMedia
   */
  public function __construct($values = array()) {
    // Filter out null and empty values
    $values = array_filter($values);

    // Turn values into object attributes
    foreach ($values as $key => $value) {
      switch ($key) {
        case 'user':
          $this->user = new InstagramUser($values['user']);
          break;
        // case 'caption':
        // $this->caption = $values['caption']['text'];
        // break;
        default:
          $this->$key = $value;
          break;
      }
    }
  }

}

/**
 * Class for containing an individual Instagram user.
 */
class InstagramUser {

  // Public attributes
  public $id;
  public $username;
  public $first_name;
  public $last_name;
  public $full_name;
  public $profile_picture;
  public $bio;
  public $website;
  public $media_count;
  public $follows_count;
  public $followed_by_count;
  public $follows;
  public $followed_by;
  public $url;
  // Special attributes for the authenticated users
  protected $password;
  protected $oauth_token;
  protected $oauth_token_secret;

  /**
   * Constructor for InstagramUser
   */
  public function __construct($values = array()) {
    if (!isset($values) || empty($values)) {
      return FALSE;
    }
    if (!is_array($values)) {
      $values = (array) $values;
    }
    // Filter out null and empty values
    $values = array_filter($values);

    // Turn values into user object attributes
    foreach ($values as $key => $value) {
      switch ($key) {
        case 'counts':
          if (is_array($values['counts']) && !empty($values['counts'])) {
            $this->media_count = isset($values['counts']['media']) ? (int) $values['counts']['media'] : 0;
            $this->follows_count = isset($values['counts']['follows']) ? (int) $values['counts']['follows'] : 0;
            $this->followed_by_count = isset($values['counts']['followed_by']) ? (int) $values['counts']['followed_by'] : 0;
          }
          break;
        default:
          $this->$key = $value;
          break;
      }
    }
  }

  public function get_auth() {
    return array(
      'password' => $this->password,
      'oauth_token' => $this->oauth_token,
      'oauth_token_secret' => $this->oauth_token_secret,
    );
  }

  public function set_auth($values) {
    $this->oauth_token = isset($values['oauth_token']) ? $values['oauth_token'] : NULL;
    $this->oauth_token_secret = isset($values['oauth_token_secret']) ? $values['oauth_token_secret'] : NULL;
  }

}
