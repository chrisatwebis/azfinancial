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

    //only run the script if it is buy online page
    if ($("#webform-client-form-184").length) {

      //add 'continue' button to step 2,3,4
      $.each([1,2,3], function(index, value) {
        $("#webform-client-form-184 .webform-component--step-"+value+" > .fieldset-wrapper").append("<div class='continue_btn disabled'><a href='#'>"+Drupal.t("Continue")+"</a></div>");
      });

      //make legend of the fieldsets of step 1,2,3,4 as accordion header
      $.each([1,2,3,4], function(index, value) { 
        $("#webform-client-form-184 .webform-component--step-"+value+" > legend").click(function(){
          //if the fieldset is disabled, then do nothing;
          if ($(this).parent().hasClass("disabled")) {
            return false;
          }
          else {
            if ($(this).parent().hasClass("custom_collapsed")) {
              $(this).parent().removeClass("custom_collapsed").find(" > .fieldset-wrapper").fadeIn();
            }
            else {
              $(this).parent().addClass("custom_collapsed").find(" > .fieldset-wrapper").fadeOut();
            }
          }
        });
      });

      //register the click handler for the 'continue' button. If the button has 'disabled' class, then alert the user, otherwise, close the current fieldset and open the next fieldset.
      $(".continue_btn a").click(function(e){
        e.preventDefault();
        if ($(this).parent().hasClass("disabled") == false) {
          var parent = $(this).parents(".webform-component-fieldset");
          $.each([1,2,3,4], function(index, value) { 
            if ($("#webform-client-form-184 .webform-component--step-"+value).hasClass("custom_collapsed") == false) {
              $("#webform-client-form-184 .webform-component--step-"+value).addClass("custom_collapsed").find("> .fieldset-wrapper").hide();
            }
          });
          parent.next().removeClass("custom_collapsed disabled").find(" > .fieldset-wrapper").show();
          var next_header = $(this).parents(".webform-component-fieldset").next().find(" > legend .fieldset-legend");
          $('html, body').animate({ scrollTop: (next_header.offset().top - 50) }, 1000, function(){});
          return false;
        }
        else {
          alert("Please fill out the required fields before click on 'Continue' button. Once the required fields are fulfilled, the 'Continue' button will be automatically enabled.");
        }
      });

      var form = $("#webform-client-form-184");
      //purchase online webform
      var step_1_complete = false;
      var step_2_complete = false;
      var step_3_complete = false;
      var step_4_complete = false;

      form.on("step_complete", function(e, step_number){
        switch(step_number) {
          case 1:
            form.find(".webform-component--step-"+step_number+" .continue_btn").removeClass("disabled");
            step_1_complete = true;
            buyonline_step_2_auto_expanse();
            break;
          case 2:
            form.find(".webform-component--step-"+step_number+" .continue_btn").removeClass("disabled");
            step_2_complete = true;
            //Step 3 doesn't really need to do anything, hence just check it upon step 2 is completed.
            buyonline_step_3_check_completion();
            break;
          case 3:
            form.find(".webform-component--step-"+step_number+" .continue_btn").removeClass("disabled");
            step_3_complete = true;
            buyonline_step_4_review();
            break;
          case 4:
            step_4_complete = true;
            break;
          default:
            break;
        }
      }).on("step_incomplete", function(e, step_number){
        switch(step_number) {
          case 1:
            form.find(".webform-component--step-"+step_number+" .continue_btn").addClass("disabled");
            step_1_complete = false;
            buyonline_collapse_step(2);
            buyonline_collapse_step(3);
            buyonline_collapse_step(4);
            break;
          case 2:
            form.find(".webform-component--step-"+step_number+" .continue_btn").addClass("disabled");
            step_2_complete = false;
            buyonline_collapse_step(3);
            buyonline_collapse_step(4);
            break;
          case 3:
            form.find(".webform-component--step-"+step_number+" .continue_btn").addClass("disabled");
            step_3_complete = false;
            buyonline_collapse_step(4);
            break;
          case 4:
            step_4_complete = false;
            break;
          default:
            break;
        }
      }).on("premium_factor_change", function(e){
        buyonline_step_4_review();
      });
      
      buyonline_step_1_monitor();
      buyonline_step_2_monitor();
      buyonline_step_3_monitor();
      buyonline_step_4_monitor();
    
      //Verify whether effective date and expiry date are fulfilled.
      function buyonline_step_2_effective_expiry_is_complete() {
        var all_selected = true;
        $(".webform-component--step-2--travel-dates--effective-date select").each(
          function(){
            if($(this).val() == "") {
              all_selected = false;
              return all_selected;
            }
          }
        );
        $(".webform-component--step-2--travel-dates--expiry-date select").each(
          function(){
            if ($(this).val() == "") {
              all_selected = false;
              return all_selected;
            }
          }
        );
        return all_selected;
      }
      
      function buyonline_step_2_show_duration() {
        if (buyonline_step_2_effective_expiry_is_complete()) {
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
          var total_days = 0;
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
        }
        else {
          if($("#duration_days").length) {
            $("#duration_days").remove();
          }
        }
      }
      //get the individual birthday in following format: yyyy-mm-dd
      function buyonline_step_2_get_dob(delta) {
        if (buyonline_step_2_is_bdate_complete(delta)) {
          var dob_year = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .year").val();
          var dob_day = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .day").val();
          var dob_month = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .month").val();
          return dob_year+"-"+dob_month+"-"+dob_day;
        }        
      }
      //calculate the individual age bases on the birthday
      function buyonline_step_2_get_age(delta) {
        if (buyonline_step_2_is_bdate_complete(delta)) {
          var dob_year = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .year").val();
          var dob_day = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .day").val();
          var dob_month = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .month").val();            
          var minutes = 1000*60;
          var hours = minutes*60;
          var days = hours*24;          
          var dob_date = new Date();
          dob_date.setFullYear(dob_year,dob_month-1,dob_day);
          var current_date = new Date();
          var diff = current_date - dob_date;
          var diffdays = diff / days;
          var insured_age = Math.floor(diffdays / 365.25);
          return insured_age;
        }
      }
      //show the age tooltip
      function buyonline_step_2_show_age() {
        // var delta = event.data.element;
        for (var delta = 1; delta <= 5; delta++) {
          var insured_age = buyonline_step_2_get_age(delta);
          if (typeof insured_age !== 'undefined') {
            if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").length) {
              $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age .insured_age_duration").html(
                Drupal.t("Age")+": <b>"+insured_age+" "+Drupal.t("year old")+" </b>"
              );
            }
            else {
              $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .fieldset-wrapper").append('<span class="insured_age"><span class="insured_age_duration">'+Drupal.t("Age")+': <b>'+insured_age+" "+Drupal.t("year old")+' </b></span></span>');
            }
            if (insured_age < 0) {
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
        };
      }

      function buyonline_step_2_is_bdate_complete(delta) {
        var all_selected = true;
        $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday select").each(
          function(){
            if ($(this).val() == "") {
              all_selected = false;
              return all_selected;
            }
          }
        );
        return all_selected;
      }
      //check whether the insured info have been completed
      function buyonline_step_2_check_insured_completion(delta) {
        var insured_info_completed = true;
        if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta).length > 0) {
          $(".webform-component--step-2--traveller-information-insured--insured-"+delta).find("input:not(:image), select").each(function(){
            if ($(this).val() == false) {
              insured_info_completed = false;
            }
          });
          return insured_info_completed;
        }
      }

      function buyonline_step_2_check_all_insured_completion() {
        var insured_completion = [];
        for (var i = 1; i <= 5; i++) {
          var insured_info_complete = buyonline_step_2_check_insured_completion(i);
          insured_completion[i-1] = insured_info_complete;
        };
        return insured_completion;
      }
      
      //collapse the step
      function buyonline_collapse_step(step_number) {
        $("#webform-client-form-184 .webform-component--step-"+step_number).addClass("custom_collapsed disabled").find("> .fieldset-wrapper").hide();    
      }

      //check anytime whether step 1 is completed.
      function buyonline_step_1_check() {
        if ($("#edit-submitted-step-1-for-all-members-1").prop("checked")) {
          form.trigger("step_complete", [1]);
          return true;
        }
        else {
          form.trigger("step_incomplete", [1]);
          return false;
        }
      }

      //monitor step 1 element change event
      function buyonline_step_1_monitor() {
        $(".webform-component--step-1").find("input, select").change(function(){
          buyonline_step_1_check();
        });
        $(".webform-component--step-1").find("input, select").change();
      }
      //Auto expanse the step 2 accordion.
      function buyonline_step_2_auto_expanse() {
        form.find(".webform-component--step-1 .continue_btn a").click();
      }
      //get the price entity id
      function buyonline_step_2_get_pid() {
        var pid = $("#edit-submitted-step-2-insurance-product").val();
        return pid;
      }
      //get the arrival date 
      function buyonline_step_2_get_arrival_date() {
        var month = $("#edit-submitted-step-2-travel-dates-arrival-date-month").val();
        var day = $("#edit-submitted-step-2-travel-dates-arrival-date-day").val();
        var year = $("#edit-submitted-step-2-travel-dates-arrival-date-year").val();
        return year+"-"+month+"-"+day;
      }
      //get the effective date 
      function buyonline_step_2_get_effective_date() {
        var month = $("#edit-submitted-step-2-travel-dates-effective-date-month").val();
        var day = $("#edit-submitted-step-2-travel-dates-effective-date-day").val();
        var year = $("#edit-submitted-step-2-travel-dates-effective-date-year").val();
        return year+"-"+month+"-"+day;
      }
      //get the expiry date 
      function buyonline_step_2_get_expiry_date() {
        var month = $("#edit-submitted-step-2-travel-dates-expiry-date-month").val();
        var day = $("#edit-submitted-step-2-travel-dates-expiry-date-day").val();
        var year = $("#edit-submitted-step-2-travel-dates-expiry-date-year").val();
        return year+"-"+month+"-"+day;
      }
      //get the deductible 
      function buyonline_step_2_get_deductible() {
        return $("#edit-submitted-step-2-coverage-and-deductible-select-a-deductible-amount").val();
      }
      //get the coverage 
      function buyonline_step_2_get_coverage() {
        return $("#edit-submitted-step-2-coverage-and-deductible-coverage-sum-insured").val();
      }
      //check whether step 2 is completed.
      function buyonline_step_2_check_completion() {
        var fulfilled = true;
        $(".webform-component--step-2").find(".required").each(function(){
          if ($(this).val() == '') {
            fulfilled = false;
          }
        });
        if (fulfilled && buyonline_step_2_effective_expiry_is_complete()) {
          form.trigger("step_complete", [2]);
          return true;
        }
        else {
          form.trigger("step_incomplete", [2]);
          return false;
        }
      }
      //monitor step 2 element change event
      function buyonline_step_2_monitor() {
        $(".webform-component--step-2").find("input, select").change(function(){
          buyonline_step_2_show_age();
          buyonline_step_2_show_duration();
          buyonline_step_2_check_completion();
          buyonline_step_3_update();
          form.trigger("premium_factor_change");
        });
        $(".webform-component--step-2").find("input, select").last().change();
      }
      //step 3 is depended on step 2's insured info.
      function buyonline_step_3_update() {
        var all_insured_completion = buyonline_step_2_check_all_insured_completion();
        for (var i = 0; i <= all_insured_completion.length - 1; i++) {
          if (window.console) console.log(all_insured_completion[i], i);

          if (!all_insured_completion[i]) {
            $(".webform-component--step-3--do-you-want-pre-existing-condition-covered-"+(i+1)).fadeOut().addClass("custom_hidden");
          }
          else {
            $(".webform-component--step-3--do-you-want-pre-existing-condition-covered-"+(i+1)).fadeIn().removeClass("custom_hidden");
          }
        };
      }
      //check whether step 3 is completed.
      function buyonline_step_3_check_completion() {
        var fulfilled = true;
        $(".webform-component--step-3").find(".webform-component-radios").each(function(){
          if ($(this).find("input:radio:checked").length <= 0) {
            fulfilled = false;
          }
        });
        if (fulfilled) {
          form.trigger("step_complete", [3]);          
        }
        else {
          form.trigger("step_incomplete", [3]);          
        }
        return fulfilled;
      }
      //monitor step 3 element change event
      function buyonline_step_3_monitor() {
        $(".webform-component--step-3").find("input, select").change(function(){
          buyonline_step_3_check_completion();
          form.trigger("premium_factor_change");
        });
        $(".webform-component--step-3").find("input, select").last().change();
      }
      //get individual insured spmcc info
      function buyonline_step_3_get_insured_spmcc(delta) {
        return $("#edit-submitted-step-3-do-you-want-pre-existing-condition-covered-"+delta).find("input:radio:checked").val();
      }
      //Get individual insured information
      function buyonline_step_4_get_insured_info(delta) {
        if (buyonline_step_2_check_insured_completion(delta)) {
          var insured = [];
          insured['first_name'] = $("#edit-submitted-step-2-traveller-information-insured-insured-"+delta+"-given-name").val();
          insured['last_name'] = $("#edit-submitted-step-2-traveller-information-insured-insured-"+delta+"-surname").val();
          insured['dob'] = buyonline_step_2_get_dob(delta);
          insured['sex'] = $("#edit-submitted-step-2-traveller-information-insured-insured-"+delta+"-gender").val();
          insured['spmcc'] = buyonline_step_3_get_insured_spmcc(delta);
          return insured;
        }
      }
      //Get all insured information
      function buyonline_step_4_get_all_insured_info() {
        var all_insured = [];
        for (var delta = 1; delta <= 5; delta++) {
          all_insured[delta-1] = buyonline_step_4_get_insured_info(delta);
        };
        return all_insured;
      }
      //monitor step 4 element change event - current not in use.
      function buyonline_step_4_monitor() {
         
      }
      function  buyonline_step_4_review() {
        if (!step_1_complete || !step_2_complete || !step_3_complete) {
          return ;
        }
        //contact information
        var contact_fn = $("#edit-submitted-step-2-contact-information-given-name").val();
        var contact_ln = $("#edit-submitted-step-2-contact-information-surname").val();
        var contact_email = $("#edit-submitted-step-2-contact-information-email").val() ? ("<br>"+Drupal.t("Email: ")+$("#edit-submitted-step-2-contact-information-email").val()) : "";
        var contact_hphone = $("#edit-submitted-step-2-contact-information-home-phone").val() ? ("<br>"+Drupal.t("Home Phone: ")+$("#edit-submitted-step-2-contact-information-home-phone").val()) : "";
        var contact_cphone = $("#edit-submitted-step-2-contact-information-cell-phone").val() ? ("<br>"+Drupal.t("Cell Phone: ")+$("#edit-submitted-step-2-contact-information-cell-phone").val()) : "";
        var contact_fax = $("#edit-submitted-step-2-contact-information-fax-number").val() ? ("<br>"+Drupal.t("Fax Number: ")+$("#edit-submitted-step-2-contact-information-fax-number").val()) : "";
        var contact = contact_fn+" "+contact_ln+contact_email+contact_hphone+contact_cphone+contact_fax;
        //canada address
        var address_1 = $("#edit-submitted-step-2-canada-address-canadian-address-thoroughfare").val();
        var address_2 = $("#edit-submitted-step-2-canada-address-canadian-address-premise").val() ? ("<br>"+$("#edit-submitted-step-2-canada-address-canadian-address-premise").val()) : "";
        var city = $("#edit-submitted-step-2-canada-address-canadian-address-locality").val() ? ("<br>"+$("#edit-submitted-step-2-canada-address-canadian-address-locality")) : "";
        var province = $("#edit-submitted-step-2-canada-address-canadian-address-administrative-area").val() ? (" "+$("#edit-submitted-step-2-canada-address-canadian-address-administrative-area").val()) : "";
        var postal_code = $("#edit-submitted-step-2-canada-address-canadian-address-postal-code").val() ? (" "+$("#edit-submitted-step-2-canada-address-canadian-address-postal-code").val()) : "";
        var phone_1 = $("#edit-submitted-step-2-canada-address-phone-1").val() ? ("<br>"+$("#edit-submitted-step-2-canada-address-phone-1").val()) : "";
        var phone_2 = $("#edit-submitted-step-2-canada-address-phone-2").val() ? ("  "+$("#edit-submitted-step-2-canada-address-phone-2").val()) : "";
        var canada_address = address_1+address_2+city+province+postal_code+phone_1+phone_2;
        //traveller information
        var insured = $("<div class='item i_header'><div class='name'>"+Drupal.t("First Name, Last Name")+"</div><div class='birthday'>"+Drupal.t("Birthday (age)")+"</div><div class='spmcc' title='"+Drupal.t("Stable pre-existing medical condition coverage")+"'>"+Drupal.t("SPMCC")+"</div><div class='premium'>"+Drupal.t("Premium")+"</div></div>");
        var insured_completion = buyonline_step_2_check_all_insured_completion();
        var insured_info = buyonline_step_4_get_all_insured_info();
        if (window.console) console.log(insured_info);        
        
        var ajax_premium_counter = 0;
        for (var i = 0; i <= insured_completion.length - 1; i++) {
          if (insured_completion[i]) {
            //set up the counter. when the counter is 0, then trigger the total premium.
            ajax_premium_counter++;
            if (window.console) console.log(ajax_premium_counter);
            insured += $("<div class='item'><div class='name'>"+Drupal.t("First Name, Last Name")+"</div><div class='birthday'>"+Drupal.t("Birthday (age)")+"</div><div class='spmcc' title='"+Drupal.t("Stable pre-existing medical condition coverage")+"'>"+Drupal.t("SPMCC")+"</div><div class='premium'>"+Drupal.t("Premium")+"</div></div>");
            //get the price
            $.ajax({
              type: "GET",
              url: "/get-a-quote/visitor-to-canada-insurance/calculate-premium",
              data: {
                pid: buyonline_step_2_get_pid(), 
                effective: buyonline_step_2_get_effective_date(),
                expiry: buyonline_step_2_get_expiry_date(),
                coverage: buyonline_step_2_get_coverage(),
                deductible: buyonline_step_2_get_deductible(),
                insured_bod: insured_info[i]['dob'],
                spmcc: insured_info[i]['spmcc']
              }
            })
            .done(function( data ) {
              ajax_premium_counter--;
              if (window.console) console.log(ajax_premium_counter, data.premium);
              //if all the insured have the price.
              if (ajax_premium_counter == 0) {
                //todo - show the total premium
                if (window.console) console.log('show the total premium!');

              }
            });              
          }
        };
        //coverage & deductible
        var coverage = "<div class='item coverage'><span class='label'>"+Drupal.t("Coverage:")+"</span><span class='value'>"+$("#edit-submitted-step-2-coverage-and-deductible-coverage-sum-insured").val()+"</span></div>";
        var deductible = "<div class='item deductible'><span class='label'>"+Drupal.t("Deductible:")+"</span><span class='value'>"+$("#edit-submitted-step-2-coverage-and-deductible-select-a-deductible-amount").val()+"</span></div>";
        var beneficiary = "<div class='item beneficiary'><span class='label'>"+Drupal.t("Beneficiary:")+"</span><span class='value'>"+$("#edit-submitted-step-2-insured-members-beneficiary-name").val()+"</span></div>";
        var converage_deductible = coverage+deductible+beneficiary;
        var review = $("<div class='review_wrapper'><div class='review'><div class='section plan'><div class='s_header'></div><class='s_content'></div></div><div class='section policy_summary'><div class='s_header'>"+Drupal.t("Policy Summary")+"</div><class='s_content'></div></div><div class='section converage_deductible'><div class='s_header'>"+Drupal.t("Coverage & Deductible")+"</div><class='s_content'>"+converage_deductible+"</div></div><div class='section insured'><div class='s_header'>"+Drupal.t("Traveller Information")+"</div><class='s_content'></div></div><div class='section contact'><div class='s_header'>"+Drupal.t("Contact Information")+"</div><div class='s_content'>"+contact+"</div></div><div class='section address'><div class='s_header'>"+Drupal.t("Canada Address")+"</div><class='s_content'>"+canada_address+"</div></div></div></div>");
        $(".webform-component--step-4--review").html(review);

      }
    }
  });

})(jQuery);
