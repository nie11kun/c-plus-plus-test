#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include "math.h"
#include "BMPPic.h"
#include <iostream>

using namespace std;

void main()
{
	BMPPic bmpPic;

	/*
	const int weight = 1080, height = 300;

	struct {
		char r;
		char g;
		char b;
	} pRGB[height][weight];

	memset(pRGB, 0, sizeof(pRGB)); // Fill block of memory string.h

	for (int j = 0; j < weight; j++) {
		int i = sin(j * 3.14 / 180) * height / 2 + height / 2;
		pRGB[i][j].r = 0xbb;
		pRGB[i][j].g = 0xff;
		pRGB[i][j].b = 0xaa;
	}

	bmpPic.generateBmp((char*)pRGB, weight, height, (char*)"D:\\rgb.bmp");
	*/

	int height;
	int width;
	FILE *fpbmp = fopen("picture//bmp.bmp", "r+");
	if (fpbmp == NULL)
	{
		printf("Open mbp failed!!!\n");
	}

	//bmpPic.bmpWidthHeight(fpbmp, width, height);
	bmpPic.readBmp(fpbmp);

	//cin.ignore();
	//cin.get();
}

