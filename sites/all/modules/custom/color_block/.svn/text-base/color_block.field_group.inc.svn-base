<?php
/**
 * @file
 * color_block.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function color_block_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_color_block_style|bean|color_block|form';
  $field_group->group_name = 'group_color_block_style';
  $field_group->entity_type = 'bean';
  $field_group->bundle = 'color_block';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block Style',
    'weight' => '2',
    'children' => array(
      0 => 'field_cb_rendering_style',
      1 => 'field_cb_background_color',
      2 => 'field_cb_icon',
      3 => 'field_cb_description',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-color-block-style field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_color_block_style|bean|color_block|form'] = $field_group;

  return $export;
}
