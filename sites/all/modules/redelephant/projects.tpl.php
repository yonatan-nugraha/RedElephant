<script>
function get_projectid(projectid) {
  var xmlhttp;
  if (window.XMLHttpRequest){
    xmlhttp = new XMLHttpRequest();
  } else{
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }

  xmlhttp.onreadystatechange = function(){
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			document.getElementById("project").innerHTML = xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET", "admin/red-elephant/projects?projectid=" + projectid, true);
  xmlhttp.send();
}

function set_image(filepath) {
	document.getElementById("pic").src = filepath;
}
</script>


<div class="row" style="margin-top: 50px">
  <div class="col-xs-6">

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px"><</a>
		</div>

    <div class="col-xs-10">
	    <h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">LOCAL</h4>
			<ul class="nav nav-tabs">
			  <li class="active"><a href="#jakarta" data-toggle="tab">Jakarta</a></li>
			  <li><a href="#bandung" data-toggle="tab">Bandung</a></li>
			  <li><a href="#bali" data-toggle="tab">Bali</a></li>
			</ul>
			<div id="myTabContent" class="tab-content">
			  <div class="tab-pane fade active in" id="jakarta">
			  	<?php foreach ($projects as $i=>$project) { if ($i > 7) break; ?>
			  	<?php if ($project->city == "Jakarta") { $filename = explode("/", $project->filename); ?>
			  	<div class="col-xs-3" style="padding: 0" onclick="get_projectid(<?php print $project->id ?>)">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print file_create_url('public://') . $filename[0]; ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } } ?>  
			  </div>
			  <div class="tab-pane fade" id="bandung">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/bandung.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			  <div class="tab-pane fade" id="bali">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/bali.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			</div>
		</div>

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px">></a>
		</div>
  </div>


  <div class="col-xs-6">
  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px"><</a>
		</div>

    <div class="col-xs-10">
    	<h4 style="margin-bottom: 40px; font-weight: bold; font-size: 25px;">OVERSEAS</h4>
			<ul class="nav nav-tabs">
			  <li class="active"><a href="#singapore" data-toggle="tab">Singapore</a></li>
			  <li><a href="#malaysia" data-toggle="tab">Malaysia</a></li>
			</ul>
			<div id="myTabContent" class="tab-content">
			  <div class="tab-pane fade active in" id="singapore">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/singapore.jpg' ?>" style="height: 100px">
				    </a>
				    <div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
			  <div class="tab-pane fade" id="malaysia">
			  	<?php for ($i=0; $i<8; $i++) { ?>
			  	<div class="col-xs-3" style="padding: 0">
				  	<a href="#myModal" class="thumbnail" data-toggle="modal" style="margin-bottom: 0">
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/malaysia.jpg' ?>" style="height: 100px">
				    </a>
						<div class="caption">
        			<p style="text-align: center">Lorem Ipsum</p>
           	</div>
			  	</div>
					<?php } ?>  
			  </div>
		  </div>
		</div>

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a style="font-size: 70px; margin-top: 50px">></a>
		</div>
  </div>
</div>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
	    <div id="project">
	    </div>
    </div>
  </div>
</div>

