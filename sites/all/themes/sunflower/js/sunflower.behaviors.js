(function ($) {

  /**
   * The recommended way for producing HTML markup through JavaScript is to write
   * theming functions. These are similiar to the theming functions that you might
   * know from 'phptemplate' (the default PHP templating engine used by most
   * Drupal themes including Omega). JavaScript theme functions accept arguments
   * and can be overriden by sub-themes.
   *
   * In most cases, there is no good reason to NOT wrap your markup producing
   * JavaScript in a theme function.
   */
  Drupal.theme.prototype.sunflowerExampleButton = function (path, title) {
    // Create an anchor element with jQuery.
    return $('<a href="' + path + '" title="' + title + '">' + title + '</a>');
  };

  /**
   * Behaviors are Drupal's way of applying JavaScript to a page. In short, the
   * advantage of Behaviors over a simple 'document.ready()' lies in how it
   * interacts with content loaded through Ajax. Opposed to the
   * 'document.ready()' event which is only fired once when the page is
   * initially loaded, behaviors get re-executed whenever something is added to
   * the page through Ajax.
   *
   * You can attach as many behaviors as you wish. In fact, instead of overloading
   * a single behavior with multiple, completely unrelated tasks you should create
   * a separate behavior for every separate task.
   *
   * In most cases, there is no good reason to NOT wrap your JavaScript code in a
   * behavior.
   *
   * @param context
   *   The context for which the behavior is being executed. This is either the
   *   full page or a piece of HTML that was just added through Ajax.
   * @param settings
   *   An array of settings (added through drupal_add_js()). Instead of accessing
   *   Drupal.settings directly you should use this because of potential
   *   modifications made by the Ajax callback that also produced 'context'.
   */
  Drupal.behaviors.sunflowerExampleBehavior = {
    attach: function (context, settings) {
      // By using the 'context' variable we make sure that our code only runs on
      // the relevant HTML. Furthermore, by using jQuery.once() we make sure that
      // we don't run the same piece of code for an HTML snippet that we already
      // processed previously. By using .once('foo') all processed elements will
      // get tagged with a 'foo-processed' class, causing all future invocations
      // of this behavior to ignore them.
      $('#block-views-custom-content-block-3', context).once('morelink', function () {
        var more = $(this).find(".more-link");
        $(this).find(".block__title").append(more);
      });
      $('#block-webform-client-block-76', context).once('get_a_quote_accordion', function () {
        var block = $(this);
        var header = $(this).find(".block__title");
        var content = $(this).find(".block__content");
        header.append("<span class='arrow'></span>");
        header.click(function(){
          if (block.hasClass("expanded")) {
            block.removeClass("expanded");
            content.slideUp();
          }
          else {
            block.addClass("expanded");
            content.slideDown();
          }
        });
      });
    }
  };

  Drupal.behaviors.sunflowerMageMenu = {
    attach: function (context, settings) {
      /**
      * Superfish mega menu handling
      **/
      $('#superfish-1', context).once('megamenu', function () {
        var menu_width = $(this).outerWidth();
        if($(this).children("li.menuparent").length > 0){
          $(this).children("li.menuparent").each(function(){
            if(!$(this).hasClass("sf-parent-children-0")){
/*              var prev = $(this).prev().outerWidth();
              var next = $(this).next().outerWidth();
              var width = prev + next + $(this).outerWidth();
              $(this).children(".sf-megamenu").css({"left": -prev, width: width});*/
              $(this).children(".sf-megamenu").css({"left": 0, width: menu_width});
            }
          });
        }
      });
    }
  };

  Drupal.behaviors.sunflowerFlexsliderCaptionColor = {
    attach: function (context, settings) {
      /**
      * Flex slider caption color handling
      **/
      $('#flexslider-1', context).once('captionColor', function () {
        $(this).find(".flex-caption .item_color").each(function(){
          var color = $(this).text();
          $(this).parent().find(".item_title a").css("color", color);
          $(this).parent().find(".item_body").css("color", color);
          $(this).parent().find(".item_link a").css("color", color);
        });
      });
    }
  };

  Drupal.behaviors.sunflowerPriceSearchResultAccordion = {
    attach: function (context, settings) {
      /**
      * Price search result accordion
      **/
      $('.plan_result_wrapper', context).once('resultAccordion', function () {
        $(this).find(".deductible").each(function(){
          var accordion = $(this);
          var header = $(this).find(".deductible_header");
          var content = $(this).find(".deductible_content");
          var handler = $("<span class='accordion_btn'></span>");
          header.append(handler);
          handler.click(function(){
            if (accordion.hasClass("collapsed")) {
              accordion.removeClass("collapsed");
              content.slideDown();
            }
            else {
              accordion.addClass("collapsed");
              content.slideUp();
            }          
          });
        });
      });
    }
  };
  
  $( document ).ready(function() {
    //Add close button for mobile menu
    $("<span class='close_btn'></span>").appendTo(".mm-menu").click(function(){
      $(".mm-menu").trigger("close");
    });
  });

})(jQuery);
