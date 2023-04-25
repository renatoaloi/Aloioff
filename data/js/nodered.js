function getField(fieldName, buttonName) {
  document.getElementById(fieldName).disabled = true;
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        if (fieldName === "commandTopic") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[0];
        } else if (fieldName === "payloadOn") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[1];
        } else if (fieldName === "payloadOff") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[2];
        }
        document.getElementById(fieldName).disabled = false;
        document.getElementById(buttonName).disabled = false;
      }
    };
    xhttp.open("GET", "/nodered/state", true);
    xhttp.send();
  }, 1000);
}

function saveField(fieldName1, fieldName2, fieldName3, buttonName) {
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        location.href = "wifi.html";
      }
    };
    var fieldValue1 = document.getElementById(fieldName1).value; // commandTopic
    var fieldValue2 = document.getElementById(fieldName2).value; // payloadOn
    var fieldValue3 = document.getElementById(fieldName3).value; // payloadOff
    var urlParams2 =
      "/nodered/config?" +
      fieldName1 +
      "=" +
      fieldValue1 +
      "&" +
      fieldName2 +
      "=" +
      fieldValue2 +
      "&" +
      fieldName3 +
      "=" +
      fieldValue3;

    xhttp.open("GET", urlParams2, true);
    xhttp.send();
  }, 1000);
}
