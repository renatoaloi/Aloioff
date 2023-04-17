function getField(fieldName, buttonName) {
  document.getElementById(fieldName).disabled = true;
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        if (fieldName === "wifiSSID") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[0];
        } else {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[1];
        }
        document.getElementById(fieldName).disabled = false;
        document.getElementById(buttonName).disabled = false;
      }
    };
    xhttp.open("GET", "/wifi/state", true);
    xhttp.send();
  }, 1000);
}

function saveField(fieldName1, fieldName2, buttonName) {
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        location.href = "reset.html";
      }
    };
    var fieldValue1 = document.getElementById(fieldName1).value;
    var fieldValue2 = document.getElementById(fieldName2).value;
    var urlParams =
      "/wifi/config?" +
      fieldName1 +
      "=" +
      fieldValue1 +
      "&" +
      fieldName2 +
      "=" +
      fieldValue2;

    xhttp.open("GET", urlParams, true);
    xhttp.send();
  }, 1000);
}
