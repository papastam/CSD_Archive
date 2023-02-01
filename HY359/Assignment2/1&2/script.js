$(document).ready(function(){
	map = new OpenLayers.Map("Map");
	var mapnik = new OpenLayers.Layer.OSM();
	map.addLayer(mapnik);
	const zoom = 15;

	function setPosition(lat, lon){
		var fromProjection = new OpenLayers.Projection("EPSG:4326"); // Transform from 	WGS 1984
		var toProjection = new OpenLayers.Projection("EPSG:900913"); // to Spherical Mercator Projection
		var position = new OpenLayers.LonLat(lon, lat).transform( fromProjection, toProjection);
		return position;
	}

	function handler(position, message){
		var popup = new OpenLayers.Popup.FramedCloud("Popup", position, null, message, null, true /* <-- true if we want a close (X) button, false otherwise*/);
		map.addPopup(popup);
	}

	//Markers
	var markers = new OpenLayers.Layer.Markers("Markers");
	map.addLayer(markers);

	$("#city,#address,#country,#addrnumber").change(function(){
		const data = null;
		// $("#Map").hide();
		markers.clearMarkers();
		const xhr = new XMLHttpRequest();
		xhr.withCredentials = true;

		xhr.addEventListener("readystatechange", function () {
			if (this.readyState === this.DONE) {
				const obj = JSON.parse(xhr.responseText);
				var text=obj[0];
				console.log(text);
				if(!text){
					$("#wrondaddress").show();
					$("#outsideCrete").hide();
					$("#showmapbtn").prop("disabled",true);
				}else if(!(text["display_name"].includes("Region of Crete"))){
					$("#showmapbtn").prop("disabled",true);
					$("#outsideCrete").show();
				}else{
					$("#outsideCrete").hide();
					$("#wrondaddress").hide();
					$("#showmapbtn").prop("disabled",false);

					var position=setPosition(text["lat"],text["lon"]);
					map.setCenter(position, zoom);

					var mar=new OpenLayers.Marker(position);
					markers.addMarker(mar);
					mar.events.register('mousedown', mar, function(evt) { 
						handler(position,address);}
					);
				}
			}
		});

		var addressName=$("#address").val();
		var addressNumber=$("#addrnumber").val();
		var city=$("#city").val();
		var country=$("#country").val();
		var address=addressName+" "+addressNumber+" "+city+" "+country; 

		xhr.open("GET", "https://forward-reverse-geocoding.p.rapidapi.com/v1/search?q="+address+"&accept-language=en&format=json&polygon_threshold=0.0");
		xhr.setRequestHeader("x-rapidapi-host", "forward-reverse-geocoding.p.rapidapi.com");
		xhr.setRequestHeader("x-rapidapi-key", "bd2e97d2d1msh175dda3181f8171p1988aejsnf9cec4a9c8d3");

		xhr.send(data);

	});

	$("#getloc").click(function getLocation() {
		if(navigator.geolocation){
			navigator.geolocation.getCurrentPosition(function(position){
				if (navigator.geolocation) {
					// console.log("Latitude: " + position.coords.latitude +"Longitude: " + position.coords.longitude);
					const data = null;

					const xhr = new XMLHttpRequest();
					xhr.withCredentials = true;

					xhr.addEventListener("readystatechange", function () {
						if (this.readyState === this.DONE) {
							// console.log(this.responseText);
							const obj = JSON.parse(xhr.responseText);
							var text=obj[0];
							// console.log(obj);
							if(!obj){
								$("#geolocationerr").show();
							}else{
								$("#address").val(obj.address.pedestrian);
								// $("#addrnumber").val();
								$("#city").val(obj.address.city);
								$("#country").val(obj.address.country);
							}
						}
					});

					xhr.open("GET", "https://forward-reverse-geocoding.p.rapidapi.com/v1/reverse?lat="+position.coords.latitude+"&lon="+position.coords.longitude+"&accept-language=en&format=json&polygon_threshold=0.0");
					xhr.setRequestHeader("x-rapidapi-host", "forward-reverse-geocoding.p.rapidapi.com");
					xhr.setRequestHeader("x-rapidapi-key", "bd2e97d2d1msh175dda3181f8171p1988aejsnf9cec4a9c8d3");

					xhr.send(data);
				}else{
					$("#getloc").prop("disable","true");
				}
			});
		}else{
			$("#geolocationerr").show();
		}
	});

	$("#showmapbtn").click(function(){
		if($("#Map").is(":visible")){
			$("#Map").hide();
			$("#showmapbtn").html("Show Map");
		}else{
			$("#Map").show();
			$("#showmapbtn").html("Hide Map");
		}
	});

	$("#cpasswordfield").keyup(function(){
		var pass = $("#passwordfield").val();
		var cpass = $("#cpasswordfield").val();

		if(pass!==cpass){
			$("#wrongpass").show();
			$("#formsubmit").prop("disabled",true);
		}else{
			$("#wrongpass").hide();
			$("#formsubmit").prop("disabled",false);
		}
	});


	$("#showpass,#cshowpass").click(function(){
		if($(this).siblings(".pwrdfld").attr('type')=="password"){
			$(this).siblings(".pwrdfld").attr('type', 'text');
			$(this).html("Hide Password");
		}else{
			$(this).siblings(".pwrdfld").attr('type', 'password');
			$(this).html("Show Password");
		}
	});

	$("#passwordfield").keyup(function(){
		var pass = $("#passwordfield").val();
		var passdict = {"num":0}
		var strongpassflag = 1;
		var weakpassflag = 0;

		if(pass.length==0){$("#passwordstrength").html(" ");return;}

		for(var i=0;i<pass.length;i++){
			if(!(isNaN(pass.charAt(i)))){
				passdict["num"]++;
			}
			if(pass.charAt(i) in passdict){
				passdict[pass.charAt(i)]++;
			}else{
				passdict[pass.charAt(i)]=1;
			}
		}

		for(ind in passdict){
			if(ind!="num" && passdict[ind]>=(pass.length*0.2)){
				strongpassflag=0;
			}
			if(passdict[ind]>=(pass.length/2)){
				weakpassflag=1;
			}
		}
		if(strongpassflag){
			$("#passwordstrength").html("Strong");
			$("#passwordstrength").css("color","green");	
		}else if(weakpassflag){
			$("#passwordstrength").html("Weak");
			$("#passwordstrength").css("color","red");
		}else{
			$("#passwordstrength").html("Medium");
			$("#passwordstrength").css("color","orange");
		}
	})

	$("#usertype").change(function(){
		if($(this).val()=="producer"){
			$(this).siblings("#producertype").show();
			$("#produceerinfo").show();
			$("#address").html("Studio Address:");
		}else{
			$(this).siblings("#producertype").hide();
			$("#produceerinfo").hide();
			$("#address").html("Address:");
		}
	})

	$("#bdate,#amka").change(function(){
		var datestr=$("#bdate").val();
		var parsed=datestr.split("-");
		var final=parsed[2]+parsed[1]+parsed[0].slice(2,4);

		if(final!=$("#amka").val().slice(0,6)){
			$("#amkadatemiss").show();
		}else{
			$("#amkadatemiss").hide();
		}

		// console.log($("#amka").val().slice(0,6));
	})

	$("#eula").click(function(){
		if(!(this.checked)){
			$("#formsubmit").prop("disabled",true);
			$("#eulaunchecked").show();
		}else{
			$("#formsubmit").prop("disabled",false);
			$("#eulaunchecked").hide();
		}
	})
});