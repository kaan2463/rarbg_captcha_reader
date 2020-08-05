// Send a message containing the page details back to the event page
chrome.runtime.sendMessage({
    'imageString': getCaptchaImageAsBase64()
});







function getCaptchaImageAsBase64() {
    //----------------VARIABLES------------------
    //FIXME: These variables would be global constant
    var character_arr = [
        '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];

    var n2 = [5, 4, 6, 7, 7, 7, 8, 9, 7, 2];
    var n3 = [3, 3, 4, 6, 6, 6, 8, 12, 7];
    var n4 = [3, 4, 4, 5, 5, 4, 4, 16, 16, 2, 2];
    var n5 = [9, 10, 6, 6, 6, 6, 6, 9, 6];
    var n6 = [7, 11, 6, 6, 6, 6, 6, 7, 10, 4];
    var n7 = [2, 3, 5, 6, 6, 6, 6, 6, 5, 3];
    var n8 = [8, 13, 8, 6, 6, 6, 6, 8, 13, 8];
    var n9 = [4, 10, 6, 6, 6, 6, 6, 5, 11, 7];
    var a = [2, 5, 6, 7, 8, 7, 5, 8, 8, 6, 6, 4, 1];
    var b = [16, 16, 6, 6, 6, 6, 6, 8, 13, 8];
    var c = [6, 10, 6, 4, 3, 4, 4, 4, 4, 4, 4, 4];
    var d = [16, 16, 4, 4, 4, 4, 4, 3, 4, 6, 10, 6];
    var e = [16, 16, 6, 6, 6, 6, 6, 6, 6];
    var f = [16, 16, 4, 4, 4, 4, 4, 4, 4];
    var g = [6, 10, 6, 4, 3, 4, 4, 6, 6, 6, 9, 9];
    var h = [16, 16, 2, 2, 2, 2, 2, 2, 2, 16, 16];
    var i = [4, 4, 16, 16, 4, 4];
    var k = [16, 16, 2, 3, 6, 6, 6, 7, 7, 3, 1];
    var m = [16, 16, 3, 4, 4, 5, 4, 3, 4, 4, 3, 16, 16];
    var n = [16, 16, 3, 4, 4, 4, 3, 4, 4, 16, 16];
    var o = [6, 10, 6, 4, 4, 4, 4, 4, 4, 4, 4, 6, 10, 6];
    var p = [16, 16, 4, 4, 4, 4, 4, 4, 7, 4];
    var q = [6, 10, 6, 4, 3, 4, 4, 4, 6, 7, 6, 9, 13, 8];
    var r = [16, 16, 4, 4, 4, 5, 6, 7, 10, 8, 2, 1];
    var s = [5, 9, 6, 7, 6, 6, 6, 6, 9, 4];
    var t = [2, 2, 2, 2, 2, 16, 16, 2, 2, 2, 2, 2];
    var u = [13, 14, 2, 2, 2, 2, 2, 2, 2, 15, 13];
    var v = [2, 5, 7, 7, 6, 5, 3, 6, 6, 6, 6, 4, 1];
    var w = [1, 5, 8, 8, 7, 4, 7, 6, 6, 4, 6, 6, 7, 4, 5, 7, 8, 6, 2];
    var x = [1, 4, 8, 6, 7, 6, 4, 8, 6, 7, 6, 2];
    var y = [1, 3, 4, 3, 4, 10, 10, 3, 3, 4, 3, 1];
    var z = [2, 6, 7, 8, 8, 8, 8, 7, 7, 6, 4];

    var letters = [n2, n3, n4, n5, n6, n7, n8, n9, a, b, c, d, e, f, g, h, i, k, m, n, o, p, q, r, s, t, u, v, w, x, y, z];

    //---------------------------------------------------------



    var imgTag = document.getElementsByTagName('img')[1];
    var canvas = document.createElement('canvas'),
        ctx = canvas.getContext('2d');
    canvas.height = imgTag.naturalHeight;
    canvas.width = imgTag.naturalWidth;
    ctx.drawImage(imgTag, 0, 0);
    var data = ctx.getImageData(0, 0, canvas.width, canvas.height);
    var pixels = data.data;
    var height = data.height;
    var width = data.width;
    var xHist = [];
    var compArr = [];

    for (var i = 0; i < width; i++) {
        xHist[i] = 0;
    }

    for (var i = 0; i < height; i++) {
        for (var j = 0; j < width * 4; j += 4) {
            var r = pixels[i * width * 4 + j];
            var g = pixels[i * width * 4 + j + 1];
            var b = pixels[i * width * 4 + j + 2];
            var a = pixels[i * width * 4 + j + 3];
            var greyValue = (r * 299 + g * 586 + b * 114) / 1000;
            if (Math.floor(greyValue) < 90) {
                xHist[j / 4] = xHist[j / 4] + 1;
            }
        }
    }

    var index = 0;
    for (var i = 0; i < width; i++) {
        if (xHist[i] != 0) {
            compArr[index] = xHist[i];
            index++;
        }
    }


    var captchaString = "";

    var letterBegin = 0;
    var count = 0;
    while (count < 5) {
        for (var i = 0; i < character_arr.length; i++) {
            if (compare_array(letters[i], compArr.slice(letterBegin, letterBegin + letters[i].length))) {
                captchaString += character_arr[i];
                letterBegin += letters[i].length;
            }
        }
        count++;
    }


    return captchaString;
}

function compare_array(arr1, arr2) {
    if (arr1.length != arr2.length) {
        return false;
    }
    for (var i = 0; i < arr1.length; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}