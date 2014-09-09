<?php
/**
 * @file
 * travel_insurance_price_entity_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function travel_insurance_price_entity_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function travel_insurance_price_entity_type_eck_bundle_info() {
  $items = array(
    'insurance_price_life_insurance_price' => array(
      'machine_name' => 'insurance_price_life_insurance_price',
      'entity_type' => 'insurance_price',
      'name' => 'life_insurance_price',
      'label' => 'Life Insurance Price',
    ),
    'insurance_price_visitor_to_canada_insurance_price' => array(
      'machine_name' => 'insurance_price_visitor_to_canada_insurance_price',
      'entity_type' => 'insurance_price',
      'name' => 'visitor_to_canada_insurance_price',
      'label' => 'Visitor to canada Insurance Price',
    ),
  );
  return $items;
}
