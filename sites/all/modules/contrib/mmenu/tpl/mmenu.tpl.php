<?php

/**
 * @file
 * Default theme implementation to display a mmenu.
 *
 * Available variables:
 * - $mmenu: the original mmenu definitions.
 * - $id: the id of the mmenu.
 * - $name: the machine name of the mmenu.
 * - $blocks: an array that contains all rendered blocks and its configurations.
 *
 * @see template_preprocess()
 * @see template_preprocess_mmenu()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<nav id="<?php print $id; ?>" class="clearfix">
  <ul>
    <?php foreach ($blocks as $k => $block): ?>
      <?php if ($block['collapsed']): ?>
        <li class="mmenu-collapsed">
          <?php if (!empty($block['subject'])): ?>
            <span class="mmenu-block-collapsed mmenu-list"><i class="mmenu-list-icon mmenu-list-icon-<?php print $block['module']; ?>-<?php print $block['delta']; ?>"></i><span class="mmenu-list-title"><?php print $block['subject']; ?></span></span>
          <?php endif; ?>
          <?php if($block['wrap']): ?>
            <ul><li class="mmenu-wrap"><span><?php print $block['content']; ?></span></li></ul>
          <?php else : ?>
            <?php print $block['content']; ?>
          <?php endif; ?>
        </li>
      <?php else : ?>
        <?php if (!empty($block['subject'])): ?>
          <li class="mmenu-expanded">
            <span class="mmenu-block-expanded mmenu-list"><i class="mmenu-list-icon mmenu-list-icon-<?php print $block['module']; ?>-<?php print $block['delta']; ?>"></i><span class="mmenu-list-title"><?php print $block['subject']; ?></span></span>
          </li>
        <?php endif; ?>
        <?php if($block['wrap']): ?>
          <ul><li class="mmenu-wrap"><span><?php print $block['content']; ?></span></li></ul>
        <?php else : ?>
          <?php print $block['content']; ?>
        <?php endif; ?>
      <?php endif; ?>
    <?php endforeach; ?>
  </ul>
</nav>
