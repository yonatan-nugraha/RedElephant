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

  $banner = '<img src="'. file_create_url('public://') . $result[0]->filename .'" style="height: 250px; width: 700px;">';

	$form['about_us'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('About us'),
	  '#collapsible' => TRUE,
	  '#collapsed' => FALSE,
	);

  $form['filename'] = array(
    '#type' => 'value',
    '#value' => $result[0]->filename,
  );

  $form['about_us']['file'] = array(
    '#title' => 'Image',
    '#type' => 'file',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30,
  );

  if ($result[0]->filename != "") {
    $form['about_us']['image'] = array(
      '#markup' => $banner,
    );
  }

	$form['about_us']['left'] = array(
    '#type' => 'textarea',
    '#title' => t('Left description'),
    '#default_value' => $result[0]->desc_left
  );

	$form['about_us']['right'] = array(
    '#type' => 'textarea',
    '#title' => t('Right description'),
    '#default_value' => $result[0]->desc_right
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
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      $filename = $form_state['values']['filename'];
      return;
    }
  }
  else {
    $filename = $form_state['values']['filename'];
    return;
  }

  $desc_left = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['left']);
  $desc_right = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['right']);

	$result = db_update('about_us')
    ->fields(array(
      'desc_left' => $desc_left,
      'desc_right' => $desc_right,
      'filename' => $filename,
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
function services_form() {
  $output = '<a href="services/add/"">Add Services here</a>';

  $header = array( 
    array('data' => t('No')),
    array('data' => t('Banner')), 
    array('data' => t('Title')),
    array('data' => t('Project')), 
    array('data' => t('Location')),
    array('data' => t('Area')),
    array('data' => t('Type')),
    array('data' => t('Size')),
    array('data' => t('Facilities')),
    array('data' => t('Floor')),
    array('data' => t('Action')),
  ); 

  $result = db_select('services', 's')
  ->fields('s')
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;
    $banner =  '<img src="'. file_create_url('public://') . $record->filename .'" style="height: 100px; width: 150px;">';
    $row[] = array(
      array('data' => $no),
      array('data' => $banner),
      array('data' => $record->title),
      array('data' => $record->project),
      array('data' => $record->location),
      array('data' => $record->area),
      array('data' => $record->type),
      array('data' => $record->size),
      array('data' => $record->facilities),
      array('data' => $record->floor),
      array('data' => l('Edit', 'admin/red-elephant/services/edit/'. $record->id).' | '.l('Delete', 'admin/red-elephant/services/delete/'. $record->id))
    );
  }

  $output .= theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!'))) . theme('pager');
  return $output;
}

function add_services_form($form, &$form_state) {
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

  $form['services']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/services',
  );

  return $form;
}

function add_services_form_submit($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }

  $filename = substr($file->destination, strrpos($file->destination, '/')+1);
  $facilities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['facilities']);

  $result = db_insert('services')
  ->fields(array(
    'title' => strtoupper($form_state['values']['title']),
    'project' => $form_state['values']['project'],
    'location' => $form_state['values']['location'],
    'area' => $form_state['values']['area'],
    'type' => $form_state['values']['type'],
    'size' => $form_state['values']['size'],
    'facilities' => $facilities,
    'floor' => $form_state['values']['floor'],
    'filename' => $filename,
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
}

function edit_services_form($form, &$form_state, $id) {
  $result = db_select('services', 's')
          ->fields('s')
          ->condition('id', $id, '=')
          ->execute()
          ->fetchAll();

  $banner = '<img src="'. file_create_url('public://') . $result[0]->filename .'" style="height: 250px; width: 700px;">';

  $form['services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['services']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  if ($result[0]->filename != "") {
    $form['services']['image'] = array(
      '#markup' => $banner,
    );
  }

  $form['services']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
    '#default_value' => $result[0]->title,
  );

  $form['services']['project'] = array(
    '#type' => 'textfield',
    '#title' => 'Project',
    '#default_value' => $result[0]->project,
  );

  $form['services']['location'] = array(
    '#type' => 'textfield',
    '#title' => 'Location',
    '#default_value' => $result[0]->location,
  );

  $form['services']['area'] = array(
    '#type' => 'textfield',
    '#title' => 'Area',
    '#default_value' => $result[0]->area,
  );

  $form['services']['type'] = array(
    '#type' => 'textfield',
    '#title' => 'Type',
    '#default_value' => $result[0]->type,
  );

  $form['services']['size'] = array(
    '#type' => 'textfield',
    '#title' => 'Size',
    '#default_value' => $result[0]->size,
  );

  $form['services']['facilities'] = array(
    '#type' => 'textarea',
    '#title' => 'Facilities',
    '#default_value' => $result[0]->facilities,
  );

  $form['services']['floor'] = array(
    '#type' => 'textarea',
    '#title' => 'Floor',
    '#default_value' => $result[0]->floor,
  );

  $form['services']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  $form['services']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/services',
  );

  return $form;
}

function edit_services_form_submit($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $filename = substr($file->destination, strrpos($file->destination, '/')+1);
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      $filename = $form_state['values']['filename'];
      return;
    }
  }
  else {
    $filename = $form_state['values']['filename'];
    return;
  }

  $facilities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['facilities']);

  $result = db_update('services')
  ->fields(array(
    'title' => strtoupper($form_state['values']['title']),
    'project' => $form_state['values']['project'],
    'location' => $form_state['values']['location'],
    'area' => $form_state['values']['area'],
    'type' => $form_state['values']['type'],
    'size' => $form_state['values']['size'],
    'facilities' => $facilities,
    'floor' => $form_state['values']['floor'],
    'filename' => $filename,
  ))
  ->condition('id', $form_state['values']['id'] , '=')
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/services';
}

function delete_services_form($form, &$form_state, $id) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Delete Services'),
    'admin/red-elephant/services',
    t('Are you sure you want to delete this ?'),
    t('Delete'),
    t('Cancel')
  );
}

function delete_services_form_submit($form, &$form_state) {
  $result = db_delete('services')
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Succesfully deleted');
  $form_state['redirect'] = 'admin/red-elephant/services';
}









/**
 * News Form
 */

function news_form() {
  $output = '<a href="news/add/"">Add News here</a>';

  $header = array( 
    array('data' => t('No')),
    array('data' => t('Banner')), 
    array('data' => t('Date')), 
    array('data' => t('Title')),
    array('data' => t('Description')),
    array('data' => t('Action')),
  ); 

  $result = db_select('news', 'n')
  ->fields('n')
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;
    $banner =  '<img src="'. file_create_url('public://') . $record->filename .'" style="height: 100px; width: 150px;">';
    $row[] = array(
      array('data' => $no),
      array('data' => $banner),
      array('data' => $record->date),
      array('data' => $record->title),
      array('data' => $record->description),
      array('data' => l('Edit', 'admin/red-elephant/news/edit/'. $record->id).' | '.l('Delete', 'admin/red-elephant/news/delete/'. $record->id))
    );
  }

  $output .= theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!'))) . theme('pager');
  return $output;
}

function add_news_form($form, &$form_state) {
  $form['news'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add News'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['news']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['news']['date'] = array(
    '#type' => 'textfield',
    '#title' => 'Date',
  );

  $form['news']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
  );

  $form['news']['desc'] = array(
    '#type' => 'textarea',
    '#title' => 'Description',
  );

  $form['news']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add',
  );

  $form['news']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/news',
  );

  return $form;
}


function add_news_form_submit($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
    }
  }
  else {
    form_set_error('file', t('No file was uploaded.'));
  }

  $filename = substr($file->destination, strrpos($file->destination, '/')+1);

  $description = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['desc']);

  $result = db_insert('news')
  ->fields(array(
    'date' => $form_state['values']['date'],
    'title' => $form_state['values']['title'],
    'description' => $description,
    'filename' => $filename
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');

  $form_state['redirect'] = 'admin/red-elephant/news';
}

function edit_news_form($form, &$form_state, $id) {
  $result = db_select('news', 'n')
          ->fields('n')
          ->condition('id', $id, '=')
          ->execute()
          ->fetchAll();

  $banner = '<img src="'. file_create_url('public://') . $result[0]->filename .'" style="height: 250px; width: 700px;">';

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['news'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit News'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['news']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30,
  );

  if ($result[0]->filename != "") {
    $form['news']['image'] = array(
      '#markup' => $banner,
    );
  }

  $form['news']['date'] = array(
    '#type' => 'textfield',
    '#title' => 'Date',
    '#default_value' => $result[0]->date,
  );

  $form['news']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
    '#default_value' => $result[0]->title,
  );

  $form['news']['desc'] = array(
    '#type' => 'textarea',
    '#title' => 'Description',
    '#default_value' => $result[0]->description,
  );

  $form['news']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  
  $form['news']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/news',
  );

  return $form;
}

function edit_news_form_submit($form, &$form_state) {
  $file = file_save_upload('file', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file) {
    if ($file = file_move($file, 'public://')) {
      $filename = substr($file->destination, strrpos($file->destination, '/')+1);
      $form_state['storage']['file'] = $file;
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      $filename = $form_state['values']['filename'];
      return;
    }
  }
  else {
    $filename = $form_state['values']['filename'];
    return;
  }

  $description = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['desc']);

  $result = db_update('news')
    ->fields(array(
      'date' => $form_state['values']['date'],
      'title' => $form_state['values']['title'],
      'description' => $form_state['values']['desc'],
      'filename' => $filename
    ))
    ->condition('id', $form_state['values']['id'] , '=')
    ->execute();

    drupal_set_message('Your change has been saved!');
    $form_state['redirect'] = 'admin/red-elephant/news';
}

function delete_news_form($form, &$form_state, $id) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Delete News'),
    'admin/red-elephant/news',
    t('Are you sure you want to delete this ?'),
    t('Delete'),
    t('Cancel')
  );
}

function delete_news_form_submit($form, &$form_state) {
  $result = db_delete('news')
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Succesfully deleted');
  $form_state['redirect'] = 'admin/red-elephant/news';
}












/*
  Implement Hook View form
 */
function aboutus_view() {
	$result = db_select('about_us', 'a')
          ->fields('a')
          ->condition('id', 1, '=')
          ->execute()
          ->fetchAll();

	return theme('about-us', array(
    'filename' => $result[0]->filename,
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
  $result = db_select('news', 'n')
    ->fields('n')
    ->execute()
    ->fetchAll();

  return theme('news', array(
    'news' => $result,
  ));
}

function contact_view() {
  return theme('contact');
}