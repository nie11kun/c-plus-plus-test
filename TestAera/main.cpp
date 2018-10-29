#include<iostream>
#include<map>
#include<string>
#include<windows.h>
#include<fstream>

using namespace std;


//get length of hearder
void bmpHeaderPartLength(FILE* fpbmp);
// get width and height
void BmpWidthHeight(FILE* fpbmp);
 //save letter's black pixel number into a map
void SaveLetterInfo(FILE* fpbmp,int asc_code);

//draw the bmp on screen with charcter
void bmpOut(FILE* fpbmp);

unsigned int OffSet = 0;    // OffSet from Header part to Data Part
long BmpWidth = 0;          // The Width of the Data Part
long BmpHeight = 0;         // The Height of the Data Part
int point[256];

//get header length(offset)
void bmpHeaderPartLength(FILE* fpbmp)
{
     fseek(fpbmp, 10, SEEK_SET);
     fread(&OffSet, sizeof(char), 4, fpbmp);
     //printf("The Header Part is of length %d.\n", OffSet);
}

//get width and height
void BmpWidthHeight(FILE* fpbmp)
{
     fseek(fpbmp, 18, SEEK_SET);
     fread(&BmpWidth, sizeof(char), 4, fpbmp);
     fread(&BmpHeight, sizeof(char), 4, fpbmp);
}

void bmpOut(FILE* fpbmp)
{
	unsigned char* bmpPixelTmp = NULL;
	unsigned char* tem ;
	unsigned char * charcterToPrint = NULL;
	fseek(fpbmp, OffSet, SEEK_SET);

	if ((bmpPixelTmp=(unsigned char*)malloc(sizeof(char)*BmpWidth*BmpHeight))==NULL)
	{
		printf("Data allocation failed.!!!\n");
		exit(1);
	}
	charcterToPrint=(unsigned char*)malloc(sizeof(char)*BmpWidth*BmpHeight +1+ BmpHeight);
	if (charcterToPrint == NULL)
	{
		printf("allocation failed.!!!\n");
		exit(1);
	}
	int index = 0;
	tem = bmpPixelTmp;
	fread(bmpPixelTmp, sizeof(char), BmpWidth*BmpHeight, fpbmp);
	bmpPixelTmp += BmpHeight * BmpWidth -1;
	///////////////////////////////////////////////////////////////////////////////////

	bmpPixelTmp = bmpPixelTmp - BmpWidth +1;
	for(int i=0;i<BmpHeight;++i)
	{
        for(int j=0;j<BmpWidth;++j)
		{
			charcterToPrint[index++] = (char)point[*bmpPixelTmp];
			bmpPixelTmp++;
		}
		charcterToPrint[index++] = '\n';
		bmpPixelTmp = bmpPixelTmp - 2*BmpWidth;

	}
	charcterToPrint[index] = '\0';
	cout <<charcterToPrint<<endl;

	free(tem);
	free(charcterToPrint);
}


int main()
{
    /*
    fstream file;
    file.open("data.txt", ios::out);
    for(int i = 0; i < 256; i ++)
    {
        file << i << " ";
    }
    file.close();
	*/

	FILE *fpdata = fopen("data.txt", "r+");
	if (fpdata == NULL)
	{
		printf("Open data failed!!!%d\n");
		return 1;
	}

	for(int i=0;i<256;++i)
	{
		fscanf(fpdata,"%d ",&point[i]);
	}
    // open the picture and draw it!
	FILE *fpbmp = fopen("bmp.bmp", "r+");
	if (fpbmp == NULL)
	{
		printf("Open mbp failed!!!\n");
		return 1;
	}

	bmpHeaderPartLength(fpbmp);
	BmpWidthHeight(fpbmp);
	bmpOut(fpbmp);

	return 0;
}
