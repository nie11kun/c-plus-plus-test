#define _CRT_SECURE_NO_WARNINGS

#include "BMPPic.h"
#include "stdlib.h"
#include "stdio.h"
#include <fstream>

using namespace std;

BMPPic::BMPPic()
{
}

BMPPic::~BMPPic()
{
}

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short WORD;

#pragma pack(2) //2字节对齐
struct BMPFILEHEADER_T //BMP文件头（14字节）
{
	WORD    bfType;//文件类型，必须是0x424D,即字符“BM”
	DWORD   bfSize;//文件大小
	WORD    bfReserved1;//保留字
	WORD    bfReserved2;//保留字
	DWORD   bfOffBits;//从文件头到实际位图数据的偏移字节数
};

struct BMPINFOHEADER_T //3：位图信息头（40字节）
{
	DWORD      biSize;//信息头大小
	LONG       biWidth;//图像宽度
	LONG       biHeight;//图像高度
	WORD       biPlanes;//位平面数，必须为1
	WORD       biBitCount;//每像素位数
	DWORD      biCompression;//压缩类型
	DWORD      biSizeImage;//压缩图像大小字节数
	LONG       biXPelsPerMeter;//水平分辨率
	LONG       biYPelsPerMeter;//垂直分辨率
	DWORD      biClrUsed;//位图实际用到的色彩数
	DWORD      biClrImportant;//本位图中重要的色彩数
};

struct tagRGBQUAD  //颜色表
{
	char rgbBlue;//蓝色的亮度（值范围为0-255)
	char rgbGreen;//绿色的亮度（值范围为0-255)
	char rgbRed;//红色的亮度（值范围为0-255)
	char rgbReserved;//保留，必须为0
};

#pragma pack(pop)//恢复对齐状态

bool BMPPic::generateBmp(char* pData, int width, int height, char * filename)
{
	int size = width * height * 3; // 每个像素点3个字节
	
	BMPFILEHEADER_T bfh;
	bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size  // data size
		+ sizeof(BMPFILEHEADER_T) // first section size
		+ sizeof(BMPINFOHEADER_T) // second section size
		;
	bfh.bfReserved1 = 0; // reserved
	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size;

	// 位图第二部分，数据信息
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE * fp = fopen(filename, "wb"); // open in binary and write mode
	if (!fp) return false;

	fwrite(&bfh, 1, sizeof(BMPFILEHEADER_T), fp); //1.Pointer to the array of elements to be written  2.Size in bytes of each element 3.Number of elements
	fwrite(&bih, 1, sizeof(BMPINFOHEADER_T), fp);
	fwrite(pData, 1, size, fp);
	fclose(fp);

	return true;
}

int bmpHeaderPartLength(FILE* fpbmp)
{
	int offSet = 0;
	fseek(fpbmp, 10, SEEK_SET);
	fread(&offSet, sizeof(char), 4, fpbmp);
	return offSet;
	//printf("The Header Part is of length %d.\n", OffSet);
}

void BMPPic::bmpWidthHeight(FILE* fpbmp, int &width, int &height)
{
	int bmpWidth = 0;
	int bmpHeight = 0;
	fseek(fpbmp, 18, SEEK_SET);
	fread(&bmpWidth, sizeof(char), 4, fpbmp);
	fread(&bmpHeight, sizeof(char), 4, fpbmp);
	width = bmpWidth;
	height = bmpHeight;

}

void BMPPic::readBmp(FILE* filename)
{

	int height;
	int width;
	
	int offSet = bmpHeaderPartLength(filename);
	bmpWidthHeight(filename, width, height);
	fseek(filename, offSet, SEEK_SET);

	/*
	char* bmpPixelTmp = NULL;
	if ((bmpPixelTmp = (char*)malloc(sizeof(char) * width * height * 3)) == NULL)
	{
		printf("Data allocation failed.!!!\n");
		exit(1);
	}
	*/

	fstream file;
	file.open("data.txt", ios::out);
	int pixel = 0;
	int data;
	unsigned char* bmpPixelTmp = NULL;
	if ((bmpPixelTmp = (unsigned char*)malloc(sizeof(char) * width * height * 3)) == NULL)
	{
		printf("Data allocation failed.!!!\n");
		exit(1);
	}
	for (int i = 0; i < width * height * 3; i++)
	{
		fread(bmpPixelTmp, sizeof(char), 1, filename);
		data = *bmpPixelTmp;
		file << data << " ";
		pixel ++;
		if (pixel == 3)
		{
			file << "\n";
			pixel = 0;
		}

	}
}