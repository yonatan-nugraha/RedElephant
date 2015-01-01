<script>
document.getElementById("news").classList.add("active");
</script>

<div class="row">
  <div class="col-lg-3 news-title">
 		<h2>WHAT'S NEW?</h2>
  </div>

  <div class="col-lg-9">
  	<?php foreach($news as $i => $n) { ?>
  	<div class="news-item" onclick="location.href='news/<?php print $n->id; ?>';">
      <div class="row">
        <div class="col-lg-5">
            <img class="img-responsive" src="<?php print file_create_url('public://') . $n->filename; ?>">
        </div>
        <div class="col-lg-7">
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