#include "DIPS.h"

/* Change color image to black and white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT],
				 unsigned char G[WIDTH][HEIGHT],
				 unsigned char B[WIDTH][HEIGHT])
{
	for(int y = 0; y < HEIGHT; ++y) {
		for(int x = 0; x < WIDTH; ++x) {
			char avg_intensity = (R[x][y] + G[x][y] + B[x][y]) / 3;
			R[x][y] = avg_intensity;
			G[x][y] = avg_intensity;
			B[x][y] = avg_intensity;
		}
	}
}