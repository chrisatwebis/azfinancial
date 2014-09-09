/**
 * @file
 * Utility functions to handle the mmenu.
 */

(function ($) {
  Drupal.behaviors.mmenuExampleHandler = {
    attach: function (context, settings) {
      var mmenus = Drupal.settings.mmenus;
      var mmenu_left = mmenus.mmenu_left;

      var $menu = $('nav#mmenu_left');
      $menu.mmenu({
        // e.g. You can use the default option 'mmenu_left.options.position'
        // or override its value to 'right'.
        position: 'left',
        classes: 'mm-basic',
        dragOpen: true,
        counters: true,
        searchfield: true,
        labels: {
          fixed	: !$.mmenu.support.touch
        },
        header: {
          add: true,
          update: true,
          title	: Drupal.t('Drupal')
        }
      });
    }
  };
})(jQuery);
