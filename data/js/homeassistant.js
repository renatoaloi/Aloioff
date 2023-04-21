function getField(fieldName, buttonName) {
  document.getElementById(fieldName).disabled = true;
  document.getElementById(buttonName).disabled = true;
  setTimeout(() => {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        if (fieldName === "configTopic") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[0];
        } else if (fieldName === "commandTopic") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[1];
        } else if (fieldName === "statusTopic") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[2];
        } else if (fieldName === "deviceClass") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[3];
        } else if (fieldName === "payloadOn") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[4];
        } else if (fieldName === "payloadOff") {
          document.getElementById(fieldName).value =
            this.responseText.split("|")[5];
        }
        document.getElementById(fieldName).disabled = false;
        document.getElementById(buttonName).disabled = false;
      }
    };
    xhttp.open("GET", "/homeassistant/state", true);
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
    xhttp.onreadystatechange = function () {
      console.log(this.responseText);
      if (this.readyState == 4 && this.status == 200) {
        location.href = "wifi.html";
      }
    };
    var fieldValue1 = document.getElementById(fieldName1).value; // configTopic
    var fieldValue2 = document.getElementById(fieldName2).value; // commandTopic
    var fieldValue3 = document.getElementById(fieldName3).value; // statusTopic
    var fieldValue4 = document.getElementById(fieldName4).value; // deviceClass
    var fieldValue5 = document.getElementById(fieldName5).value; // payloadOn
    var fieldValue6 = document.getElementById(fieldName6).value; // payloadOff
    var urlParams2 =
      "/homeassistant/config?" +
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
