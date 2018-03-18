#include "DIPS.h"

/* Change color image to black and white */
void BlackNWhite(IMAGE* image)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			char avg_intensity = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, avg_intensity);
			SetPixelG(image, x, y, avg_intensity);
			SetPixelB(image, x, y, avg_intensity);
		}
	}
}

void Negative(IMAGE* image)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
			SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
			SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
		}
	}
}

bool inRange(int lower, int upper, int target) {
	return lower <= target && target <= upper;
}

void ColorFilter(IMAGE* image, int target_r, int target_g, int target_b, int threshold,
				int replace_r, int replace_g, int replace_b)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			unsigned char curr_r = GetPixelR(image, x, y);
			unsigned char curr_g = GetPixelG(image, x, y);
			unsigned char curr_b = GetPixelB(image, x, y);

			if(inRange(target_r - threshold, target_r + threshold, curr_r) &&
			   inRange(target_g - threshold, target_g + threshold, curr_g) &&
			   inRange(target_b - threshold, target_b + threshold, curr_b)) {
				SetPixelR(image, x, y, replace_r);
				SetPixelG(image, x, y, replace_g);
				SetPixelB(image, x, y, replace_b);
			}
		}
	}
}

