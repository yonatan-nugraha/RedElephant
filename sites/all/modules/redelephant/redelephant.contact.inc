<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */


/**
 * Contact Form
 */
function contact_form() {
  $header = array( 
    array('data' => t('No')),
    array('data' => t('Name')), 
    array('data' => t('Email')), 
    array('data' => t('Phone')),
    array('data' => t('Address')),
    array('data' => t('Action')),
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
      array('data' => l('Delete', 'admin/red-elephant/contact/delete/'. $record->id))
    );
  }

  $output = theme('table', array('header' => $header,
                     'rows' => $row, 'empty' => t('Table has no row!'))) . theme('pager');
  return $output;
}

function contact_form_submit() {
  if ($_POST['name']) {

    $to = "yonatan.nugraha@hotmail.com";
    $from = "info@redelephant.com";
     
    $subject = "Red Elephant Contact Information";

    $body = "Name: " . $_POST['name'] . "\n";
    $body .= "Email: " . $_POST['email'] . "\n";
    $body .= "Phone: " . $_POST['phone'] . "\n";
    $body .= "Address: " . $_POST['address'];

    $params = array(
        'subject' => $subject,
        'body' => $body,
        );
     
    drupal_mail('redelephant', 'contact_info', $to, language_default(), $params, $from, TRUE);


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

function redelephant_mail($key, &$message, $params) {
  switch ($key) {
    case 'contact_info':
      $message['subject'] = $params['subject'];
      $message['body'][] = $params['body'];
    break;
    }
}

function delete_contact_form($form, &$form_state, $id) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Delete Contact'),
    'admin/red-elephant/contact',
    t('Are you sure you want to delete this ?'),
    t('Delete'),
    t('Cancel')
  );
}

function delete_contact_form_submit($form, &$form_state) {
  $result = db_delete('contact')
  ->condition('id', $form_state['values']['id'], '=')
  ->execute();

  drupal_set_message('Succesfully deleted');
  $form_state['redirect'] = 'admin/red-elephant/contact';
}