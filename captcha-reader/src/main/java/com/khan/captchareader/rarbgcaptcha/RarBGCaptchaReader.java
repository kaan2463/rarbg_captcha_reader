package com.khan.captchareader.rarbgcaptcha;

public class RarBGCaptchaReader {
	static {
		System.loadLibrary("rarbgcaptcha");
	}

	/*
	 * path : path of rarbg png captcha file
	 **/
	public native String readCaptha(String path);
}
