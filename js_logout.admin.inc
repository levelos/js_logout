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
  
  $form['js_logout_use_watchdog'] = array(
   '#type' => 'checkbox',
   '#title' => t('Enable watchdog Automated Logout logging'),
   '#default_value' => variable_get('js_logout_use_watchdog', ''),
   '#description' => t('Enable logging of automatically logged out users')
  );

  $form['js_logout_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Logout Roles'),
    '#description' => t('Select which roles should be forced to logout.'),
    '#collapsible' => FALSE,
  );
  
  foreach (user_roles(TRUE) as $role) {
    $form['js_logout_roles']['js_logout_role_' . $role] = array(
      '#type' => 'checkbox',
      '#title' => $role,
      '#default_value' => variable_get('js_logout_role_' . $role, TRUE)
    );
  }
  
  $form['js_logout_redirect_url']  = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL at logout'),
    '#default_value' => variable_get('js_logout_redirect_url', '<front>'),
    '#size' => 40,
    '#description' => t('Send users to this page when they are logged out.')
  );

  $form['js_logout_message']  = array(
    '#type' => 'textarea',
    '#title' => t('Message to display in the logout dialog.'),
    '#default_value' => variable_get('js_logout_message', 'Your session has expired and you will be logged out.'),
    '#size' => 40,
  );

  // $form['autologout_one_session'] = array(
  //   '#type'  => 'fieldset',
  //   '#title' => t('One Session settings'),
  //   '#tree'  => TRUE,
  //   '#description' => t('One session will provide enforcement for "one session" per user. If a user logs in when another session for that user is active the other session will be deactivated. The user will be notified and the event logged.'),
  // );
  // $values = variable_get('autologout_one_session', 0);
  // 
  // foreach (user_roles(TRUE) as $role) {
  //   $this_value = $values[$role];
  // 
  //   $form['autologout_one_session'][$role] = array(
  //     '#type' => 'select',
  //     '#title' => $role,
  //     '#options' => array('1' => t('Enforce'), '0' => t('Exclude')),
  //     '#default_value' => (isset($values[$role]) ? $values[$role] : 0),
  //   );
  // }
  // $markup4_items = array(
  //   t('Enforce : all users in this role will be only allowed one session.'),
  //   t('Exclude : all users in this role are excluded from one session functionality.'),
  // );
  // $markup4 = theme('item_list', $markup4_items, t('Policy description')) . t('Please note: If a user is found to be in a role that allows disabling this feature, this overrides any enforcement');
  // $form['autologout_one_session']['markup4'] = array(
  //  '#type' => 'markup',
  //  '#value' => $markup4,
  // );
  
  return system_settings_form($form);  
}