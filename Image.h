#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

typedef struct IMAGE {
	unsigned int W;		// width
	unsigned int H;		// height
	unsigned char* R;	// pointer for all R intensity values
	unsigned char* G;	// pointer for all G intensity values
	unsigned char* B; 	// pointer for all B intensity values
} IMAGE;

/* Allocate memory for image structure and memory spaces for color intensity 
 * values. Returns pointer to image, or NULL in case of error. 
 */
IMAGE* CreateImage(unsigned int width, unsigned int height);

/* Release the memory space for the pixel color intensity values 
 * Deallocate all memory spaces for image
 * Set RGB pointer to NULL
 */
void DeleteImage(IMAGE* image);

/* Get the color intensity of the channels for each pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE* image, unsigned int x, unsigned int y);
unsigned char GetPixelG(const IMAGE* image, unsigned int x, unsigned int y);
unsigned char GetPixelB(const IMAGE* image, unsigned int x, unsigned int y);

/* Set the color intensity of the channels for each pixel (x, y) in image to r, g, or b */
void SetPixelR(IMAGE* image, unsigned int x, unsigned int y, unsigned char r);
void SetPixelG(IMAGE* image, unsigned int x, unsigned int y, unsigned char g);
void SetPixelB(IMAGE* image, unsigned int x, unsigned int y, unsigned char b);

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE* image);

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE* image);

/* Copies pixels from src to dest. Both image dimensions must be the same,
 * else there will be errors.
 */
void CopyImage(IMAGE* src, IMAGE* dest);

#endif /* IMAGE_H */
