/*
 * CodeLetter.h
 *
 *  Created on: Jul 2, 2020
 *      Author: khan
 */

#ifndef DATA_STRUCTURES_RARBGLETTER_H_
#define DATA_STRUCTURES_RARBGLETTER_H_
#include <stdlib.h>
class CodeLetter {
public:
	int **code_char_mat;
	int sz_arr[32];
	char character_arr[32] = { '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
			'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'M', 'N', 'O', 'P', 'Q',
			'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	int n2[10] = { 5, 4, 6, 7, 7, 7, 8, 9, 7, 2 };
	int n3[9] = { 3, 3, 4, 6, 6, 6, 8, 12, 7 };
	int n4[11] = { 3, 4, 4, 5, 5, 4, 4, 16, 16, 2, 2 };
	int n5[9] = { 9, 10, 6, 6, 6, 6, 6, 9, 6 };
	int n6[10] = { 7, 11, 6, 6, 6, 6, 6, 7, 10, 4 };
	int n7[10] = { 2, 3, 5, 6, 6, 6, 6, 6, 5, 3 };
	int n8[10] = { 8, 13, 8, 6, 6, 6, 6, 8, 13, 8 };
	int n9[10] = { 4, 10, 6, 6, 6, 6, 6, 5, 11, 7 };
	int a[13] = { 2, 5, 6, 7, 8, 7, 5, 8, 8, 6, 6, 4, 1 };
	int b[10] = { 16, 16, 6, 6, 6, 6, 6, 8, 13, 8 };
	int c[12] = { 6, 10, 6, 4, 3, 4, 4, 4, 4, 4, 4, 4 };
	int d[12] = { 16, 16, 4, 4, 4, 4, 4, 3, 4, 6, 10, 6 };
	int e[9] = { 16, 16, 6, 6, 6, 6, 6, 6, 6 };
	int f[9] = { 16, 16, 4, 4, 4, 4, 4, 4, 4 };
	int g[12] = { 6, 10, 6, 4, 3, 4, 4, 6, 6, 6, 9, 9 };
	int h[11] = { 16, 16, 2, 2, 2, 2, 2, 2, 2, 16, 16 };
	int i[6] = { 4, 4, 16, 16, 4, 4 };
	int k[11] = { 16, 16, 2, 3, 6, 6, 6, 7, 7, 3, 1 };
	int m[13] = { 16, 16, 3, 4, 4, 5, 4, 3, 4, 4, 3, 16, 16 };
	int n[11] = { 16, 16, 3, 4, 4, 4, 3, 4, 4, 16, 16 };
	int o[14] = { 6, 10, 6, 4, 4, 4, 4, 4, 4, 4, 4, 6, 10, 6 };
	int p[10] = { 16, 16, 4, 4, 4, 4, 4, 4, 7, 4 };
	int q[14] = { 6, 10, 6, 4, 3, 4, 4, 4, 6, 7, 6, 9, 13, 8 };
	int r[12] = { 16, 16, 4, 4, 4, 5, 6, 7, 10, 8, 2, 1 };
	int s[10] = { 5, 9, 6, 7, 6, 6, 6, 6, 9, 4 };
	int t[12] = { 2, 2, 2, 2, 2, 16, 16, 2, 2, 2, 2, 2 };
	int u[11] = { 13, 14, 2, 2, 2, 2, 2, 2, 2, 15, 13 };
	int v[13] = { 2, 5, 7, 7, 6, 5, 3, 6, 6, 6, 6, 4, 1 };
	int w[19] = { 1, 5, 8, 8, 7, 4, 7, 6, 6, 4, 6, 6, 7, 4, 5, 7, 8, 6, 2 };
	int x[12] = { 1, 4, 8, 6, 7, 6, 4, 8, 6, 7, 6, 2 };
	int y[12] = { 1, 3, 4, 3, 4, 10, 10, 3, 3, 4, 3, 1 };
	int z[11] = { 2, 6, 7, 8, 8, 8, 8, 7, 7, 6, 4 };
	CodeLetter() {
		code_char_mat = (int**) malloc(sizeof(int*) * 32);
		init_code_char_mat(0, code_char_mat[0], n2, 10);
		init_code_char_mat(1, code_char_mat[1], n3, 9);
		init_code_char_mat(2, code_char_mat[2], n4, 11);
		init_code_char_mat(3, code_char_mat[3], n5, 9);
		init_code_char_mat(4, code_char_mat[4], n6, 10);
		init_code_char_mat(5, code_char_mat[5], n7, 10);
		init_code_char_mat(6, code_char_mat[6], n8, 10);
		init_code_char_mat(7, code_char_mat[7], n9, 10);
		init_code_char_mat(8, code_char_mat[8], a, 13);
		init_code_char_mat(9, code_char_mat[9], b, 10);
		init_code_char_mat(10, code_char_mat[10], c, 12);
		init_code_char_mat(11, code_char_mat[11], d, 12);
		init_code_char_mat(12, code_char_mat[12], e, 9);
		init_code_char_mat(13, code_char_mat[13], f, 9);
		init_code_char_mat(14, code_char_mat[14], g, 12);
		init_code_char_mat(15, code_char_mat[15], h, 11);
		init_code_char_mat(16, code_char_mat[16], i, 6);
		init_code_char_mat(17, code_char_mat[17], k, 11);
		init_code_char_mat(18, code_char_mat[18], m, 13);
		init_code_char_mat(19, code_char_mat[19], n, 11);
		init_code_char_mat(20, code_char_mat[20], o, 14);
		init_code_char_mat(21, code_char_mat[21], p, 10);
		init_code_char_mat(22, code_char_mat[22], q, 14);
		init_code_char_mat(23, code_char_mat[23], r, 12);
		init_code_char_mat(24, code_char_mat[24], s, 10);
		init_code_char_mat(25, code_char_mat[25], t, 12);
		init_code_char_mat(26, code_char_mat[26], u, 11);
		init_code_char_mat(27, code_char_mat[27], v, 13);
		init_code_char_mat(28, code_char_mat[28], w, 19);
		init_code_char_mat(29, code_char_mat[29], x, 12);
		init_code_char_mat(30, code_char_mat[30], y, 12);
		init_code_char_mat(31, code_char_mat[31], z, 11);

	}
	void init_code_char_mat(int index, int *&piece, int *arr, int sz) {
		piece = (int*) malloc(sizeof(int) * sz);
		for (int i = 0; i < sz; i++) {
			piece[i] = arr[i];
		}
		sz_arr[index] = sz;
	}
	char* captcha_characters(int *arr, int sz) {
		int index = 0;
		int buffer_index = 0;
		char *buffer = new char[10];
		for (int i = 0; index < sz && i < sz; i++) {
			for (int j = 0; j < 32; j++) {
				if (compare_array(arr, index, code_char_mat[j], sz,
						sz_arr[j])) {
					buffer[buffer_index] = character_arr[j];
					buffer_index++;
					index += sz_arr[j];
					break;
				}

			}
		}
		return buffer;
	}

//private:
	/*return index of match begin*/
	static bool compare_array(int *arr1, int first, int *arr2, int sz1,
			int sz2) {
		for (int i = first; i < sz2 + first; i++) {
			if (arr1[i] != arr2[i - first]) {
				return false;
			}
		}
		return true;
	}
} codeLetter;

#endif /* DATA_STRUCTURES_RARBGLETTER_H_ */
