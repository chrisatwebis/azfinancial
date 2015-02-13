<?php
/**
*
* Visitor to canada insurance related api functions.
**/


/**
*
* Get the available coverage for visitor to canada insurance
**/
function webis_insurance_quoting_engine_vtc_get_coverage(){
  $coverage = array(
    ""        => "- Select -",
    "10000"   => "$10,000 CAD",
    "15000"   => "$15,000 CAD",
    "20000"   => "$20,000 CAD",
    "25000"   => "$25,000 CAD",
    "30000"   => "$30,000 CAD",
    "40000"   => "$40,000 CAD",
    "50000"   => "$50,000 CAD",
    "60000"   => "$60,000 CAD",
    "80000"   => "$80,000 CAD",
    "100000"  => "$100,000 CAD",
    "150000"  => "$150,000 CAD",
    "200000"  => "$200,000 CAD",
    "250000"  => "$250,000 CAD",
    "300000"  => "$300,000 CAD", 
  );
  return $coverage;
}

/**
* Build an options list for use by webforms.
*/
function webis_insurance_quoting_engine_vtc_get_deductible() {   
  
  $options = array(
    ""        => "- Select -",
    "0"       => "$0 CAD",
    "50"      => "$50 CAD",
    "75"      => "$75 CAD",
    "100"     => "$100 CAD",
    "250"     => "$250 CAD",
    "500"     => "$500 CAD",
    "1000"    => "$1,000 CAD",
    "2500"    => "$2,500 CAD",
    "3000"    => "$3,000 CAD",
    "5000"    => "$5,000 CAD",
    "10000"   => "$10,000 CAD"
  );
  
  return $options;
  
}

/**
*
* Get the next level coverage by current coverage
**/
function webis_insurance_quoting_engine_vtc_get_next_coverage ($coverage) {
  $coverage_arr = webis_insurance_quoting_engine_vtc_get_coverage();
  $keys = array_keys($coverage_arr);
  foreach ($keys as $k => $v ) {
    if ($v == $coverage) {
      $next_coverage = !empty($keys[$k+1]) ? $keys[$k+1] : null;
      return $next_coverage;
    }
  }
}

/**
*
* Get the previous level coverage by current coverage
**/
function webis_insurance_quoting_engine_vtc_get_previous_coverage ($coverage) {
  $coverage_arr = webis_insurance_quoting_engine_vtc_get_coverage();
  $keys = array_keys($coverage_arr);
  foreach ($keys as $k => $v ) {
    if ($v == $coverage) {
      $previous_coverage = !empty($keys[$k-1]) ? $keys[$k-1] : null;
      return $previous_coverage;
    }
  }
}

/**
* 
* Calculate the premium - web api
* Example: get-a-quote/visitor-to-canada-insurance/calculate-premium?pid=1&effective=2015-01-01&expiry=2015-01-01&coverage=50000&deductible=1010&insured_bod=1950-01-01&spmcc=0
**/
function webis_insurance_quoting_engine_wapi_vtc_cal_premium () {
  
  $query = drupal_get_query_parameters();
  $response = array();
  $response['status_code'] = 1;
  $response['message'] = "";
  $response['query'] = $query;
  $mandatory_args = array('pid', 'effective', 'expiry', 'coverage', 'deductible', 'insured_bod');

  /*validate the query to make sure we have what we need.
  if the query is missing, return the error response.*/
  $missing_args = array();
  foreach ($mandatory_args as $key => $value) {
    if (!isset($query[$value])) {
      $response['status_code'] = 0;
      $missing_args[] = $value;
    }
  }
  if (!$response['status_code']) {
    $response['message'] = t("The following URL arguments are needed:");
    foreach ($missing_args as $key => $value) {
      if ($key == (count($missing_args) - 1) ) {
        $response['message'] .= " ".$value."!";
      }
      else {
        $response['message'] .= " ".$value.",";        
      }
    }
    drupal_json_output($response);
    drupal_exit();
  }

  $plan = entity_load_single(INSURANCE_PRICE_ENTITY_NAME, $query['pid']);
  if (empty($plan)) {
    $response['status_code'] = 0;
    $response['message'] .= 'The pid is invalid.';
    drupal_json_output($response);
    drupal_exit();
  }

  $start_time = strtotime($query['effective']);
  $end_time   = strtotime($query['expiry']);
  $dob        = $query['insured_bod'];

  $which_age = webis_insurance_quoting_engine_get_tip_age_to_cal_premium($plan);
  switch ($which_age) {
    case 'effective_date_age':
      //get age from birthday and start time
      $age = webis_insurance_quoting_engine_age_from_dob($dob, $start_time);
      break;
    case 'purchase_date_age':
    default:
      //get age from birthday
      $age = webis_insurance_quoting_engine_age_from_dob($dob);
      break;
  }
  $coverage = $query['coverage'];
  $deductible = $query['deductible'];

  //total days
  $days = (($end_time - $start_time)/(60*60*24))+1;
  $days = round($days);
  $premium['spmcc'] = webis_insurance_quoting_engine_get_tip_total_price_by_deductible($plan, $age, $coverage, TRUE, $days, $deductible);
  $premium['no_spmcc'] = webis_insurance_quoting_engine_get_tip_total_price_by_deductible($plan, $age, $coverage, FALSE, $days, $deductible);
  if (!empty($premium['spmcc'])) {
    $premium['spmcc'] = round($premium['spmcc'], 2);
  }
  if (!empty($premium['no_spmcc'])) {
    $premium['no_spmcc'] = round($premium['no_spmcc'], 2);
  }
  $response['message'] = 'Success!';
  $response['premium'] = $premium;
  if (isset($query['storage'])) {
    $response['storage'] = $query['storage'];    
  }
  drupal_json_output($response);
  drupal_exit();

}

/**
* Get the deductible list and coverage list of price entity - web api
*
* URL Argument
*   pid - price entity id
*   age - age string of the insurer, e.g. 10_65_71 (3 insurers, the ages are 10, 65 and 71)
*   intersect - whether the result should be in
**/
function webis_insurance_quoting_engine_wapi_vtc_get_deductible_coverage() {
  $query = drupal_get_query_parameters();
  // $query = $_POST;
  $response = array();
  $response['status_code'] = 1;
  $response['message'] = "";
  $response['query'] = $query;
  $mandatory_args = array('pid');

  /*validate the query to make sure we have what we need.
  if the query is missing, return the error response.*/
  $missing_args = array();
  foreach ($mandatory_args as $key => $value) {
    if (!isset($query[$value])) {
      $response['status_code'] = 0;
      $missing_args[] = $value;
    }
  }
  //if missing arguments, then return the error message.
  if (!$response['status_code']) {
    $response['message'] = t("The following URL arguments are needed:");
    foreach ($missing_args as $key => $value) {
      if ($key == (count($missing_args) - 1) ) {
        $response['message'] .= " ".$value."!";
      }
      else {
        $response['message'] .= " ".$value.",";        
      }
    }
    drupal_json_output($response);
    drupal_exit();
  }

  //if there is no plan for provided pid, then return error message.
  $plan = entity_load_single(INSURANCE_PRICE_ENTITY_NAME, $query['pid']);
  if (empty($plan)) {
    $response['status_code'] = 0;
    $response['message'] .= 'The pid is invalid.';
    drupal_json_output($response);
    drupal_exit();
  }

  $rate_adjustment = webis_insurance_quoting_engine_get_tip_rate_adjustment($plan);
  // print_r($rate_adjustment);
  $deductibles = array();
  $coverages = array();

  //check whether array operation should be: intersect or merge.
  $array_intersect = true;
  if (isset($query['intersect']) && ($query['intersect'] == 'false')) {
    $array_intersect = false;
  }

  //if the age argument is passed.
  // var_dump( !empty($query['age']) );
  if (!empty($query['age'])) {
    $age_arr = explode("_", $query['age']);
    foreach ($age_arr as $age_key => $age_value) {
      if (strlen($age_value) > 0) {
        $age = intval($age_value);
        $deductible_age = array();
        $coverage_age = array();
        foreach ($rate_adjustment as $key => $value) {
          if (($value['min_age'] <= $age) && ($age <= $value['max_age'])) {
            foreach ($value['deductible'] as $key_1 => $deductible) {
              //check whether coverage value is passed.
              if (isset($query['coverages']) && ($query['coverages'] != "null")) {
                 if (in_array($query['coverages'], $deductible['coverages'])) {
                  $deductible_age[] = $deductible['amount'];                  
                 }
              }
              else {
                $deductible_age[] = $deductible['amount'];
              }
              $coverage_age = array_merge($coverage_age, $deductible['coverages']);                
            }
          }
        }
        //if we need to intersect the array.
        if ($array_intersect) {
          //if it is empty, it means this is the first time of the loop.
          if (empty($deductibles)) {
            $deductibles = $deductible_age;
          }
          else {
            $deductibles = array_intersect($deductibles, $deductible_age);            
          }
          //if it is empty, it means this is the first time of the loop.
          if (empty($coverages)) {
            $coverages = $coverage_age;
          }
          else {
            $coverages = array_intersect($coverages, $coverage_age);
          }
          //if the intersect result is empty, then return the loop immediately.
          if (empty($deductibles) || empty($coverages)) {
            break;
          }
        }
        else {
          //if we merge the array
          $deductibles = array_merge($deductibles, $deductible_age);
          $coverages = array_merge($coverages, $coverage_age);
        }
      }
    }
  }
  else {
    foreach ($rate_adjustment as $key => $value) {
      foreach ($value['deductible'] as $key_1 => $deductible) {
        //check whether coverage value is passed.
        if (isset($query['coverages']) && ($query['coverages'] != "null")) {
          if (in_array($query['coverages'], $deductible['coverages'])) {
            $deductibles[] = $deductible['amount'];
          }
        }
        else {
          $deductibles[] = $deductible['amount'];
        }
        $coverages = array_merge($coverages, $deductible['coverages']);
      }
    }
  }

  $deductibles = array_unique($deductibles);
  sort($deductibles);
  $coverages = array_unique($coverages);
  sort($coverages);

  $response['message']     = 'Success!';
  $response['deductibles'] = $deductibles;
  $response['coverages']   = $coverages;
  drupal_json_output($response);
  drupal_exit();
}
