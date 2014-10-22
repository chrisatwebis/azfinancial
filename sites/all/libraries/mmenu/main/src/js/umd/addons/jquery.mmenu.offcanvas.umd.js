(function ( factory ) {
    if ( typeof define === 'function' && define.amd )
    {
        // AMD. Register as an anonymous module.
        define( [ 'jquery' ], factory );
    }
    else if ( typeof exports === 'object' )
    {
        // Node/CommonJS
        factory( require( 'jquery' ) );
    }
    else
    {
        // Browser globals
        factory( jQuery );
    }
}( function ( jQuery ) {


/*	
 * jQuery mmenu offCanvas addon
 * mmenu.frebsite.nl
 *
 * Copyright (c) Fred Heusschen
 */
!function(e){function o(o){return("top"==o.position||"bottom"==o.position)&&("back"==o.zposition||"next"==o.zposition)&&(e[s].deprecated('Using position "'+o.position+'" in combination with zposition "'+o.zposition+'"','zposition "front"'),o.zposition="front"),o}function t(e){return"string"!=typeof e.pageSelector&&(e.pageSelector="> "+e.pageNodetype),e}function n(){c=!0,p=e[s]._c,a=e[s]._d,r=e[s]._e,p.add("offcanvas modal background opening blocker page"),a.add("style"),r.add("opening opened closing closed setPage"),l=e[s].glbl,l.$allMenus=(l.$allMenus||e()).add(this.$menu),l.$wndw.on(r.keydown,function(e){return l.$html.hasClass(p.opened)&&9==e.keyCode?(e.preventDefault(),!1):void 0});var o=0;l.$wndw.on(r.resize,function(e,t){if(t||l.$html.hasClass(p.opened)){var n=l.$wndw.height();(t||n!=o)&&(o=n,l.$page.css("minHeight",n))}})}var s="mmenu",i="offCanvas";e[s].prototype["_init_"+i]=function(){if(this.opts[i]&&!this.vars[i+"_added"]){this.vars[i+"_added"]=!0,c||n(),this.opts[i]=o(this.opts[i]),this.conf[i]=t(this.conf[i]);var e=this.opts[i],s=this.conf[i],a=[p.offcanvas];"boolean"!=typeof this.vars.opened&&(this.vars.opened=!1),"left"!=e.position&&a.push(p.mm(e.position)),"back"!=e.zposition&&a.push(p.mm(e.zposition)),this.$menu.addClass(a.join(" ")).parent().removeClass(p.wrapper),this[i+"_initPage"](l.$page),this[i+"_initBlocker"](),this[i+"_initOpenClose"](),this[i+"_bindCustomEvents"](),this.$menu[s.menuInjectMethod+"To"](s.menuWrapperSelector)}},e[s].addons.push(i),e[s].defaults[i]={position:"left",zposition:"back",modal:!1,moveBackground:!0},e[s].configuration[i]={pageNodetype:"div",pageSelector:null,menuWrapperSelector:"body",menuInjectMethod:"prepend"},e[s].prototype.open=function(){if(this.vars.opened)return!1;var e=this;return this._openSetup(),setTimeout(function(){e._openFinish()},this.conf.openingInterval),"open"},e[s].prototype._openSetup=function(){l.$allMenus.not(this.$menu).trigger(r.close),l.$page.data(a.style,l.$page.attr("style")||""),l.$wndw.trigger(r.resize,[!0]);var e=[p.opened];this.opts[i].modal&&e.push(p.modal),this.opts[i].moveBackground&&e.push(p.background),"left"!=this.opts[i].position&&e.push(p.mm(this.opts[i].position)),"back"!=this.opts[i].zposition&&e.push(p.mm(this.opts[i].zposition)),this.opts.classes&&e.push(this.opts.classes),l.$html.addClass(e.join(" ")),this.vars.opened=!0,this.$menu.addClass(p.current+" "+p.opened)},e[s].prototype._openFinish=function(){var e=this;this.__transitionend(l.$page,function(){e.$menu.trigger(r.opened)},this.conf.transitionDuration),l.$html.addClass(p.opening),this.$menu.trigger(r.opening)},e[s].prototype.close=function(){if(!this.vars.opened)return!1;var e=this;return this.__transitionend(l.$page,function(){e.$menu.removeClass(p.current).removeClass(p.opened),l.$html.removeClass(p.opened).removeClass(p.modal).removeClass(p.background).removeClass(p.mm(e.opts[i].position)).removeClass(p.mm(e.opts[i].zposition)),e.opts.classes&&l.$html.removeClass(e.opts.classes),l.$page.attr("style",l.$page.data(a.style)),e.vars.opened=!1,e.$menu.trigger(r.closed)},this.conf.transitionDuration),l.$html.removeClass(p.opening),this.$menu.trigger(r.closing),"close"},e[s].prototype[i+"_initBlocker"]=function(){var o=this;l.$blck||(l.$blck=e('<div id="'+p.blocker+'" />').appendTo(l.$body)),l.$blck.off(r.touchstart).on(r.touchstart,function(e){e.preventDefault(),e.stopPropagation(),l.$blck.trigger(r.mousedown)}).on(r.mousedown,function(e){e.preventDefault(),l.$html.hasClass(p.modal)||o.close()})},e[s].prototype[i+"_initPage"]=function(o){o||(o=e(this.conf[i].pageSelector,l.$body),o.length>1&&(e[s].debug("Multiple nodes found for the page-node, all nodes are wrapped in one <"+this.conf[i].pageNodetype+">."),o=o.wrapAll("<"+this.conf[i].pageNodetype+" />").parent())),o.addClass(p.page),l.$page=o},e[s].prototype[i+"_initOpenClose"]=function(){var o=this,t=this.$menu.attr("id");t&&t.length&&(this.conf.clone&&(t=p.umm(t)),e('a[href="#'+t+'"]').off(r.click).on(r.click,function(e){e.preventDefault(),o.open()}));var t=l.$page.attr("id");t&&t.length&&e('a[href="#'+t+'"]').on(r.click,function(e){e.preventDefault(),o.close()})},e[s].prototype[i+"_bindCustomEvents"]=function(){var e=this,o=r.open+" "+r.opening+" "+r.opened+" "+r.close+" "+r.closing+" "+r.closed+" "+r.setPage;this.$menu.off(o).on(o,function(e){e.stopPropagation()}),this.$menu.on(r.open,function(){e.open()}).on(r.close,function(){e.close()}).on(r.setPage,function(o,t){e[i+"_initPage"](t),e[i+"_initOpenClose"]()})};var p,a,r,l,c=!1}(jQuery);
}));