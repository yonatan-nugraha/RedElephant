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

function get_projects(city, page) {
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

get_projects("Jakarta", 0);

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

<style type="text/css">
.pager {
	font-size: 70px; 
	margin-top: 50px; 
	cursor: pointer
}
</style>

<div class="row" style="margin-top: 50px">
  <span id="city" style="display: none">Jakarta</span>
  <span id="page" style="display: none">0</span>
  <div class="col-xs-6" id="local">
  </div>


  <div class="col-xs-6">
  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a class="pager"><</a>
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

  	<div class="col-xs-1" style="top: 190px; padding: 0">
			<a class="pager">></a>
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