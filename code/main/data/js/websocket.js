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
      console.log("added Hide & Seek buttons");
      document.getElementById("playhidenseek").addEventListener("click", function() { connection.send('M2'); });
      break;
    case "Greg Says":
      console.log("added Greg Says buttons");
      document.getElementById("playgregsays").addEventListener("click", function() { connection.send('M3');});
      break;
    case "Visualise":
      console.log("added Visualise buttons");
      document.getElementById("playvisualise").addEventListener("click", function() { connection.send('M4'); });
      break;
  }
}

function sendJson(object) {
  console.log(object);
  connection.send(object);
}
