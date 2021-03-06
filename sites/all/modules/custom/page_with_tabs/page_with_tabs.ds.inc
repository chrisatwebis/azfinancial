<?php
/**
 * @file
 * page_with_tabs.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function page_with_tabs_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|page_with_tabs|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'page_with_tabs';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'body',
        1 => 'field_pwt_tab',
        2 => 'tab_clone',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
      'field_pwt_tab' => 'ds_content',
      'tab_clone' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|page_with_tabs|default'] = $ds_layout;

  return $export;
}
