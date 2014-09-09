<?php
/**
 * @file
 * travel_insurance_price_entity_type.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function travel_insurance_price_entity_type_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'travel_insurance_price|travel_insurance_price|default';
  $ds_layout->entity_type = 'travel_insurance_price';
  $ds_layout->bundle = 'travel_insurance_price';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_tip_age_to_cal_premium',
        1 => 'field_tip_rate_schedule',
        2 => 'field_tip_rate_schedule_no_spmcc',
        3 => 'field_tip_rate_adjustment',
      ),
    ),
    'fields' => array(
      'field_tip_age_to_cal_premium' => 'ds_content',
      'field_tip_rate_schedule' => 'ds_content',
      'field_tip_rate_schedule_no_spmcc' => 'ds_content',
      'field_tip_rate_adjustment' => 'ds_content',
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
  $export['travel_insurance_price|travel_insurance_price|default'] = $ds_layout;

  return $export;
}
