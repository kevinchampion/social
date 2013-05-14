<?php

/**
 * @file
 * Class definition of SocialProcessor.
 */

/**
 * Creates nodes from feed items.
 */
class SocialProcessor extends FeedsProcessor {

  /**
   * Define entity type.
   */
  public function entityType() {
    return 'social';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Social items');
    return $info;
  }

  /**
   * Creates a new node in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $social = new stdClass();
    $social->social_type = $this->bundle();
    $social->type = $this->bundle();
    $social->bundle = $this->bundle();
    $social->changed = REQUEST_TIME;
    $social->created = REQUEST_TIME;
    $social->language = LANGUAGE_NONE;
    $social->is_new = TRUE;
    // node_object_prepare($social);
    // Populate properties that are set by node_object_prepare().
    $social->log = 'Created by SocialProcessor';
    $social->uid = $this->config['author'];
    return $social;
  }

  /**
   * Bundle type this processor operates on.
   *
   * Defaults to the entity type for entities that do not define bundles.
   *
   * @return string|NULL
   *   The bundle type this processor operates on, or NULL if it is undefined.
   */
  public function bundle() {
    return $this->config['bundle'];
  }

  /**
   * Provides a list of bundle options for use in select lists.
   *
   * @return array
   *   A keyed array of bundle => label.
   */
  public function bundleOptions() {
    $options = array();
    foreach (field_info_bundles($this->entityType()) as $bundle => $info) {
      if (!empty($info['label'])) {
        $options[$bundle] = $info['label'];
      }
      else {
        $options[$bundle] = $bundle;
      }
    }
    return $options;
  }

  /**
   * Loads an existing node.
   *
   * If the update existing method is not FEEDS_UPDATE_EXISTING, only the node
   * table will be loaded, foregoing the node_load API for better performance.
   *
   * @todo Reevaluate the use of node_object_prepare().
   */
  protected function entityLoad(FeedsSource $source, $smid) {
    $social = parent::entityLoad($source, $smid);

    if ($this->config['update_existing'] != FEEDS_UPDATE_EXISTING) {
      $social->uid = $this->config['author'];
    }

    // social_object_prepare($social);

    // Workaround for issue #1247506. See #1245094 for backstory.
    if (!empty($social->menu)) {
      // If the social has a menu item(with a valid mlid) it must be flagged
      // 'enabled'.
      $social->menu['enabled'] = (int) (bool) $social->menu['mlid'];
    }

    // Populate properties that are set by social_object_prepare().
    if ($this->config['update_existing'] == FEEDS_UPDATE_EXISTING) {
      $social->log = 'Updated by SocialProcessor';
    }
    else {
      $social->log = 'Replaced by SocialProcessor';
    }
    return $social;
  }

  /**
   * Check that the user has permission to save a node.
   */
  protected function entitySaveAccess($entity) {

    // The check will be skipped for anonymous nodes.
    if ($this->config['authorize'] && !empty($entity->uid)) {

      $author = user_load($entity->uid);

      // If the uid was mapped directly, rather than by email or username, it
      // could be invalid.
      if (!$author) {
        $message = 'User %uid is not a valid user.';
        throw new FeedsAccessException(t($message, array('%uid' => $entity->uid)));
      }

      if (empty($entity->smid) || !empty($entity->is_new)) {
        $op = 'create';
        $access = social_access($op, $entity->type, $author);
      }
      else {
        $op = 'update';
        $access = social_access($op, $entity, $author);
      }

      if (!$access) {
        $message = 'User %name is not authorized to %op content type %content_type.';
        throw new FeedsAccessException(t($message, array('%name' => $author->name, '%op' => $op, '%content_type' => $entity->type)));
      }
    }
  }

  /**
   * Validates a node.
   */
  protected function entityValidate($entity) {
    if (!isset($entity->uid) || !is_numeric($entity->uid)) {
       $entity->uid = $this->config['author'];
    }
  }

  /**
   * Save a node.
   */
  public function entitySave($entity) {
    social_save($entity);
  }

  /**
   * Delete a series of nodes.
   */
  protected function entityDeleteMultiple($smids) {
    social_delete_multiple($smids);
  }

  /**
   * Implement expire().
   *
   * @todo: move to processor stage?
   */
  /*public function expire($time = NULL) {
    if ($time === NULL) {
      $time = $this->expiryTime();
    }
    if ($time == FEEDS_EXPIRE_NEVER) {
      return;
    }
    $count = $this->getLimit();
    $nodes = db_query_range("SELECT n.nid FROM {node} n JOIN {feeds_item} fi ON fi.entity_type = 'node' AND n.nid = fi.entity_id WHERE fi.id = :id AND n.created < :created", 0, $count, array(':id' => $this->id, ':created' => REQUEST_TIME - $time));
    $nids = array();
    foreach ($nodes as $node) {
      $nids[$node->nid] = $node->nid;
    }
    $this->entityDeleteMultiple($nids);
    if (db_query_range("SELECT 1 FROM {node} n JOIN {feeds_item} fi ON fi.entity_type = 'node' AND n.nid = fi.entity_id WHERE fi.id = :id AND n.created < :created", 0, 1, array(':id' => $this->id, ':created' => REQUEST_TIME - $time))->fetchField()) {
      return FEEDS_BATCH_ACTIVE;
    }
    return FEEDS_BATCH_COMPLETE;
  }*/

  /**
   * Return expiry time.
   */
  /*public function expiryTime() {
    return $this->config['expire'];
  }*/

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'expire' => FEEDS_EXPIRE_NEVER,
      'author' => 0,
      'authorize' => TRUE,
    ) + parent::configDefaults();
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);

    $form['bundle']['#title'] = t('Social Media type');

    /*$author = user_load($this->config['author']);
    $form['author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#description' => t('Select the author of the nodes to be created - leave empty to assign "anonymous".'),
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => empty($author->name) ?  'anonymous' : check_plain($author->name),
    );
    $form['authorize'] = array(
      '#type' => 'checkbox',
      '#title' => t('Authorize'),
      '#description' => t('Check that the author has permission to create the node.'),
      '#default_value' => $this->config['authorize'],
    );*/
    $period = drupal_map_assoc(array(FEEDS_EXPIRE_NEVER, 3600, 10800, 21600, 43200, 86400, 259200, 604800, 2592000, 2592000 * 3, 2592000 * 6, 31536000), 'feeds_format_expire');
    $form['expire'] = array(
      '#type' => 'select',
      '#title' => t('Expire nodes'),
      '#options' => $period,
      '#description' => t('Select after how much time nodes should be deleted. The node\'s published date will be used for determining the node\'s age, see Mapping settings.'),
      '#default_value' => $this->config['expire'],
    );
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    /*if ($author = user_load_by_name($values['author'])) {
      $values['author'] = $author->uid;
    }
    else {
      $values['author'] = 0;
    }*/
  }

  /**
   * Reschedule if expiry time changes.
   */
  public function configFormSubmit(&$values) {
    if ($this->config['expire'] != $values['expire']) {
      feeds_reschedule($this->id);
    }
    parent::configFormSubmit($values);
  }

  /**
   * Override setTargetElement to operate on a target item that is a social.
   */
  public function setTargetElement(FeedsSource $source, $target_social, $target_element, $value) {
    switch ($target_element) {
      case 'created':
        $target_social->created = feeds_to_unixtime($value, REQUEST_TIME);
        break;
      case 'feeds_source':
        // Get the class of the feed social importer's fetcher and set the source
        // property. See feeds_social_update() how $social->feeds gets stored.
        if ($id = feeds_get_importer_id($this->bundle())) {
          $class = get_class(feeds_importer($id)->fetcher);
          $target_social->feeds[$class]['source'] = $value;
          // This effectively suppresses 'import on submission' feature.
          // See feeds_social_insert().
          $target_social->feeds['suppress_import'] = TRUE;
        }
        break;
      case 'user_name':
        if ($user = user_load_by_name($value)) {
          $target_social->uid = $user->uid;
        }
        break;
      case 'user_mail':
        if ($user = user_load_by_mail($value)) {
          $target_social->uid = $user->uid;
        }
        break;
      default:
        parent::setTargetElement($source, $target_social, $target_element, $value);
        break;
    }
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $type = social_get_types($this->bundle());

    $targets = parent::getMappingTargets();
    /*if ($type->has_title) {
      $targets['title'] = array(
        'name' => t('Title'),
        'description' => t('The title of the node.'),
        'optional_unique' => TRUE,
      );
    }*/
    $targets['smid'] = array(
      'name' => t('Social Media social ID'),
      'description' => t('The smid of the social. NOTE: use this feature with care, social ids are usually assigned by Drupal.'),
      'optional_unique' => TRUE,
    );
    $targets['iid'] = array(
      'name' => t('Social Media item ID'),
      'description' => t('The unique ID of the individual social media item.'),
    );
    /*$targets['user_name'] = array(
      'name' => t('Username'),
      'description' => t('The Drupal username of the node author.'),
    );
    $targets['user_mail'] = array(
      'name' => t('User email'),
      'description' => t('The email address of the node author.'),
    );
    $targets['status'] = array(
      'name' => t('Published status'),
      'description' => t('Whether a node is published or not. 1 stands for published, 0 for not published.'),
    );
    $targets['created'] = array(
      'name' => t('Published date'),
      'description' => t('The UNIX time when a node has been published.'),
    );
    $targets['promote'] = array(
      'name' => t('Promoted to front page'),
      'description' => t('Boolean value, whether or not node is promoted to front page. (1 = promoted, 0 = not promoted)'),
    );
    $targets['sticky'] = array(
      'name' => t('Sticky'),
      'description' => t('Boolean value, whether or not node is sticky at top of lists. (1 = sticky, 0 = not sticky)'),
    );*/

    // Include language field if Locale module is enabled.
    if (module_exists('locale')) {
      $targets['language'] = array(
        'name' => t('Language'),
        'description' => t('The two-character language code of the node.'),
      );
    }

    // Include comment field if Comment module is enabled.
    /*if (module_exists('comment')) {
      $targets['comment'] = array(
        'name' => t('Comments'),
        'description' => t('Whether comments are allowed on this node: 0 = no, 1 = read only, 2 = read/write.'),
      );
    }*/

    // If the target content type is a Feed node, expose its source field.
    if ($id = feeds_get_importer_id($this->bundle())) {
      $name = feeds_importer($id)->config['name'];
      $targets['feeds_source'] = array(
        'name' => t('Feed source'),
        'description' => t('The social type created by this processor is a Feed Node, it represents a source itself. Depending on the fetcher selected on the importer "@importer", this field is expected to be for example a URL or a path to a file.', array('@importer' => $name)),
        'optional_unique' => TRUE,
      );
    }

    // Let other modules expose mapping targets.
    self::loadMappers();
    $entity_type = $this->entityType();
    $bundle = $this->bundle();
    drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);

    return $targets;
  }

  /**
   * Get nid of an existing feed item node if available.
   */
  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    if ($smid = parent::existingEntityId($source, $result)) {
      return $smid;
    }

    // Iterate through all unique targets and test whether they do already
    // exist in the database.
    foreach ($this->uniqueTargets($source, $result) as $target => $value) {
      switch ($target) {
        case 'smid':
          $smid = db_query("SELECT smid FROM {social} WHERE smid = :smid", array(':smid' => $value))->fetchField();
          break;
        case 'iid':
          $smid = db_query("SELECT smid FROM {social} WHERE iid = :iid AND social_type = :social_type", array(':iid' => $value, ':social_type' => $this->bundle()))->fetchField();
          break;
        case 'feeds_source':
          if ($id = feeds_get_importer_id($this->bundle())) {
            $smid = db_query("SELECT fs.feed_smid FROM {social} s JOIN {feeds_source} fs ON s.smid = fs.feed_smid WHERE fs.id = :id AND fs.source = :source", array(':id' => $id, ':source' => $value))->fetchField();
          }
          break;
      }
      if ($smid) {
        // Return with the first nid found.
        return $smid;
      }
    }
    return 0;
  }
}
