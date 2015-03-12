<?php

/**
 * @file
 * Hooks provided by mmenu module.
 */


/**
 * Allows modules to add more mmenus.
 */
function hook_mmenu() {
  $module_path = drupal_get_path('module', 'mmenu');

  return array(
    'mmenu_left' => array(
      'enabled' => TRUE,
      'name' => 'mmenu_left',
      'title' => t('Left menu'),
      'blocks' => array(
        array(
          'title' => t('Main menu'),
          'module' => 'system',
          'delta' => 'main-menu',
          'collapsed' => FALSE,
          'wrap' => FALSE,
        ),
        array(
          'title' => t('Management'),
          'module' => 'system',
          'delta' => 'management',
          'collapsed' => FALSE,
          'wrap' => FALSE,
          'menu_parameters' => array(
            'min_depth' => 2,
          ),
        ),
      ),
      'options' => array(
        'position' => 'left',
        'classes' => 'mm-light',
      ),
      'configurations' => array(),
      // Adds your own JS handler if you want.
      'custom' => array(
        'js' => array(
          $module_path . '/js/handlers/mmenu_example.handler.js',
        ),
      ),
    ),
  );
}

/**
 * Allows modules to alter mmenu settings.
 */
function hook_mmenu_alter(&$mmenus) {
  $mmenus['mmenu_left']['enabled'] = FALSE;
}

/**
 * Allows modules to add more mmenu classes.
 */
function hook_mmenu_class() {
  $module_path = drupal_get_path('module', 'mmenu');
  return array(
    'mm-basic' => array(
      'name' => 'mm-basic',
      'css' => array(
        $module_path . '/classes/mm-basic/css/mm-basic.css',
      ),
    ),
  );
}

/**
 * Allows modules to alter mmenu class settings.
 */
function hook_mmenu_class_alter(&$classes) {
  $module_path = drupal_get_path('module', 'mmenu');
  $classes['mm-basic']['css'] = array(
    $module_path . '/classes/mm-basic/css/custom.css',
  );
}
