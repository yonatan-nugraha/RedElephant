<script>
document.getElementById("about-us").classList.add("active");
</script>

<div class="row" style="margin-bottom: 30px">
	<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
		<img class="img-responsive" src="<?php print file_create_url('public://') . $filename; ?>">
	</div>
</div>


<div class="row marketing">
  <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6 left-content">
    <?php print $desc_left; ?>
  </div>

  <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6 right-content">
  	<?php print $desc_right; ?>
	</div>
</div>
