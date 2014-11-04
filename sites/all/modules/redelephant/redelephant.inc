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










/**
 * Projects Form
 */

function projects_form() {
  $output = '<a href="projects/add/local">Add Projects here</a>';

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
    array('data' => t('Action')),
  ); 

  $result = db_select('projects', 'p')
  ->fields('p')
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
      array('data' => l('Edit', 'admin/red-elephant/projects/edit/'. $record->localoverseas . '/' . $record->id).' | '.l('Delete', 'admin/red-elephant/projects/delete/' . $record->id))
    );
  }

  if (isset($_GET['projectid'])) {
    $result = db_select('projects', 'p')
    ->fields('p')
    ->condition('id', $_GET['projectid'], '=')
    ->execute()
    ->fetchAll();

    $filename = explode('/', $result[0]->filename);

    print '
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
            <h2 class="text-primary" style="margin-top: 0"><strong>'. $result[0]->title .'</strong></h2>
      </div>
      <div class="modal-footer">
        <div class="col-xs-4" style="padding: 0; text-align: left;">
          <span class="text-primary"><strong>PROJECT</span><br/> 
          <p>'. $result[0]->project .'</p>
          <span class="text-primary">LOCATION</span><br/>
          <p>'. $result[0]->location .'</p>
          <span class="text-primary">TYPE</span><br/>
          <p>'. $result[0]->type .'</p>
          <span class="text-primary">SIZE</span><br/>
          <p>'. $result[0]->size .'</p>
          <span class="text-primary">FACILITIES</span><br/>
          <p>'. $result[0]->facilities .'</p>
          <span class="text-primary">AMENITIES</span><br/>
          <p>'. $result[0]->amenities .'</p></strong>
        </div>
        <div class="col-xs-8">
          <div class="row" style="margin-bottom: 10px">
            <img id="pic" src="'. file_create_url('public://') . $filename[0] .'" style="width: 370px; height: 200px; border: 5px ridge">
          </div>
        <div class="row">';
    for ($i=0; $i<count($filename); $i++) {
      if ($filename[$i] != "") {
      print '
            <div class="col-xs-2" style="padding-left: 0; cursor: pointer" onclick="set_image('. "'" . file_create_url('public://') . $filename[$i] . "'" .')">
              <img src="'. file_create_url('public://') . $filename[$i] .'" style="width: 55px; height: 55px; border: 5px ridge">
            </div>';
      }
    }
    print '
          </div>
        </div>
      </div>';
    die();
  }



  if (isset($_GET['city'])) {
    $project = db_select('projects', 'p')
    ->fields('p')
    ->condition('city', $_GET['city'], '=')
    ->execute()
    ->fetchAll();

    if ($_GET['page'] > 0) {
      print '
        <div class="col-xs-1" style="top: 190px; padding: 0">
          <a class="pager" onclick="click_prevnext(\'prev\')"><</a>
        </div>';
    }
    else {
         print '
        <div class="col-xs-1" style="top: 130px; padding: 0">
          <a class="pager btn btn-link disabled"><</a>
        </div>';   
    }
      print '
      <div class="col-xs-10">
        <div id="city" style="display: none"></div>
        <h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">LOCAL</h4>
        <ul class="nav nav-tabs">';

        $projects_list = db_select('projects_list', 'pl')
        ->fields('pl')
        ->condition('localoverseas', 'local', '=')
        ->execute()
        ->fetchAll();

      foreach ($projects_list as $i => $pl) {
        $result = db_select('projects', 'p')
          ->fields('p')
          ->condition('city', $pl->city, '=')
          ->execute()
          ->fetchAll();

        if ($pl->city == $_GET['city']) {
          print '
          <li class="active"><a href="#'. $pl->city .'" data-toggle="tab" onclick="set_city(\''. $pl->city .'\')">'. $pl->city .'</a></li>';
        } else {
          print '
          <li><a href="#'. $pl->city .'" data-toggle="tab" onclick="set_city(\''. $pl->city .'\')">'. $pl->city .'</a></li>';
        }
      }
        print '
        </ul>

        <div id="myTabContent" class="tab-content">';
      foreach ($projects_list as $i => $pl) {

        if ($pl->city == $_GET['city']) {
          print '
          <div class="tab-pane fade active in" id="'. $pl->city .'">';
        } else {
          print '
          <div class="tab-pane fade" id="'. $pl->city .'">';
        }

        $result = db_select('projects', 'p')
        ->fields('p')
        ->condition('city', $pl->city, '=')
        ->range(8*$_GET['page'], 8)
        ->execute()
        ->fetchAll();

          foreach ($result as $record) {
            $filename = explode('/', $record->filename);
            print '
            <div class="col-xs-3" style="padding: 0" onclick="get_projectid(' . $record->id . ')">
              <a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
                <img src="'. file_create_url('public://') . $filename[0] .'" style="height: 100px">
              </a>
              <div class="caption">
                <p style="text-align: center">' . $record->title .'</p>
              </div>
            </div>';
          }
          print '</div>';
        }

          print '
        </div>
      </div>';

    if (count($project) > ($_GET['page']+1)*8) {
      print '
      <div class="col-xs-1" style="top: 190px; padding: 0">
        <a class="pager" onclick="click_prevnext(\'next\')">></a>
      </div>';
    }
    else {
      print '<div class="col-xs-1" style="top: 130px; padding: 0">
        <a class="pager btn btn-link disabled">></a>
      </div>';    
    }
    die();
  }

  $output .= theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!'))) . theme('pager');
  return $output;
}

function add_projects_form($form, &$form_state, $locover) {
  $form['projects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Projects'),
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
  );

  $form['projects']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
  );

  $form['projects']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
  );

  $form['projects']['file4'] = array(
    '#type' => 'file',
    '#title' => 'Image4',
  );

  $form['projects']['file5'] = array(
    '#type' => 'file',
    '#title' => 'Image5',
  );

  $form['projects']['file6'] = array(
    '#type' => 'file',
    '#title' => 'Image6',
  );

  if ($locover == "local") {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Local',
      '#options' => array(
        'Jakarta' => t('Jakarta'),
        'Bandung' => t('Bandung'),
        'Bali' => t('Bali'),
      ),
    );
  }

  else {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Overseas',
      '#options' => array(
        'Singapore' => t('Singapore'),
        'Malaysia' => t('Malaysia'),
      ),
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
    '#title' => t('Projects'),
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
  );

  if (isset($banner[0])) {
    $form['projects']['image'] = array(
      '#markup' => $banner[0],
    );
  }

  $form['projects']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
  );

  if (isset($banner[1])) {
    $form['projects']['image2'] = array(
      '#markup' => $banner[1],
    );
  }

  $form['projects']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
  );

  if (isset($banner[2])) {
    $form['projects']['image3'] = array(
      '#markup' => $banner[2],
    );
  }

  $form['projects']['file4'] = array(
    '#type' => 'file',
    '#title' => 'Image4',
  );

  if (isset($banner[3])) {
    $form['projects']['image4'] = array(
      '#markup' => $banner[3],
    );
  }

  $form['projects']['file5'] = array(
    '#type' => 'file',
    '#title' => 'Image5',
  );

  if (isset($banner[4])) {
    $form['projects']['image5'] = array(
      '#markup' => $banner[4],
    );
  }

  $form['projects']['file6'] = array(
    '#type' => 'file',
    '#title' => 'Image6',
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
      '#options' => array(
        'Jakarta' => t('Jakarta'),
        'Bandung' => t('Bandung'),
        'Bali' => t('Bali'),
      ),
    );
  }

  else {
    $form['projects']['city'] = array(
      '#type' => 'select',
      '#title' => 'Overseas',
      '#options' => array(
        'Singapore' => t('Singapore'),
        'Malaysia' => t('Malaysia'),
      ),
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
    'floor' => $form_state['values']['floor'],
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
    '#title' => t('Services'),
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
      $filename = substr($file->destination, strrpos($file->destination, '/')+1);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
    }
  }

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

  $form['filename'] = array(
    '#type' => 'value',
    '#value' => $result[0]->filename,
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

  $description = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['desc']);

  $result = db_update('news')
    ->fields(array(
      'date' => $form_state['values']['date'],
      'title' => $form_state['values']['title'],
      'description' => $description,
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






function contact_form() {
  $header = array( 
    array('data' => t('No')),
    array('data' => t('Name')), 
    array('data' => t('Email')), 
    array('data' => t('Phone')),
    array('data' => t('Address')),
  ); 

  $result = db_select('contact', 'c')
  ->fields('c')
  ->execute()
  ->fetchAll();

  $row = null;
  foreach ($result as $i => $record) {
    $no = $i+1;
    $row[] = array(
      array('data' => $no),
      array('data' => $record->name),
      array('data' => $record->email),
      array('data' => $record->phone),
      array('data' => $record->address),
    );
  }

  $output = theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!'))) . theme('pager');
  return $output;
}

function contact_form_submit() {
  if ($_POST['name']) {
    $result = db_insert('contact')
    ->fields(array(
      'name' => $_POST['name'],
      'email' => $_POST['email'],
      'phone' => $_POST['phone'],
      'address' => $_POST['address'],
    ))
    ->execute();
  }

  drupal_goto('contact');
}






/*
  Implement Hook View form
 */
function aboutus_view() {
	return theme('about-us', array(
    'filename' => variable_get('filename'),
    'desc_left' => variable_get('desc_left'),
    'desc_right' => variable_get('desc_right'),
  ));
}

function projects_view() {
  $projectid = "";
  if (isset($_GET['projectid'])) {
    $projectid = $_GET['projectid'];
  }
  $result = db_select('projects', 'p')
        ->fields('p')
        ->execute()
        ->fetchAll();

	return theme('projects', array(
    'projects' => $result,
    'projectid' => $projectid,
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

function newsdetail_view($id) {
  $result = db_select('news', 'n')
    ->fields('n')
    ->execute()
    ->fetchAll();

  foreach ($result as $i => $r) {
    if ($r->id == $id) {
      $next = "";
      $previous = "";
      if (isset($result[$i+1]->id)) {
        $next = $result[$i+1]->id;
      }
      if (isset($result[$i-1]->id)) {
        $previous = $result[$i-1]->id;
      }
      return theme('newsdetail', array(
        'news' => $r,
        'next' => $next,
        'previous' => $previous
      ));   
    }
  }
}

function contact_view() {
  return theme('contact');
}