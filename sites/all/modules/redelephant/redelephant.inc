<?php

/**
 * @author yonatan.nugraha@reebonz.com
 * @since 2014-10-21
 */


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