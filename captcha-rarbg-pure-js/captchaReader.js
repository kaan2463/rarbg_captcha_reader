document.addEventListener('DOMContentLoaded', function () {

    chrome.tabs.executeScript(null, {
        file: "content.js"
    });

    chrome.runtime.onMessage.addListener(function (message) {
        // Call the callback function
        // Image string as base64 format (message)
        createWindow(message);
    });


}, false);

//imgSrc:imgSrc,aHref:aHref

function fillInputArea(captchaString) {
    chrome.tabs.executeScript({
        code: "document.getElementById('solve_string').value = '" + captchaString + "'; document.getElementById('button_submit').style.display='block';"
    });
}

function createWindow(message) {
    var imageString = message.imageString;
    fillInputArea(imageString);
}