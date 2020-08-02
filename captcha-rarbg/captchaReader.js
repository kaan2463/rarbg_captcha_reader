document.addEventListener('DOMContentLoaded', function() {

        chrome.tabs.executeScript(null, {
            file: "content.js"
        });

        chrome.runtime.onMessage.addListener(function(message) {
            // Call the callback function
            // Image string as base64 format (message)
            createWindow(message);
        });


},false);

//imgSrc:imgSrc,aHref:aHref

function fillInputArea(captchaString){
    chrome.tabs.executeScript({
        code: "document.getElementById('solve_string').value = '"+captchaString+"'; document.getElementById('button_submit').style.display='block';"
      });
}

function createWindow(message){
    var imageString =message.imageString;
    var imageDiv = document.getElementById('imageDiv');
    var imgTag = document.createElement('img');
    imgTag.src = "data:image/png;base64,"+imageString;
    imageDiv.appendChild(imgTag);

    var pp = document.createElement('p');
    imageDiv.appendChild(pp);

    var captchaString = "";

    // send data (method:post)
    var xhr = new XMLHttpRequest();
    var url = "http://localhost:9090/captcha/imageStringBase64POST";
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            //var json = JSON.parse(xhr.responseText);
            captchaString=xhr.responseText;
            captchaString=captchaString.substring(0,5);
            console.log(captchaString);
            pp.innerHTML=captchaString;
            fillInputArea(captchaString);
            //console.log(json.email + ", " + json.password);
        }
    };
    var data = JSON.stringify({"imageString": imageString});
    xhr.send(data);
}