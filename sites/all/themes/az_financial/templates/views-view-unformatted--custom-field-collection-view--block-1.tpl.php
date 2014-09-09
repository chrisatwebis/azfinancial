<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
$set_per_row = 3;
$total_row = count($rows); //5
$perfect_set = false;
$total_set = 1;

if ($total_row % $set_per_row == 0)
{
  //if the total rows number is divisible by 3, all the row should be .triple
  $perfect_set = true;
}
if ($total_row > $set_per_row) {
  $total_set = ceil( $total_row / $set_per_row ); //2
}

?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>

  <?php
    if ($perfect_set) {
      $classes_array[$id] .= " triple";
    }
    else {
      if ($id < ($total_set-1) * $set_per_row) {
        $classes_array[$id] .= " triple";
      }
    }
    if($id % $set_per_row == 2){
      $classes_array[$id] .= " triple-last";
    }
    //Set up the first-set or last-set class
    if($id < $set_per_row){
      $classes_array[$id] .= " first-set";      
    }
    if($id >= ($total_set-1) * $set_per_row && $id < $total_set * $set_per_row){
      $classes_array[$id] .= " last-set";
    }
    
  ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>

