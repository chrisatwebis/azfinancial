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
function webis_insurance_quoting_engine_vtc_get_next_coverage($coverage){
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
function webis_insurance_quoting_engine_vtc_get_previous_coverage($coverage){
  $coverage_arr = webis_insurance_quoting_engine_vtc_get_coverage();
  $keys = array_keys($coverage_arr);
  foreach ($keys as $k => $v ) {
    if ($v == $coverage) {
      $previous_coverage = !empty($keys[$k-1]) ? $keys[$k-1] : null;
      return $previous_coverage;
    }
  }
}