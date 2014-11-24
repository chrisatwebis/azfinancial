<?php
/**
 * @file
 * page_with_tabs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function page_with_tabs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function page_with_tabs_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function page_with_tabs_image_default_styles() {
  $styles = array();

  // Exported image style: badge_medium.
  $styles['badge_medium'] = array(
    'name' => 'badge_medium',
    'label' => 'Badge Medium',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 350,
          'height' => 189,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function page_with_tabs_node_info() {
  $items = array(
    'page_with_tabs' => array(
      'name' => t('Page With Tabs'),
      'base' => 'node_content',
      'description' => t('Use <em>page with tabs</em> for your static content with multiple tabs.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
