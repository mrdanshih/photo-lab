#include "DIPS.h"

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

bool inRange(int lower, int upper, int target)
{
	return lower <= target && target <= upper;
}

void ColorFilter(IMAGE* image, int target_r, int target_g, int target_b, int threshold,
				int replace_r, int replace_g, int replace_b)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			int curr_r = GetPixelR(image, x, y);
			int curr_g = GetPixelG(image, x, y);
			int curr_b = GetPixelB(image, x, y);

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

bool inBounds(IMAGE* image, int x, int y)
{
	return 0 <= x && x < ImageWidth(image) && 0 <= y && y < ImageHeight(image);
}

int edgeNeighborSum(IMAGE* image, int target_x, int target_y, char color_channel)
{
	// Color channel should be 'R, 'G', or 'B'
	int sum = 0;

	for(int y = target_y - 1; y <= target_y + 1; ++y) {
		for(int x = target_x - 1; x <= target_x + 1; ++x) {
			int adjusted_pixel;

			if(inBounds(image, x, y)) {
				if(color_channel == 'R') 		adjusted_pixel = GetPixelR(image, x, y);
				else if(color_channel == 'G') 	adjusted_pixel = GetPixelG(image, x, y);
				else if(color_channel == 'B') 	adjusted_pixel = GetPixelB(image, x, y);

				sum += (x == target_x && y == target_y) ? 8 * adjusted_pixel : -1 * adjusted_pixel;
			}
		}
	} 

	if(sum < 0) 		return 0;
	else if(sum > 255)	return 255;
	return sum;
}

void Edge(IMAGE* image)
{
	IMAGE* tempImage = CreateImage(ImageWidth(image), ImageHeight(image));

	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			SetPixelR(tempImage, x, y, edgeNeighborSum(image, x, y, 'R'));
			SetPixelG(tempImage, x, y, edgeNeighborSum(image, x, y, 'G'));
			SetPixelB(tempImage, x, y, edgeNeighborSum(image, x, y, 'B'));
		}
	}

	CopyImage(image, tempImage);
	DeleteImage(tempImage);
}

