try{
  var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);

  connection.onopen = function () {
      connection.send('Connect ' + new Date());
  };
  connection.onerror = function (error) {
      console.log('WebSocket Error ', error);
  };
  connection.onmessage = function (e) {
      if(e.data[0]="W"){}
      else{console.log('Server: ', e.data);}
  };
  connection.onclose = function(){
      console.log('WebSocket connection closed');
  };
}
catch(err) {}


window.onload = init;
function init(){
  switch (document.title) {
    case "Hide & Seek":
      document.getElementById("playhidenseek").addEventListener("click", function() { sendJson( {type:"modechange", mode:2} ); });
      break;
    case "Grey Says":
      document.getElementById("playgregsays").addEventListener("click", function() { sendJson( {type:"modechange", mode:3} ); });
      break;
    case "Visualise":
      document.getElementById("playvisualise").addEventListener("click", function() { sendJson( {type:"modechange", mode:4} ); });
      break;
  }
}

function sendJson(object) {
  console.log(object);
  connection.sendJson(object);
}
