var configBoxes = {};



// var configObj = JSON.parse(requirejs(['./config'])).config;

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
  configBoxes = document.getElementsByClassName("config")
  if(configBoxes.length>0){
    loadConfig();
  }

  switch (document.title) {
    case "Main Menu":
      console.log("added Main Menu buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      break;
    case "Emo Greg":
      console.log("added Idle buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      document.getElementById("playidle").addEventListener("click", function() { connection.send('M1'); });
      break;
    case "Hide & Seek":
      console.log("added Hide & Seek buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      document.getElementById("playhidenseek").addEventListener("click", function() { connection.send('M2'); });
      break;
    case "Greg Says":
      console.log("added Greg Says buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      document.getElementById("playgregsays").addEventListener("click", function() { connection.send('M3');});
      break;
    case "Greg Sings":
      console.log("added Greg Sings buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      document.getElementById("playgregsings").addEventListener("click", function() { connection.send('M4'); });
      break;
    case "Visualise":
      console.log("added Visualise buttons");
      document.getElementById("applyConfig").addEventListener("click", sendConfig);
      document.getElementById("playvisualise").addEventListener("click", function() { connection.send('M5'); });
      break;
  }
}

function loadConfig(){
  console.log("Loading Config");
  configObj = configObj.config;
  for(var i=0;i<configObj.length;i++){

    if(configObj[i].title == document.title){
      console.log(configObj[i]);
      for(var l=0;l<configObj[i].settings.length;l++){
        configBoxes[l].checked = configObj[i].settings[l];
      }
    }
  }
}

function sendConfig() {
  var config = "S";
  for(var i=0;i<configBoxes.length;i++){
    if(configBoxes[i].checked){
      config += "1"
    } else {
      config += "0"
    }
  }
  console.log(config);
  connection.send(config);
}
