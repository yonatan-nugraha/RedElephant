<script>
document.getElementById("news").classList.add("active");
</script>

<div class="row">
  <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 news-title">
 		<h2>WHAT'S NEW?</h2>
  </div>

  <div class="col-lg-9 col-md-9 col-sm-9 col-xs-12">
  	<?php foreach($news as $i => $n) { $filename = explode("/", $n->filename); ?>
  	<div class="news-item" onclick="location.href='news/<?php print $n->id; ?>';">
      <div class="row">
        <div class="col-lg-5 col-md-5 col-sm-5 col-xs-5">
            <img class="img-responsive" src="<?php print file_create_url('public://') . $filename[0]; ?>">
        </div>
        <div class="col-lg-7 col-md-7 col-sm-7 col-xs-7">
          <span class="date"><?php print $n->date; ?></span>
          <h4><?php print $n->title; ?></h4>
          <div class="description">
            <?php print $n->description; ?>
          </div>
          <p>>></p>
        </div>
      </div>
  	</div>
  	<?php } ?>
	</div>
</div>