// Send a message containing the page details back to the event page
chrome.runtime.sendMessage({
    'imageString': getCaptchaImageAsBase64()
});

function getCaptchaImageAsBase64(){
    var imgTag = document.getElementsByTagName('img')[1];
    var canvas = document.createElement('canvas'),
    ctx = canvas.getContext('2d');
    canvas.height = imgTag.naturalHeight;
    canvas.width = imgTag.naturalWidth;
    //ctx.fillStyle = "rgb(0, 0, 0)";
    //ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.drawImage(imgTag, 0, 0);
    /**var idata = ctx.getImageData(0,0,canvas.width,canvas.height);
    var pixels = idata.data;
    pixels = pixels.filter(function(value,index){return (index+1)%4!=0;});
    idata.data=pixels;
    ctx.putImageData(idata,canvas.width,canvas.height);
    //ctx.drawImage(imgTag, 0, 0);
*/
    // Unfortunately, we cannot keep the original image type, so all images will be converted to PNG
    // For this reason, we cannot get the original Base64 string 
    var uri = canvas.toDataURL('image/png'),
    b64 = uri.replace(/^data:image.+;base64,/, '');
    
    return ""+b64;
}