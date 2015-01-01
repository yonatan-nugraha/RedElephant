<script>
document.getElementById("projects").classList.add("active");

function get_projectid(projectid) {
  var xmlhttp;
  if (window.XMLHttpRequest){
    xmlhttp = new XMLHttpRequest();
  } else {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }

  xmlhttp.onreadystatechange = function(){
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			document.getElementById("project").innerHTML = xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET", "projects/show_projects?projectid=" + projectid, true);
  xmlhttp.send();
}

function get_projects_local(city, page) {
  var xmlhttp;
  if (window.XMLHttpRequest){
    xmlhttp = new XMLHttpRequest();
  } else {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }

  xmlhttp.onreadystatechange = function(){
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			document.getElementById("local").innerHTML = xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET", "projects/show_projects?city=" + city + "&page=" + page, true);
  xmlhttp.send();
}

function get_projects_overseas(city, page) {
  var xmlhttp;
  if (window.XMLHttpRequest){
    xmlhttp = new XMLHttpRequest();
  } else {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }

  xmlhttp.onreadystatechange = function(){
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			document.getElementById("overseas").innerHTML = xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET", "projects/show_projects?city=" + city + "&page=" + page, true);
  xmlhttp.send();
}

get_projects_local("local", 0);
get_projects_overseas("overseas", 0);

function click_prevnext(prevnext) {
	if (prevnext == "next") {
		var page = parseInt(document.getElementById("page").innerHTML) + 1;
	}
	else {
		var page = parseInt(document.getElementById("page").innerHTML) - 1;
	}
	document.getElementById("page").innerHTML = page;

	var city = document.getElementById("city").innerHTML;

	get_projects(city, page);
}

function set_image(filepath) {
	document.getElementById("pic").src = filepath;
}

function set_city(city) {
	document.getElementById("city").innerHTML = city;
	document.getElementById("page").innerHTML = 0;
	get_projects(city, 0);
}

</script>

<div class="row">
  <!-- <span id="city" style="display: none">Jakarta</span>
  <span id="page" style="display: none">0</span>

  <span id="city" style="display: none">Jakarta</span>
  <span id="page" style="display: none">0</span> -->
  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 list-projects">
    <div class="row" id="local">
    </div>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 hidden-xs">&nbsp;</div>
  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 list-projects">
    <div class="row" id="overseas">
    </div>
  </div>
<!--
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
							<img src="<?php print drupal_get_path('module', 'redelephant') . '/images/singapore.jpg' ?>" style="height: 80px">
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

  </div>-->
</div>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg">
	    <div id="project">
	    </div>
  </div>
</div>