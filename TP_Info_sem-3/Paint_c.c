#include "Paint_h.h"

float RGBtoGrey(Pixel* p)
{
	float sum = (float)(p->R + p->G + p->B);
	float div = sum / (float)3;
	return div;
}

Image* readImage(char* imgpath)
{
	Image* img = NULL;
	FILE* pfile = NULL;
	int pad;
	int buf = 0, i, pos = 0;

	img = (Image*)calloc(sizeof(Image), 1);
	if (!img)
	{
		printf("No image\n");
		return NULL;
	}

	pfile = fopen(imgpath, "r");
	if (!pfile)
	{
		printf("No file\n");
		return NULL;
	}

	// Lecture du header
	fread(img->header, 54, 1, pfile);
	fseek(pfile, 18, SEEK_SET);
	fread(&img->width, 4, 1, pfile);
	//printf("width= %d\n", img->width);
	pad = (4 - (img->width * 3 % 4)) % 4;

	fread(&img->height, 4, 1, pfile);
	//printf("height= %d\n", img->height);

	img->size = img->height * img->width;

	// Allocation des pixels
	img->pix = (Pixel*)calloc(sizeof(Pixel), img->size);
	if (!img->pix)
	{
		printf("No pixel\n");
		return NULL;
	}

	// Lecture des pixels
	fseek(pfile, 54, SEEK_SET);
	for (i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			fread(&(img->pix[pos].B), 1, 1, pfile);
			fread(&(img->pix[pos].G), 1, 1, pfile);
			fread(&(img->pix[pos].R), 1, 1, pfile);
			pos++;
		}
		fread(&buf, pad, 1, pfile);
	}

	// Conversion au systeme Grey
	for (i = 0; i < img->size; i++)
	{
		img->pix[i].grey = RGBtoGrey(&(img->pix[i]));
	}

	fclose(pfile);

	return img;
}


void writeImage(Image* img, char* imgpath)
{
	int pos = 0;
	int buf = 0;
	int pad;
	int i;
	FILE* pfile = NULL;
	pfile = fopen(imgpath, "w");
	if (!pfile)
	{
		printf("No file\n");
		return;
	}
	pad = (4 - (img->width * 3 % 4)) % 4;

	int nb = 0;

	printf("Entrer la classe du nombre : ");

	int poubelle = scanf("%d", &nb);

	fprintf(pfile, "%d %d %d\n%d\t", 1, 10, 784, nb);

	for (i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			int number = (int)img->pix[pos].grey;
			fprintf(pfile, "%d ", number);
			pos++;
		}
	}


	fclose(pfile);

	return;
}

void modifyDataset(Image* img, char* imgpathW, char* imgpathD, char* imgpathC)
{
	if (!img)
	{
		return;
	}
	if (!imgpathW)
	{
		return;
	}
	if (!imgpathC)
	{
		return;
	}

	FILE* origin = NULL;
	FILE* new = NULL;
	FILE* copy = NULL;
	new = fopen(imgpathW, "r");
	origin = fopen(imgpathD, "r");
	copy = fopen(imgpathC, "w");
	int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, poubelle = 0;
	poubelle = fscanf(origin, "%d %d %d", &tmp1, &tmp2, &tmp3);
	fprintf(copy, "%d %d %d\n", tmp1 + 1, 10, 784);
	for (int i = 0; i < tmp1; i++)
	{
		poubelle = fscanf(origin, "%d\t", &tmp4);
		fprintf(copy, "%d\t", tmp4);
		for (int j = 0; j < 784; j++)
		{
			poubelle = fscanf(origin, "%d ", &tmp4);
			fprintf(copy, "%d ", tmp4);
		}
		fprintf(copy, "\n");
	}
	fclose(origin);

	int pos = 0, buf = 0, pad, i, nb = 0;
	pad = (4 - (img->width * 3 % 4)) % 4;

	printf("Entrer la classe du nombre : ");

	poubelle = scanf("%d", &nb);

	fprintf(copy, "%d\t", nb);

	for (i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			int number = (int)img->pix[pos].grey;
			fprintf(copy, "%d ", number);
			pos++;
		}
	}
	fclose(copy);
	fclose(new);

	return;

}

void copyDataset(char* imgpathD, char* imgpathC)
{
	if (!imgpathD)
	{
		return;
	}
	if (!imgpathC)
	{
		return;
	}
	
	FILE* origin = NULL;
	FILE* copy = NULL;
	origin = fopen(imgpathC, "r");
	copy = fopen(imgpathD, "w");
	int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, poubelle = 0;
	poubelle = fscanf(origin, "%d %d %d", &tmp1, &tmp2, &tmp3);
	fprintf(copy, "%d %d %d\n", tmp1, 10, 784);
	for (int i = 0; i < tmp1; i++)
	{
		poubelle = fscanf(origin, "%d\t", &tmp4);
		fprintf(copy, "%d\t", tmp4);
		for (int j = 0; j < 784; j++)
		{
			poubelle = fscanf(origin, "%d ", &tmp4);
			fprintf(copy, "%d ", tmp4);
		}
		fprintf(copy, "\n");
	}
	fclose(origin);
	fclose(copy);

	return;
}

void freeImage(Image* img)
{
	if (!img) return;
	if (img->pix) free(img->pix);
	free(img);
}