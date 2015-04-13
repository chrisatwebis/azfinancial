<?php

/**
 * @file
 * Customize the e-mails sent by Webform after successful submission.
 *
 * This file may be renamed "webform-mail-[nid].tpl.php" to target a
 * specific webform e-mail on your site. Or you can leave it
 * "webform-mail.tpl.php" to affect all webform e-mails on your site.
 *
 * Available variables:
 * - $node: The node object for this webform.
 * - $submission: The webform submission.
 * - $email: The entire e-mail configuration settings.
 * - $user: The current user submitting the form.
 * - $ip_address: The IP address of the user submitting the form.
 *
 * The $email['email'] variable can be used to send different e-mails to different users
 * when using the "default" e-mail template.
 [submission:values]
 */
?>

<?php 
	setlocale(LC_MONETARY, 'en_US.UTF-8');
	$submission_data = $submission->data;
	$submission_def = $node->webform['components'];
	
	$summary = array(
		'arrival_date' 		=> $submission_data[9][0],
		'effective_date' 	=> $submission_data[10][0],
		'expiry_date' 		=> $submission_data[11][0],
		'family_plan'	 		=> !empty($submission_data[14][0]) ? t("Yes") : t("No"),
		'coverage'				=> money_format('%.0n', (float)$submission_data[16][0])." CAD",
		'deductible'			=> money_format('%.0n', (float)$submission_data[17][0])." CAD",
		'beneficiary' 		=> $submission_data[13][0],
		'total_premium'		=> money_format('%.2n', (float)$submission_data[74][0])." CAD",
		'insured_1'				=> array(
			'given_name'		=> $submission_data[22][0],
			'surname'				=> $submission_data[21][0],
			'birthday'			=> $submission_data[23][0],
			'gender'				=> $submission_data[24][0],
			// 'age'						=> sunflower_age_by_birthday($submission_data[23][0]),
			'spmcc'					=> $submission_data[57][0],
			'premium'				=> money_format('%.2n', (float)$submission_data[69][0])." CAD",
		),
		'insured_2'				=> array(
			'given_name'		=> $submission_data[27][0],
			'surname'				=> $submission_data[26][0],
			'birthday'			=> $submission_data[28][0],
			'gender'				=> $submission_data[29][0],			
			// 'age'						=> sunflower_age_by_birthday($submission_data[28][0]),
			'spmcc'					=> $submission_data[58][0],
			'premium'				=> money_format('%.2n', (float)$submission_data[70][0])." CAD",
		),
		'insured_3'				=> array(
			'given_name'		=> $submission_data[32][0],
			'surname'				=> $submission_data[31][0],
			'birthday'			=> $submission_data[33][0],
			'gender'				=> $submission_data[34][0],			
			// 'age'						=> sunflower_age_by_birthday($submission_data[33][0]),
			'spmcc'					=> $submission_data[59][0],
			'premium'				=> money_format('%.2n', (float)$submission_data[71][0])." CAD",
		),
		'insured_4'				=> array(
			'given_name'		=> $submission_data[37][0],
			'surname'				=> $submission_data[36][0],
			'birthday'			=> $submission_data[38][0],
			'gender'				=> $submission_data[39][0],			
			// 'age'						=> sunflower_age_by_birthday($submission_data[38][0]),
			'spmcc'					=> $submission_data[60][0],
			'premium'				=> money_format('%.2n', (float)$submission_data[72][0])." CAD",
		),
		'insured_5'				=> array(
			'given_name'		=> $submission_data[42][0],
			'surname'				=> $submission_data[41][0],
			'birthday'			=> $submission_data[43][0],
			'gender'				=> $submission_data[44][0],			
			// 'age'						=> sunflower_age_by_birthday($submission_data[43][0]),
			'spmcc'					=> $submission_data[61][0],
			'premium'				=> money_format('%.2n', (float)$submission_data[73][0])." CAD",
		),
		'contact_info'		=> array(
			'given_name'		=> $submission_data[50][0],
			'surname'				=> $submission_data[51][0],
			'email'					=> $submission_data[52][0],
			'home_phone'		=> $submission_data[48][0],
			'cell'					=> $submission_data[47][0],
			'fax'						=> $submission_data[49][0],
			'address'				=> $submission_data[45][0],
		),
	);

	$start_date = new DateTime($summary['effective_date']);
	$end_date = new DateTime($summary['expiry_date']);
	$interval = date_diff($end_date, $start_date);
	$summary['trip_duration'] = $interval->format('%a') + 1;
	if (!empty($summary['contact_info']['address'])) {
		$address  = !empty($summary['contact_info']['address']['thoroughfare']) ? $summary['contact_info']['address']['thoroughfare'] : "";
		$address .= !empty($summary['contact_info']['address']['premise']) ? "<br>".$summary['contact_info']['address']['premise'] : "";
		$address .= !empty($summary['contact_info']['address']['dependent_locality']) ? "<br>".$summary['contact_info']['address']['dependent_locality'] : "";
		$address .= !empty($summary['contact_info']['address']['locality']) ? "<br>".$summary['contact_info']['address']['locality'] : "";
		$address .= !empty($summary['contact_info']['address']['administrative_area']) ? ", ".$summary['contact_info']['address']['administrative_area'] : "";
		$address .= !empty($summary['contact_info']['address']['postal_code']) ? " ".$summary['contact_info']['address']['postal_code'] : "";
		$summary['contact_info']['address'] = $address;
	}
	if (!empty($email['eid']) && $email['eid'] == '2') {
		print ($email['html'] ? '<p>' : '') . t('Hi @name,', array("@name" => $summary['contact_info']['given_name'])). ($email['html'] ? '</p>' : '');
		print ($email['html'] ? '<p>' : '') . t('Thank you for contacting us, your submission has been received. Here is the summary of your policy:'). ($email['html'] ? '</p>' : '');
	}
	else {
		print ($email['html'] ? '<p>' : '') . t('Hello Administrator,'). ($email['html'] ? '</p>' : ''); 
		print ($email['html'] ? '<p>' : '') . t('You have a new submission!'). ($email['html'] ? '</p>' : ''); 
		print ($email['html'] ? '<p>' : '') . t('Submitted on [submission:date:long]'). ($email['html'] ? '</p>' : ''); 
		if ($user->uid){
			print ($email['html'] ? '<p>' : '') . t('Submitted by user: [submission:user]') . ($email['html'] ? '</p>' : '');
		}
		else{
			print ($email['html'] ? '<p>' : '') . t('Submitted by anonymous user: [submission:ip-address]') . ($email['html'] ? '</p>' : '');
		}
		print ($email['html'] ? '<p>' : '') . t('Here is the summary of the policy:') . ':' . ($email['html'] ? '</p>' : '');
	}
?>

<div class="policy_review_wrapper">
	<div class="review">
		<div class="section policy_summary">
			<div class="s_header" style="background: #e5e5e5;font-size: 16px;padding: 10px 15px;color: #ca9f03;"><?php print t("Policy Summary");?></div>
			<div class="s_content" style="background: white;padding: 10px 15px;font-size: 14px;line-height: 150%;margin-bottom: 10px;overflow: hidden;">
				<div class="item application_date" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print ("Application Date");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print date("Y-m-d");?></span>
				</div>
				<div class="item arrival_date" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Arrival Date");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['arrival_date'];?></span>
				</div>
				<div class="item effective_date" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Effective Date");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['effective_date'];?></span>
				</div>
				<div class="item expiry_date" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Expiry Date");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['expiry_date'];?></span>
				</div>
				<div class="item trip_duration" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Trip Duration");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print t("@num days", array("@num" => $summary['trip_duration']));?></span>
				</div>
				<div class="item family_plan" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Family Plan");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['family_plan']; ?></span>
				</div>
				<div class="item coverage" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Coverage");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['coverage'];?></span>
				</div>
				<div class="item deductible" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Deductible");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['deductible'];?></span>
				</div>
				<div class="item beneficiary" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Beneficiary");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><?php print $summary['beneficiary'];?></span>
				</div>
				<div class="item total_premium" style="margin: 5px 0;border: 1px solid #e5e5e5;overflow: hidden;width: 100%; padding: 10px;">
					<span class="label" style="width: 45%;float: left;margin-right: 1.69492%;"><?php print t("Total Premium");?></span><span class="value" style="width: 45%;float: right;margin-right: 0;font-weight: bold;"><span class="total_premium_amount"><?php print $summary['total_premium']?></span></span>
				</div>
			</div>
		</div>
		<div class="section insured">
			<div class="s_header" style="background: #e5e5e5;font-size: 16px;padding: 10px 15px;color: #ca9f03;"><?php print t("Traveller Information");?></div>
			<div class="s_content" style="background: white;padding: 10px 15px;font-size: 14px;line-height: 150%;margin-bottom: 10px;overflow: hidden;">
				<div class="item i_header" style="margin: 5px 0;font-weight: bold;overflow: hidden;">
					<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print t("Name (Gender)");?></div>
					<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print t("Birthday");?></div>
					<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print t("SPMCC");?></div>
					<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><?php print t("Premium");?></div>
				</div>
				<?php 
					if (!empty($summary['insured_1']['given_name'])) {
				?>
				<div class="item " id="insured_person_1" style="margin: 5px 0;overflow: hidden;">
						<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_1']['given_name']." ".$summary['insured_1']['surname']." (".$summary['insured_1']['gender'].")";?></div>
						<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_1']['birthday'];?></div>
						<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_1']['spmcc'];?></div>
						<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><span class="premium_amount"><?php print $summary['insured_1']['premium'];?></span></div>
					</div>
				</div>
				<?php
					}
				?>
				<?php 
					if (!empty($summary['insured_2']['given_name'])) {
				?>
				<div class="item " id="insured_person_2" style="margin: 5px 0;overflow: hidden;">
						<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_2']['given_name']." ".$summary['insured_2']['surname']." (".$summary['insured_2']['gender'].")";?></div>
						<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_2']['birthday'];?></div>
						<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_2']['spmcc'];?></div>
						<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><span class="premium_amount"><?php print $summary['insured_2']['premium'];?></span></div>
					</div>
				</div>
				<?php
					}
				?>
				<?php 
					if (!empty($summary['insured_3']['given_name'])) {
				?>
				<div class="item " id="insured_person_3" style="margin: 5px 0;overflow: hidden;">
						<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_3']['given_name']." ".$summary['insured_3']['surname']." (".$summary['insured_3']['gender'].")";?></div>
						<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_3']['birthday'];?></div>
						<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_3']['spmcc'];?></div>
						<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><span class="premium_amount"><?php print $summary['insured_3']['premium'];?></span></div>
					</div>
				</div>
				<?php
					}
				?>
				<?php 
					if (!empty($summary['insured_4']['given_name'])) {
				?>
				<div class="item " id="insured_person_4" style="margin: 5px 0;overflow: hidden;">
						<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_4']['given_name']." ".$summary['insured_4']['surname']." (".$summary['insured_4']['gender'].")";?></div>
						<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_4']['birthday'];?></div>
						<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_4']['spmcc'];?></div>
						<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><span class="premium_amount"><?php print $summary['insured_4']['premium'];?></span></div>
					</div>
				</div>
				<?php
					}
				?>
				<?php 
					if (!empty($summary['insured_5']['given_name'])) {
				?>
				<div class="item " id="insured_person_5" style="margin: 5px 0;overflow: hidden;">
						<div class="name" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_5']['given_name']." ".$summary['insured_5']['surname']." (".$summary['insured_5']['gender'].")";?></div>
						<div class="birthday" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_5']['birthday'];?></div>
						<div class="spmcc" style="width: 23.72881%;float: left;margin-right: 1.69492%;"><?php print $summary['insured_5']['spmcc'];?></div>
						<div class="premium" style="width: 23.72881%;float: left;margin-right: 0;"><span class="dollar_sign">$</span><span class="premium_amount"><?php print $summary['insured_5']['premium'];?></span></div>
					</div>
				</div>
				<?php
					}
				?>
		</div>
		<div class="section contact">
			<div class="s_header" style="background: #e5e5e5;font-size: 16px;padding: 10px 15px;color: #ca9f03;"><?php print t("Contact Information");?></div>
			<div class="s_content" style="background: white;padding: 10px 15px;font-size: 14px;line-height: 150%;margin-bottom: 10px;overflow: hidden;">
				<div class='name'><?php print $summary['contact_info']['given_name'];?></div>
				<div class='email'><span class='label'>Email: </span><span class='data'><?php print $summary['contact_info']['email'];?></span></div>
				<div class='home_phone'><span class='label'>Home Phone: </span><span class='data'><?php print $summary['contact_info']['home_phone'];?></span></div>
				<div class='cell'><span class='label'>Cell: </span><span class='data'><?php print $summary['contact_info']['cell'];?></span></div>
				<div class='fax'><span class='label'>Fax: </span><span class='data'><?php print $summary['contact_info']['fax'];?></span></div>
		</div>
		<div class="section address">
			<div class="s_header" style="background: #e5e5e5;font-size: 16px;padding: 10px 15px;color: #ca9f03;"><?php print t("Canada Address");?></div>
			<div class="s_content" style="background: white;padding: 10px 15px;font-size: 14px;line-height: 150%;margin-bottom: 10px;overflow: hidden;"><?php print $summary['contact_info']['address'];?></div>
		</div>
	</div>
</div>

<?php
	if (!empty($email['eid']) && $email['eid'] != '2') {
?>

<?php print ($email['html'] ? '<p>' : '') . t('The results of this submission may be viewed at:') . ($email['html'] ? '</p>' : '') ?>

<?php print ($email['html'] ? '<p>' : ''); ?>[submission:url]<?php print ($email['html'] ? '</p>' : ''); ?>

<?php
	}
	else {
?>

<?php print ($email['html'] ? '<p>' : '') . t('We will contact you within 24 hours.') . ($email['html'] ? '</p>' : '') ?>

<?php print ($email['html'] ? '<p>' : '') . t('-- Your Insurance Experts') . ($email['html'] ? '</p>' : '') ?>
<?php		
	}
?>