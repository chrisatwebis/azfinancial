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

// function sunflower_webform_mail_headers($variables) {

//   $headers = array(
//     'X-Mailer' => 'Drupal Webform (PHP/' . phpversion() . ')',
//   );

//   // Get the HTML Email field
//   $html_email_field = field_get_items('node', $variables['node'], 'field_html_email');

//   // Check if this webform node needs to send HTML emails
//   if (!empty($html_email_field)) {
//     $html = $html_email_field[0]['value'] == 1 ? TRUE : FALSE;
//   }

//   if ($html === TRUE) {
//     $headers['Content-Type'] = 'text/html; charset=UTF-8; format=flowed; delsp=yes';
//   }
//   dpm($variables);
//   dpm($headers);
//   return $headers;
// } 

function sunflower_age_by_birthday($birthday) {
  if (!empty($birthday)) {
    //explode the date to get month, day and year
    $birthday = explode("-", $birthday);
    //get age from date or birthday
    $age = (date("md", date("U", mktime(0, 0, 0, $birthday[0], $birthday[1], $birthday[2]))) > date("md")
      ? ((date("Y") - $birthday[2]) - 1)
      : (date("Y") - $birthday[2]));
    return $age;
  }
}