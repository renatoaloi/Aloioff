
function hideMessage() {
    setTimeout(function () {
        document.getElementById('msg').style.display = 'none';
    }, 2000);
}

function setData(responseText) {
    const responseSplit = responseText.split('|');
    if (responseSplit.length == 2) {
        var ssid = responseSplit[0];
        var password = responseSplit[1];
        document.getElementById('ssid').value = ssid;
        document.getElementById('password').value = password;
        document.getElementById('ssid').disabled = false;
        document.getElementById('password').disabled = false;
        document.getElementById('salvar').disabled = false;
    }
}

function loadData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            setData(this.responseText);
        }
    }
    xhttp.open("GET", "/wifi/state", true);
    xhttp.send();
}

function sendData() {
    document.getElementById('ssid').disabled = true;
    document.getElementById('password').disabled = true;
    document.getElementById('salvar').disabled = true;
    var form = document.getElementById("formWifi");
    var ssid = document.getElementById('ssid').value;
    var password = document.getElementById('password').value;
    var action = form.getAttribute("action") + "?ssid=" + ssid + "&password=" + password;
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById('msg').style.display = 'block';
            document.getElementById('msg').style.color = 'green';
            document.getElementById('msg').innerText = "Dados gravados com sucesso!";
            hideMessage();
            setData(this.responseText);
        }
    };
    xhr.open('GET', action, true);
    xhr.send();
}

window.onload = function (event) {
    document.getElementById('msg').style.display = 'none';
    document.getElementById('ssid').disabled = true;
    document.getElementById('password').disabled = true;
    document.getElementById('salvar').disabled = true;
    loadData();
};
