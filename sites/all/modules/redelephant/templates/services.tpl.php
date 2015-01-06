<script>
document.getElementById("services").classList.add("active");

function set_image(id, filepath) {
  document.getElementById(id).src = filepath;
}

$(document).ready() {
   $('.selectpicker').selectpicker({
      style: 'btn-info',
      size: 4
  });
}
</script>

<div class="service-search">
   <div class="col-lg-5 col-md-5 col-sm-7 col-xs-7 title">
      <h2>Search<br>Project<br>></h2>
   </div>
   <div class="col-lg-7 col-md-7 col-sm-5 col-xs-5 search-form">
      <div class="row">
         <div class="col-lg-5 col-md-5 col-sm-6">
            <div class="input-group">
               <select class="selectpicker">
                 <option>Buy</option>
                 <option>Sell</option>
                 <option>Rent</option>
               </select>
            </div>
            <div class="input-group">
               <select class="selectpicker">
                 <option>Buy</option>
                 <option>Sell</option>
                 <option>Rent</option>
               </select>
            </div>
            <div class="input-group">
               <select class="selectpicker">
                 <option>Buy</option>
                 <option>Sell</option>
                 <option>Rent</option>
               </select>
            </div>
         </div>
         <div class="col-lg-5 col-md-5 col-sm-6">
            <div class="input-group">
               <select class="selectpicker">
                 <option>Buy</option>
                 <option>Sell</option>
                 <option>Rent</option>
               </select>
            </div>
            <div class="input-group">
               <select class="selectpicker">
                 <option>Buy</option>
                 <option>Sell</option>
                 <option>Rent</option>
               </select>
            </div>
            <div class="input-group">
               <button class="btn btn-primary">Find Project</button>
            </div>
         </div>
         <div class="col-lg-2 col-md-2 hidden-sm">&nbsp;</div>
         <div class="clearfix"></div>
      </div>
   </div>
   <div class="clearfix"></div>
</div>
<div class="not-found">"search not found"</div>
<?php foreach ($services as $id=>$service) { $filename = explode("/", $service->filename); ?>

  <div class="service-item">
    <div class="col-lg-5 col-md-5 col-sm-7 col-xs-7 service-gallery">
  		<div class="row">
  			<div class="col-lg-8 col-md-8 col-sm-9 col-xs-8">
  				<img id="<?php print $id; ?>" class="img-responsive" src="<?php print file_create_url('public://') . $filename[0]; ?>">
    		</div>
        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-4">
          <?php for ($i=0; $i<3; $i++) { if (isset($filename[$i])) { ?>
          <div class="thumb">
            <img src="<?php print file_create_url('public://') . $filename[$i]; ?>" onclick="set_image('<?php print $id . "','" . file_create_url('public://') . $filename[$i] ?>')">
          </div>
          <?php } } ?>
        </div>
        <div class="col-lg-1 col-md-1 hidden-sm hidden-xs">&nbsp;</div>
  		</div>
    </div>
    <div class="col-lg-7 col-md-7 col-sm-5 col-xs-5 service-description">
    	<h4><?php print $service->title; ?></h4>
      <div class="row">
        <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6">
          <label>Project</label>
          <p><?php print $service->project; ?></p>
          <label>Location</label>
          <p><?php print $service->location; ?></p>
          <label>Area</label>
          <p><?php print $service->area; ?></p>
          <label>Bedroom</label>
          <p><?php print $service->bedroom; ?></p>
        </div>
        <div class="col-lg-6 col-md-6 col-sm-6 col-xs-5">
          <label>Size</label>
          <p><?php print $service->size; ?></p>
          <label>Facilities</label>
          <p><?php print $service->facilities; ?></p>
          <label>Price</label>
          <p><?php print $service->price; ?></p>
          <label>Type</label>
          <p><?php print $service->type; ?></p>
        </div>
      </div>
  	</div>
    <div class="clearfix"></div>
  </div>

<?php } ?>