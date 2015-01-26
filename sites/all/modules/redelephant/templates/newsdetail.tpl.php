<script>
document.getElementById("news").classList.add("active");

function set_image(id, filepath) {
  document.getElementById(id).src = filepath;
}
</script>

<div class="news-detail">
  <h2>WHAT'S NEW?</h2>
  <div class="row">
    <?php $filename = explode("/", $news->filename); ?>
	  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-5">
      <img id="img-newsdetail" class="img-responsive" src="<?php print file_create_url('public://') . $filename[0]; ?>">
      <?php for ($i=0; $i<3; $i++) { if (isset($filename[$i])) { ?>
      <div class="col-lg-4 col-md-4 col-sm-4 col-xs-4">
        <img class="img-responsive" src="<?php print file_create_url('public://') . $filename[$i]; ?>" onclick="set_image('<?php print "img-newsdetail" . "','" . file_create_url('public://') . $filename[$i] ?>')" style="cursor: pointer">
      </div>
      <?php }} ?>
		</div>
		<div class="col-lg-7 col-md-7 col-sm-7 col-xs-7">
			<span class="date"><?php print $news->date; ?></span>
			<h4><?php print $news->title; ?></h4>
			<div class="description"><?php print $news->description; ?></div>
      <ul class="pager">
        <?php if ($previous == "") { ?><li class="previous disabled"><a href=""> <?php } else { ?> <li class="previous"><a href="<?php print $previous; ?>"><?php } ?><</a></li>
        <?php if ($next == "") { ?><li class="next disabled"><a href=""><?php } else { ?><li class="next"><a href="<?php print $next; ?>"><?php } ?> ></a></li>
      </ul>
    </div>
	</div>
</div>