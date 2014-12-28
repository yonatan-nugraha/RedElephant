<?php
global $user;
?>

<div id="wrapper">

  <div id="header">
    <div class="container container-header">
	    <div class="navbar" role="navigation">
  		  <div class="collapse navbar-collapse" style="padding: 0">
          <ul class="nav navbar-nav">
            <li>
              <a href="<?php print $front_page;?>">
                <img src="<?php print $logo; ?>" alt="<?php print $site_name;?>" style="height: 40px; width: 210px;" />
              </a>
            </li>
          </ul>
          <ul class="nav navbar-nav navbar-right">
            <li>
              <a id="about-us" href="<?php print $front_page . 'about-us';?>"><strong>ABOUT US</strong></a>
            </li>
            <li>
              <a id="projects" href="<?php print $front_page . 'projects';?>"><strong>PROJECTS</strong></a>
            </li>
            <li>
              <a id="services" href="<?php print $front_page . 'services';?>"><strong>OUR SERVICES</strong></a>
            </li>
            <li>
              <a id="news" href="<?php print $front_page . 'news';?>"><strong>NEWS & UPDATES</strong></a>
            </li>
            <li>
              <a id="contact" href="<?php print $front_page . 'contact';?>"><strong>CONTACT</strong></a>
            </li>
          </ul>
  		  </div>
  	  </div>	
    </div>
	</div>
	
<div class="container">
    <a href="<?php print $front_page . 'about-us';?>"><img src="<?php print base_path() . drupal_get_path('theme', 'custom') . '/images/RE_web_opening-page.jpg'; ?>"></a>
</div>
  </div>

</div>      

<div id="footer">  
  <div class="container container-footer">    
    <?php if ($page['footer']): ?>    
      <?php print render($page['footer']); ?>
    <?php endif; ?> 
    <strong class="pull-left"><a href="#">info@redelephant.com</a></strong>
    <strong class="pull-right">&copy; 2014 Red Elephant, Inc. &middot;</strong>
  </div>
</div>