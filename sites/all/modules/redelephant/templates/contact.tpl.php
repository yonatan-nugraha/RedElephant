<script>
document.getElementById("contact").classList.add("active");
</script>

<div class="contact-us">
	<h2>HELLO THERE!</h2>
	<p>Please take a moment to let us know what are your thoughts -</p>
	<div class="row contact-form">
		<div class="col-lg-5">
			<div class="row">
				<div class="col-lg-10">
					<form role="form" id="myForm" action="admin/red-elephant/contact/submit" method="post" onsubmit="return alert('Thank you for taking your time to fill this form!');">
						<div class="form-group">
							<input type="text" class="form-control" id="name" name="name" placeholder="Name" required>
						</div>
						<div class="form-group">
							<input type="email" class="form-control" id="email" name="email" placeholder="Email" required>
						</div>
						<div class="form-group">
							<input type="text" class="form-control" id="phone" name="phone" placeholder="Phone" required>
						</div>
						<div class="form-group">
							<textarea class="form-control" rows="5" id="address" name="address" placeholder="Note" required></textarea>
						</div>
						<button type="submit" class="btn btn-default pull-right">Submit</button>
					</form>
				</div>
				<div class="col-lg-2">&nbsp;</div>
				<div class="clearfix"></div>
			</div>
		</div>
		<div class="col-lg-7 address">
			<h4 class="logo">Red Elephant</h4>
			<p>PT. REPRO KONSULTAN INDONESIA<br>Epicentrum Walk 6th Fl, unit #B627<br>Jl. HR Rasuna Said | Jakarta 12940<br>Indonesia</p>
			<p>p. +62 21 299 121 43 | f. +62 21 299 121 42</p>
		</div>
		<div class="clearfix"></div>
	</div>
</div>