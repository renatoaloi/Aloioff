function resetDevice(buttonName) {
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/reset", true);
    xhttp.send();
    alert("Dispositivo reiniciado com sucesso!");
  }, 1000);
}
