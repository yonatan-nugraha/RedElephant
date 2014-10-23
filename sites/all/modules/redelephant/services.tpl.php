

<?php foreach ($services as $service) { ?>
<div class="row" style="color: #EDEDED">
  <div class="col-xs-6" style="background-color: lightgrey; height: 300px">
		<div class="row">
			<div class="col-xs-9">
				<img src="<?php print file_create_url('public://') . $service->filename; ?>" style="width: 400px; height: 250px; margin-top: 25px; margin-bottom: 25px; margin-left: 20px;">
  		</div>
      <div class="col-xs-3">
        <?php for ($i=0; $i<3; $i++) { ?>
        <div class="row">
          <img src="<?php print file_create_url('public://') . $service->filename; ?>" style="width: 100px; height: 65px; margin-top: 25px; margin-left: 20px;">
        </div>
        <?php } ?>
      </div>
		</div>
  </div>

  <div class="col-xs-6" style="background-color: rgb( 72, 71, 72 ); height: 300px">
  	<h4 style="margin-top: 25px; margin-bottom: 20px; font-size: 20px; font-weight: bold; color: #EDEDED"><?php print $service->title; ?></h4>
  	<div class="col-xs-6" style="padding: 0">
  		<p>
        <small>PROJECT</small><br>
        <small><?php print $service->project; ?></small>
      </p>
      <p>
  		  <small>LOCATION</small><br>
        <small><?php print $service->location; ?></small>
      </p>
  		<p>
        <small>AREA</small><br>
        <small><?php print $service->area; ?></small>
      </p>
			<p>
        <small>TYPE</small><br>
        <small><?php print $service->type; ?></small>
      </p>
  	</div>
  	<div class="col-xs-6">
  		<p>
        <small>SIZE</small><br>
        <small><?php print $service->size; ?></small><br>
      </p>
      <p>
        <small>FACILITIES</small><br>
        <small><?php print $service->facilities; ?></small><br>
      </p>
  		<p>
        <small>FLOOR</small><br>
        <small><?php print $service->floor; ?></small>
      </p>
  	</div>
	</div>
</div>
<br>

<?php } ?>