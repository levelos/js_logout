<?php
// $Id:

/**
 * @file
 * contains all admin pages, settings, and validate.
 *
 * This file will only be parsed when processing admin menu options.
 * See http://drupal.org/node/146172
 */


/**
 * Settings form for menu callback
 */
function js_logout_settings() {
  $form = array();

  $form['js_logout_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout value in seconds'),
    '#default_value' => variable_get('js_logout_timeout', 1800),
    '#size' => 8,
    '#description' => t('The length of inactivity time, in seconds, before Automated Logout.  Must be 60 seconds or greater.')
  );
  
  $form['js_logout_padding'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout padding'),
    '#default_value' => variable_get('js_logout_padding', 10),
    '#size' => 8,
    '#description' => t('How many seconds to give a user to respond to the logout dialog before ending their session.')
  );

  $form['js_logout_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Logout Roles'),
    '#description' => t('Select which roles should be forced to logout.'),
    '#collapsible' => FALSE,
  );
  
  foreach (user_roles(TRUE) as $key => $role) {
    $form['js_logout_roles']['js_logout_role_' . $key] = array(
      '#type' => 'checkbox',
      '#title' => $role,
      '#default_value' => variable_get('js_logout_role_' . $key, TRUE)
    );
  }
  
  $form['js_logout_redirect_url']  = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL at logout'),
    '#default_value' => variable_get('js_logout_redirect_url', 'user/login'),
    '#size' => 40,
    '#description' => t('Send users to this internal page when they are logged out.')
  );

  $form['js_logout_message']  = array(
    '#type' => 'textarea',
    '#title' => t('Message to display in the logout dialog.'),
    '#default_value' => variable_get('js_logout_message', 'Your session is about to expire. Do you want to reset it?'),
    '#size' => 40,
    '#description' => t('This message must be plain text as it might appear in a javascript confirm dialog.')
  );
  
  $form['js_logout_use_watchdog'] = array(
   '#type' => 'checkbox',
   '#title' => t('Enable watchdog Automated Logout logging'),
   '#default_value' => variable_get('js_logout_use_watchdog', ''),
   '#description' => t('Enable logging of automatically logged out users')
  );
  
  $form['js_logout_enforce_admin'] = array(
   '#type' => 'checkbox',
   '#title' => t('Enforce auto logout on admin pages'),
   '#default_value' => variable_get('js_logout_enforce_admin', FALSE),
   '#description' => t('If checked, than users will be auto logged out when administering the site.')
  );

  return system_settings_form($form);  
}

function js_logout_settings_validate($form, &$form_state) {
  // validate timeout
  $timeout = $form_state['values']['js_logout_timeout'];
  if (!is_numeric($timeout) || ((int)$timeout != $timeout) || $timeout < 60) {
    form_set_error('js_logout_timeout', t('The timeout must be an integer greater than 60.'));
  }
    
  // validate redirect path
  if (!menu_valid_path(array('link_path' => $form_state['values']['js_logout_redirect_url']))) {
    form_set_error('js_logout_redirect_url', t('The redirect URL you entered is not a valid path on this site.'));
  }
  
  // ensure message is plain text
  $form_state['values']['js_logout_message'] = check_plain($form_state['values']['js_logout_message']);
}