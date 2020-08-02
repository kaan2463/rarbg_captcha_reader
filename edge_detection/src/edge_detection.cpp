//============================================================================
// Name        : edge_detection.cpp
// Author      : Khan
// Version     : 1
// Copyright   : There is no copyright :)
// Description : Edge detection in C++, Ansi-style. I wish I could play a guitar!
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <png.h>
#include <dirent.h>

#include "data_structures/RarBGLetter.h"
using namespace std;

int sign(int x) {
	if (x < 90) {
		return 0;
	} else
		return 255;
}
//TODO: useless, creating ppm image
void create_char_image(int x_first, int x_last, int y_first, int y_last,
		int **matrix, int height, int width, string prefix) {
	string name = prefix + ".ppm";
	FILE *fppm = fopen(name.c_str(), "wb");
	(void) fprintf(fppm, "P3\n%d %d\n255\n", x_last - x_first + 1,
			y_last - y_first + 1);
	for (int i = y_first; i <= y_last; i++) {
		for (int j = x_first; j <= x_last; j++) {
			fprintf(fppm, "%d %d %d\n", matrix[i][j], matrix[i][j],
					matrix[i][j]);
		}
	}
	(void) fclose(fppm);
}

static unsigned int component(png_const_bytep row, png_uint_32 x,
		unsigned int c, unsigned int bit_depth, unsigned int channels) {
	/* PNG images can be up to 2^31 pixels wide, but this means they can be up to
	 * 2^37 bits wide (for a 64-bit pixel - the largest possible) and hence 2^34
	 * bytes wide.  Since the row fitted into memory, however, the following must
	 * work:
	 */
	png_uint_32 bit_offset_hi = bit_depth * ((x >> 6) * channels);
	png_uint_32 bit_offset_lo = bit_depth * ((x & 0x3f) * channels + c);

	row = (png_const_bytep) (((const png_byte (*)[8]) row) + bit_offset_hi);
	row += bit_offset_lo >> 3;
	bit_offset_lo &= 0x07;

	/* PNG pixels are packed into bytes to put the first pixel in the highest
	 * bits of the byte and into two bytes for 16-bit values with the high 8 bits
	 * first, so:
	 */
	switch (bit_depth) {
	case 1:
		return (row[0] >> (7 - bit_offset_lo)) & 0x01;
	case 2:
		return (row[0] >> (6 - bit_offset_lo)) & 0x03;
	case 4:
		return (row[0] >> (4 - bit_offset_lo)) & 0x0f;
	case 8:
		return row[0];
	case 16:
		return (row[0] << 8) + row[1];
	default:
		/* This should never happen; it indicates a bug in this program or in
		 * libpng itself:
		 */
		fprintf(stderr, "pngpixel: invalid bit depth %u\n", bit_depth);
		exit(1);
	}
}

static void print_pixel(png_structp png_ptr, png_infop info_ptr,
		png_const_bytep row, png_uint_32 x) {
	unsigned int bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	switch (png_get_color_type(png_ptr, info_ptr)) {
	case PNG_COLOR_TYPE_GRAY:
		printf("GRAY %u\n", component(row, x, 0, bit_depth, 1));
		return;
	case PNG_COLOR_TYPE_PALETTE: {
		int index = component(row, x, 0, bit_depth, 1);
		png_colorp palette = NULL;
		int num_palette = 0;

		if ((png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette) &
		PNG_INFO_PLTE) && num_palette > 0 && palette != NULL) {
			png_bytep trans_alpha = NULL;
			int num_trans = 0;
			if ((png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans,
			NULL) & PNG_INFO_tRNS) && num_trans > 0 && trans_alpha != NULL)
				printf("INDEXED %u = %d %d %d %d\n", index, palette[index].red,
						palette[index].green, palette[index].blue,
						index < num_trans ? trans_alpha[index] : 255);

			else
				/* no transparency */
				printf("INDEXED %u = %d %d %d\n", index, palette[index].red,
						palette[index].green, palette[index].blue);
		}

		else
			printf("INDEXED %u = invalid index\n", index);
	}
		return;

	case PNG_COLOR_TYPE_RGB:
		printf("RGB %u %u %u\n", component(row, x, 0, bit_depth, 3),
				component(row, x, 1, bit_depth, 3),
				component(row, x, 2, bit_depth, 3));
		return;

	case PNG_COLOR_TYPE_GRAY_ALPHA:
		printf("GRAY+ALPHA %u %u\n", component(row, x, 0, bit_depth, 2),
				component(row, x, 1, bit_depth, 2));
		return;

	case PNG_COLOR_TYPE_RGB_ALPHA:
		printf("RGBA %u %u %u %u\n", component(row, x, 0, bit_depth, 4),
				component(row, x, 1, bit_depth, 4),
				component(row, x, 2, bit_depth, 4),
				component(row, x, 3, bit_depth, 4));
		return;

	default:
		png_error(png_ptr, "pngpixel: invalid color type");
	}
}

string extract_letters_in_file(FILE *fp) {
	png_structp pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
	NULL, NULL);
	png_infop pnginfo = png_create_info_struct(pngptr);
	png_set_palette_to_rgb(pngptr);
	png_init_io(pngptr, fp);
	png_bytepp rows;
	png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
	rows = png_get_rows(pngptr, pnginfo);
	int HEIGHT = png_get_image_height(pngptr, pnginfo);
	int WIDTH = png_get_image_width(pngptr, pnginfo);
	//------------ppm----------
	int y_hist[HEIGHT] = { };
	int x_hist[WIDTH] = { };
	int **image_matrix = (int**) malloc(sizeof(int*) * HEIGHT); //[HEIGHT][WIDTH] = { };

	for (int i = 0; i < HEIGHT; i++) {
		image_matrix[i] = (int*) malloc(sizeof(int) * WIDTH);
	}

	unsigned int bit_depth = png_get_bit_depth(pngptr, pnginfo);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int r = component(rows[i], j, 0, bit_depth, 4);
			int g = component(rows[i], j, 1, bit_depth, 4);
			int b = component(rows[i], j, 2, bit_depth, 4);
			int grey = (r * 299u + g * 586u + b * 114u) / 1000;
			image_matrix[i][j] = sign(grey);
			if (sign(grey) == 0) {
				y_hist[i] += 1;
				x_hist[j] += 1;
			}
		}
	}
	//-----------
	int countHist = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (x_hist[i] != 0) {
			countHist++;
		}
	}
	int compArr[countHist];
	countHist = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (x_hist[i] != 0) {
			compArr[countHist] = x_hist[i];
			countHist++;
		}
	}
	string captcha(codeLetter.captcha_characters(compArr, countHist));

	return captcha;

}

string readRARBGCaptchaFile(string path) {
	FILE *fp = fopen(path.c_str(), "r");
	string captchaVal = extract_letters_in_file(fp);
	return captchaVal;
}

void create_letters(FILE *fp, string prefix) {
	png_structp pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
	NULL, NULL);
	png_infop pnginfo = png_create_info_struct(pngptr);

	png_set_palette_to_rgb(pngptr);
	png_init_io(pngptr, fp);
	png_bytepp rows;
	png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
	rows = png_get_rows(pngptr, pnginfo);
	int HEIGHT = png_get_image_height(pngptr, pnginfo);
	int WIDTH = png_get_image_width(pngptr, pnginfo);
	//------------ppm----------
	int y_hist[HEIGHT] = { };
	int x_hist[WIDTH] = { };
	int **image_matrix = (int**) malloc(sizeof(int*) * HEIGHT); //[HEIGHT][WIDTH] = { };

	for (int i = 0; i < HEIGHT; i++) {
		image_matrix[i] = (int*) malloc(sizeof(int) * WIDTH);
	}

	unsigned int bit_depth = png_get_bit_depth(pngptr, pnginfo);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int r = component(rows[i], j, 0, bit_depth, 4);
			int g = component(rows[i], j, 1, bit_depth, 4);
			int b = component(rows[i], j, 2, bit_depth, 4);
			int grey = (r * 299u + g * 586u + b * 114u) / 1000;
			image_matrix[i][j] = sign(grey);
			if (sign(grey) == 0) {
				y_hist[i] += 1;
				x_hist[j] += 1;
			}
		}
	}

	//-----------
	int countHist = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (x_hist[i] != 0) {
			countHist++;
		}
	}

	create_char_image(0, WIDTH - 1, 0, HEIGHT - 1, image_matrix, HEIGHT, WIDTH,
			prefix);

}

int main(int argc, char **argv) {
	cout << readRARBGCaptchaFile("/home/khan/Desktop/captcha/captcha8.png")
			<< endl;
	if (true) {
		return 0;
	}
//aaa
	//captcha0
	FILE *ff = fopen("/home/khan/Desktop/captcha/captcha8.png", "r");
	create_letters(ff, "captcha9v2");
	if (true) {
		return 0;
	}
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("/home/khan/Desktop/captcha")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			string str_name(ent->d_name);
			string::size_type loc = str_name.find(".png");
			if (loc != string::npos) {
				string path("/home/khan/Desktop/captcha/");
				path += str_name;
				FILE *fp = fopen(path.c_str(), "r");
				create_letters(fp, str_name);
				cout << path.c_str() << endl;
			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("");
		return EXIT_FAILURE;
	}

	return 0;
}
