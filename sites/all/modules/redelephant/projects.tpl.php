
<div class="row" style="margin-top: 50px">
  <div class="col-xs-6">

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px"><</a>
		</div>

    <div class="col-xs-10">
	    <h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">LOCAL</h4>
			<ul class="nav nav-tabs">
			  <li class="active"><a href="#jakarta" data-toggle="tab">Jakarta</a></li>
			  <li><a href="#bandung" data-toggle="tab">Bandung</a></li>
			  <li><a href="#bali" data-toggle="tab">Bali</a></li>
			</ul>
			<div id="myTabContent" class="tab-content">
			  <div class="tab-pane fade active in" id="jakarta">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/jakarta.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			  <div class="tab-pane fade" id="bandung">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/bandung.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			  <div class="tab-pane fade" id="bali">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/bali.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			</div>
		</div>

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px">></a>
		</div>
  </div>


  <div class="col-xs-6">
  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px"><</a>
		</div>

    <div class="col-xs-10">
    	<h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">OVERSEAS</h4>
			<ul class="nav nav-tabs">
			  <li class="active"><a href="#singapore" data-toggle="tab">Singapore</a></li>
			  <li><a href="#malaysia" data-toggle="tab">Malaysia</a></li>
			</ul>
			<div id="myTabContent" class="tab-content">
			  <div class="tab-pane fade active in" id="singapore">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/singapore.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			  <div class="tab-pane fade" id="malaysia">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/malaysia.jpg' ?>" style="height: 100px">
				    </a>
						<div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
		  </div>
		</div>

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px">></a>
		</div>
  </div>
</div>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-footer">
      	<div class="row" style="margin: 0; margin-bottom: 10px">
      		<button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
				</div>
				<div class="col-xs-4" style="padding: 0; text-align: left;">
					<h2 style="margin-top: 0; margin-bottom: 20px; color: red"><strong><?php print $title; ?></strong></h2>
					<p style=" color: red">PROJECT</p>
					<p><?php print $project; ?></p>
					<p style=" color: red">LOCATION</p>
					<p><?php print $location; ?></p>
					<p style=" color: red">TYPE</p>
					<p><?php print $type; ?></p>
					<p style=" color: red">SIZE</p>
					<p><?php print $size; ?></p>
					<p style=" color: red">FACILITIES</p>
					<p><?php print $facilities; ?></p>
					<p style=" color: red">AMENITIES</p>
					<p><?php print $amenities; ?></p>
				</div>
				<div class="col-xs-8">
					<div class="row" style="margin-bottom: 20px">
						<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/malaysia.jpg' ?>" style="width: 350px; height: 200px">
					</div>
					<div class="row" style="margin-bottom: 20px">
						<?php for ($i=0; $i<4; $i++) { ?>
						<div class="col-xs-2" style="padding: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/malaysia.jpg' ?>" style="width: 45px; height: 45px;">
						</div>
						<?php } ?>
					</div>
					<div class="row">
					<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/logo.gif' ?>" style="width: 45px; height: 45px;">
					</div>
				</div>
      </div>
    </div>
  </div>
</div>