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
    "10000" => "$10000 CAD",
    "15000" => "$15000 CAD",
    "20000" => "$20000 CAD",
    "25000" => "$25000 CAD",
    "30000" => "$30000 CAD",
    "40000" => "$40000 CAD",
    "50000" => "$50000 CAD",
    "60000" => "$60000 CAD",
    "80000" => "$80000 CAD",
    "100000" => "$100000 CAD",
    "150000" => "$150000 CAD",
    "200000" => "$200000 CAD",
    "250000" => "$250000 CAD",
    "300000" => "$300000 CAD", 
  );
  return $coverage;
}

/**
* Build an options list for use by webforms.
*/
function webis_insurance_quoting_engine_vtc_get_deductible() {   
  
  $options = array(
    "0"=>"$0 CAD",
    "50"=>"$50 CAD",
    "75"=>"$75 CAD",
    "100"=>"$100 CAD",
    "250"=>"$250 CAD",
    "500"=>"$500 CAD",
    "1000"=>"$1000 CAD",
    "3000"=>"$3000 CAD",
    "5000"=>"$5000 CAD",
    "10000"=>"$10000 CAD"
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
* Calculate the premium
* Example: get-a-quote/visitor-to-canada-insurance/calculate-premium?pid=1&effective=2015-01-01&expiry=2015-01-01&coverage=50000&deductible=1010&insured_bod=1950-01-01&spmcc=0
**/
function webis_insurance_quoting_engine_vtc_cal_premium () {
  
  $query = drupal_get_query_parameters();

  $response = array();
  $response['status_code'] = 1;
  $response['message'] = "";
  $mandatory_args = array('pid', 'effective', 'expiry', 'coverage', 'deductible', 'insured_bod', 'spmcc');

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
  $spmcc = ($query['spmcc'] == 1) ? TRUE : FALSE;

  //total days
  $days = (($end_time - $start_time)/(60*60*24))+1;
  $days = round($days);
  $premium = webis_insurance_quoting_engine_get_tip_total_price_by_deductible($plan, $age, $coverage, $spmcc, $days, $deductible);

  $response['message'] = 'Success!';
  $response['premium'] = $premium;
//  return $response['message'];
  drupal_json_output($response);
  drupal_exit();

}

