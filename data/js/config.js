
function hideMessage() {
    setTimeout(function () {
        document.getElementById('msg').style.display = 'none';
    }, 2000);
}

function setData(responseText) {
    document.getElementById('nomeDispositivo').value = responseText;
    document.getElementById('nomeDispositivo').disabled = false;
    document.getElementById('salvar').disabled = false;
}

function loadData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            setData(this.responseText);
        }
    }
    xhttp.open("GET", "/dispositivo/state", true);
    xhttp.send();
}

function sendData() {
    document.getElementById('nomeDispositivo').disabled = true;
    document.getElementById('salvar').disabled = true;
    var form = document.getElementById("formDevice");
    var valorToSend = document.getElementById('nomeDispositivo').value;
    var action = form.getAttribute("action") + "?nomeDispositivo=" + valorToSend;
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
    document.getElementById('nomeDispositivo').disabled = true;
    document.getElementById('salvar').disabled = true;
    loadData();
};