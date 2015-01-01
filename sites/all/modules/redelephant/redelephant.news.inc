<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */

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

    $filename = explode('/', $record->filename);
    $banner =  '<img src="'. file_create_url('public://') . $filename[0] .'" style="height: 100px; width: 150px;">';

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

  $form['news']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
    '#description' => 'Recommendation size: 675 x 270',
    '#size' => 30
  );

  $form['news']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
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
      file_save($file2);
    }
  }

  $description = str_replace(array("\r\n", "\n", "\r"), "<br/>", $form_state['values']['desc']);

  $result = db_insert('news')
  ->fields(array(
    'date' => $form_state['values']['date'],
    'title' => $form_state['values']['title'],
    'description' => $description,
    'filename' => $filename,
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

  $filename = explode('/', $result[0]->filename);

  for ($i=0; $i<count($filename); $i++) {
    $banner[$i] = '<img src="'. file_create_url('public://') . $filename[$i] .'" style="height: 250px; width: 700px;">';
  }

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

  if (isset($filename[0])) {
    $form['news']['image'] = array(
      '#markup' => $banner[0],
    );
  }

  $form['news']['file2'] = array(
    '#type' => 'file',
    '#title' => 'Image2',
  );

  if (isset($filename[1])) {
    $form['news']['image2'] = array(
      '#markup' => $banner[1],
    );
  }

  $form['news']['file3'] = array(
    '#type' => 'file',
    '#title' => 'Image3',
  );

  if (isset($filename[2])) {
    $form['news']['image3'] = array(
      '#markup' => $banner[2],
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