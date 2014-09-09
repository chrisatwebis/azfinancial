<?php
/**
 * @file
 * page_with_tabs.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function page_with_tabs_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'custom_field_collection_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Custom field collection view';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'item_id' => 'item_id',
    'field_resume_job_title' => 'field_resume_job_title',
    'field_resume_time_period' => 'field_resume_time_period',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'item_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_resume_job_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_resume_time_period' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '[nothing_2]';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $handler->display->display_options['footer']['area']['tokenize'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Field collection item: Field path */
  $handler->display->display_options['fields']['field_path']['id'] = 'field_path';
  $handler->display->display_options['fields']['field_path']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['field_path']['field'] = 'field_path';
  $handler->display->display_options['fields']['field_path']['label'] = '';
  $handler->display->display_options['fields']['field_path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_path']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: Host Entity ID */
  $handler->display->display_options['fields']['host_entity_id']['id'] = 'host_entity_id';
  $handler->display->display_options['fields']['host_entity_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['host_entity_id']['field'] = 'host_entity_id';
  $handler->display->display_options['fields']['host_entity_id']['label'] = '';
  $handler->display->display_options['fields']['host_entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['host_entity_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['host_entity_id']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: Host Entity Path */
  $handler->display->display_options['fields']['host_entity_path']['id'] = 'host_entity_path';
  $handler->display->display_options['fields']['host_entity_path']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['host_entity_path']['field'] = 'host_entity_path';
  $handler->display->display_options['fields']['host_entity_path']['label'] = '';
  $handler->display->display_options['fields']['host_entity_path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['host_entity_path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['host_entity_path']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: Host Entity Type */
  $handler->display->display_options['fields']['host_entity_type']['id'] = 'host_entity_type';
  $handler->display->display_options['fields']['host_entity_type']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['host_entity_type']['field'] = 'host_entity_type';
  $handler->display->display_options['fields']['host_entity_type']['label'] = '';
  $handler->display->display_options['fields']['host_entity_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['host_entity_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['host_entity_type']['hide_alter_empty'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Edit';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Edit';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[field_path]/[item_id]/edit?destination=[host_entity_path]';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Delete';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Delete';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = '[field_path]/[item_id]/delete?destination=[host_entity_path]';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'Add';
  $handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['alter']['path'] = '[field_path]/add/[host_entity_type]/[host_entity_id]?destination=[host_entity_path]';
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  /* Sort criterion: Field collection item: Field collection item ID */
  $handler->display->display_options['sorts']['item_id']['id'] = 'item_id';
  $handler->display->display_options['sorts']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['sorts']['item_id']['field'] = 'item_id';
  /* Contextual filter: Field collection item: Field collection item ID */
  $handler->display->display_options['arguments']['item_id']['id'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['arguments']['item_id']['field'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['item_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['item_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['item_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['item_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['item_id']['break_phrase'] = TRUE;

  /* Display: Badges Field Collection */
  $handler = $view->new_display('block', 'Badges Field Collection', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $translatables['custom_field_collection_view'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('[nothing_2]'),
    t('Field collection item ID'),
    t('.'),
    t('Edit'),
    t('Delete'),
    t('Add'),
    t('All'),
    t('Badges Field Collection'),
  );
  $export['custom_field_collection_view'] = $view;

  return $export;
}
