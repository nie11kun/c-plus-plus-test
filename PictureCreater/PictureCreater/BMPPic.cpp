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

#pragma pack(2) //2�ֽڶ���
struct BMPFILEHEADER_T //BMP�ļ�ͷ��14�ֽڣ�
{
	WORD    bfType;//�ļ����ͣ�������0x424D,���ַ���BM��
	DWORD   bfSize;//�ļ���С
	WORD    bfReserved1;//������
	WORD    bfReserved2;//������
	DWORD   bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���
};

struct BMPINFOHEADER_T //3��λͼ��Ϣͷ��40�ֽڣ�
{
	DWORD      biSize;//��Ϣͷ��С
	LONG       biWidth;//ͼ����
	LONG       biHeight;//ͼ��߶�
	WORD       biPlanes;//λƽ����������Ϊ1
	WORD       biBitCount;//ÿ����λ��
	DWORD      biCompression;//ѹ������
	DWORD      biSizeImage;//ѹ��ͼ���С�ֽ���
	LONG       biXPelsPerMeter;//ˮƽ�ֱ���
	LONG       biYPelsPerMeter;//��ֱ�ֱ���
	DWORD      biClrUsed;//λͼʵ���õ���ɫ����
	DWORD      biClrImportant;//��λͼ����Ҫ��ɫ����
};

struct tagRGBQUAD  //��ɫ��
{
	char rgbBlue;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	char rgbGreen;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	char rgbRed;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	char rgbReserved;//����������Ϊ0
};

#pragma pack(pop)//�ָ�����״̬

bool BMPPic::generateBmp(char* pData, int width, int height, char * filename)
{
	int size = width * height * 3; // ÿ�����ص�3���ֽ�
	
	BMPFILEHEADER_T bfh;
	bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size  // data size
		+ sizeof(BMPFILEHEADER_T) // first section size
		+ sizeof(BMPINFOHEADER_T) // second section size
		;
	bfh.bfReserved1 = 0; // reserved
	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size;

	// λͼ�ڶ����֣�������Ϣ
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