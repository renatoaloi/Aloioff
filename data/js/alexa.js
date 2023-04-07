function getField(fieldName, buttonName) {
  document.getElementById(fieldName).disabled = true;
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById(fieldName).value = this.responseText;
        document.getElementById(fieldName).disabled = false;
        document.getElementById(buttonName).disabled = false;
      }
    };
    xhttp.open("GET", "/dispositivo/state", true);
    xhttp.send();
  }, 1000);
}

function saveField(fieldName, buttonName) {
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        location.href = "wifi.html";
      }
    };
    var fieldValue = document.getElementById(fieldName).value;
    var urlParams = "/dispositivo?" + fieldName + "=" + fieldValue;

    xhttp.open("GET", urlParams, true);
    xhttp.send();
  }, 1000);
}
