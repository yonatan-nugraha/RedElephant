  
<div class="row" style="margin-top: 50px">
	<div class="col-xs-12" style="color: red; font-size: 25px; margin-bottom: 10px">
		<strong>WHAT'S NEW?</strong>
	</div>
  <div class="col-xs-12" style="padding: 0">
	  <div class="col-xs-6">
      <img src="<?php print file_create_url('public://') . $news->filename; ?>" style="width: 550px; height: 250px;">
		</div>
		<div class="col-xs-6">
      <div class="col-xs-12">
  			<strong style="font-size: 15px; color:#000; border-bottom: 3px solid red; margin-bottom: 20px";><?php print $news->date; ?></strong>
  			<h4 style="font-size: 15px; font-weight: bold"><?php print $news->title; ?></h4>
  			<div style="min-height: 200px"><strong><?php print $news->description; ?></strong></div><br/>
        <ul class="pager">
          <?php if ($previous == "") { ?><li class="previous disabled"><a href=""> <?php } else { ?> <li class="previous"><a href="<?php print $previous; ?>"><?php } ?>← Older</a></li>
          <?php if ($next == "") { ?><li class="next disabled"><a href=""><?php } else { ?><li class="next"><a href="<?php print $next; ?>"><?php } ?> Newer →</a></li>
        </ul>
  		</div>
    </div>
	</div>

</div> 