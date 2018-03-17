#include "DIPS.h"

/* Change color image to black and white */
void BlackNWhite(IMAGE* image)
{
	for(int y = 0; y < HEIGHT; ++y) {
		for(int x = 0; x < WIDTH; ++x) {
			char avg_intensity = (GetPixelR(image, x, y) + 
									GetPixelG(image, x, y) + 
									GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, avg_intensity);
			SetPixelG(image, x, y, avg_intensity);
			SetPixelB(image, x, y, avg_intensity);
		}
	}
}