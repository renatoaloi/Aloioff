function hideMessage() {
    setTimeout(function () {
        document.getElementById('msg').style.display = 'none';
    }, 2000);
}

function sendReset() {
    var form = document.getElementById("formReset");
    var action = form.getAttribute("action");
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById('msg').style.display = 'block';
            document.getElementById('msg').style.color = 'green';
            document.getElementById('msg').innerText = "Reset efetuado com sucesso!";
            hideMessage();
        }
    };
    xhr.open('GET', action, true);
    xhr.send();
}

window.onload = function (event) {
    document.getElementById('msg').style.display = 'none';
};