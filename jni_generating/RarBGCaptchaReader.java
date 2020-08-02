package com.khan.captchareader.rarbgcaptcha;
public class RarBGCaptchaReader{
  static{
    System.loadLibrary("rarbgcaptcha");
  }
/*
* path : path of rarbg png captcha file
**/
  public native String readCaptha(String path);
  
  public static void main(String[] args){
  	System.out.println("HELLO");
  	System.out.println(new RarBGCaptchaReader().readCaptha("/home/khan/Desktop/captcha/asd.png"));
  }
}
