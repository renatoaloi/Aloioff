
function hideMessage() {
    setTimeout(function () {
        document.getElementById('msg').style.display = 'none';
    }, 2000);
}

function setData(responseText) {
    if (responseText === "1") {
        document.getElementById('modoAlexa').checked = true;
        document.getElementById('modoSmartphone').checked = false;
    }
    else if (responseText === "2") {
        document.getElementById('modoAlexa').checked = false;
        document.getElementById('modoSmartphone').checked = true;
    }
    else {
        document.getElementById('modoAlexa').checked = true;
        document.getElementById('modoSmartphone').checked = false;
    }
    document.getElementById('modoAlexa').disabled = false;
    document.getElementById('modoSmartphone').disabled = false;
    document.getElementById('salvar').disabled = false;
}

function loadData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            setData(this.responseText);
        }
    }
    xhttp.open("GET", "/modo/state", true);
    xhttp.send();
}

function sendData() {
    document.getElementById('salvar').disabled = true;

    var modoOperacao = "0";
    if (document.getElementById('modoAlexa').checked) {
        modoOperacao = "1";
    }
    else if (document.getElementById('modoSmartphone').checked) {
        modoOperacao = "2";
    }

    var form = document.getElementById("formModo");
    var action = form.getAttribute("action") + "?modo=" + modoOperacao;
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
    document.getElementById('modoAlexa').disabled = true;
    document.getElementById('modoSmartphone').disabled = true;
    document.getElementById('salvar').disabled = true;
    loadData();
};
