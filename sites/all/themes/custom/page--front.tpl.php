<?php
global $user;
?>

<div id="wrapper">
  <div class="container">
    <div id="header">
      <div class="row">
        <div class="col-lg-4 col-sm-3 col-xs-3">
          <h1><a href="<?php print $front_page;?>">Red Elephant</a></h1>
        </div>
        <div class="col-lg-8 col-sm-9 col-xs-12 top-menu">
          <div class="navbar navbar-default">
            <div class="navbar-header">
              <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#redElephantMenu">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
              </button>
            </div>
            <div class="collapse navbar-collapse" id="redElephantMenu">
              <ul class="nav navbar-nav">
                <li>
                  <a id="about-us" href="<?php print $front_page . 'about-us';?>">ABOUT US</a>
                </li>
                <li>
                  <a id="projects" href="<?php print $front_page . 'projects';?>">PROJECTS</a>
                </li>
                <li>
                  <a id="services" href="<?php print $front_page . 'services';?>">OUR SERVICES</a>
                </li>
                <li>
                  <a id="news" href="<?php print $front_page . 'news';?>">NEWS & UPDATES</a>
                </li>
                <li>
                  <a id="contact" href="<?php print $front_page . 'contact';?>">CONTACT</a>
                </li>
              </ul>
            </div>
          </div>
        </div>
        <div class="clearfix"></div>
      </div>
    </div>

    <div class="home-banner">
     <a href="<?php print $front_page . 'about-us';?>"><img class="img-responsive" src="<?php print base_path() . drupal_get_path('theme', 'custom') . '/images/re_web_home-image.jpg'; ?>"></a>
     <div class="text-content">
        <h2>LUXURY IS YOURS</h2>
        <p>-</p>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque eget velit vitae<br>see more ></p>
     </div>
    </div>
  </div>
  <div id="footer">
      <div class="container">
        <?php if ($page['footer']): ?>
          <?php print render($page['footer']); ?>
        <?php endif; ?>
        <div class="pull-left"><a href="#">info@redelephant.com</a></div>
        <div class="pull-right">&copy; 2014 Red Elephant, Inc.</div>
        <div class="clearfix"></div>
      </div>
  </div>
</div>
