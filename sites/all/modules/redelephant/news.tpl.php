
<div class="row" style="margin-top: 50px">

  <div class="col-xs-3" style="height: 200px; background-color: red; color: #fff; font-size: 50px">
 		<strong>WHAT'S NEW?</strong>
  </div>

  <div class="col-xs-9">
  	<?php for ($i=0; $i<3; $i++) { ?>
  	<div class="row" style="margin-bottom: 10px">
  		<div class="col-xs-5" style="padding-right: 0">
          <img src="<?php print drupal_get_path('module', 'redelephant') . '/images/banner.jpg' ?>" style="width: 350px; height: 200px;">
  		</div>
  		<div class="col-xs-7" style="height: 200px; background-color: lightgrey; padding: 0">
  			<h4 style="margin-left: 25px; margin-bottom: 20px; font-size: 15px; font-weight: bold;">21/06/14</h4>
  			<h4 style="margin-left: 25px; font-size: 15px; font-weight: bold;">LOREM IPSUM DOLOR SIT AMET</h4>
  			<strong style="margin-left: 25px;">Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat.</strong>
  		</div>
  	</div>
  	<?php } ?>
	</div>

</div>