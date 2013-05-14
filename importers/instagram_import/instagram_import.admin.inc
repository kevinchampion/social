<?php
/**
 * @file Instagram import administration.
 */


/**
 * Instagram import admin configuration form.
 *
 * @ingroup forms
 */
function instagram_import_admin() {

  $form = array();

  $form['instagram_import_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Instagram Client ID'),
    '#description' => t('Instagram requires creating an Instagram App to retrieve even the smallest amount of information, even if it\'s public to begin with. Please visit <a href="@url">instagram.com/developer</a> to setup your App. After it\'s setup, Instagram will assign it an App Client ID. Enter that number here.', array('@url' => 'http://instagram.com/developer/clients/register/')),
    '#default_value' => variable_get('instagram_import_client_id', ''),
  );
  $form['instagram_import_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Instagram Client Secret'),
    '#description' => t('Instagram requires creating a Instagram App to retrieve even the smallest amount of information, even if it\'s public to begin with. Please visit <a href="@url">instagram.com/developer</a> to setup your App. After it\'s setup, Instagram will assign it a App Client Secret. Enter that value here.', array('@url' => 'http://instagram.com/developer/clients/register/')),
    '#default_value' => variable_get('instagram_import_client_secret', ''),
  );
  $form['callback_url'] = array(
    '#type' => 'item',
    '#title' => t('Callback URL'),
    '#markup' => url('instagram-import/oauth', array('absolute' => TRUE)),
  );

  return system_settings_form($form);

}

