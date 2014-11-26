<?php
/**
 * @file
 * azfinancial_content_and_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function azfinancial_content_and_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Call Us 800';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'call_us_800';
  $fe_block_boxes->body = '<p>Call Us: <a href="tel:18003812348">1.800.381.2348</a></p>
';

  $export['call_us_800'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Contact Us';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'contact_us';
  $fe_block_boxes->body = '<p><strong>Business Phone:</strong></p>

<p><a href="tel: 416-834-9204">416-834-9204</a> (cell)</p>

<p><a href="tel:905-771-8288">905-771-8288</a> (Toronto)</p>

<p><a href="tel:905-771-8288">604-637-2195</a> (Vancouver)</p>

<p><a href="tel:403-228-1798">403-228-1798</a> (Calgary)</p>

<p><strong>Toll Free:</strong></p>

<p><a href="tel:18778349204" style="line-height: 20.7999992370605px;" title="Call AZ Financial">1-877-834-9204</a></p>

<p><strong>Email:</strong><br />
<a href="mailto:info@financial.ca?subject=Thank%20you&amp;body=You%20will%20get%20reply%20with%2024%20hours.">info@azfinancial.ca</a></p>
';

  $export['contact_us'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Phone 800';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'phone_800';
  $fe_block_boxes->body = '<div><img alt="" src="/sites/default/files/cell_icon.png" style="float:left; height:29px; width:16px" />&nbsp;&nbsp;<a href="tel:18778349204" style="font-size: 20px; line-height: 30px;"><span style="color:rgb(0, 0, 0)">1.877.834.9204</span></a></div>
';

  $export['phone_800'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Phone local';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'phone_local';
  $fe_block_boxes->body = '<div><span style="font-size:20px"><span style="color:#000000"><img alt="" src="/sites/default/files/cell_icon.png" style="float:left; height:29px; width:16px" />&nbsp;&nbsp;</span><a href="tel:4168349204" style="line-height: 30px;"><span style="color:#000000">416.834.9204</span></a></span></div>
';

  $export['phone_local'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'QR Code Contact';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'qrcode_contact';
  $fe_block_boxes->body = '<div><img alt="" src="/sites/default/files/qrcode.png" style="width:100%" /></div>
';

  $export['qrcode_contact'] = $fe_block_boxes;

  return $export;
}
