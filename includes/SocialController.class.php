<?php
/**
 * @file
 *
 * Contains the controller class for the Social entity.
 */

/**
 * SocialControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */

interface SocialControllerInterface
  extends DrupalEntityControllerInterface {
    public function create($values);
    public function save($entity);
    public function delete($entity);
}

/**
 * SocialController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class SocialController
  extends EntityAPIController {
  // implements SocialControllerInterface {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  public function create(array $values = array()) {
    $entity = (object) array(
      'bundle' => $values['social_type'],
      'language' => LANGUAGE_NONE,
      'is_new' => TRUE,
    );

    // Ensure basic fields are defined.
    $values += array(
      'type' => 'social',
      'social_type' => '',
      // 'title' => '',
      'iid' => '',
      // 'delta' => '',
      // 'label' => FALSE,
      // 'title' => '',
      'view_mode' => 'default',
      'data' => '',
      'vid' => '',
      'current_vid' => '',
    );

    // Apply the given values.
    foreach ($values as $key => $value) {
      $entity->$key = $value;
    }

    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record()
   */
  public function save($entity) {

    $entity = (object) $entity;
     // Determine if we will be inserting a new entity.
    $entity->is_new = !(isset($entity->smid) && is_numeric($entity->smid));

    // Load the stored entity, if any.
    if (!$entity->is_new && !isset($entity->original)) {
      $entity->original = entity_load_unchanged('social', $entity->smid);
    }

    $transaction = db_transaction();

    // Set the timestamp fields.
    if (empty($entity->created)) {
      $entity->created = REQUEST_TIME;
    }

    // Only change revision timestamp if it doesn't exist.
    if (empty($entity->timestamp)) {
      $entity->timestamp = REQUEST_TIME;
    }

    $entity->changed = REQUEST_TIME;

    field_attach_presave('social', $entity);
    module_invoke_all('entity_presave', $entity, 'social');

    // When saving a new entity revision, unset any existing $entity->vid
    // to ensure a new revision will actually be created and store the old
    // revision ID in a separate property for entity hook implementations.
    if (!$entity->is_new && !empty($entity->revision) && $entity->vid) {
      $entity->old_vid = $entity->vid;
      unset($entity->vid);
      $entity->timestamp = REQUEST_TIME;
    }

    module_invoke_all('entity_presave', $entity, 'social');

    try {
      if (!$entity->is_new) {
        // Since we already have an smid, write the revision to ensure the
        // vid is the most up to date, then write the record.
        $this->saveRevision($entity);
        drupal_write_record('social', $entity, 'smid');

        field_attach_update('social', $entity);
        module_invoke_all('entity_update', $entity, 'social');

      }
      else {
        // If this is new, write the record first so we have an fpid,
        // then save the revision so that we have a vid. This means we
        // then have to write the vid again.
        drupal_write_record('social', $entity);
        $this->saveRevision($entity);
        db_update('social')
          ->fields(array('vid' => $entity->vid))
          ->condition('smid', $entity->smid)
          ->execute();

        field_attach_insert('social', $entity);
        module_invoke_all('entity_insert', $entity, 'social');
      }

      return $entity;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('social', $e);
    }

    return FALSE;
  }

  /**
   * Saves an entity revision with the uid of the current user.
   *
   * @param $entity
   *   The fully loaded entity object.
   * @param $uid
   *   The user's uid for the current revision.
   * @param $update
   *   TRUE or FALSE indicating whether or not the existing revision should be
   *     updated instead of a new one created.
   */
  function saveRevision($entity, $uid = NULL) {
    if (!isset($uid)) {
      $uid = $GLOBALS['user']->uid;
    }

    $entity->uid = $uid;
    // Update the existing revision if specified.
    if (!empty($entity->vid)) {
      drupal_write_record('social_revision', $entity, 'vid');
    }
    else {
      // Otherwise insert a new revision. This will automatically update $entity
      // to include the vid.
      drupal_write_record('social_revision', $entity);
    }
  }

  public function delete($smids) {
    $transaction = db_transaction();
    if (!empty($smids)) {
      $entities = social_load_multiple($smids, array());
      try {
        foreach ($entities as $smid => $entity) {
          // Call the entity-specific callback (if any):
          module_invoke_all('entity_delete', $entity, 'social');
          field_attach_delete('social', $entity);
        }

        // Delete after calling hooks so that they can query entity tables as needed.
        db_delete('social')
          ->condition('smid', $smids, 'IN')
          ->execute();

        db_delete('social_revision')
          ->condition('smid', $smids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('social', $e);
        throw $e;
      }

      // Clear the page and block and entity_load_multiple caches.
      entity_get_controller('social')->resetCache();
    }
  }

  /**
   * Overriding the buldContent function to add entity specific fields
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);
    /*$content['model_sample_data'] =  array(
      '#markup' => theme('model_sample_data', array('model_sample_data' => check_plain($entity->data['sample_data']), 'model' => $entity)),
    );*/

    return $content;
  }

  /**
   * Implements EntityAPIControllerInterface.
   */
  public function view($entities, $view_mode = 'full', $langcode = NULL, $page = NULL) {
    // For Field API and entity_prepare_view, the entities have to be keyed by
    // (numeric) id.
    $entities = entity_key_array_by_property($entities, $this->idKey);
    if (!empty($this->entityInfo['fieldable'])) {
      field_attach_prepare_view($this->entityType, $entities, $view_mode);
    }
    entity_prepare_view($this->entityType, $entities);
    $langcode = isset($langcode) ? $langcode : $GLOBALS['language_content']->language;

    $view = array();
    foreach ($entities as $entity) {
      $build = entity_build_content($this->entityType, $entity, $view_mode, $langcode);
      $build += array(
        // If the entity type provides an implementation, use this instead the
        // generic one.
        // @see template_preprocess_entity()
        '#theme' => 'social',
        '#entity_type' => $this->entityType,
        '#entity' => $entity,
        '#view_mode' => $view_mode,
        '#language' => $langcode,
        '#page' => $page,
      );
      // Allow modules to modify the structured entity.
      drupal_alter(array($this->entityType . '_view', 'entity_view'), $build, $this->entityType);
      $key = isset($entity->{$this->idKey}) ? $entity->{$this->idKey} : NULL;
      $view[$this->entityType][$key] = $build;
    }
    return $view;
  }


}
