<script>
document.getElementById("services").classList.add("active");

function set_image(id, filepath) {
  document.getElementById(id).src = filepath;
}
</script>

<?php foreach ($services as $id=>$service) { $filename = explode("/", $service->filename); ?>
<div class="row" style="color: #EDEDED; border: 5px outset">
  <div class="col-xs-6" style="background-color: lightgrey; min-height: 300px;">
		<div class="row">
			<div class="col-xs-9">
				<img id="<?php print $id; ?>" src="<?php print file_create_url('public://') . $filename[0]; ?>" style="width: 330px; height: 250px; margin-top: 25px; margin-bottom: 25px; margin-left: 20px; border: 5px ridge">
  		</div>
      <div class="col-xs-3">
        <?php for ($i=0; $i<3; $i++) { if (isset($filename[$i])) { ?>
        <div class="row">
          <img src="<?php print file_create_url('public://') . $filename[$i]; ?>" style="width: 90px; height: 65px; margin-top: 25px; margin-left: 20px; cursor: pointer; border: 5px ridge" onclick="set_image('<?php print $id . "','" . file_create_url('public://') . $filename[$i] ?>')">
        </div>
        <?php } } ?>
      </div>
		</div>
  </div>

  <div class="col-xs-6" style="background-color: rgb( 72, 71, 72 ); min-height: 300px">
  	<h4 style="margin-top: 25px; margin-bottom: 20px; font-size: 20px; font-weight: bold; color: #EDEDED"><?php print $service->title; ?></h4>
  	<div class="col-xs-6" style="padding: 0">
      <small>PROJECT</small><br/>
      <small><?php print $service->project; ?></small><br/><br/>

		  <small>LOCATION</small><br>
      <small><?php print $service->location; ?></small><br/><br/>

      <small>AREA</small><br>
      <small><?php print $service->area; ?></small><br/><br/>

      <small>TYPE</small><br>
      <small><?php print $service->type; ?></small>
  	</div>
  	<div class="col-xs-6">
      <small>SIZE</small><br/>
      <small><?php print $service->size; ?></small><br/><br/>

      <small>FACILITIES</small><br/>
      <small><?php print $service->facilities; ?></small><br/><br/>

      <small>FLOOR</small><br/>
      <small><?php print $service->floor; ?></small>
  	</div>
	</div>
</div>
<br>

<?php } ?>