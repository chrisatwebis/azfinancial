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

  $export['menu-menu-footer-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'menu-footer-menu',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'menu',
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
        'region' => 'footer',
        'status' => 1,
        'theme' => 'omega',
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'footer',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['menu-menu-header-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'menu-header-menu',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'menu',
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
        'weight' => -34,
      ),
      'sunflower' => array(
        'region' => 'user_bar',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -36,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['menu_block-1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 1,
    'i18n_block_language' => array(
      0 => 'zh-hans',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_first',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => '访加探亲旅游保险',
    'visibility' => 0,
  );

  $export['menu_block-2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 2,
    'i18n_block_language' => array(
      0 => 'en',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_second',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => 'Life Insurance',
    'visibility' => 0,
  );

  $export['menu_block-3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 3,
    'i18n_block_language' => array(
      0 => 'en',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_first',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => 'Visitor to Canada Insurance',
    'visibility' => 0,
  );

  $export['menu_block-4'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 4,
    'i18n_block_language' => array(
      0 => 'en',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_third',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -43,
      ),
    ),
    'title' => 'International Students Insurance',
    'visibility' => 0,
  );

  $export['menu_block-5'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 5,
    'i18n_block_language' => array(
      0 => 'en',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_third',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -40,
      ),
    ),
    'title' => 'Travel insurance for Canadians',
    'visibility' => 0,
  );

  $export['menu_block-6'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 6,
    'i18n_block_language' => array(
      0 => 'zh-hant',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_first',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => '訪加探親旅遊保險',
    'visibility' => 0,
  );

  $export['menu_block-7'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 7,
    'i18n_block_language' => array(
      0 => 'zh-hans',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_second',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => '人寿保险',
    'visibility' => 0,
  );

  $export['menu_block-8'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 8,
    'i18n_block_language' => array(
      0 => 'zh-hant',
    ),
    'i18n_mode' => 0,
    'module' => 'menu_block',
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
        'weight' => 0,
      ),
      'sunflower' => array(
        'region' => 'postscript_second',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => 0,
      ),
    ),
    'title' => '人壽保險',
    'visibility' => 0,
  );

  $export['menu_block-9'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 9,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'menu_block',
    'node_types' => array(),
    'pages' => '<front>',
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
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'sunflower',
        'weight' => -38,
      ),
    ),
    'title' => 'Main Menu',
    'visibility' => 0,
  );

  return $export;
}
