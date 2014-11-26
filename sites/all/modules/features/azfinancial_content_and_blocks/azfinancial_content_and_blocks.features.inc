<?php
/**
 * @file
 * azfinancial_content_and_blocks.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function azfinancial_content_and_blocks_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
