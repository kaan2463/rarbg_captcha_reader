package com.khan.captchareader.controller;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.util.Base64;
import java.util.Map;

import javax.imageio.ImageIO;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.khan.captchareader.rarbgcaptcha.RarBGCaptchaReader;

@Controller
@RequestMapping("captcha")
public class CaptchaController {
	private static long countCaptcha = 0;
	private RarBGCaptchaReader rarBGCaptchaReader = new RarBGCaptchaReader();

	@RequestMapping(value = "imageStringBase64POST", method = RequestMethod.POST)
	public @ResponseBody String helloposre(@RequestBody Map<String, String> objectMap) {
		String captchaBase64String = objectMap.get("imageString");

		byte[] imageBytes = Base64.getDecoder().decode(captchaBase64String);

		ByteArrayInputStream bis = new ByteArrayInputStream(imageBytes);
		BufferedImage image;
		String captcha = "";
		try {
			image = ImageIO.read(bis);
			bis.close();
			File outputfile = new File("/home/khan/Desktop/captcha/captcha" + countCaptcha + ".png");
			ImageIO.write(image, "png", outputfile);
			captcha = rarBGCaptchaReader.readCaptha("/home/khan/Desktop/captcha/captcha" + countCaptcha + ".png");
			System.out.println("captcha" + countCaptcha + ".png");
			countCaptcha++;
		} catch (Exception e) {
			e.printStackTrace();
		}
		// write the image to a file
		return captcha;
	}
}
