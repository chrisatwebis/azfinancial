<?php

/**
 * @file
 * Mmenu administration menu items.
 */

/**
 * Callback function for the Mmenu admin page.
 */
function mmenu_admin_settings($mmenu_name = '') {
  if (!empty($mmenu_name)) {
    drupal_goto('admin/config/mmenu/' . $mmenu_name);
  }
  return '';
}

/**
 * Form constructor for the Mmenu settings form.
 */
function mmenu_admin_settings_form($form, &$form_state, $mmenu_name = '') {
  $mmenu = mmenu_list($mmenu_name);

  $site_name = variable_get('site_name', t('Drupal'));
  $bool_options = array(
    'true' => t('Yes'),
    'false' => t('No'),
  );

  $form['general'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['general']['enabled'] = array(
    '#title' => t('Enabled?'),
    '#type' => 'select',
    '#options' => array(
      1 => t('Yes'),
      0 => t('No'),
    ),
    '#default_value' => $mmenu['enabled'] ? 1 : 0,
    '#required' => TRUE,
    '#weight' => -3,
    '#description' => t('Enable or disable the mmenu.'),
  );
  $form['general']['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => $mmenu['title'],
    '#required' => TRUE,
    '#weight' => -2,
    '#description' => t('The administrator title of the mmenu.'),
  );

  $form['general']['name'] = array(
    '#type' => 'hidden',
    '#value' => $mmenu_name,
  );

  $drupal_blocks = mmenu_get_blocks();
  $options = array();
  $options[] = t('--- Please select a block ---');
  foreach ($drupal_blocks as $module => $drupal_block) {
    foreach ($drupal_block as $delta => $info) {
      $options[$module . '|' . $delta] = drupal_ucfirst($module) . ' - ' . $info['info'];
    }
  }

  $form['blocks'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Blocks'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $blocks = array();
  foreach ($mmenu['blocks'] as $k => $block) {
    $blocks[] = $block;
  }
  $mmenu_allowed_blocks_nums = variable_get('mmenu_allowed_blocks_nums', 5);
  for ($i = count($blocks); $i < $mmenu_allowed_blocks_nums; $i++) {
    $blocks[$i]['title'] = '';
    $blocks[$i]['module'] = '';
    $blocks[$i]['delta'] = '';
    $blocks[$i]['collapsed'] = TRUE;
    $blocks[$i]['wrap'] = FALSE;
  }

  foreach ($blocks as $k => $block) {
    $form['blocks'][$k] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Block'),
      '#collapsible' => TRUE,
      '#collapsed' => !empty($block['module']) && !empty($block['delta']) ? FALSE : TRUE,
    );
    $form['blocks'][$k]['module_delta'] = array(
      '#title' => t('Select a block'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => !empty($block['module']) && !empty($block['delta']) ? $block['module'] . '|' . $block['delta'] : '',
      '#description' => t('Select a block to display on the mmenu.'),
    );
    $form['blocks'][$k]['menu_parameters'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Menu parameters'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['blocks'][$k]['menu_parameters']['min_depth'] = array(
      '#title' => t('Min depth'),
      '#type' => 'select',
      '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9)),
      '#default_value' => (isset($block['menu_parameters']) && isset($block['menu_parameters']['min_depth'])) ? $block['menu_parameters']['min_depth'] : 1,
      '#description' => t('The minimum depth of menu links in the resulting tree. Defaults to 1, which is the default to build a whole tree for a menu (excluding menu container itself).'),
    );

    $form['blocks'][$k]['title'] = array(
      '#title' => t('Title'),
      '#type' => 'textfield',
      '#default_value' => $block['title'],
      '#description' => t('Override the default title for the block. Use <em>!placeholder</em> to display no title, or leave blank to use the default block title.', array('!placeholder' => '&lt;none&gt;')),
    );
    $form['blocks'][$k]['collapsed'] = array(
      '#title' => t('Collapsed'),
      '#type' => 'select',
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      ),
      '#default_value' => $block['collapsed'] ? 1 : 0,
      '#description' => t('Collapse or expand the block content by default.'),
    );
    $form['blocks'][$k]['wrap'] = array(
      '#title' => t('Wrap'),
      '#type' => 'select',
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      ),
      '#default_value' => $block['wrap'] ? 1 : 0,
      '#description' => t('Determine if needs to wrap the block content. Usually to set it to true if the block is not a system menu.'),
    );
  }

  $options = $mmenu['options'];
  $form['options'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Mmenu options'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('For more information about the options, please visit the page <a href="!link">!link</a>.', array('!link' => 'http://mmenu.frebsite.nl/options.php')),
  );
  $form['options']['isMenu'] = array(
    '#title' => t('isMenu'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['isMenu'] ? 'true' : 'false',
    '#description' => t('Is this a menu?'),
  );
  $form['options']['position'] = array(
    '#title' => t('position'),
    '#type' => 'textfield',
    '#default_value' => $options['position'],
    '#attributes' => array(
      'readonly' => 'readonly',
    ),
    '#description' => t('The position of the menu relative to the page. Possible values: "top", "right", "bottom" or "left"'),
  );
  $form['options']['zposition'] = array(
    '#title' => t('zposition'),
    '#type' => 'select',
    '#options' => array(
      'back' => t('Back'),
      'front' => t('Front'),
      'next' => t('Next'),
    ),
    '#default_value' => $options['zposition'],
    '#description' => t('Whether or not the submenus should come sliding in from the right. If false, the submenus expand below their parent.'),
  );
  $form['options']['slidingSubmenus'] = array(
    '#title' => t('slidingSubmenus'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['slidingSubmenus'] ? 'true' : 'false',
    '#description' => t('Whether or not the submenus should come sliding in from the right. If false, the submenus expand below their parent.'),
  );
  $form['options']['moveBackground'] = array(
    '#title' => t('moveBackground'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['moveBackground'] ? 'true' : 'false',
    '#description' => t('Whether or not the page should inherit the background of the body when the menu opens.'),
  );

  $classes = mmenu_class_list();
  $class_options = array();
  foreach ($classes as $class) {
    $class_options[$class['name']] = $class['name'];
  }
  $form['options']['classes'] = array(
    '#title' => t('classes'),
    '#type' => 'select',
    '#options' => $class_options,
    '#default_value' => $options['classes'],
    '#description' => t('A collection of space-separated classnames to add to both the menu and the HTML.'),
  );

  $form['options']['modal'] = array(
    '#title' => t('modal'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['modal'] ? 'true' : 'false',
    '#description' => t('Whether or not the menu should be opened as a "modal". Basically, this means the user has no default way of closing the menu. You\'ll have to provide a close-button yourself.'),
  );

  $form['options']['counters'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Counters'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['counters']['add'] = array(
    '#title' => t('add'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['counters']['add'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically append a counter to each menu item that has a submenu.'),
  );
  $form['options']['counters']['update'] = array(
    '#title' => t('update'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['counters']['update'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically count the number of items in the submenu, updates when typing in the search field.'),
  );

  $form['options']['dragOpen'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('dragOpen'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['dragOpen']['open'] = array(
    '#title' => t('open'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['dragOpen']['open'] ? 'true' : 'false',
    '#description' => t('Whether or not the menu should open when dragging the page.'),
  );
  $form['options']['dragOpen']['pageNode'] = array(
    '#title' => t('pageNode'),
    '#type' => 'textfield',
    '#default_value' => $options['dragOpen']['pageNode'] ? $options['dragOpen']['pageNode'] : 'body',
    '#description' => t('The node on which the user can drag to open the menu. If omitted, the entire page is used.'),
  );
  $form['options']['dragOpen']['threshold'] = array(
    '#title' => t('threshold'),
    '#type' => 'textfield',
    '#default_value' => $options['dragOpen']['threshold'] ? $options['dragOpen']['threshold'] : 100,
    '#description' => t('The minimum amount of pixels to drag before actually opening the menu, less than 50 is not advised.'),
  );
  $form['options']['dragOpen']['maxStartPos'] = array(
    '#title' => t('maxStartPos'),
    '#type' => 'textfield',
    '#default_value' => $options['dragOpen']['maxStartPos'] ? $options['dragOpen']['maxStartPos'] : 50,
    '#description' => t('The maximum x-position to start dragging the page.For a menu with a position set to "top" or "bottom", the default value is 50.'),
  );

  $form['options']['labels'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('labels'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['labels']['add'] = array(
    '#title' => t('add'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['labels']['add'] ? 'true' : 'false',
  );

  $form['options']['header'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('header'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['header']['add'] = array(
    '#title' => t('add'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['header']['add'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically prepend a fixed header to the menu.'),
  );
  $form['options']['header']['update'] = array(
    '#title' => t('update'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['header']['update'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically update the header text and back- (and next-) button when opening sub-menus.'),
  );
  $form['options']['header']['title'] = array(
    '#title' => t('title'),
    '#type' => 'textfield',
    '#default_value' => $options['header']['title'] ? $options['header']['title'] : $site_name,
    '#description' => t('The text above the mainmenu.'),
  );

  $form['options']['searchfield'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('searchfield'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['searchfield']['add'] = array(
    '#title' => t('add'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['searchfield']['add'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically prepend a search field to the menu.'),
  );
  $form['options']['searchfield']['search'] = array(
    '#title' => t('search'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['searchfield']['search'] ? 'true' : 'false',
    '#description' => t('Whether or not to automatically search when typing.'),
  );
  $form['options']['searchfield']['placeholder'] = array(
    '#title' => t('title'),
    '#type' => 'textfield',
    '#default_value' => $options['searchfield']['placeholder'] ? $options['searchfield']['placeholder'] : t('Search'),
    '#description' => t('The placeholder text in the search field.'),
  );
  $form['options']['searchfield']['noResults'] = array(
    '#title' => t('noResults'),
    '#type' => 'textfield',
    '#default_value' => $options['searchfield']['noResults'] ? $options['searchfield']['noResults'] : t('No results found.'),
    '#description' => t('The text to show when no results are found. If false no message will be shown.'),
  );
  $form['options']['searchfield']['showLinksOnly'] = array(
    '#title' => t('showLinksOnly'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['searchfield']['showLinksOnly'] ? 'true' : 'false',
    '#description' => t('Whether or not to only show links (A elements) in the search results. If false, also SPAN elements will be shown.'),
  );

  $form['options']['onClick'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('onClick'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['options']['onClick']['setSelected'] = array(
    '#title' => t('setSelected'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['onClick']['setSelected'] ? 'true' : 'false',
    '#description' => t('Whether or not the clicked link should be visibly "selected".'),
  );
  $form['options']['onClick']['preventDefault'] = array(
    '#title' => t('preventDefault'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['onClick']['preventDefault'] ? 'true' : 'false',
    '#description' => t('Whether or not to prevent the default behavior for the clicked link. The default value varies per link: true if its href is equal to or starts with a hash (#), false otherwise.'),
  );
  $form['options']['onClick']['close'] = array(
    '#title' => t('close'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['onClick']['close'] ? 'true' : 'false',
    '#description' => t('Whether or not the menu should close after clicking a link inside it. The default value varies per link: true if the default behavior for the clicked link is prevented, false otherwise.'),
  );
  $form['options']['onClick']['blockUI'] = array(
    '#title' => t('blockUI'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $options['onClick']['blockUI'] ? 'true' : 'false',
    '#description' => t('Whether or not to block the user interface while loading the new page. The default value varies per link: false if the default behavior for the clicked link is prevented, true otherwise.'),
  );
  $form['options']['onClick']['selector'] = array(
    '#title' => t('selector'),
    '#type' => 'textfield',
    '#default_value' => isset($options['onClick']['selector']) ? $options['onClick']['selector'] : '',
    '#description' => t("Clicks the selector to open the mmenu. e.g. #logo or a[id='logo']"),
  );

  $configurations = $mmenu['configurations'];
  $form['configurations'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Mmenu configurations'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('For more information about the configurations, please visit the page <a href="!link">!link</a>.', array('!link' => 'http://mmenu.frebsite.nl/options.php')),
  );
  $form['configurations']['clone'] = array(
    '#title' => t('clone'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $configurations['clone'] ? 'true' : 'false',
    '#description' => t('Whether or not to clone the menu before prepending it to the BODY. If true, the ID on the menu and every ID inside it will be prepended with "mm-" to prevent using double IDs.'),
  );
  $form['configurations']['preventTabbing'] = array(
    '#title' => t('preventTabbing'),
    '#type' => 'select',
    '#options' => $bool_options,
    '#default_value' => $configurations['preventTabbing'] ? 'true' : 'false',
    '#description' => t('Whether or not to prevent the default behavior when pressing the tab key. If false, the user will be able to tab out of the menu and using some other way to prevent this (for example TABguard) is strongly recommended.'),
  );
  $form['configurations']['panelClass'] = array(
    '#title' => t('panelClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['panelClass'] ? $configurations['panelClass'] : 'Panel',
    '#description' => t('The classname on an element (for example a DIV) that should be considered to be a panel. Only applies if the "isMenu" option is set to false.'),
  );
  $form['configurations']['listClass'] = array(
    '#title' => t('listClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['listClass'] ? $configurations['listClass'] : 'List',
    '#description' => t('The classname on an UL that should be styled as an app-like list. Automatically applied to all ULs if the "isMenu" option is set to true.'),
  );
  $form['configurations']['selectedClass'] = array(
    '#title' => t('selectedClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['selectedClass'] ? $configurations['selectedClass'] : 'active-trail',
    '#description' => t('The classname on the LI that should be displayed as selected.'),
  );
  $form['configurations']['labelClass'] = array(
    '#title' => t('labelClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['labelClass'] ? $configurations['labelClass'] : 'Label',
    '#description' => t('The classname on a LI that should be displayed as a label.'),
  );
  $form['configurations']['counterClass'] = array(
    '#title' => t('counterClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['counterClass'] ? $configurations['counterClass'] : 'Counter',
    '#description' => t('The classname on an EM that should be displayed as a counter. Only applies if the counters are not added automatically.'),
  );
  $form['configurations']['pageNodetype'] = array(
    '#title' => t('pageNodetype'),
    '#type' => 'textfield',
    '#default_value' => $configurations['pageNodetype'] ? $configurations['pageNodetype'] : 'div',
    '#description' => t('The node-type of the page.'),
  );
  $form['configurations']['panelNodetype'] = array(
    '#title' => t('panelNodetype'),
    '#type' => 'textfield',
    '#default_value' => $configurations['panelNodetype'] ? $configurations['panelNodetype'] : 'div, ul, ol',
    '#description' => t('The node-type of panels.'),
  );
  $form['configurations']['transitionDuration'] = array(
    '#title' => t('transitionDuration'),
    '#type' => 'textfield',
    '#default_value' => $configurations['transitionDuration'] ? $configurations['transitionDuration'] : 400,
    '#description' => t('The number of milliseconds used in the CSS transitions.'),
  );

  $form['configurations']['dragOpen'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('dragOpen'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configurations']['dragOpen']['width'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('width'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configurations']['dragOpen']['width']['perc'] = array(
    '#title' => t('perc'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['width']['perc'] ? $configurations['dragOpen']['width']['perc'] : 0.8,
    '#description' => t('The width of the menu as a percentage. From 0.0 (fully hidden) to 1.0 (fully opened).'),
  );
  $form['configurations']['dragOpen']['width']['min'] = array(
    '#title' => t('min'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['width']['min'] ? $configurations['dragOpen']['width']['min'] : 140,
    '#description' => t('The minimum width of the menu.'),
  );
  $form['configurations']['dragOpen']['width']['max'] = array(
    '#title' => t('max'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['width']['max'] ? $configurations['dragOpen']['width']['max'] : 440,
    '#description' => t('The maximum width of the menu.'),
  );
  $form['configurations']['dragOpen']['height'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('height'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configurations']['dragOpen']['height']['perc'] = array(
    '#title' => t('perc'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['height']['perc'] ? $configurations['dragOpen']['height']['perc'] : 0.8,
    '#description' => t('The height of the menu as a percentage. From 0.0 (fully hidden) to 1.0 (fully opened).'),
  );
  $form['configurations']['dragOpen']['height']['min'] = array(
    '#title' => t('min'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['height']['min'] ? $configurations['dragOpen']['height']['min'] : 140,
    '#description' => t('The minimum height of the menu.'),
  );
  $form['configurations']['dragOpen']['height']['max'] = array(
    '#title' => t('max'),
    '#type' => 'textfield',
    '#default_value' => $configurations['dragOpen']['height']['max'] ? $configurations['dragOpen']['height']['max'] : 440,
    '#description' => t('The maximum height of the menu.'),
  );

  $form['configurations']['labels'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('labels'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configurations']['labels']['collapsedClass'] = array(
    '#title' => t('collapsedClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['labels']['collapsedClass'] ? $configurations['labels']['collapsedClass'] : 'Collapsed',
    '#description' => t('The classname on the list-items that should be collapsed by default.'),
  );

  $form['configurations']['header'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('header'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configurations']['header']['panelHeaderClass'] = array(
    '#title' => t('panelHeaderClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['header']['panelHeaderClass'] ? $configurations['header']['panelHeaderClass'] : 'Header',
    '#description' => t('The classname on the element (for example a H2) that contains the title-text for the panel. Only applies if the "isMenu" option is set to false, otherwise the text from the parent menu-item will be used.'),
  );
  $form['configurations']['header']['panelPrevClass'] = array(
    '#title' => t('panelPrevClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['header']['panelPrevClass'] ? $configurations['header']['panelPrevClass'] : 'Header',
    '#description' => t('The classname on the A that links to the previous panel. Only applies if the "isMenu" option is set to false, otherwise the ID from the parent menu-level will be used.'),
  );
  $form['configurations']['header']['panelNextClass'] = array(
    '#title' => t('panelNextClass'),
    '#type' => 'textfield',
    '#default_value' => $configurations['header']['panelNextClass'] ? $configurations['header']['panelNextClass'] : 'Next',
    '#description' => t('The classname on the A that links to the next panel. Only applies if the "isMenu" option is set to false, otherwise there is no next panel.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Form submission handler for mmenu_admin_settings_form().
 */
function mmenu_admin_settings_form_submit($form_id, &$form_state) {
  $values = $form_state['values'];
  $blocks = array();
  foreach ($values['blocks'] as $k => $block) {
    if (!empty($block['module_delta'])) {
      $v = explode('|', $block['module_delta']);
      $blocks[$k] = $block;
      $blocks[$k] += array(
        'module' => $v[0],
        'delta' => $v[1],
      );
    }
  }
  $mmenu = array(
    'enabled' => $values['general']['enabled'],
    'title' => $values['general']['title'],
    'name' => $values['general']['name'],
    'blocks' => $blocks,
    'options' => mmenu_convert_settings($values['options']),
    'configurations' => mmenu_convert_settings($values['configurations']),
  );
  variable_set('mmenu_item_' . $values['general']['name'], $mmenu);

  // Clears mmenus cache.
  cache_clear_all('mmenus', 'cache');

  drupal_set_message(t('The settings have been saved.'));
}
