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

function get_projects(localoverseas, city, page) {
  var xmlhttp;
  if (window.XMLHttpRequest){
    xmlhttp = new XMLHttpRequest();
  } else {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }

  xmlhttp.onreadystatechange = function(){
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			document.getElementById(localoverseas).innerHTML = xmlhttp.responseText;
    }
  }
  xmlhttp.open("GET", "projects/show_projects?localoverseas=" + localoverseas + "&city=" + city + "&page=" + page, true);
  xmlhttp.send();
}

get_projects("local", "Jakarta", 0);
get_projects("overseas", "Singapore", 0);

function click_prevnext(prevnext, localoverseas) {
	if (prevnext == "next") {
    if (localoverseas == "local") {
		  var page = parseInt(document.getElementById("page-local").innerHTML) + 1;
      document.getElementById("page-local").innerHTML = page;

      var city = document.getElementById("city-local").innerHTML;
    }
    else {
      var page = parseInt(document.getElementById("page-overseas").innerHTML) + 1;
      document.getElementById("page-overseas").innerHTML = page;

      var city = document.getElementById("city-overseas").innerHTML;
    }
	}
	else {
    if (localoverseas == "local") {
		  var page = parseInt(document.getElementById("page-local").innerHTML) - 1;
      document.getElementById("page-local").innerHTML = page;

      var city = document.getElementById("city-local").innerHTML;
    }
    else {
      var page = parseInt(document.getElementById("page-overseas").innerHTML) + 1;
      document.getElementById("page-overseas").innerHTML = page;

      var city = document.getElementById("city-overseas").innerHTML;
    }
	}
  get_projects(localoverseas, city , page);
}

function set_image(filepath) {
	document.getElementById("pic").src = filepath;
}

function set_city(localoverseas, city) {
  if (localoverseas == "local") {
  	document.getElementById("city-local").innerHTML = city;
  	document.getElementById("page-local").innerHTML = 0;
  }
  else {
    document.getElementById("city-overseas").innerHTML = city;
    document.getElementById("page-overseas").innerHTML = 0;  
  }
	get_projects(localoverseas, city, 0);
}

</script>

<div class="row">
  <span id="city-local" style="display: none">Jakarta</span>
  <span id="page-local" style="display: none">0</span>

  <span id="city-overseas" style="display: none">Singapore</span>
  <span id="page-overseas" style="display: none">0</span>

  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 list-projects">
    <div class="row" id="local">
    </div>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 hidden-xs">&nbsp;</div>
  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 list-projects">
    <div class="row" id="overseas">
    </div>
  </div>
</div>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog modal-lg">
	    <div id="project">
	    </div>
  </div>
</div>