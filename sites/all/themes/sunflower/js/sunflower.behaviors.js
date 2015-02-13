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

  function buyonline_get_today_date() {
    var today = new Date();
    var dd = today.getDate();
    var mm = today.getMonth()+1; //January is 0!
    var yyyy = today.getFullYear();
    if (dd<10) { dd='0'+dd; }
    if (mm<10) { mm='0'+mm; }
    return yyyy+"-"+mm+"-"+dd;
  }

  $( document ).ready(function() {
    //Add close button for mobile menu
    $("<span class='close_btn'></span>").appendTo(".mm-menu").click(function(){
      $(".mm-menu").trigger("close");
    });

    //purchase online webform
    //only run the script if it is buy online page
    if ($("#webform-client-form-184").length) {

      var form = $("#webform-client-form-184");

      //Get product field object
      function get_obj_product() {
        return $("#edit-submitted-step-2-insurance-product");
      }
      //Get deductibles field object
      function get_obj_deductibles() {
        return $("#edit-submitted-step-2-coverage-and-deductible-select-a-deductible-amount");
      }
      //Get deductibles clone field object
      function get_obj_deductibles_clone() {
        return $("#deductibles_clone");
      }
      //Get coverage field object
      function get_obj_coverages() {
        return $("#edit-submitted-step-2-coverage-and-deductible-coverage-sum-insured");
      }
      //Get coverages clone field object
      function get_obj_coverages_clone() {
        return $("#coverages_clone");
      }
      //Get the traveller information fieldset
      function add_dropdown_to_traveller_information_fieldset() {
        var traveller_info_feildset = $("fieldset.webform-component--step-2--traveller-information-insured");
        var count = traveller_info_feildset.find("> .fieldset-wrapper > fieldset").length;
        if (count > 1) {
          var traveller_number = $("<div id='traveller_number'><label for='traveller_number_select'>"+Drupal.t("Number Of Insured: ")+"</label><select id='traveller_number_select'></select></div>");
          for (var i = 1; i <= count; i++) {
            traveller_number.find("select").append("<option value='"+i+"'>"+i+"</option>");
          };
          traveller_info_feildset.prepend(traveller_number);
          traveller_number.find("select").change(function(){
            traveller_info_feildset.find("> .fieldset-wrapper > fieldset").slice(0, $(this).val()).fadeIn();
            traveller_info_feildset.find("> .fieldset-wrapper > fieldset").slice($(this).val()).fadeOut();
          });
          traveller_number.find("select").change();                   
        }
      }
      //Add the "how many insured" dropdown
      add_dropdown_to_traveller_information_fieldset();

      //clone the deductibles;
      var deductibles_clone = $("<select id='deductibles_clone'></select>");
      get_obj_deductibles().find("option").clone().appendTo(deductibles_clone);
      deductibles_clone.find("option:selected").removeAttr("selected").prop("selected", false);
      get_obj_deductibles().after(deductibles_clone);

      //clone the coverages;
      var coverages_clone = $("<select id='coverages_clone'></select>");
      get_obj_coverages().find("option").clone().appendTo(coverages_clone);
      coverages_clone.find("option:selected").removeAttr("selected").prop("selected", false);
      get_obj_coverages().after(coverages_clone);

      //add 'continue' button to step 2,3,4
      $.each([1,2,3], function(index, value) {
        $("#webform-client-form-184 .webform-component--step-"+value+" > .fieldset-wrapper").append("<div class='continue_btn disabled'><a href='#'>"+Drupal.t("Continue")+"</a></div>");
      });

      //hide the 'submit' button
      buyonline_show_submit_btn(false);

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
          //if the continue button is not disabled, then open the next step.
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
          //if the continue button is disabled. 
          if ($(".no_result_found").length > 0) {
            $('html, body').animate({ scrollTop: ($(".no_result_found:first").offset().top - 100) }, 1000, function(){});
          }
          else {
            $("#webform-client-form-184 .form-actions .form-submit").click();            
          }
        }
      });

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
            buyonline_show_submit_btn(true);
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
            buyonline_show_submit_btn(false);
            break;
          case 2:
            form.find(".webform-component--step-"+step_number+" .continue_btn").addClass("disabled");
            step_2_complete = false;
            buyonline_collapse_step(3);
            buyonline_collapse_step(4);
            buyonline_show_submit_btn(false);
            break;
          case 3:
            form.find(".webform-component--step-"+step_number+" .continue_btn").addClass("disabled");
            step_3_complete = false;
            buyonline_collapse_step(4);
            buyonline_show_submit_btn(false);
            break;
          case 4:
            step_4_complete = false;
            break;
          default:
            break;
        }

      }).on("get_deductible_coverage_by_pid", function(e, price_entity_id, passed_coverages_value){

        //check whether pid is ready
        if (price_entity_id.length > 0) {

          var insured_info = buyonline_step_4_get_all_insured_info();
          var insured_age = "";

          for (var i = insured_info.length - 1; i >= 0; i--) {
            if ((typeof insured_info[i] !== 'undefined') && (typeof insured_info[i]['age'] !== 'undefined')) {
              insured_age += insured_info[i]['age']+"_";
            }
          };
          
          var data_arg = { pid: price_entity_id, age: insured_age, intersect: true };
          //check whether coverage value is passed
          if (typeof passed_coverages_value !== 'undefined') {
            data_arg.coverages = passed_coverages_value;
          }
          //get the deductible and coverage
          $.ajax({
            // type: "POST",
            type: "GET",
            url: "/get-a-quote/visitor-to-canada-insurance/get-deductible-coverage",
            traditional: false,
            data: data_arg
          })
          .done(function( data ) {
            var age = data.query.age;
            var coverages = data.coverages;
            var deductibles = data.deductibles;
            var coverages_obj = get_obj_coverages();
            var deductibles_obj = get_obj_deductibles();
            var coverages_obj_clone = get_obj_coverages_clone();
            var deductibles_obj_clone = get_obj_deductibles_clone();

            var deductibles_value = deductibles_obj.val();
            var coverages_value = coverages_obj.val();

            coverages_obj.find("option").remove();
            deductibles_obj.find("option").remove();

            var coverage_selected = false;
            if (coverages !== undefined) {
              //if there are coverages
              if (coverages.length > 0) {
                for (var i = 0; i < coverages.length; i++) {
                  coverages_obj.append(coverages_obj_clone.find("option[value="+coverages[i]+"]").clone());
                  if (coverages_value == coverages[i]) {
                    coverage_selected = true;
                    coverages_obj.val(coverages[i]);
                  }

                };
                //found the coverages, trigger the event to remove the error message if there is any.
                form.trigger("found_coverages");
              }
              else {
                //If there is no coverage found;
                var error_msg = "";
                //if there is at least 1 insured
                if (age.length > 0) {
                  var age_arr = age.split("_");
                  //if there are more than 1 insured (the last element of age_arr is not in use)
                  if (age_arr.length > 2) {
                    error_msg = "There is no common coverage found for all insured's age: ";
                    for (var i = age_arr.length - 1; i >= 0; i--) {
                      if (age_arr[i] !== "") {
                        error_msg += age_arr[i] + ", ";
                      }
                    };
                    error_msg = error_msg.substring(0, error_msg.length - 2) + ". ";
                    error_msg += "You might have to split your policy into 2 policies. Also, remember that you could always call us!!";
                  }
                  else {
                    //if there is only 1 insured
                    error_msg = "There is no coverage found for insured's age: "+age_arr[0]+", please choose different plan. Also, remember that you could always call us!";
                  }
                }
                else {
                //if there is no insured
                  error_msg = "There is no coverage found! But you could call us to find out the quote!";
                }
                //if there aren't coverages, then trigger the "no_deductibles" event
                form.trigger("no_coverages", error_msg);
              }
            }
            if (!coverage_selected) {
              coverages_obj.val("").find("option:selected").removeAttr("selected").prop("selected", false);
            }

            var deductible_selected = false;
            if ( deductibles !== undefined ) {
              if (deductibles.length > 0) {
                for (var i = 0; i < deductibles.length; i++) {
                  deductibles_obj.append(deductibles_obj_clone.find("option[value="+deductibles[i]+"]").clone());
                  if (deductibles_value == deductibles[i]) {
                    deductible_selected = true;
                    deductibles_obj.val(deductibles[i]);
                  }
                };
                //found the deductibles, trigger the event to remove the error message if there is any.
                form.trigger("found_deductibles");
              }
              else {
                var error_msg = "";
                //if there is at least 1 insured
                if (age.length > 0) {
                  var age_arr = age.split("_");
                  //if there are more than 1 insured (the last element of age_arr is not in use)
                  if (age_arr.length > 2) {
                    error_msg = "There is no common deductible found for all insured's age: ";
                    for (var i = age_arr.length - 1; i >= 0; i--) {
                      if (age_arr[i] !== "") {
                        error_msg += age_arr[i] + ", ";
                      }
                    };
                    error_msg = error_msg.substring(0, error_msg.length - 2) + ". ";
                    error_msg += "You might have to split your policy into 2 policies. Also, remember that you could always call us!!";
                  }
                  else {
                    //if there is only 1 insured
                    error_msg = "There is no deductible found for insured's age: "+age_arr[0]+", please try different plan.";
                  }
                }
                else {
                  //if there is no insured
                  error_msg = "There is no deductible found! But you could call us to find out the quote!";
                }
                //Trigger the "no_deductibles" event
                form.trigger("no_deductibles", Drupal.t(error_msg));     
              }
            }
            if (!deductible_selected) {
              deductibles_obj.val("").find("option:selected").removeAttr("selected").prop("selected", false);
            }

            buyonline_step_2_check_completion();
            buyonline_step_3_update();

          });
        }  

      }).on("found_deductibles", function(e, error_msg){

        var deductibles_obj = get_obj_deductibles();
        deductibles_obj.removeClass("error");
        if (deductibles_obj.parent().find(".no_result_found").length >= 0) {
          deductibles_obj.parent().find(".no_result_found").remove();
        }

      }).on("found_coverages", function(e, error_msg){

        var coverages_obj = get_obj_coverages();
        coverages_obj.removeClass("error");
        if (coverages_obj.parent().find(".no_result_found").length >= 0) {
          coverages_obj.parent().find(".no_result_found").remove();
        }

      }).on("no_deductibles", function(e, error_msg){

        var deductibles_obj = get_obj_deductibles();
        deductibles_obj.addClass("error");
        if (deductibles_obj.parent().find(".no_result_found").length >= 0) {
          deductibles_obj.parent().find(".no_result_found").remove();
        }
        deductibles_obj.parent().append('<div class="ife_messages messages error messages-inline no_result_found">'+error_msg+'</div>');
        //delete the price hint for each insured.
        $(".insured_premium").remove();

      }).on("no_coverages", function(e, error_msg){

        var coverages_obj = get_obj_coverages();
        coverages_obj.addClass("error");
        if (coverages_obj.parent().find(".no_result_found").length >= 0) {
          coverages_obj.parent().find(".no_result_found").remove();
        }
        coverages_obj.parent().append('<div class="ife_messages messages error messages-inline no_result_found">'+error_msg+'</div>');
        //delete the price hint for each insured.
        $(".insured_premium").remove();

      }).on("premium_factor_change", function(e){

        buyonline_step_4_review();

      }).on("total_premium_update", function(e){

        buyonline_step_4_update_total_premium();

      }).on("premium_found", function(e, delta, data){
        //get all insureds information
        var insured_info = buyonline_step_4_get_all_insured_info();
        var ajax_premium = (insured_info[data.storage.insured_id]['spmcc'] == 'yes' ? data.premium.spmcc : data.premium.no_spmcc);        
        // if the premium is found for the insured, then remove the error message.
        var the_insured = $(".webform-component--step-2--traveller-information-insured--insured-"+delta);
        
        if (the_insured.find(".error").length >= 0) {
          the_insured.find(".error").remove();
        }

        var insured_premium_price = ("<span class='insured_premium_price'>"+Drupal.t('Price/Day: ')+"<span class='price'>$"+ajax_premium+"</span></span>");
        
        //show the premium for this insured.
        if (the_insured.find(".insured_information").length <= 0) {
          the_insured.find(".fieldset-wrapper").append("<div class='insured_information'><span class='insured_premium'>"+insured_premium_price+"</span></div>");
        }
        else {
          if (the_insured.find(".insured_premium").length > 0) {
            the_insured.find(".insured_premium").html(insured_premium_price);
          }
          else {
            the_insured.find(".insured_information").append("<span class='insured_premium'>"+insured_premium_price+"</span>");
          }
        }

        // update the premium in the traveller information section
        $("#insured_person_"+(delta-1)).find(".premium_amount").html(ajax_premium);
        $("#insured_person_"+(delta-1)).find(".dollar_sign").html("$");
        $("#edit-submitted-step-4-premium-insured-"+delta+"-premium").val(ajax_premium);

      }).on("premium_not_found", function(e, delta, age){
        
        // if the premium is not found for the insured, then add the error message.
        var the_insured = $(".webform-component--step-2--traveller-information-insured--insured-"+delta);
        form.trigger("step_incomplete", [2]);
        
        if (the_insured.find(".no_result_found").length >= 0) {
          the_insured.find(".no_result_found").remove();
        }
        
        the_insured.find(".fieldset-wrapper").append("<div class='ife_messages messages error messages-inline no_result_found'>"+Drupal.t("We can't find the price for the 'insured "+(delta)+"' whose age is "+age+", please choose different coverage, deductible or plan. Also, remember that you could always call us!")+"</div>");
        
        if (the_insured.find(".insured_premium").length > 0) {
          the_insured.find(".insured_premium").remove();
        }
        
        // update the premium in the traveller information section
        $("#insured_person_"+(delta-1)).find(".premium_amount").html("n/a");
        $("#insured_person_"+(delta-1)).find(".dollar_sign").html("");

      }).on("premium_found_spmcc", function(e, delta, ajax_premium){
        
        // if the premium is found for the insured, then remove the error message.
        var the_insured = $(".webform-component--step-2--traveller-information-insured--insured-"+delta);
        
        if (the_insured.find(".no_result_found").length >= 0) {
          the_insured.find(".no_result_found").remove();
        }

        var spmcc_options = $("#edit-submitted-step-3-do-you-want-pre-existing-condition-covered-"+delta);
        spmcc_options.find("input:radio[value=yes]").attr('disabled', false).parent().fadeIn();
        spmcc_options.find(".spmcc_msg").remove();

      }).on("premium_not_found_spmcc", function(e, delta, age){
        
        //disable the radio option, and check the other option automatically
        var spmcc_options = $("#edit-submitted-step-3-do-you-want-pre-existing-condition-covered-"+delta);
        spmcc_options.find("input:radio[value=yes]").attr('disabled', true).parent().fadeOut();
        spmcc_options.find("input:radio[value=no]").attr('checked', 'checked').parent().fadeIn();
        
        if (spmcc_options.find(".spmcc_msg").length <= 0) {
          spmcc_options.append("<div class='spmcc_msg'>"+Drupal.t("For the insured's age, the pre-existing medical condition is not coverred!")+"</div>")
        }

      }).on("premium_found_no_spmcc", function(e, delta, ajax_premium){
        
        // if the premium is found for the insured, then remove the error message.
        var the_insured = $(".webform-component--step-2--traveller-information-insured--insured-"+delta);
        
        if (the_insured.find(".no_result_found").length >= 0) {
          the_insured.find(".no_result_found").remove();
        }

        var spmcc_options = $("#edit-submitted-step-3-do-you-want-pre-existing-condition-covered-"+delta);
        spmcc_options.find("input:radio[value=no]").attr('disabled', false).parent().fadeIn();
        spmcc_options.find(".spmcc_msg").remove();

      }).on("premium_not_found_no_spmcc", function(e, delta, age){
        
        //disable the radio option, and check the other option automatically
        var spmcc_options = $("#edit-submitted-step-3-do-you-want-pre-existing-condition-covered-"+delta);
        spmcc_options.find("input:radio[value=no]").attr('disabled', true).parent().fadeOut();
        spmcc_options.find("input:radio[value=yes]").attr('checked', 'checked').parent().fadeIn();
        
        if (spmcc_options.find(".spmcc_msg").length <= 0) {
          spmcc_options.append("<div class='spmcc_msg'>"+Drupal.t("For the insured's age, the pre-existing medical condition is automatically covered!")+"</div>")
        }

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
        var total_days = buyonline_step_2_get_duration();
        if (typeof total_days !== 'undefined') {
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
      //get the total days of the policy
      function buyonline_step_2_get_duration() {
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
          return total_days;
        }
      }
      //get the individual birthday in following format: yyyy-mm-dd
      function buyonline_step_2_get_dob(delta) {
        if (buyonline_step_2_is_bdate_complete(delta)) {
          var year = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .year").val();
          var day = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .day").val();
          var month = $(".webform-component--step-2--traveller-information-insured--insured-"+delta+"--birthday .month").val();
          if (day<10) { day = '0' + day; }
          if (month<10) { month = '0'+ month; }
          return year+"-"+month+"-"+day;
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
          if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_information").length <= 0) {
            $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .fieldset-wrapper").append("<div class='insured_information'></div>");
          }
          if (typeof insured_age !== 'undefined') {
            if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age").length) {
              $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_age .insured_age_duration").html(
                Drupal.t("Age")+": <b>"+insured_age+" "+Drupal.t("year old")+" </b>"
              );
            }
            else {
              $(".webform-component--step-2--traveller-information-insured--insured-"+delta+" .insured_information").append('<span class="insured_age"><span class="insured_age_duration">'+Drupal.t("Age")+': <b>'+insured_age+" "+Drupal.t("year old")+' </b></span></span>');
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
        var insured_complete = true;
        if ($(".webform-component--step-2--traveller-information-insured--insured-"+delta).length > 0) {
          $(".webform-component--step-2--traveller-information-insured--insured-"+delta).find("input:not(:image), select").each(function(){
            if ($(this).val() == false) {
              insured_complete = false;
            }
          });
          return insured_complete;
        }
      }
      /*
      * check all the insured info completion.
      * return - an array with item value: true or false 
      */
      function buyonline_step_2_check_all_insured_completion() {
        var insured_completion = [];
        for (var i = 1; i <= 5; i++) {
          insured_completion[i-1] = buyonline_step_2_check_insured_completion(i);
        };
        return insured_completion;
      }

      //get the count of completed insured info
      function buyonline_step_insured_completion_count() {
        var completion = buyonline_step_2_check_all_insured_completion();
        var count = 0;
        for (var i = completion.length - 1; i >= 0; i--) {
          if (completion[i]) {
            count++;
          }
        };
        return count;
      }
      
      //collapse the step
      function buyonline_collapse_step(step_number) {
        $("#webform-client-form-184 .webform-component--step-"+step_number).addClass("custom_collapsed disabled").find("> .fieldset-wrapper").hide();    
      }

      //check anytime whether step 1 is completed.
      function buyonline_step_1_check_completion() {
        if ($("#edit-submitted-step-1-for-all-members-1").prop("checked")) {
          form.trigger("step_complete", [1]);
          return true;
        }
        else {
          form.trigger("step_incomplete", [1]);
          return false;
        }
      }

      //Hide form submit button
      function buyonline_show_submit_btn(show){
        if (show == true) {
          $("#webform-client-form-184 .form-actions").show();         
        }
        else {
          $("#webform-client-form-184 .form-actions").hide();        
        }
      }
      //monitor step 1 element change event
      function buyonline_step_1_monitor() {
        $(".webform-component--step-1").find("input, select").change(function(){
          buyonline_step_1_check_completion();
        });
        $(".webform-component--step-1").find("input, select").change();
      }
      //Auto expanse the step 2 accordion.
      function buyonline_step_2_auto_expanse() {
        form.find(".webform-component--step-1 .continue_btn a").click();
      }
      //get the price entity id
      function buyonline_step_2_get_pid() {
        var pid = get_obj_product().val();
        return pid;
      }
      //get the beneficiary name
      function buyonline_step_2_get_beneficiary() {
        return $("#edit-submitted-step-2-insured-members-beneficiary-name").val();
      }
      //get the arrival date 
      function buyonline_step_2_get_arrival_date() {
        var month   = $("#edit-submitted-step-2-travel-dates-canada-arrival-date-month").val();
        var day     = $("#edit-submitted-step-2-travel-dates-canada-arrival-date-day").val();
        var year    = $("#edit-submitted-step-2-travel-dates-canada-arrival-date-year").val();
        if (day<10) { day = '0' + day; }
        if (month<10) { month = '0'+ month; }
        return year+"-"+month+"-"+day;
      }
      //get the effective date 
      function buyonline_step_2_get_effective_date() {
        var month   = $("#edit-submitted-step-2-travel-dates-effective-date-month").val();
        var day     = $("#edit-submitted-step-2-travel-dates-effective-date-day").val();
        var year    = $("#edit-submitted-step-2-travel-dates-effective-date-year").val();
        if (day < 10) { day = '0' + day; }
        if (month < 10) { month = '0' + month; }
        return year+"-"+month+"-"+day;
      }
      //get the expiry date 
      function buyonline_step_2_get_expiry_date() {
        var month = $("#edit-submitted-step-2-travel-dates-expiry-date-month").val();
        var day = $("#edit-submitted-step-2-travel-dates-expiry-date-day").val();
        var year = $("#edit-submitted-step-2-travel-dates-expiry-date-year").val();
        if (day < 10) { day = '0' + day; }
        if (month < 10) { month = '0' + month; }
        return year+"-"+month+"-"+day;
      }
      //get the deductible 
      function buyonline_step_2_get_deductible() {
        var deductibles_obj = get_obj_deductibles();
        var deductible = [];
        if (deductibles_obj.val() !== "") {
          deductible['value'] = deductibles_obj.val();
          deductible['label'] = $("#edit-submitted-step-2-coverage-and-deductible-select-a-deductible-amount option:selected").text();
        }
        else {
          deductible['value'] = "";
          deductible['label'] = "";        
        }
        return deductible;          
      }
      //get the coverage 
      function buyonline_step_2_get_coverage() {
        var coverages_obj = get_obj_coverages();
        var coverage = [];
        if (coverages_obj.val() !== "") {
          coverage['value'] = coverages_obj.val();
          coverage['label'] = coverages_obj.find("option:selected").text();
        }
        else {
          coverage['value'] = "";
          coverage['label'] = "";         
        }
        return coverage;          
      }
      //get family plan
      function buyonline_step_2_get_family_plan() {
        if ($("#edit-submitted-step-2-insured-members-family-plan-1").is(':checked')) {
          return 1;
        }
        return 0;
      }
      //check whether step 2 is completed.
      function buyonline_step_2_check_completion() {

        var fulfilled = true;
        $(".webform-component--step-2").find(".required").each(function(){
          if ($(this).val() == '') {
            fulfilled = false;
          }
        });
        if (fulfilled && buyonline_step_2_effective_expiry_is_complete() && step_1_complete) {
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

        $(".webform-component--step-2").find("input, select").change(function(e){
          form.trigger("get_deductible_coverage_by_pid", [buyonline_step_2_get_pid(), $("#edit-submitted-step-2-coverage-and-deductible-coverage-sum-insured").val()]);
          // form.trigger("get_deductible_coverage_by_pid", [buyonline_step_2_get_pid()]);
          buyonline_step_2_show_age();
          buyonline_step_2_show_duration();
        });
        $("#edit-submitted-step-2-coverage-and-deductible-coverage-sum-insured").change(function(){

        });
        get_obj_product().change();

      }

      //step 3 is depended on step 2's insured info.
      function buyonline_step_3_update() {

        var all_insured_completion = buyonline_step_2_check_all_insured_completion();
        for (var i = 0; i <= all_insured_completion.length - 1; i++) {
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
        //check whether step 1, 2, 3 are all completed.
        if (fulfilled && step_2_complete && step_1_complete) {
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
          insured['age'] = buyonline_step_2_get_age(delta);
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
      //Update total premium
      function buyonline_step_4_update_total_premium() {
        if ($(".total_premium").length > 0) {
          var total_premium = 0;
          if (buyonline_step_2_get_family_plan()) {
            var max_premium = 0;
            $(".insured .premium_amount").each(function(){
              max_premium = max_premium > parseFloat($(this).text()) ? max_premium : parseFloat($(this).text());
            });               
            total_premium = max_premium * 2;
          }
          else {
            $(".insured .premium_amount").each(function(){
              total_premium += parseFloat($(this).text());
            });            
          }
          //round it up;
          total_premium = Math.round(total_premium * 100)/100;
          $(".total_premium").find(".total_premium_amount").html(total_premium);
          $("#edit-submitted-step-4-premium-total-premium").val(total_premium);
        }
      }

      //monitor step 4 element change event - current not in use.
      function buyonline_step_4_monitor() {
         
      }

      //Show the review on step 4
      function  buyonline_step_4_review() {
        if (!step_1_complete || !step_2_complete || !step_3_complete) {
          return ;
        }
        var price_entity_id   = buyonline_step_2_get_pid();
        var application_date  = buyonline_get_today_date();
        var arrival_date      = buyonline_step_2_get_arrival_date();
        var effective_date    = buyonline_step_2_get_effective_date();
        var expiry_date       = buyonline_step_2_get_expiry_date();
        var trip_duration     = buyonline_step_2_get_duration();
        var beneficiary       = buyonline_step_2_get_beneficiary();
        var family_plan       = buyonline_step_2_get_family_plan();
        var deductible        = buyonline_step_2_get_deductible();
        var deductible_amount = deductible['value'];
        var deductible_label  = deductible['label'];
        var coverage          = buyonline_step_2_get_coverage();
        var coverage_amount   = coverage['value'];
        var coverage_label    = coverage['label'];

        //policy summary
        var application_date_dom  = "<div class='item application_date'><span class='label'>"+Drupal.t("Application Date")+"</span><span class='value'>"+application_date+"</span></div>";
        var arrival_date_dom      = "<div class='item arrival_date'><span class='label'>"+Drupal.t("Arrival Date")+"</span><span class='value'>"+arrival_date+"</span></div>";
        var effective_date_dom    = "<div class='item effective_date'><span class='label'>"+Drupal.t("Effective Date")+"</span><span class='value'>"+effective_date+"</span></div>";
        var expiry_date_dom       = "<div class='item expiry_date'><span class='label'>"+Drupal.t("Expiry Date")+"</span><span class='value'>"+expiry_date+"</span></div>";
        var trip_duration         = "<div class='item trip_duration'><span class='label'>"+Drupal.t("Trip Duration")+"</span><span class='value'>"+trip_duration+" "+Drupal.t("days")+"</span></div>";
        var coverage_dom          = "<div class='item coverage'><span class='label'>"+Drupal.t("Coverage")+"</span><span class='value'>"+coverage_label+"</span></div>";
        var deductible_dom        = "<div class='item deductible'><span class='label'>"+Drupal.t("Deductible")+"</span><span class='value'>"+deductible_label+"</span></div>";
        var beneficiary_dom       = "<div class='item beneficiary'><span class='label'>"+Drupal.t("Beneficiary")+"</span><span class='value'>"+beneficiary+"</span></div>";
        var family_plan_dom       = "<div class='item family_plan'><span class='label'>"+Drupal.t("Family Plan")+"</span><span class='value'>"+(family_plan ? "Yes" : "No")+"</span></div>";
        var total_premium_dom     = "<div class='item total_premium'><span class='label'>"+Drupal.t("Total Premium")+"</span><span class='value'><span class='dollar_sign'>$</span><span class='total_premium_amount'>0</span></span></div>";
        var policy_summary        = application_date_dom+arrival_date_dom+effective_date_dom+expiry_date_dom+trip_duration+family_plan_dom+coverage_dom+deductible_dom+beneficiary_dom+total_premium_dom;

        //contact information
        var contact_fn        = $("#edit-submitted-step-2-contact-information-given-name").val();
        var contact_ln        = $("#edit-submitted-step-2-contact-information-surname").val();
        var contact_email     = $("#edit-submitted-step-2-contact-information-email").val() ? ("<br>"+Drupal.t("Email: ")+$("#edit-submitted-step-2-contact-information-email").val()) : "";
        var contact_hphone    = $("#edit-submitted-step-2-contact-information-home-phone").val() ? ("<br>"+Drupal.t("Home Phone: ")+$("#edit-submitted-step-2-contact-information-home-phone").val()) : "";
        var contact_cphone    = $("#edit-submitted-step-2-contact-information-cell-phone").val() ? ("<br>"+Drupal.t("Cell Phone: ")+$("#edit-submitted-step-2-contact-information-cell-phone").val()) : "";
        var contact_fax       = $("#edit-submitted-step-2-contact-information-fax-number").val() ? ("<br>"+Drupal.t("Fax Number: ")+$("#edit-submitted-step-2-contact-information-fax-number").val()) : "";
        var contact_info      = contact_fn+" "+contact_ln+contact_email+contact_hphone+contact_cphone+contact_fax;

        //canada address
        var address_1         = $("#edit-submitted-step-2-canada-address-canadian-address-thoroughfare").val();
        var address_2         = $("#edit-submitted-step-2-canada-address-canadian-address-premise").val() ? ("<br>"+$("#edit-submitted-step-2-canada-address-canadian-address-premise").val()) : "";
        var city              = $("#edit-submitted-step-2-canada-address-canadian-address-locality").val() ? ("<br>"+$("#edit-submitted-step-2-canada-address-canadian-address-locality").val()) : "";
        var province          = $("#edit-submitted-step-2-canada-address-canadian-address-administrative-area").val() ? (", "+$("#edit-submitted-step-2-canada-address-canadian-address-administrative-area").val()) : "";
        var postal_code       = $("#edit-submitted-step-2-canada-address-canadian-address-postal-code").val() ? (" "+$("#edit-submitted-step-2-canada-address-canadian-address-postal-code").val()) : "";
        var canada_address    = address_1+address_2+city+province+postal_code;

        //traveller information
        var family_plan_class   = family_plan ? "family_plan" : "";
        var traveller_info      = ("<div class='item i_header'><div class='name'>"+Drupal.t("Name")+"</div><div class='birthday'>"+Drupal.t("Birthday")+"<span class='age'> "+Drupal.t("(age)")+"</span></div><div class='spmcc' title='"+Drupal.t("Stable pre-existing medical condition coverage")+"'>"+Drupal.t("SPMCC")+"</div><div class='premium'>"+Drupal.t("Premium")+"</div></div>");

        //get the insured's premium
        var insured_completion  = buyonline_step_2_check_all_insured_completion();
        var insured_info        = buyonline_step_4_get_all_insured_info();

        var ajax_premium_counter = buyonline_step_insured_completion_count();
        for (var i = 0; i <= insured_completion.length - 1; i++) {
          if (insured_completion[i]) {
            //set up the counter. when the counter is 0, then trigger the total premium.
            traveller_info += ("<div class='item "+family_plan_class+"' id='insured_person_"+i+"'><div class='name'>"+insured_info[i]['first_name']+" "+insured_info[i]['last_name']+"</div><div class='birthday'>"+insured_info[i]['dob']+"<span class='age'> ("+insured_info[i]['age']+" years old)</span></div><div class='spmcc' title='"+Drupal.t("Stable pre-existing medical condition coverage")+"'>"+insured_info[i]['spmcc']+"</div><div class='premium'><span class='dollar_sign'>$</span><span class='premium_amount'>0</span></div></div>");
            //get the price
            $.ajax({
              type: "GET",
              url: "/get-a-quote/visitor-to-canada-insurance/calculate-premium",
              data: {
                pid:          price_entity_id, 
                effective:    effective_date,
                expiry:       expiry_date,
                coverage:     coverage_amount,
                deductible:   deductible_amount,
                insured_bod:  insured_info[i]['dob'],
                storage:      {insured_id:i, age:insured_info[i]['age']}
              }
            })
            .done(function( data ) {
              ajax_premium_counter--;
              if (typeof data.storage !== 'undefined' && typeof data.storage.insured_id !== 'undefined') {
                var delta = parseInt(data.storage.insured_id)+1;
                if ($("#insured_person_"+data.storage.insured_id).length) {
                  //if neither spmcc premium nor no_spmcc premium is found, then triger the 'premium not found' event.
                  if ((data.premium.spmcc == null) && (data.premium.no_spmcc == null)) {
                    form.trigger("premium_not_found", [delta, data.storage.age]);
                  }
                  else {
                    var found_premium = false;
                    //if the premium of spmcc is same as price for no_spmcc, then disable no_spmcc.
                    if (data.premium.spmcc == data.premium.no_spmcc) {
                      found_premium = true;
                      form.trigger("premium_not_found_no_spmcc", [delta, data.storage.age]);                    
                    }
                    else {
                      //if the premium for spmcc is not found, then trigger event;
                      if (data.premium.spmcc == null) {
                        form.trigger("premium_not_found_spmcc", [delta, data.storage.age]);
                      }
                      else {
                        found_premium = true;
                        form.trigger("premium_found_spmcc", [delta, data.storage.age]);
                      }
                      //if the premium for no_spmcc is not found, then trigger event;
                      if (data.premium.no_spmcc == null) {
                        form.trigger("premium_not_found_no_spmcc", [delta, data.storage.age]);
                      }
                      else {
                        found_premium = true;
                        form.trigger("premium_found_no_spmcc", [delta, data.storage.age]);                    
                      }
                    }
                    //if the desired premium is not found, then trigger the 'premium'.
                    if (found_premium) {
                      form.trigger("premium_found", [delta, data]);
                    }
                  }
                }
              }
              //if all the insured have the price.
              if (ajax_premium_counter == 0) {
                form.trigger("total_premium_update");
              }            
            });
          }
        }; 
        var review = $("<div class='review_wrapper'><div class='review'><div class='section policy_summary'><div class='s_header'>"+Drupal.t("Policy Summary")+"</div><div class='s_content'>"+policy_summary+"</div></div><div class='section insured'><div class='s_header'>"+Drupal.t("Traveller Information")+"</div><div class='s_content'>"+traveller_info+"</div></div><div class='section contact'><div class='s_header'>"+Drupal.t("Contact Information")+"</div><div class='s_content'>"+contact_info+"</div></div><div class='section address'><div class='s_header'>"+Drupal.t("Canada Address")+"</div><div class='s_content'>"+canada_address+"</div></div></div></div>");
        $(".webform-component--step-4--review").html(review);

      }
    }
  });

})(jQuery);
