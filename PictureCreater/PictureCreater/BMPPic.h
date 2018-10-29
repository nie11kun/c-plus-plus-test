#pragma once
#include<stdio.h>

class BMPPic
{
public:
	BMPPic();
	~BMPPic();
	bool generateBmp(char* pData, int width, int height, char * filename);
	void readBmp(FILE* filename);
	void bmpWidthHeight(FILE* fpbmp, int &width, int &height);
};

