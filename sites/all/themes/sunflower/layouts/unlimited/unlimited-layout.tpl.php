<div<?php print $attributes; ?>>
  <div class='section-wrapper section-wrapper-user'>
    <div class='l-user'>
      <div class='l-user-bar'>
        <?php print render($page['user_bar']); ?>
      </div>
    </div>
  </div>
  <div class='section-wrapper section-wrapper-header'>
    <header class="l-header" role="banner">
      <div class="l-branding">
        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="site-logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
        <?php endif; ?>

        <?php if ($site_name || $site_slogan): ?>
          <?php if ($site_name): ?>
            <h1 class="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 class="site-slogan"><?php print $site_slogan; ?></h2>
          <?php endif; ?>
        <?php endif; ?>

        <?php print render($page['branding']); ?>
      </div>

      <?php print render($page['header']); ?>
      <?php print render($page['navigation']); ?>
      <div class='l-overlay'>
        <?php print render($page['overlay']); ?>
      </div>
    </header>
  </div>
  
  <?php if (!empty($page['hero'])): ?>
  <div class='section-wrapper section-wrapper-hero'>
    <div class='l-hero'>
      <?php print render($page['hero']); ?>
    </div>
  </div>
  <?php endif; ?>

  <?php if (!empty($page['highlighted'])): ?>
  <div class='section-wrapper section-wrapper-highlighted'>
    <div class='l-highlighted'>
        <?php print render($page['highlighted']); ?>
    </div>
  </div>
  <?php endif; ?>
  
  <div class='section-wrapper section-wrapper-main'>
    <div class="l-main">
      <div class="l-content" role="main">
        
        <?php if ($title || $breadcrumb): ?>
        <div class='main_content_header'>
          <?php print $breadcrumb; ?>
          <a id="main-content"></a>
          <?php print render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 id="page_title"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
        </div>
        <?php endif; ?>

        <?php print $messages; ?>
        <?php print render($tabs); ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div>

      <?php print render($page['sidebar_first']); ?>
      <?php print render($page['sidebar_second']); ?>
    </div>
  </div>
  <div class='section-wrapper section-wrapper-below-content'>
    <div class="l-below-content">
      <?php print render($page['below_content']); ?>      
    </div>
  </div>
  <div class='section-wrapper section-wrapper-above-postscript'>
    <div class="l-above-postscript">
      <?php print render($page['above_postscript']); ?>
    </div>
  </div>
  <div class='section-wrapper section-wrapper-postscript'>
    <div class='l-postscript'>
      <?php print render($page['postscript_first']); ?>
      <?php print render($page['postscript_second']); ?>
      <?php print render($page['postscript_third']); ?>
      <?php print render($page['postscript_fourth']); ?>
    </div>
  </div>
  <div class='section-wrapper section-wrapper-below-postscript'>
    <div class='l-below-postscript'>
      <?php print render($page['below_postscript']); ?>
    </div>
  </div>
  <div class='section-wrapper section-wrapper-footer'>
    <footer class="l-footer" role="contentinfo">
      <?php print render($page['footer']); ?>
    </footer>
  </div>
</div>
