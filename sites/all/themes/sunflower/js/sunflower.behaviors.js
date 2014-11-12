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



  function get_total_days() {
    var all_selected = true;
    $("#webform-component-travel-dates--effective-date select").each(
      function(){
        if($(this).val() == "") {
          all_selected = false;
          return all_selected;
        }
      }
    );
    $("#webform-component-travel-dates--expiry-date select").each(
      function(){
        if ($(this).val() == "") {
          all_selected = false;
          return all_selected;
        }
      }
    );
    return all_selected;
  }
  
  function show_duration() {
    if (get_total_days()) {
      var effective_year = $(".webform-component--step-2--travel-dates--effective-date .year").val();
      var effective_day = $(".webform-component--step-2--travel-dates--effective-date .day").val();
      var effective_month = $(".webform-component--step-2--travel-dates--effective-date .month").val();
      
      var expiry_month = $(".webform-component--step-2--travel-dates--expiry-date .month").val();
      var expiry_day = $(".webform-component--step-2--travel-dates--expiry-date .day").val();
      var expiry_year = $(".webform-component--step-2--travel-dates--expiry-date .year").val();
      
      var minutes = 1000*60;
      var hours = minutes*60;
      var days = hours*24;
      var expiry_date = new Date();
      expiry_date.setFullYear(expiry_year,expiry_month-1,expiry_day);
      var effective_date = new Date();
      effective_date.setFullYear(effective_year,effective_month-1,effective_day);
      var t = expiry_date.getTime() - effective_date.getTime();
      total_days = Math.round(t/days)+1;

      if($("#duration_days").length) {
        $("#duration_days #duration").html(Drupal.t("Duration")+": <b>"+total_days+" "+Drupal.t("days")+" </b>");
      }
      else {
        $(".webform-component--step-2--travel-dates .fieldset-wrapper").append('<span id="duration_days"><span id="duration">'+Drupal.t("Duration")+': <b>'+total_days+" "+Drupal.t("days")+' </b></span></span>');
      }
      
      if (total_days <= 0) {
        $("#duration_days").addClass("warning");
      }
      else {
        $("#duration_days").removeClass("warning");          
      }
      
      // sum_insured_dedutible_check();
    }
    else {
      if($("#duration_days").length) {
        $("#duration_days").remove();
      }
    }
  }

  function show_age(event) {
    var delta = event.data.element;
    if (birth_date_all_selected(delta)) {
      var dob_year = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .year").val();
      var dob_day = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .day").val();
      var dob_month = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .month").val();
        
      var minutes = 1000*60;
      var hours = minutes*60;
      var days = hours*24;
      
      var dob_date = new Date();
      dob_date.setFullYear(dob_year,dob_month-1,dob_day);
      
      var current_date = new Date();
      
      var insured_1_age = 0;
      
      var diff = current_date - dob_date;

      var diffdays = diff / days;
            
      var insured_1_age = Math.floor(diffdays / 365.25);
      
      if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").length) {
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age .insured_age_duration").html(
          Drupal.t("Age")+": <b>"+insured_1_age+" "+Drupal.t("year old")+" </b>"
        );
      }
      else {
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .fieldset-wrapper").append('<span class="insured_age"><span class="insured_age_duration">'+Drupal.t("Age")+': <b>'+insured_1_age+" "+Drupal.t("year old")+' </b></span></span>');
      }

      if (insured_1_age < 0) {
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").addClass("warning");
      }
      else {
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").removeClass("warning");          
      }

    }
    else {
      if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").length) {
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").remove();
      }
    }
  }

  function birth_date_all_selected(delta) {
    var all_selected = true;
    $("#webform-component-insurable-members--insured-"+delta+"--birth-date select").each(
      function(){
        if ($(this).val() == "") {
          all_selected = false;
          return all_selected;
        }
      }
    );
    return all_selected;
  }
  
  $( document ).ready(function() {
    //Add close button for mobile menu
    $("<span class='close_btn'></span>").appendTo(".mm-menu").click(function(){
      $(".mm-menu").trigger("close");
    });

    //purchase online webform
    $("#webform-client-form-184 .webform-component--step-1 > .fieldset-wrapper").append("<div class='continue_btn'><a href='#'>"+Drupal.t("Continue")+"</a></div>");
    $("#webform-client-form-184 .webform-component--step-2 > .fieldset-wrapper").append("<div class='continue_btn'><a href='#'>"+Drupal.t("Continue")+"</a></div>");
    $("#webform-client-form-184 .webform-component--step-3 > .fieldset-wrapper").append("<div class='continue_btn'><a href='#'>"+Drupal.t("Continue")+"</a></div>");
    $(".continue_btn").click(function(e){
      if ($("#webform-client-form-184 .webform-component--step-1").hasClass("collapsed") == false) {
        $("#webform-client-form-184 .webform-component--step-1").addClass("collapsed").find("> .fieldset-wrapper").hide();
      }
      if ($("#webform-client-form-184 .webform-component--step-2").hasClass("collapsed") == false) {
        $("#webform-client-form-184 .webform-component--step-2").addClass("collapsed").find("> .fieldset-wrapper").hide();
      }
      if ($("#webform-client-form-184 .webform-component--step-3").hasClass("collapsed") == false) {
        $("#webform-client-form-184 .webform-component--step-3").addClass("collapsed").find("> .fieldset-wrapper").hide();
      }
      if ($("#webform-client-form-184 .webform-component--step-4").hasClass("collapsed") == false) {
        $("#webform-client-form-184 .webform-component--step-4").addClass("collapsed").find("> .fieldset-wrapper").hide();
      }
      $(this).parents(".webform-component-fieldset").next().removeClass("collapsed").find(" > .fieldset-wrapper").show();
      var next_header = $(this).parents(".webform-component-fieldset").next().find(" > legend .fieldset-title");
      // next_header.click();
      $('html, body').animate({ scrollTop: (next_header.offset().top - 50) }, 1000, function(){});
      return false;
    });
    
    //purchase online webform custom script
    var total_days = 0;
    if($(".webform-component--step-2--travel-dates--effective-date").length > 0){
      $(".webform-component--step-2--travel-dates--effective-date select").bind("change",show_duration);
      $(".webform-component--step-2--travel-dates--expiry-date select").bind("change",show_duration);
      show_duration();
    }

    //Initilize the default behavior when the page is loaded.   
    //Since the dob field is well named: ***1***,***2***, so , we can use 1,2,3,4,5 as delta.   
    $.each([1,2,3,4,5], function(index, value) { 
      $(".webform-component--step-2--traveller-information-insured--insured-"+value+"--birthday select").bind("change",{element:value},show_age);
      $(".webform-component--step-2--traveller-information-insured--insured-"+value+"--birthday select").change();
    });
    
  });

})(jQuery);
