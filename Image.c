#include "Image.h"

IMAGE* CreateImage(unsigned int width, unsigned int height)
{
	IMAGE* image = malloc(sizeof(IMAGE));
	image->R = calloc(width * height, sizeof(char));
	image->G = calloc(width * height, sizeof(char));
	image->B = calloc(width * height, sizeof(char));
	image->W = width;
	image->H = height;
	return image;
}

void DeleteImage(IMAGE* image)
{
	free(image->R);
	free(image->G);
	free(image->B);
	image->R = NULL;
	image->G = NULL;
	image->B = NULL;
	free(image);
}

unsigned char GetPixelR(const IMAGE* image, unsigned int x, unsigned int y)
{
	return image->R[x + y * image->W];
}

unsigned char GetPixelG(const IMAGE* image, unsigned int x, unsigned int y)
{

	return image->G[x + y * image->W];
}

unsigned char GetPixelB(const IMAGE* image, unsigned int x, unsigned int y)
{
	return image->B[x + y * image->W];
}

void SetPixelR(IMAGE* image, unsigned int x, unsigned int y, unsigned char r)
{
	image->R[x + y * image->W] = r;
}

void SetPixelG(IMAGE* image, unsigned int x, unsigned int y, unsigned char g)
{
	image->G[x + y * image->W] = g;
}

void SetPixelB(IMAGE* image, unsigned int x, unsigned int y, unsigned char b)
{
	image->B[x + y * image->W] = b;
}

unsigned int ImageWidth(IMAGE* image)
{
	return image->W;
}

unsigned int ImageHeight(IMAGE* image)
{
	return image->H;
}
