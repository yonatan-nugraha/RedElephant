<?php
global $user;
?>

<div id="wrapper">

  <div id="header">
  	<div class="navbar" role="navigation">
      <div class="container">
  		  <div class="collapse navbar-collapse" style="padding: 0">
          <ul class="nav navbar-nav">
            <li>
              <a href="<?php print $front_page;?>">
                <img src="<?php print $logo; ?>" alt="<?php print $site_name;?>" style="height: 35px; width: 200px;" />
              </a>
            </li>
          </ul>
          <!--
  			  <?php if ($main_menu): ?>
  			    <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => 'nav navbar-nav navbar-right'))); ?>
  			  <?php endif; ?>
          -->
          <ul class="nav navbar-nav navbar-right">
            <li>
              <a href="<?php print $front_page . 'about-us';?>"><strong>ABOUT US</strong></a>
            </li>
            <li>
              <a href="<?php print $front_page . 'projects';?>"><strong>PROJECTS</strong></a>
            </li>
            <li>
              <a href="<?php print $front_page . 'services';?>"><strong>OUR SERVICES</strong></a>
            </li>
            <li>
              <a href="<?php print $front_page . 'news';?>"><strong>NEWS & UPDATES</strong></a>
            </li>
            <li>
              <a href="<?php print $front_page . 'contact';?>"><strong>CONTACT</strong></a>
            </li>
          </ul>
          <!--
          <ul class="nav navbar-nav navbar-right">
            <?php if ($user->uid) { ?>
            <li class="dropdown">
              <?php print l(t($user->name), 'user/logout', array('attributes' => array('class' => 'dropdown-toggle', 'data-toggle' => 'dropdown'))); ?>
            </li>
            <?php } else { ?>
            <li>
              <?php print l(t('Sign in'), 'user/login'); ?>
            </li>
            <?php } ?>
          </ul>
          -->
  		  </div>
  	  </div>	
    </div>
	</div>
	
  <div class="container">
    <div id="content">
      <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1><?php print $title; ?></h1><?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php print render($messages); ?>
      <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

      <?php print render($page['content']); ?>
    </div>

    <?php if ($page['sidebar_first']): ?>    
      <div id="sidebar">
        <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>  

    <div class="footer">      
      <?php if ($page['footer']): ?>    
        <?php print render($page['footer']); ?>
      <?php endif; ?> 
      <strong class="pull-left"><a href="#">info@redelephant.com</a></strong>
      <strong class="pull-right">&copy; 2014 Red Elephant, Inc. &middot;</strong>
    </div>

  </div>
</div>