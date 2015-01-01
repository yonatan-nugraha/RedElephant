
<div class="news-detail">
  <h2>WHAT'S NEW?</h2>
  <div class="row">
	  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-5">
      <img class="img-responsive" src="<?php print file_create_url('public://') . $news->filename; ?>">
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