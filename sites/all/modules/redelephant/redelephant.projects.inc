<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */

/**
 * Projects List Form
 */

function projects_list_form() {
  $output = '<a href="projects_list/add/local">Add Projects List here</a><br/>';

  $header = array(
    array('data' => t('No')),
    array('data' => t('Local or Overseas')),
    array('data' => t('City')),
    array('data' => t('Action')),
  );

  $result = db_select('projects_list', 'pl')
  ->fields('pl')
  ->orderBy('localoverseas', 'ASC')
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;

    $row[] = array(
      array('data' => $no),
      array('data' => $record->localoverseas),
      array('data' => $record->city),
      array('data' => l('Edit', 'admin/red-elephant/projects_list/edit/' . $record->id).' | '.l('Delete', 'admin/red-elephant/projects_list/delete/' . $record->id))
    );
  }

  $output .= theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!')));

  return $output;
}

function add_projects_list_form() {
    $form['projects_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Projects List'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['projects_list']['localoverseas'] = array(
    '#type' => 'select',
    '#title' => 'Local or Overseas',
    '#options' => array(
      'local' => t('Local'),
      'overseas' => t('Overseas'),
    ),
  );

  $form['projects_list']['city'] = array(
    '#type' => 'textfield',
    '#title' => 'City',
  );

  $form['projects_list']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  $form['projects_list']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/projects_list',
  );

  return $form;
}

function add_projects_list_form_submit($form, &$form_state) {
  $result = db_insert('projects_list')
  ->fields(array(
    'localoverseas' => $form_state['values']['localoverseas'],
    'city' => $form_state['values']['city'],
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/projects_list';
}


function edit_projects_list_form($form, &$form_state, $id) {
  $result = db_select('projects_list', 'pl')
  ->fields('pl')
  ->condition('id', $id, '=')
  ->execute()
  ->fetchAll();

  $form['projects_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit Projects List'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['projects_list']['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['projects_list']['localoverseas'] = array(
    '#type' => 'select',
    '#title' => 'Local or Overseas',
    '#options' => array(
      'local' => t('Local'),
      'overseas' => t('Overseas'),
    ),
  );

  $form['projects_list']['city'] = array(
    '#type' => 'textfield',
    '#title' => 'City',
    '#default_value' => $result[0]->city,
  );

  $form['projects_list']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  $form['projects_list']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/projects_list',
  );

  return $form;
}

function edit_projects_list_form_submit($form, &$form_state) {
  $result = db_update('projects_list')
  ->fields(array(
    'localoverseas' => $form_state['values']['localoverseas'],
    'city' => $form_state['values']['city'],
  ))
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/projects_list';
}

function delete_projects_list_form($form, &$form_state, $id) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Delete Projects List'),
    'admin/red-elephant/projects_list',
    t('Are you sure you want to delete this ?'),
    t('Delete'),
    t('Cancel')
  );
}

function delete_projects_list_form_submit($form, &$form_state) {
  $result = db_delete('projects_list')
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Succesfully deleted');
  $form_state['redirect'] = 'admin/red-elephant/projects_list';
}




/**
 * Projects Form
 */

function projects_form() {
  $output = '<a href="projects/add/local">Add Local Projects here</a><br/>';
  $output .= '<a href="projects/add/overseas">Add Overseas Projects List here</a><br/>';

  $header = array(
    array('data' => t('No')),
    array('data' => t('Banner')),
    array('data' => t('Title')),
    array('data' => t('Project')),
    array('data' => t('Location')),
    array('data' => t('Type')),
    array('data' => t('Size')),
    array('data' => t('Facilities')),
    array('data' => t('Amenities')),
    array('data' => t('City')),
    array('data' => t('Action')),
  );

  $result = db_select('projects', 'p')
  ->fields('p')
  ->orderBy('city', 'ASC')
  ->extend('PagerDefault')
  ->limit(10)
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;

    $filename = explode("/", $record->filename);

    $banner =  '<img src="'. file_create_url('public://') . $filename[0] .'" style="height: 100px; width: 150px;">';
    $row[] = array(
      array('data' => $no),
      array('data' => $banner),
      array('data' => $record->title),
      array('data' => $record->project),
      array('data' => $record->location),
      array('data' => $record->type),
      array('data' => $record->size),
      array('data' => $record->facilities),
      array('data' => $record->amenities),
      array('data' => $record->city),
      array('data' => l('Edit', 'admin/red-elephant/projects/edit/'. $record->localoverseas . '/' . $record->id).' | '.l('Delete', 'admin/red-elephant/projects/delete/' . $record->id))
    );
  }

  $output .= theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!')));
  $output .= theme('pager', array('tags' => array()));

  return $output;
}

function add_projects_form($form, &$form_state, $locover) {
  $result = db_select('projects_list', 'pl')
          ->fields('pl')
          ->condition('localoverseas', $locover, '=')
          ->execute()
          ->fetchAll();

  $city_array = array();
  foreach($result as $res) {
    $city_array[$res->city] = $res->city;
  }

  $form['projects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Projects'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['locover'] = array(
    '#type' => 'value',
    '#value' => $locover,
  );

  $form['projects']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommended size : w554px h372px',
  );

  $form['projects']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
    '#description' => 'Recommended size : w554px h372px',
  );

  $form['projects']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
    '#description' => 'Recommended size : w554px h372px',
  );

  $form['projects']['file4'] = array(
    '#type' => 'file',
    '#title' => 'Image4',
    '#description' => 'Recommended size : w554px h372px',
  );

  $form['projects']['file5'] = array(
    '#type' => 'file',
    '#title' => 'Image5',
    '#description' => 'Recommended size : w554px h372px',
  );

  $form['projects']['file6'] = array(
    '#type' => 'file',
    '#title' => 'Image6',
    '#description' => 'Recommended size : w554px h372px',
  );

  if ($locover == "local") {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Local',
      '#options' => $city_array,
    );
  }

  else {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Overseas',
      '#options' => $city_array,
    );
  }

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

  $form['projects']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/projects',
  );

  return $form;
}

function add_projects_form_submit($form, &$form_state) {
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
      return;
    }
  }

  $file2 = file_save_upload('file2', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file2) {
    if ($file2 = file_move($file2, 'public://')) {
      $filename .= "/" . substr($file2->destination, strrpos($file2->destination, '/')+1);
      $file2->status = FILE_STATUS_PERMANENT;
      file_save($file2);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      return;
    }
  }

  $file3 = file_save_upload('file3', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file3) {
    if ($file3 = file_move($file3, 'public://')) {
      $filename .= "/" . substr($file3->destination, strrpos($file3->destination, '/')+1);
      $file3->status = FILE_STATUS_PERMANENT;
      file_save($file3);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      return;
    }
  }

  $file4 = file_save_upload('file4', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file4) {
    if ($file4 = file_move($file4, 'public://')) {
      $filename .= "/" . substr($file4->destination, strrpos($file4->destination, '/')+1);
      $file4->status = FILE_STATUS_PERMANENT;
      file_save($file4);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      return;
    }
  }

  $file5 = file_save_upload('file5', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file5) {
    if ($file5 = file_move($file5, 'public://')) {
      $filename .= "/" . substr($file5->destination, strrpos($file5->destination, '/')+1);
      $file5->status = FILE_STATUS_PERMANENT;
      file_save($file5);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      return;
    }
  }

  $file6 = file_save_upload('file6', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file6) {
    if ($file6 = file_move($file6, 'public://')) {
      $filename .= "/" . substr($file6->destination, strrpos($file6->destination, '/')+1);
      $file6->status = FILE_STATUS_PERMANENT;
      file_save($file6);
    }
    else {
      form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
      return;
    }
  }

  $facilities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['facilities']);
  $amenities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['amenities']);

  $result = db_insert('projects')
  ->fields(array(
    'title' => $form_state['values']['title'],
    'project' => $form_state['values']['project'],
    'location' => $form_state['values']['location'],
    'type' => $form_state['values']['type'],
    'size' => $form_state['values']['size'],
    'facilities' => $facilities,
    'amenities' => $amenities,
    'localoverseas' => $form_state['values']['locover'],
    'city' => $form_state['values']['city'],
    'filename' => $filename,
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/projects';
}


function edit_projects_form($form, &$form_state, $locover, $id) {
  $projects_list = db_select('projects_list', 'pl')
          ->fields('pl')
          ->condition('localoverseas', $locover, '=')
          ->execute()
          ->fetchAll();

  $city_array = array();
  foreach($projects_list as $pl) {
    $city_array[$pl->city] = $pl->city;
  }

  $result = db_select('projects', 'p')
          ->fields('p')
          ->condition('id', $id, '=')
          ->execute()
          ->fetchAll();

  $filename = explode("/", $result[0]->filename);

  for ($i=0; $i<count($filename); $i++) {
    $banner[$i] = '<img src="'. file_create_url('public://') . $filename[$i] .'" style="height: 250px; width: 700px;">';
  }

  $form['projects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit Projects'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['locover'] = array(
    '#type' => 'value',
    '#value' => $locover,
  );

  $form['filename'] = array(
    '#type' => 'value',
    '#value' => $result[0]->filename,
  );

  $form['projects']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[0])) {
    $form['projects']['image'] = array(
      '#markup' => $banner[0],
    );
  }

  $form['projects']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[1])) {
    $form['projects']['image2'] = array(
      '#markup' => $banner[1],
    );
  }

  $form['projects']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[2])) {
    $form['projects']['image3'] = array(
      '#markup' => $banner[2],
    );
  }

  $form['projects']['file4'] = array(
    '#type' => 'file',
    '#title' => 'Image4',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[3])) {
    $form['projects']['image4'] = array(
      '#markup' => $banner[3],
    );
  }

  $form['projects']['file5'] = array(
    '#type' => 'file',
    '#title' => 'Image5',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[4])) {
    $form['projects']['image5'] = array(
      '#markup' => $banner[4],
    );
  }

  $form['projects']['file6'] = array(
    '#type' => 'file',
    '#title' => 'Image6',
    '#description' => 'Recommended size : w554px h372px',
  );

  if (isset($banner[5])) {
    $form['projects']['image6'] = array(
      '#markup' => $banner[5],
    );
  }

  if ($locover == "local") {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Local',
      '#options' => $city_array,
    );
  }

  else {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Overseas',
      '#options' => $city_array,
    );
  }

  $form['projects']['title'] = array(
    '#type' => 'textfield',
    '#title' => 'Title',
    '#default_value' => $result[0]->title,
  );

  $form['projects']['project'] = array(
    '#type' => 'textfield',
    '#title' => 'Project',
    '#default_value' => $result[0]->project,
  );

  $form['projects']['location'] = array(
    '#type' => 'textfield',
    '#title' => 'Location',
    '#default_value' => $result[0]->location,
  );

  $form['projects']['type'] = array(
    '#type' => 'textfield',
    '#title' => 'Type',
    '#default_value' => $result[0]->type,
  );

  $form['projects']['size'] = array(
    '#type' => 'textfield',
    '#title' => 'Size',
    '#default_value' => $result[0]->size,
  );

  $form['projects']['facilities'] = array(
    '#type' => 'textarea',
    '#title' => 'Facilities',
    '#default_value' => $result[0]->facilities,
  );

  $form['projects']['amenities'] = array(
    '#type' => 'textarea',
    '#title' => 'Amenities',
    '#default_value' => $result[0]->amenities,
  );

  $form['projects']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  $form['projects']['cancel'] = array(
    '#type' => 'link',
    '#title' => 'Cancel',
    '#href' => 'admin/red-elephant/projects',
  );

  return $form;
}

function edit_projects_form_submit($form, &$form_state) {
  $fn = explode("/", $form_state['values']['filename']);
  for ($i=0; $i<6; $i++) {
    if (!isset($fn[$i])) {
      $fn[$i] = "";
    }
  }

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
      $filename = $fn[0];
      return;
    }
  }
  else {
    $filename = $fn[0];
  }

  $file2 = file_save_upload('file2', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file2) {
    if ($file2 = file_move($file2, 'public://')) {
      $filename .= "/" . substr($file2->destination, strrpos($file2->destination, '/')+1);
      $file2->status = FILE_STATUS_PERMANENT;
      file_save($file2);
    }
    else {
      form_set_error('file2', t("Failed to write the uploaded file to the site's file folder."));
      $filename .= "/" . $fn[1];
      return;
    }
  }
  else {
    $filename .= "/" . $fn[1];
  }

  $file3 = file_save_upload('file3', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file3) {
    if ($file3 = file_move($file3, 'public://')) {
      $filename .= "/" . substr($file3->destination, strrpos($file3->destination, '/')+1);
      $file3->status = FILE_STATUS_PERMANENT;
      file_save($file3);
    }
    else {
      form_set_error('file3', t("Failed to write the uploaded file to the site's file folder."));
      $filename .= "/" . $fn[2];
      return;
    }
  }
  else {
    $filename .= "/" . $fn[2];
  }

  $file4 = file_save_upload('file4', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file4) {
    if ($file4 = file_move($file4, 'public://')) {
      $filename .= "/" . substr($file4->destination, strrpos($file4->destination, '/')+1);
      $file4->status = FILE_STATUS_PERMANENT;
      file_save($file4);
    }
    else {
      form_set_error('file4', t("Failed to write the uploaded file to the site's file folder."));
      $filename .= "/" . $fn[3];
      return;
    }
  }
  else {
    $filename .= "/" . $fn[3];
  }

  $file5 = file_save_upload('file5', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file5) {
    if ($file5 = file_move($file5, 'public://')) {
      $filename .= "/" . substr($file5->destination, strrpos($file5->destination, '/')+1);
      $file5->status = FILE_STATUS_PERMANENT;
      file_save($file5);
    }
    else {
      form_set_error('file5', t("Failed to write the uploaded file to the site's file folder."));
      $filename .= "/" . $fn[4];
      return;
    }
  }
  else {
    $filename .= "/" . $fn[4];
  }

  $file6 = file_save_upload('file6', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file6) {
    if ($file6 = file_move($file6, 'public://')) {
      $filename .= "/" . substr($file6->destination, strrpos($file6->destination, '/')+1);
      $file6->status = FILE_STATUS_PERMANENT;
      file_save($file6);
    }
    else {
      form_set_error('file6', t("Failed to write the uploaded file to the site's file folder."));
      $filename .= "/" . $fn[5];
      return;
    }
  }
  else {
    $filename .= "/" . $fn[5];
  }

  $facilities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['facilities']);
  $amenities = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['amenities']);

  $result = db_update('projects')
  ->fields(array(
    'title' => $form_state['values']['title'],
    'project' => $form_state['values']['project'],
    'location' => $form_state['values']['location'],
    'type' => $form_state['values']['type'],
    'size' => $form_state['values']['size'],
    'facilities' => $facilities,
    'amenities' => $amenities,
    'localoverseas' => $form_state['values']['locover'],
    'city' => $form_state['values']['city'],
    'filename' => $filename,
  ))
  ->condition("id", $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/projects';
}

function delete_projects_form($form, &$form_state, $id) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Delete Projects'),
    'admin/red-elephant/projects',
    t('Are you sure you want to delete this ?'),
    t('Delete'),
    t('Cancel')
  );
}

function delete_projects_form_submit($form, &$form_state) {
  $result = db_delete('projects')
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Succesfully deleted');
  $form_state['redirect'] = 'admin/red-elephant/projects';
}

function show_projects() {
    if (isset($_GET['projectid'])) {
    $result = db_select('projects', 'p')
    ->fields('p')
    ->condition('id', $_GET['projectid'], '=')
    ->execute()
    ->fetchAll();

    $filename = explode('/', $result[0]->filename);

    print '
      <div class="modal-header">
        <a type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span></a>
      </div>
      <div class="modal-content">
        <div class="row">
          <div class="col-lg-5 col-md-5 col-sm-5 col-xs-5 project-description">
            <label>Project</label>
            <p>'. $result[0]->project .'</p>
            <label>Location</label>
            <p>'. $result[0]->location .'</p>
            <label>Type</label>
            <p>'. $result[0]->type .'</p>
            <label>Size</label>
            <p>'. $result[0]->size .'</p>
            <label>Facilities</label>
            <p>'. $result[0]->facilities .'</p>
            <label>Amenities</label>
            <p>'. $result[0]->amenities .'</p>
          </div>
          <div class="col-lg-7 col-md-7 col-sm-7 col-xs-7 project-gallery">
            <h2>'. $result[0]->title .'</h2>
            <img class="img-responsive" id="pic" src="'. file_create_url('public://') . $filename[0] .'">
            <div class="row display-thumbs">';
                for ($i=0; $i<count($filename); $i++) {
                  if ($filename[$i] != "") {
                  print '
                  <div class="col-lg-2 col-md-2 col-sm-4 col-xs-2 img-thumb" onclick="set_image('. "'" . file_create_url('public://') . $filename[$i] . "'" .')">
                    <img src="'. file_create_url('public://') . $filename[$i] .'">
                  </div>';
                  }
                }
                print '
            </div>
          </div>
          <div class="clearfix"></div>
        </div>
      </div>';
    die();
  }



  if (isset($_GET['localoverseas'])) {

      $firstcity = db_select('projects', 'p')
        ->fields('p')
        ->condition('city', $_GET['city'], '=')
        ->execute()
        ->fetchAll();

    if ($_GET['page'] > 0) {
      print '
          <a class="pager prev_page" onclick="click_prevnext(\'prev\', \''.$_GET['localoverseas'].'\')"></a>
        ';
    }
    else {
         print '
          <a class="pager prev_page btn btn-link disabled"></a>
        ';
    }
      print '
      <div class="col-lg-12">
        <div id="city" style="display: none"></div>
        <h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">'.strtoupper($_GET['localoverseas']).'</h4>
        <ul class="nav nav-tabs">';

      $projects_list = db_select('projects_list', 'pl')
        ->fields('pl')
        ->condition('localoverseas', $_GET['localoverseas'], '=')
        ->execute()
        ->fetchAll();

      foreach ($projects_list as $i => $pl) {
        $result = db_select('projects', 'p')
          ->fields('p')
          ->condition('city', $pl->city, '=')
          ->execute()
          ->fetchAll();

        if ($pl->city == $firstcity[0]->city) {
          print '
          <li class="active"><a href="#'. $pl->city .'" data-toggle="tab" onclick="set_city(\''. $_GET['localoverseas'] .'\', \'' . $pl->city . '\')">'. $pl->city .'</a></li>';
        } else {
          print '
          <li><a href="#'. $pl->city .'" data-toggle="tab" onclick="set_city(\''. $_GET['localoverseas'] .'\', \'' . $pl->city . '\')">'. $pl->city .'</a></li>';
        }
      }
        print '
        </ul>

        <div id="myTabContent" class="tab-content">';
      foreach ($projects_list as $i => $pl) {

        if ($pl->city == $firstcity[0]->city) {
          print '
          <div class="tab-pane fade active in" id="'. $pl->city .'">';
        } else {
          print '
          <div class="tab-pane fade" id="'. $pl->city .'">';
        }

        $project = db_select('projects', 'p')
        ->fields('p')
        ->condition('city', $pl->city, '=')
        ->range(8*$_GET['page'], 8)
        ->execute()
        ->fetchAll();

          foreach ($project as $record) {
            $filename = explode('/', $record->filename);
            print '
            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-3 project-item" onclick="get_projectid(' . $record->id . ')">
              <a href="#myModal" class="thumbnail" data-toggle="modal">
                <img src="'. file_create_url('public://') . $filename[0] .'">
                <span class="caption">' . $record->title .'</span>
              </a>
            </div>';
          }
          print '</div>';
        }

          print '
        </div>
      </div>';

    if (count($firstcity) > ($_GET['page']+1)*8) {
      print '
        <a class="pager next_page" onclick="click_prevnext(\'next\', \''.$_GET['localoverseas'].'\')"></a>
      ';
    }
    else {
      print '
        <a class="pager next_page btn btn-link disabled"></a>
      ';
    }
    die();
  }
}
