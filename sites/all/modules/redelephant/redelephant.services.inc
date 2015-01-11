<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */


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
    array('data' => t('Bedroom')),
    array('data' => t('Price')),
    array('data' => t('Action')),
  ); 

  $result = db_select('services', 's')
  ->fields('s')
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;

    $filename = explode('/', $record->filename);
    $banner =  '<img src="'. file_create_url('public://') . $filename[0] .'" style="height: 100px; width: 150px;">';

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
      array('data' => $record->bedroom),
      array('data' => $record->price),
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
    '#title' => t('Add Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['services']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
  );

  $form['services']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
  );

  $form['services']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
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

  $form['services']['bedroom'] = array(
    '#type' => 'textfield',
    '#title' => 'Bedroom',
  );

  $form['services']['price'] = array(
    '#type' => 'textfield',
    '#title' => 'Price',
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
      $filename = substr($file->destination, strrpos($file->destination, '/')+1);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
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
  }

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
    'bedroom' => $form_state['values']['bedroom'],
    'price' => $form_state['values']['price'],
    'filename' => $filename,
  ))
  ->execute();

  drupal_set_message('Your change has been saved!');
  $form_state['redirect'] = 'admin/red-elephant/services';
}

function edit_services_form($form, &$form_state, $id) {
  $result = db_select('services', 's')
          ->fields('s')
          ->condition('id', $id, '=')
          ->execute()
          ->fetchAll();

  $filename = explode('/', $result[0]->filename);

  for ($i=0; $i<count($filename); $i++) {
    $banner[$i] = '<img src="'. file_create_url('public://') . $filename[$i] .'" style="height: 250px; width: 700px;">';
  }

  $form['services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['filename'] = array(
    '#type' => 'value',
    '#value' => $result[0]->filename,
  );

  $form['services']['file'] = array(
    '#type' => 'file',
    '#title' => 'Image',
  );

  if (isset($filename[0])) {
    $form['services']['image'] = array(
      '#markup' => $banner[0],
    );
  }

  $form['services']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
  );

  if (isset($filename[1])) {
    $form['services']['image2'] = array(
      '#markup' => $banner[1],
    );
  }

  $form['services']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
  );

  if (isset($filename[2])) {
    $form['services']['image3'] = array(
      '#markup' => $banner[2],
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

  $form['services']['bedroom'] = array(
    '#type' => 'textfield',
    '#title' => 'Bedroom',
    '#default_value' => $result[0]->bedroom,
  );

  $form['services']['price'] = array(
    '#type' => 'textfield',
    '#title' => 'Price',
    '#default_value' => $result[0]->price,
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
  $fn = explode('/', $form_state['values']['filename']); 
  for ($i=0; $i<3; $i++) {
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
    'bedroom' => $form_state['values']['bedroom'],
    'price' => $form_state['values']['price'],
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

function find_projects($form, &$form_state, $id) {
  $buy = $_POST["buy"];
  $buildingname = $_POST["buildingname"];
  $bedrooms = $_POST["bedrooms"];
  $type = $_POST["type"];
  $location = $_POST["location"];

  $services = db_select('services', 's')
    ->fields('s')
    ->condition('title', $buy, '=')
    ->condition('project', '%' . $buildingname . '%', 'LIKE')
    ->condition('bedroom', '%' . $bedrooms . '%', 'LIKE')
    ->condition('type', '%' . $type . '%', 'LIKE')
    ->condition('location', '%' . $location . '%', 'LIKE')
    ->execute()
    ->fetchAll();

  if (count($services) == 0) {
    print '<div style="margin: 20px; text-align: center; color: #ff0000; font-size: 20px; ">"search not found"</div>';
  }

  foreach ($services as $id=>$service) { 
    $filename = explode("/", $service->filename);
    print '

    <div class="service-item">
      <div class="col-lg-5 col-md-5 col-sm-7 col-xs-7 service-gallery">
        <div class="row">
          <div class="col-lg-8 col-md-8 col-sm-9 col-xs-8">
            <img id="'. $id .'" class="img-responsive" src="'. file_create_url('public://') . $filename[0].'">
          </div>
          <div class="col-lg-3 col-md-3 col-sm-3 col-xs-4">';
            for ($i=0; $i<3; $i++) { 
              if (isset($filename[$i])) {
                print '
            <div class="thumb">
              <img src="'.file_create_url('public://') . $filename[$i] .'" onclick="set_image(\''. $id . '\',\'' . file_create_url('public://') . $filename[$i] .'\')">
            </div>';
              } 
            }
            print '
          </div>
          <div class="col-lg-1 col-md-1 hidden-sm hidden-xs">&nbsp;</div>
        </div>
      </div>
      <div class="col-lg-7 col-md-7 col-sm-5 col-xs-5 service-description">
        <h4 style="text-transform: uppercase">'. $service->title .'</h4>
        <div class="row">
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6">
            <label>Project</label>
            <p>'. $service->project .'</p>
            <label>Location</label>
            <p>'. $service->location .'</p>
            <label>Area</label>
            <p>'. $service->area .'</p>
            <label>Bedroom</label>
            <p>'. $service->bedroom .'</p>
          </div>
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-5">
            <label>Size</label>
            <p>'. $service->size .'</p>
            <label>Facilities</label>
            <p>'. $service->facilities .'</p>
            <label>Price</label>
            <p>'. $service->price .'</p>
            <label>Type</label>
            <p>'. $service->type .'</p>
          </div>
        </div>
      </div>
      <div class="clearfix"></div></div>';
    }
}