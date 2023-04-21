function getField(fieldName, buttonName) {
  document.getElementById(fieldName).disabled = true;
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        if (fieldName === "feedName") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[0];
        } else if (fieldName === "mqttServer") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[1];
        } else if (fieldName === "mqttServerPort") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[2];
        } else if (fieldName === "mqttUsername") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[3];
        } else if (fieldName === "mqttPassword") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[4];
        }
        document.getElementById(fieldName).disabled = false;
        document.getElementById(buttonName).disabled = false;
      }
    };
    var url = "";
    if (fieldName === "deviceName") {
      url = "/dispositivo/state";
    } else {
      url = "/mqtt/state";
    }
    xhttp.open("GET", url, true);
    xhttp.send();
  }, 1000);
}

function saveField(
  fieldName1,
  fieldName2,
  fieldName3,
  fieldName4,
  fieldName5,
  fieldName6,
  buttonName
) {
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    var fieldValue1 = document.getElementById(fieldName1).value;
    var urlParams1 = "/dispositivo?" + fieldName1 + "=" + fieldValue1;
    xhttp.open("GET", urlParams1, true);
    xhttp.send();

    xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        const urlParams = new URLSearchParams(window.location.search);
        const env = urlParams.get("env");
        location.href = env + ".html";
      }
    };
    var fieldValue2 = document.getElementById(fieldName2).value; // feed
    var fieldValue3 = document.getElementById(fieldName3).value; // server
    var fieldValue4 = document.getElementById(fieldName4).value; // port
    var fieldValue5 = document.getElementById(fieldName5).value; // username
    var fieldValue6 = document.getElementById(fieldName6).value; // password
    var urlParams2 =
      "/mqtt/config?" +
      fieldName2 +
      "=" +
      fieldValue2 +
      "&" +
      fieldName3 +
      "=" +
      fieldValue3 +
      "&" +
      fieldName4 +
      "=" +
      fieldValue4 +
      "&" +
      fieldName5 +
      "=" +
      fieldValue5 +
      "&" +
      fieldName6 +
      "=" +
      fieldValue6;

    xhttp.open("GET", urlParams2, true);
    xhttp.send();
  }, 1000);
}
