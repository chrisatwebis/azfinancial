(function ($) {


  $( document ).ready(function() {
    /**
    * Superfish mega menu handling
    **/
    if($("#superfish-1").children("li.menuparent").length > 0){
      $("#superfish-1").children("li.menuparent").each(function(){
        if(!$(this).hasClass("sf-parent-children-0")){
          var prev = $(this).prev().outerWidth();
          var next = $(this).next().outerWidth();
          var width = prev + next + $(this).outerWidth();
          $(this).children(".sf-megamenu").css({"left": -prev, width: width});

        }
      });
    }      
  });

})(jQuery);


