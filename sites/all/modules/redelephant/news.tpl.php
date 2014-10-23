
<div class="row" style="margin-top: 50px">

  <div class="col-xs-3" style="height: 200px; background-color: red; color: #fff; font-size: 50px">
 		<strong>WHAT'S NEW?</strong>
  </div>

  <div class="col-xs-9">
  	<?php foreach($news as $i => $n) { ?>
  	<div class="row" style="margin-bottom: 10px">
  		<div class="col-xs-5" style="padding-right: 0">
          <img src="<?php print file_create_url('public://') . $n->filename; ?>" style="width: 350px; height: 200px;">
  		</div>
  		<div class="col-xs-7" style="height: 200px; background-color: lightgrey; padding: 0">
        <div class="col-xs-12" style="margin-top: 10px">
    			<h4 style="font-size: 15px; font-weight: bold"><?php print $n->date; ?></h4>
    			<h4 style="font-size: 15px; font-weight: bold"><?php print $n->title; ?></h4>
    			<strong style=""><?php print $n->description; ?></strong>
    		</div>
      </div>
  	</div>
  	<?php } ?>
	</div>

</div>