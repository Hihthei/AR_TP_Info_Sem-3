#ifndef PAINT_H
#define PAINT_H

#include "Settings.h"
#ifndef _LIBBMP_H_
#define _LIBBMP_H_

typedef struct Pixel_t
{
	unsigned char R, G, B;
	float grey;
}Pixel;

typedef struct Image_t
{
	Pixel* pix;
	int width, height;
	int size;
	unsigned char header[54];
}Image;

//int RGBtoHSV(Pixel* p);
//int RGBtoYCbCr(Pixel* p);
float RGBtoGrey(Pixel* p);

Image* readImage(char* imgpath);
void writeImage(Image* img, char* imgpath);
void freeImage(Image* img);

#endif

#endif // !PAINT_H
