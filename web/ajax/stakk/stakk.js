function createXmlHttpRequest() {
    var xmlhttp = false;
    if( window.XMLHttpRequest) {
        xmlhttp = new XMLHttpRequest();
    } else if(window.ActiveXObject) {
        try {
            xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
        } catch(e) {
            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
    }
    return xmlhttp;
}
var oldquery = "";
var xmlhttp = 0;

function peekQuery () {

    if (! xmlhttp) xmlhttp = createXmlHttpRequest();

    if (! xmlhttp || xmlhttp.readyState == 1 || 
            xmlhttp.readyState == 2 || xmlhttp.readyState == 3){
        return; 
    }

    var result  = document.getElementById("result");
    var textbox = document.getElementById('query');
    var query   = encodeURI(textbox.value);

    if (query == "") {
        result.style.display = "none";
    } else if (oldquery != query) {
        xmlhttp.open("GET", "/api?query=" + query, true);
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                result.style.display = "block";
                result.innerHTML = xmlhttp.responseText;
            }
        }
        xmlhttp.send(null)
    }
    oldquery = query;
}
function keyCode(e) {
    if(document.all)
        return e.keyCode;
    else if(document.getElementById)
        return (e.keyCode)? e.keyCode: e.charCode;
    else if(document.layers)
        return e.which;
}

function check(e) {
    key = keyCode(e);
    if (key == 32) {
        peekQuery();
    }
}

onload = function () { setInterval("peekQuery()", 800); }

