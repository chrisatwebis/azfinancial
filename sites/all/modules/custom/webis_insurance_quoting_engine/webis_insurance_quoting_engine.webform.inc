<?php

/**
* Build an options list for use by webforms.
*/
function webis_insurance_quoting_engine_webform_options_available_province() {   
  return array(
    'AB' => 'Alberta',
    'BC' => 'British Columbia',
    'MB' => 'Manitoba',
    'NB' => 'New Brunswick',
    'NL' => 'Newfoundland and Labrador',
    'NS' => 'Nova Scotia',
    'ON' => 'Ontario',
    'PE' => 'Prince Edward Island',
    'QC' => 'Quebec',
    'SK' => 'Saskatchewan',
    'NT' => 'Northwest Territories',
    'NU' => 'Nunavut',
    'YT' => 'Yukon Territory',
  );
}

/**
* Build an options list for use by webforms.
*/
function webis_insurance_quoting_engine_webform_options_gender() {   
  return array(
    'male' => 'Male',
    'female' => 'Female',
  );
}
/**
* Get a list of available insurance plan
* Build an options list for use by webforms.
*/
function webis_insurance_quoting_engine_webform_options_available_visitor_to_canada_insurance(){
  $plans = webis_insurance_quoting_engine_get_plans(VISITOR_INSURANCE);
  $options = array();
  foreach ($plans as $key => $plan) {
    $options[$plan->id] = $plan->title;
  }
  return $options;
}