<?php

/**
 * This field handler aggregates operations that can be done on a social
 * under a single field providing a more flexible way to present them in a view
 */
class social_handler_social_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['smid'] = 'smid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('social', 'social', array($this->get_value($values, 'smid')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
