function selectDeviceType(type) {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/modo?modo=" + type, true);
  xhttp.send();

  if (type === "1") {
    location.href = "./alexa.html";
  } else if (type === "2") {
    location.href = "./google.html";
  } else if (type === "3") {
    location.href = "./brokermqtt.html?env=homeassistant";
  } else if (type === "4") {
    location.href = "./brokermqtt.html?env=nodered";
  }
}

function selectMqttBroker(server, port, username, password) {
  const urlParams = new URLSearchParams(window.location.search);
  const env = urlParams.get("env");
  location.href = env + ".html";
}
