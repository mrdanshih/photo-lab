#include "Image.h"

IMAGE* CreateImage(unsigned int width, unsigned int height)
{
	IMAGE* image = malloc(sizeof(IMAGE));
	if(image == NULL) return NULL;

	image->R = calloc(width * height, sizeof(char));
	image->G = calloc(width * height, sizeof(char));
	image->B = calloc(width * height, sizeof(char));
	if(image->R == NULL || image->G == NULL || image->B == NULL) return NULL;

	image->W = width;
	image->H = height;
	return image;
}

void DeleteImage(IMAGE* image)
{
	if(image != NULL) {
		free(image->R);
		free(image->G);
		free(image->B);
		image->R = NULL;
		image->G = NULL;
		image->B = NULL;
		free(image);
	}
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

unsigned int ImageWidth(const IMAGE* image)
{
	return image->W;
}

unsigned int ImageHeight(const IMAGE* image)
{
	return image->H;
}

void CopyImage(IMAGE* dest, IMAGE* src)
{
	for(int y = 0; y < ImageHeight(dest); ++y) {
		for(int x = 0; x < ImageWidth(dest); ++x) {
			SetPixelR(dest, x, y, GetPixelR(src, x, y));
			SetPixelG(dest, x, y, GetPixelG(src, x, y));
			SetPixelB(dest, x, y, GetPixelB(src, x, y));
		}
	}
}

