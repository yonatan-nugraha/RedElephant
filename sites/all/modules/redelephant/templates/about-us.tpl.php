<script>
document.getElementById("about-us").classList.add("active");
</script>

<div class="row" style="margin-bottom: 30px">
	<div class="col-xs-12">
		<img src="<?php print file_create_url('public://') . $filename; ?>" style="width: 10in; height: 3.2in;">
	</div>
</div>


<div class="row marketing">
  <div class="col-xs-6">
    <small><?php print $desc_left; ?></small>
  </div>

  <div class="col-xs-6">
  	<strong><?php print $desc_right; ?></strong>
	</div>
</div>
