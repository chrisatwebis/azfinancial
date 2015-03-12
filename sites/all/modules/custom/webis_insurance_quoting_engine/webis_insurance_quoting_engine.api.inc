<?php

require_once('webis_insurance_quoting_engine.visitor_to_canada.api.inc');

/**
* Get the entities of the given insurance type.
*/
function webis_insurance_quoting_engine_get_plans($insurance_type){
  $ids = webis_insurance_quoting_engine_get_plan_ids($insurance_type);
  if (!empty($ids)) {
    $entities = entity_load(INSURANCE_PRICE_ENTITY_NAME, $ids);
    dpm($entities);
    return $entities;
  }
}

function webis_insurance_quoting_engine_get_plan_ids($insurance_type){
  $entityQuery = new EntityFieldQuery();
  switch($insurance_type){
    case VISITOR_INSURANCE:
      $entities_query = $entityQuery->entityCondition('entity_type', INSURANCE_PRICE_ENTITY_NAME)
        ->entityCondition('bundle', VISITOR_INSURANCE_BUNDLE_NAME);
        // ->propertyOrderBy('title', 'ASC');
      break;
    case LIFE_INSURANCE:
      $entities_query = $entityQuery->entityCondition('entity_type', INSURANCE_PRICE_ENTITY_NAME)
        ->entityCondition('bundle', LIFE_INSURANCE_BUNDLE_NAME);
        // ->propertyOrderBy('title', 'ASC');
      break;
    default:
      break;
  }
  $result = $entities_query->execute();
  if(!empty($result)){
    foreach ($result as $value) {
      $ids = array_keys($value);
      break;
    }
    return $ids;
  }
}

/**
* Get the 'field_tip_age_to_cal_premium' field by entity.
* @argument
* $entity - field_collection entity
*/
function webis_insurance_quoting_engine_get_tip_age_to_cal_premium($entity){
  $field_tip_age_to_cal_premium = field_get_items(INSURANCE_PRICE_ENTITY_NAME, $entity, "field_tip_age_to_cal_premium");
  return $field_tip_age_to_cal_premium[0]['value'];
}

/**
* Get the rate adjustment by entity.
* @argument
* $entity - field_collection entity
*/
function webis_insurance_quoting_engine_get_tip_rate_adjustment($entity){
  $field_ids = field_get_items(INSURANCE_PRICE_ENTITY_NAME, $entity, "field_tip_rate_adjustment");
  if (!empty($field_ids) && is_array($field_ids)) {
    $fc_ids = array();
    foreach ($field_ids as $key => $field_collection) {
      $fc_ids[] = $field_collection['value'];
    }
    $field_collection_query = new EntityFieldQuery();
    $field_collection_entities = entity_load('field_collection_item', $fc_ids);
    $rate_adjustment_array = array();
    foreach ($field_collection_entities as $key => $field_collection_entity) {
      //get tip deductible
      $field_tip_deductible = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_deductible');
      $deductibles_entity_ids = array();
      foreach ($field_tip_deductible as $key_1 => $deductible) {
        $deductibles_entity_ids[] = $deductible['value'];
      }
      $deductibles = entity_load('field_collection_item', $deductibles_entity_ids);
      $deductibles_array = array();
      foreach ($deductibles as $key_1 => $deductible) {
        $amount = field_get_items('field_collection_item', $deductible, 'field_tip_deductible_amount');
        $amount = isset($amount) ? $amount[0]['value'] : "";
        $discount = field_get_items('field_collection_item', $deductible, 'field_tip_deductible_discount');
        $discount = isset($discount) ? $discount[0]['value'] : "";
        $max_discount = field_get_items('field_collection_item', $deductible, 'field_tip_max_discount_amount');
        $max_discount = isset($max_discount) ? $max_discount[0]['value'] : "";
        $coverages = field_get_items('field_collection_item', $deductible, 'field_tip_coverage_n');
        $coverages_array = array();
        foreach ($coverages as $key_2 => $value_2) {
          $coverages_array[] = $value_2['value'];
        }
        $deductibles_array[$key_1]['amount'] = $amount;
        $deductibles_array[$key_1]['discount'] = $discount;
        $deductibles_array[$key_1]['max_discount'] = $max_discount;
        $deductibles_array[$key_1]['coverages'] = $coverages_array;
        $deductibles_array[$key_1]['item_id'] = $key_1;
      }

      //get the min age
      $min_age = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_min_age');
      $min_age = $min_age[0]['value'];
      //get the max age
      $max_age = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_max_age');
      $max_age = $max_age[0]['value'];
      //put info back to our array.
      $rate_adjustment_array[$key]['min_age'] = $min_age;
      $rate_adjustment_array[$key]['max_age'] = $max_age;

      $rate_adjustment_array[$key]['deductible'] = $deductibles_array;
    }
    return $rate_adjustment_array;
  }
}

/**
* Get the 'field_tip_rate_schedule' or 'field_tip_rate_schedule_no_spmcc' field by entity.
* @argument
* $entity - field_collection entity
*/
function webis_insurance_quoting_engine_get_tip_rate_schedule($entity, $field_name){
  $field_tip_rate_schedule = field_get_items(INSURANCE_PRICE_ENTITY_NAME, $entity, $field_name);
  $rate =  $field_tip_rate_schedule[0]['value'];
  $rate = unserialize($rate);  
  unset($rate['rebuild']);
  unset($rate['import']);
  $new_rate = array();
  foreach ($rate as $key => $val) {
    //rebuild the arrary from 1 dimension array to 2 dimension array.
    $key_arr = explode("_",$key);
    $new_rate[$key_arr[1]][$key_arr[2]] = $val;
  }
  return $new_rate;
}

/**
* Get the base price by the 'insurance_id', 'age', 'coverage'
* @arguments
* $insurance_id - insurance entity id
* $age - the age of the insured
* $coverage - the coverage of the policy
* $spmcc - whether use the stable pre-existing medical condition coverage. 
*/
function webis_insurance_quoting_engine_get_tip_base_price($entity, $age, $coverage, $spmcc = TRUE){
  if (!empty($entity)) {
    //get the rate schedule.
    if ($spmcc) {
      $rate_schedule = webis_insurance_quoting_engine_get_tip_rate_schedule($entity, "field_tip_rate_schedule");
    }
    else {
      $rate_schedule = webis_insurance_quoting_engine_get_tip_rate_schedule($entity, "field_tip_rate_schedule_no_spmcc");    
    }
    //if the rate schedule is not empty.
    if (!empty($rate_schedule) && is_array($rate_schedule)) {
      $none_str = "n/a";
      //row is the horizontal count.
      $row = "";
      foreach ($rate_schedule as $key => $val) {
        $age_ranges_str = $val[0];
        //"0-25"
        if (strpos($age_ranges_str,"-") !== false) {
          $age_arr = explode("-",$age_ranges_str);
          $age_arr[0] = intval($age_arr[0]);
          $age_arr[1] = intval($age_arr[1]);
          if ( $age_arr[0] <= $age && $age <= $age_arr[1] ) {
            $row = $key;
            break;
          }
        }
      }
      //Column is the vertical count.
      $column = "";
      foreach ($rate_schedule[0] as $key => $val) {
        if($val == $coverage) {
          $column = $key;
          break;
        }
      }
      //Get the price here.
      if (!empty($row) && !empty($column)) {
        //If price is found in the table, calculate it.
        $price = $rate_schedule[$row][$column];
        if ($price == $none_str) {
          $price = null;
        }
      }
      else {//If the price couldn't be found in the table.
        $price = null;
      }
      return $price;
    }
  }
}

/**
* Get the 'field_tip_surcharge_to_premium' field by entity.
* @argument
* $entity - insurance price entity
*/
function webis_insurance_quoting_engine_get_surcharge_to_premium($entity){
  $field_ids = field_get_items(INSURANCE_PRICE_ENTITY_NAME, $entity, 'field_tip_surcharge_to_premium');
  if (!empty($field_ids) && is_array($field_ids)) {
    $fc_ids = array();
    foreach ($field_ids as $key => $field_collection) {
      $fc_ids[] = $field_collection['value'];
    }
    $field_collection_query = new EntityFieldQuery();
    $field_collection_entities = entity_load('field_collection_item', $fc_ids);
    $surcharge_to_premium_array = array();
    foreach ($field_collection_entities as $key => $field_collection_entity) {
      //get the min age
      $min_age = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_min_age');
      $min_age = $min_age[0]['value'];
      //get the max age
      $max_age = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_max_age');
      $max_age = $max_age[0]['value'];
      //get the surcharge percentage
      $surcharge_percentage = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_surcharge_percentage');
      $surcharge_percentage = $surcharge_percentage[0]['value'];
      //get the discount base
      $discount_base = field_get_items('field_collection_item', $field_collection_entity, 'field_tip_discount_base');
      $discount_base = $discount_base[0]['value'];

      $surcharge_to_premium_array[$key]['min_age'] = $min_age;
      $surcharge_to_premium_array[$key]['max_age'] = $max_age;
      $surcharge_to_premium_array[$key]['surcharge_percentage'] = $surcharge_percentage;
      $surcharge_to_premium_array[$key]['discount_base'] = $discount_base;
    }
    return $surcharge_to_premium_array;
  }
}

/**
* Get the final price by the 'insurance_id', 'age', 'coverage', 'deductible'
* @arguments
* $entity - insurance price entity
* $age - the age of the insured
* $coverage - the coverage of the policy
* $spmcc - whether use the stable pre-existing medical condition coverage. 
* $days - the total days of the policy
* $deductible_amount - the deductible of the policy
*
* @return - final total price
*/
function webis_insurance_quoting_engine_get_tip_total_price_by_deductible($entity, $age, $coverage, $spmcc = TRUE, $days, $deductible_amount){
  $deductible_found = false;
  $coverage_found = false;
  if (!empty($entity)) {
    $base_price = webis_insurance_quoting_engine_get_tip_base_price($entity, $age, $coverage, $spmcc);
    if (!empty($base_price)) {
      $coverage_found = true;
      $rate_adjustment = webis_insurance_quoting_engine_get_tip_rate_adjustment($entity);
      $discount = 0;
      foreach ($rate_adjustment as $key => $value) {
        if ($value['min_age'] <= $age && $age <= $value['max_age']) {
          foreach ($value['deductible'] as $key_1 => $value_1) {
            if ($value_1['amount'] == $deductible_amount && in_array($coverage, $value_1['coverages'])) {
              $discount = $value_1['discount'];
              $max_discount = isset($value_1['max_discount']) ? $value_1['max_discount'] : "";
              $deductible_found = true;
            }
          }
        }
      }
      if ($deductible_found && $coverage_found) {
        $total_base_price = $base_price * $days;
        $total_final_price = ($discount + 1) * $total_base_price;
        //if there is max discount, and there is actual discount
        if (!empty($max_discount) && $discount < 0) {
          $total_discount = ($total_base_price - $total_final_price) > $max_discount ? $max_discount : ($total_base_price - $total_final_price);
          $total_final_price = $total_base_price - $total_discount;
        }
        return $total_final_price;
      }
    }
    else {
      //If the base_price is still empty, then try to find out the base_price from surcharge premium of price of no_spmcc.
      $surcharge_to_premium_array = webis_insurance_quoting_engine_get_surcharge_to_premium($entity);
      //if this is for finding the price of spmcc, and the surcharge is set for this insurance price.
      if ($spmcc && !empty($surcharge_to_premium_array)) {
        //get the price of no_spmcc.
        $base_price_no_spmcc = webis_insurance_quoting_engine_get_tip_base_price($entity, $age, $coverage, FALSE);
        $total_final_price_no_spmcc = webis_insurance_quoting_engine_get_tip_total_price_by_deductible($entity, $age, $coverage, FALSE, $days, $deductible_amount);
        //if we could find out the price for no_spmcc, then use the no_spmcc to calculate the price of spmcc
        if (!empty($base_price_no_spmcc)) {
          foreach ($surcharge_to_premium_array as $key => $value) {
            //we will only find the first match of age.
            if ($value['min_age'] <= $age && $age <= $value['max_age']) {
              switch ($value['discount_base']) {
                case 'no_spmcc':
                  $surcharge_amount = $base_price_no_spmcc * $value['surcharge_percentage'] * $days;
                  $total_final_price = $total_final_price_no_spmcc + $surcharge_amount;
                  break;
                case 'spmcc':
                  $total_final_price = $total_final_price_no_spmcc * (1 + $value['surcharge_percentage']);
                default:
                  # code...
                  break;
              }
              return $total_final_price;
            }
          }        
        }
      }
    }
  }
}

/**
* Get the final price by the 'insurance_id', 'age', 'coverage', 'deductible'
* @arguments
* $insurance_id - insurance entity id
* $age - the age of the insured
* $coverage - the coverage of the policy
* $spmcc - whether use the stable pre-existing medical condition coverage. 
* $days - the total days of the policy
* $deductible_amount - the deductible of the policy
*/
function webis_insurance_quoting_engine_get_tip_total_price($entity, $age, $coverage, $spmcc = TRUE, $days){
  $price_array = array();
  if (!empty($entity)) {
    $rate_adjustment = webis_insurance_quoting_engine_get_tip_rate_adjustment($entity);
    foreach ($rate_adjustment as $key => $value) {
      if ($value['min_age'] <= $age && $age <= $value['max_age']) {
        foreach ($value['deductible'] as $key_1 => $value_1) {
          $total_final_price = webis_insurance_quoting_engine_get_tip_total_price_by_deductible($entity, $age, $coverage, $spmcc, $days, $value_1['amount']);
          if (!empty($total_final_price)) {
            $price_array[$value_1['amount']] = round($total_final_price, 2);
          }
        }
      }
    }
  }
  if (!empty($price_array)) {
    return $price_array;
  }
}