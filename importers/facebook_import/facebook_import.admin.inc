<?php
/**
 * @file Facebook import administration.
 */


/**
 * Facebook import admin configuration form.
 *
 * @ingroup forms
 */
function facebook_import_admin() {

  $form = array();

  $form['facebook_import_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Facebook Import'),
    '#description' => t('Checking this box will enable Facebook Import, which will start retrieving posts from the Facebook page you configure here.'),
    '#default_value' => variable_get('facebook_import_active', FALSE),
  );
  $form['facebook_import_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook App ID'),
    '#description' => t('Facebook requires creating a Facebook App to retrieve even the smallest amount of information, even if it\'s public to begin with. Please visit <a href="@url">developers.facebook.com/apps</a> to setup your App. After it\'s setup, Facebook will assign it an App ID/API Key. Enter that number here.', array('@url' => 'https://developers.facebook.com/apps')),
    '#default_value' => variable_get('facebook_import_app_id', ''),
  );
  $form['facebook_import_app_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook App Secret'),
    '#description' => t('Facebook requires creating a Facebook App to retrieve even the smallest amount of information, even if it\'s public to begin with. Please visit <a href="@url">developers.facebook.com/apps</a> to setup your App. After it\'s setup, Facebook will assign it an App Secret. Enter that value here.', array('@url' => 'https://developers.facebook.com/apps')),
    '#default_value' => variable_get('facebook_import_app_secret', ''),
  );

  $form['#submit'][] = 'facebook_import_admin_submit';

  return system_settings_form($form);

}

/**
 * Extra submit handler for admin settings form. Given the page name from the
 * settings form, retrieves the page id and stores it in a variable.
 *
 * @see facebook_import_admin()
 *
 * @ingroup forms
 */
function facebook_import_admin_submit(&$form, &$form_state) {

  // Since we'll at minimum need all these, make sure it can't be enabled if
  // any of them are missing.
  $app_id = $form_state['values']['facebook_import_app_id'];
  $app_secret = $form_state['values']['facebook_import_app_secret'];

  if ($form_state['values']['facebook_import_active'] == 1) {

    if (empty($app_id) || empty($app_secret)) {

      $form_state['values']['facebook_import_active'] = 0;

      drupal_set_message(t('The Facebook App ID and App Secret are both required for this module to retrieve information from Facebook. One or more of them are missing, and as a result Facebook Import cannot begin importing Facebook posts. Please ensure that your Facebook App ID and App Secret are both entered and correct.'), 'warning');

    }

  }

}
