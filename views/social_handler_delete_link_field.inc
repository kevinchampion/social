<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class social_handler_delete_link_field extends social_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['social_type'] = 'social_type';
  }


  function render($values) {
    $type = $values->{$this->aliases['social_type']};

    //Creating a dummy social to check access against
    $dummy_social = (object) array('type' => $type);
    if (!social_access('edit', $dummy_social)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $smid = $values->{$this->aliases['smid']};

    return l($text, 'social/' . $smid . '/delete');
  }
}
