function hideMessage() {
    setTimeout(function () {
        document.getElementById('msg').style.display = 'none';
    }, 2000);
}

function sendLigar() {
    sendStatus("formLigar", "0", "Ligado com sucesso!");
}

function sendDesligar() {
    sendStatus("formDesligar", "1", "Desligado com sucesso!");
}

function sendStatus(formName, status, msg) {
    var form = document.getElementById(formName);
    var action = form.getAttribute("action") + "?status=" + status;
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById('msg').style.display = 'block';
            document.getElementById('msg').style.color = 'green';
            document.getElementById('msg').innerText = msg;
            hideMessage();
        }
    };
    xhr.open('GET', action, true);
    xhr.send();
}

window.onload = function (event) {
    document.getElementById('msg').style.display = 'none';
};