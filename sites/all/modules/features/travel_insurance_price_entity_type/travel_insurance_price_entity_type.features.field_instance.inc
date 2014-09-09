<?php
/**
 * @file
 * travel_insurance_price_entity_type.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function travel_insurance_price_entity_type_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_tip_deductible-field_tip_coverage_n'
  $field_instances['field_collection_item-field_tip_deductible-field_tip_coverage_n'] = array(
    'bundle' => 'field_tip_deductible',
    'default_value' => array(
      0 => array(
        'value' => 10000,
      ),
      1 => array(
        'value' => 15000,
      ),
      2 => array(
        'value' => 20000,
      ),
      3 => array(
        'value' => 25000,
      ),
      4 => array(
        'value' => 30000,
      ),
      5 => array(
        'value' => 40000,
      ),
      6 => array(
        'value' => 50000,
      ),
      7 => array(
        'value' => 60000,
      ),
      8 => array(
        'value' => 80000,
      ),
      9 => array(
        'value' => 100000,
      ),
      10 => array(
        'value' => 150000,
      ),
      11 => array(
        'value' => 200000,
      ),
      12 => array(
        'value' => 250000,
      ),
      13 => array(
        'value' => 300000,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_coverage_n',
    'label' => 'Applicable Coverage',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_deductible-field_tip_deductible_amount'
  $field_instances['field_collection_item-field_tip_deductible-field_tip_deductible_amount'] = array(
    'bundle' => 'field_tip_deductible',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_deductible_amount',
    'label' => 'Deductible Amount',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_deductible-field_tip_deductible_discount'
  $field_instances['field_collection_item-field_tip_deductible-field_tip_deductible_discount'] = array(
    'bundle' => 'field_tip_deductible',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please indicate the discount for this deductible. <br>
( 1+value )*price = sell price.
<br>
E.g if you would like to offer 10% OFF, then you should put "-0.1".',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_deductible_discount',
    'label' => 'Discount',
    'required' => 1,
    'settings' => array(
      'max' => '',
      'min' => -1,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_deductible-field_tip_max_discount_amount'
  $field_instances['field_collection_item-field_tip_deductible-field_tip_max_discount_amount'] = array(
    'bundle' => 'field_tip_deductible',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please indicate whether there will be maximum discount amount for applying the discount to the current deductible.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_max_discount_amount',
    'label' => 'Max Discount Amount',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_rate_adjustment-field_tip_deductible'
  $field_instances['field_collection_item-field_tip_rate_adjustment-field_tip_deductible'] = array(
    'bundle' => 'field_tip_rate_adjustment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please provide the deducible rules.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_deductible',
    'label' => 'Deductibles',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_rate_adjustment-field_tip_max_age'
  $field_instances['field_collection_item-field_tip_rate_adjustment-field_tip_max_age'] = array(
    'bundle' => 'field_tip_rate_adjustment',
    'default_value' => array(
      0 => array(
        'value' => 200,
      ),
    ),
    'deleted' => 0,
    'description' => 'Please choose the maximum applicable age. The valid age is <b>less than or equal to</b> the maximum age.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_max_age',
    'label' => 'Maximum Age',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_tip_rate_adjustment-field_tip_min_age'
  $field_instances['field_collection_item-field_tip_rate_adjustment-field_tip_min_age'] = array(
    'bundle' => 'field_tip_rate_adjustment',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Please choose the minimum applicable age. The valid age is <b>greater than or equal to</b> the minimum age.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_tip_min_age',
    'label' => 'Minimum Age',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'insurance_price-visitor_to_canada_insurance_price-field_tip_age_to_cal_premium'
  $field_instances['insurance_price-visitor_to_canada_insurance_price-field_tip_age_to_cal_premium'] = array(
    'bundle' => 'visitor_to_canada_insurance_price',
    'default_value' => array(
      0 => array(
        'value' => 'purchase_date_age',
      ),
    ),
    'deleted' => 0,
    'description' => 'Please choose which age to calculate the policy premium.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'insurance_price',
    'field_name' => 'field_tip_age_to_cal_premium',
    'label' => 'Age to calculate premium',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'insurance_price-visitor_to_canada_insurance_price-field_tip_rate_adjustment'
  $field_instances['insurance_price-visitor_to_canada_insurance_price-field_tip_rate_adjustment'] = array(
    'bundle' => 'visitor_to_canada_insurance_price',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'insurance_price',
    'field_name' => 'field_tip_rate_adjustment',
    'label' => 'Rate Adjustment',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'insurance_price-visitor_to_canada_insurance_price-field_tip_rate_schedule'
  $field_instances['insurance_price-visitor_to_canada_insurance_price-field_tip_rate_schedule'] = array(
    'bundle' => 'visitor_to_canada_insurance_price',
    'default_value' => array(
      0 => array(
        'tablefield' => array(
          'cell_0_0' => '',
          'cell_0_1' => '',
          'cell_0_2' => '',
          'cell_0_3' => '',
          'cell_0_4' => '',
          'cell_1_0' => '',
          'cell_1_1' => '',
          'cell_1_2' => '',
          'cell_1_3' => '',
          'cell_1_4' => '',
          'cell_2_0' => '',
          'cell_2_1' => '',
          'cell_2_2' => '',
          'cell_2_3' => '',
          'cell_2_4' => '',
          'cell_3_0' => '',
          'cell_3_1' => '',
          'cell_3_2' => '',
          'cell_3_3' => '',
          'cell_3_4' => '',
          'cell_4_0' => '',
          'cell_4_1' => '',
          'cell_4_2' => '',
          'cell_4_3' => '',
          'cell_4_4' => '',
          'import' => array(
            'rebuild_field_tip_rate_schedule_0' => 'Upload CSV',
            'tablefield_csv_field_tip_rate_schedule_0' => '',
          ),
          'rebuild' => array(
            'count_cols' => 5,
            'count_rows' => 5,
            'rebuild' => 'Rebuild Table',
          ),
        ),
      ),
    ),
    'deleted' => 0,
    'description' => 'The rate schedule is a two-dimension table. Price table will show the age of the insured and the coverage of the insurance. The first row is the coverage amount; the first column is the age. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'tablefield',
        'settings' => array(),
        'type' => 'default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'insurance_price',
    'field_name' => 'field_tip_rate_schedule',
    'label' => 'Rate schedule with stable pre-existing medical condition',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'tablefield',
      'settings' => array(),
      'type' => 'tablefield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'insurance_price-visitor_to_canada_insurance_price-field_tip_rate_schedule_no_spmcc'
  $field_instances['insurance_price-visitor_to_canada_insurance_price-field_tip_rate_schedule_no_spmcc'] = array(
    'bundle' => 'visitor_to_canada_insurance_price',
    'default_value' => array(
      0 => array(
        'tablefield' => array(
          'cell_0_0' => '',
          'cell_0_1' => '',
          'cell_0_2' => '',
          'cell_0_3' => '',
          'cell_0_4' => '',
          'cell_1_0' => '',
          'cell_1_1' => '',
          'cell_1_2' => '',
          'cell_1_3' => '',
          'cell_1_4' => '',
          'cell_2_0' => '',
          'cell_2_1' => '',
          'cell_2_2' => '',
          'cell_2_3' => '',
          'cell_2_4' => '',
          'cell_3_0' => '',
          'cell_3_1' => '',
          'cell_3_2' => '',
          'cell_3_3' => '',
          'cell_3_4' => '',
          'cell_4_0' => '',
          'cell_4_1' => '',
          'cell_4_2' => '',
          'cell_4_3' => '',
          'cell_4_4' => '',
          'import' => array(
            'rebuild_field_tip_rate_schedule_no_spmcc_0' => 'Upload CSV',
            'tablefield_csv_field_tip_rate_schedule_no_spmcc_0' => '',
          ),
          'rebuild' => array(
            'count_cols' => 5,
            'count_rows' => 5,
            'rebuild' => 'Rebuild Table',
          ),
        ),
      ),
    ),
    'deleted' => 0,
    'description' => 'The rate schedule is a two-dimension table. Price table will show the age of the insured and the coverage of the insurance. The first row is the coverage amount; the first column is the age. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'tablefield',
        'settings' => array(),
        'type' => 'default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'insurance_price',
    'field_name' => 'field_tip_rate_schedule_no_spmcc',
    'label' => 'Rate schedule without stable pre-existing medical condition',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'tablefield',
      'settings' => array(),
      'type' => 'tablefield',
      'weight' => 6,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Age to calculate premium');
  t('Applicable Coverage');
  t('Deductible Amount');
  t('Deductibles');
  t('Discount');
  t('Max Discount Amount');
  t('Maximum Age');
  t('Minimum Age');
  t('Please choose the maximum applicable age. The valid age is <b>less than or equal to</b> the maximum age.');
  t('Please choose the minimum applicable age. The valid age is <b>greater than or equal to</b> the minimum age.');
  t('Please choose which age to calculate the policy premium.');
  t('Please indicate the discount for this deductible. <br>
( 1+value )*price = sell price.
<br>
E.g if you would like to offer 10% OFF, then you should put "-0.1".');
  t('Please indicate whether there will be maximum discount amount for applying the discount to the current deductible.');
  t('Please provide the deducible rules.');
  t('Rate Adjustment');
  t('Rate schedule with stable pre-existing medical condition');
  t('Rate schedule without stable pre-existing medical condition');
  t('The rate schedule is a two-dimension table. Price table will show the age of the insured and the coverage of the insurance. The first row is the coverage amount; the first column is the age. ');

  return $field_instances;
}
