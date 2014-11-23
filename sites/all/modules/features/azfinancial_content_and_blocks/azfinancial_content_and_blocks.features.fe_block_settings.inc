<?php
/**
 * @file
 * azfinancial_content_and_blocks.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function azfinancial_content_and_blocks_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-call_us_800'] = array(
    'cache' => -1,
    'custom' => 0,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'machine_name' => 'call_us_800',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ohm' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ohm',
        'weight' => 0,
      ),
      'omega' => array(
        'region' => 'branding',
        'status' => 1,
        'theme' => 'omega',
        'weight' => -27,
      ),
      'sunflower' => array(
        'region' => 'below_postscript',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -27,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['block-phone_800'] = array(
    'cache' => -1,
    'custom' => 0,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'machine_name' => 'phone_800',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ohm' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ohm',
        'weight' => 0,
      ),
      'omega' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'omega',
        'weight' => -24,
      ),
      'sunflower' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -41,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['block-phone_local'] = array(
    'cache' => -1,
    'custom' => 0,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'machine_name' => 'phone_local',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ohm' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ohm',
        'weight' => 0,
      ),
      'omega' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'omega',
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -40,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
