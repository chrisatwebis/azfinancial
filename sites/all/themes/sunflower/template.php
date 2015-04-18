<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * Sunflower theme.
 */

/**
 * Theme the form element, add the error, when one occured.
 */
function sunflower_ife_form_element($variables) {
  $output = '';
  $output = $variables['element']['#children'];
  if (isset($variables['element']['#id'])) {
    $error = ife_errors('get', $variables['element']['#id']);
    if (!empty($error)) {
      $error_wrapped = '<div class="ife_messages messages error messages-inline">' . $error . '</div>';	
      $output =   preg_replace('#(.*)(</[a-z]+>)#si', '$1' . $error_wrapped . '$2', $output);
    }
  }
  return $output;
}

function sunflower_age_by_birthday($dob) {
  $birthday_time = strtotime($dob);
  $age = ( date("md", $birthday_time) > date("md") ? ( ( date("Y") - date("Y", $birthday_time) ) - 1 ) : ( date("Y") - date("Y", $birthday_time) ) );    
  $age = $age > 0 ? $age : 0;
  return $age;
}