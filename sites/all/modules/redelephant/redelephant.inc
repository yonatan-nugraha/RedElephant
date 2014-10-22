<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */

/**
 * About us Form
 */
function aboutus_form($form, &$form_state) {

  $result = db_select('about_us', 'a')
          ->fields('a')
          ->condition('id', 1, '=')
          ->execute()
          ->fetchAll();

	$form['banner'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Banner'),
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
	);

  $form['banner']['file'] = array(
    '#title' => 'Image',
    '#type' => 'file',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['banner']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

	$form['description'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Description'),
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
	);

	$form['description']['left'] = array(
    '#type' => 'textarea',
    '#title' => t('Left description'),
    '#description' => "Please enter the left description.",
    '#default_value' => $result[0]->desc_left
  );

	$form['description']['right'] = array(
    '#type' => 'textarea',
    '#title' => t('Right description'),
    '#description' => "Please enter the right description.",
    '#default_value' => $result[0]->desc_right
  );

  $form['description']['submit'] = array(
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
      $form_state['values']['file'] = $file;
    }
    else {
      form_set_error('file', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }

  $desc_left = str_replace("\n", "<br>", $form_state['values']['left']);
  $desc_right = str_replace("\n", "<br>", $form_state['values']['right']);

	$result = db_update('about_us')
    ->fields(array(
      'desc_left' => $desc_left,
      'desc_right' => $desc_right,
    ))
    ->condition('id', 1, '=')
    ->execute();
    drupal_set_message('Your change has been saved!');
}


/**
 * Projects Form
 */
function projects_form($form, &$form_state) {

  $form['projects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Projects'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['projects']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['projects']['localoverseas'] = array(
    '#type' => 'select',
    '#title' => 'Local / Overseas',
    '#options' => array(
      0 => t('Local'),
      1 => t('Overseas'),
    ),
  );

  $form['projects']['local'] = array(
    '#type' => 'select',
    '#title' => 'Local',
    '#options' => array(
      0 => t('Jakarta'),
      1 => t('Bandung'),
      2 => t('Bali'),
    ),
  );

  $form['projects']['overseas'] = array(
    '#type' => 'select',
    '#title' => 'Overseas',
    '#options' => array(
      0 => t('Singapore'),
      1 => t('Malaysia'),
    ),
  );

  $form['projects']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
  );

  $form['projects']['project'] = array(
    '#type' => 'textfield',
    '#title' => 'Project',
  );

  $form['projects']['location'] = array(
    '#type' => 'textfield',
    '#title' => 'Location',
  );

  $form['projects']['type'] = array(
    '#type' => 'textfield',
    '#title' => 'Type',
  );

  $form['projects']['size'] = array(
    '#type' => 'textfield',
    '#title' => 'Size',
  );

  $form['projects']['facilities'] = array(
    '#type' => 'textarea',
    '#title' => 'Facilities',
  );

  $form['projects']['amenities'] = array(
    '#type' => 'textarea',
    '#title' => 'Amenities',
  );

  $form['projects']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  return $form;
}

function projects_form_submit($form, &$form_state) {
  $result = db_insert('project')
  ->fields(array(
    'desc_left' => $form_state['values']['left'],
    'desc_right' => $form_state['values']['right'],
  ))
  ->condition('id', 1, '=')
  ->execute();
  drupal_set_message('Your change has been saved!');
}


/**
 * Services Form
 */
function services_form($form, &$form_state) {

  $form['services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['services']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['services']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
  );

  $form['services']['project'] = array(
    '#type' => 'textfield',
    '#title' => 'Project',
  );

  $form['services']['location'] = array(
    '#type' => 'textfield',
    '#title' => 'Location',
  );

  $form['services']['area'] = array(
    '#type' => 'textfield',
    '#title' => 'Area',
  );

  $form['services']['type'] = array(
    '#type' => 'textfield',
    '#title' => 'Type',
  );

  $form['services']['size'] = array(
    '#type' => 'textfield',
    '#title' => 'Size',
  );

  $form['services']['facilities'] = array(
    '#type' => 'textarea',
    '#title' => 'Facilities',
  );

  $form['services']['floor'] = array(
    '#type' => 'textarea',
    '#title' => 'Floor',
  );

  $form['services']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  return $form;
}

function services_form_submit($form, &$form_state) {
  $facilities = str_replace("\n", "<br>", $form_state['values']['facilities']);

  $result = db_insert('services')
  ->fields(array(
    'title' => $form_state['values']['title'],
    'project' => $form_state['values']['project'],
    'location' => $form_state['values']['location'],
    'area' => $form_state['values']['area'],
    'type' => $form_state['values']['type'],
    'size' => $form_state['values']['size'],
    'facilities' => $facilities,
    'floor' => $form_state['values']['floor'],
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
}

/**
 * News Form
 */
function news_form($form, &$form_state) {
  $form['services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['services']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['services']['date'] = array(
    '#type' => 'textfield',
    '#title' => 'Date',
  );

  $form['services']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
  );

  $form['services']['desc'] = array(
    '#type' => 'textarea',
    '#title' => 'Description',
  );

  $form['services']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  return $form;
}

function news_form_submit($form, &$form_state) {
  $description = str_replace("\n", "<br>", $form_state['values']['desc']);

  $result = db_insert('news')
  ->fields(array(
    'title' => $form_state['values']['title'],
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
}

function aboutus_view() {
	$result = db_select('about_us', 'a')
          ->fields('a')
          ->condition('id', 1, '=')
          ->execute()
          ->fetchAll();

	return theme('about-us', array(
    'desc_left' => $result[0]->desc_left,
    'desc_right' => $result[0]->desc_right,
  ));
}

function projects_view() {
  $result = db_select('projects', 'p')
        ->fields('p')
        ->condition('id', 1, '=')
        ->execute()
        ->fetchAll();

	return theme('projects', array(
    'title' => $result[0]->title,
    'project' => $result[0]->project,
    'location' => $result[0]->location,
    'type' => $result[0]->type,
    'size' => $result[0]->size,
    'facilities' => $result[0]->facilities,
    'amenities' => $result[0]->amenities,
  ));
}

function services_view() {
  $result = db_select('services', 's')
      ->fields('s')
      ->execute()
      ->fetchAll();

  return theme('services', array(
    'services' => $result,
  ));
}

function news_view() {
  return theme('news');
}

function contact_view() {
  return theme('contact');
}