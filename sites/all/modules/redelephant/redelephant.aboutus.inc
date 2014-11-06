<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */


/**
 * About us Form
 */
function aboutus_form($form, &$form_state) {
  $banner = '<img src="'. file_create_url('public://') . variable_get('filename') .'" style="height: 250px; width: 700px;">';

	$form['about_us'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('About us'),
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
	);

  $form['filename'] = array(
    '#type' => 'value',
    '#value' => variable_get('filename'),
  );

  $form['about_us']['file'] = array(
    '#title' => 'Image',
    '#type' => 'file',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30,
  );

  if (variable_get('filename') != "") {
    $form['about_us']['image'] = array(
      '#markup' => $banner,
    );
  }

	$form['about_us']['left'] = array(
    '#type' => 'textarea',
    '#title' => t('Left description'),
    '#default_value' => variable_get('desc_left')
  );

	$form['about_us']['right'] = array(
    '#type' => 'textarea',
    '#title' => t('Right description'),
    '#default_value' => variable_get('desc_right')
  );

  $form['about_us']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

	return $form;
}

/**
 * About us Form Submit
 */
function aboutus_form_submit($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $filename = substr($file->destination, strrpos($file->destination, '/')+1);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      $filename = $form_state['values']['filename'];
      return;
    }
  }
  else {
    $filename = $form_state['values']['filename'];
  }

  $desc_left = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['left']);
  $desc_right = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['right']);

  variable_set('desc_left', $desc_left);
  variable_set('desc_right', $desc_right);
  variable_set('filename', $filename);

  drupal_set_message('Your change has been saved!');
}