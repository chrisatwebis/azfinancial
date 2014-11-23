<?php
/**
 * @file
 * travel_insurance_price_entity_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function travel_insurance_price_entity_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tip_applicable_age_range|field_collection_item|field_tip_rate_adjustment|form';
  $field_group->group_name = 'group_tip_applicable_age_range';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_tip_rate_adjustment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Applicable Age Range',
    'weight' => '0',
    'children' => array(
      0 => 'field_tip_min_age',
      1 => 'field_tip_max_age',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-tip-applicable-age-range field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_tip_applicable_age_range|field_collection_item|field_tip_rate_adjustment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tip_applicable_age_range|field_collection_item|field_tip_surcharge_to_premium|form';
  $field_group->group_name = 'group_tip_applicable_age_range';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_tip_surcharge_to_premium';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Applicable Age Range',
    'weight' => '0',
    'children' => array(
      0 => 'field_tip_min_age',
      1 => 'field_tip_max_age',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-tip-applicable-age-range field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_tip_applicable_age_range|field_collection_item|field_tip_surcharge_to_premium|form'] = $field_group;

  return $export;
}
