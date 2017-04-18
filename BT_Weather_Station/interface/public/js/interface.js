var devices = [];

$.get('/devices', function( json_data ) {
  devices = json_data;
});

$(document).ready(function() {

  function updateSensors() {

    // Update light level and status
    $.get('/' + devices[0].name + '/temperature', function(json_data) {

      $("#temperatureDisplay").html("Temperature: " + json_data.temperature + "°C");

      // Update status
      if (json_data.connected == 1){
        $("#status").html("Station Online");
        $("#status").css("color","green");
      }
      else {
        $("#status").html("Station Offline");
        $("#status").css("color","red");
      }

    });
  }

  setInterval(updateSensors, 5000);
});
