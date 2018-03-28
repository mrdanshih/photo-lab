#include "DIPS.h"

IMAGE* BlackNWhite(IMAGE* image)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			char avg_intensity = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, avg_intensity);
			SetPixelG(image, x, y, avg_intensity);
			SetPixelB(image, x, y, avg_intensity);
		}
	}

	return image;
}

IMAGE* Negative(IMAGE* image)
{
	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
			SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
			SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
		}
	}

	return image;
}

bool inRange(int lower, int upper, int target)
{
	return lower <= target && target <= upper;
}

IMAGE* ColorFilter(IMAGE* image, int target_r, int target_g, int target_b, int threshold,
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

	return image;
}

bool inBounds(IMAGE* image, int x, int y)
{
	return 0 <= x && x < ImageWidth(image) && 0 <= y && y < ImageHeight(image);
}

int edgeNeighborSum(IMAGE* image, int target_x, int target_y, char color_channel, int center_pixel_multiplier)
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

				sum += (x == target_x && y == target_y) ? center_pixel_multiplier * adjusted_pixel : -1 * adjusted_pixel;
			}
		}
	} 

	if(sum < 0) 		return 0;
	else if(sum > 255)	return 255;
	return sum;
}

IMAGE* Edge(IMAGE* image)
{
	IMAGE* tempImage = CreateImage(ImageWidth(image), ImageHeight(image));

	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			SetPixelR(tempImage, x, y, edgeNeighborSum(image, x, y, 'R', 8));
			SetPixelG(tempImage, x, y, edgeNeighborSum(image, x, y, 'G', 8));
			SetPixelB(tempImage, x, y, edgeNeighborSum(image, x, y, 'B', 8));
		}
	}

	CopyImage(image, tempImage);
	DeleteImage(tempImage);

	return image;
}

void swapBlocks(IMAGE* image, int firstBlockNum, int secondBlockNum)
{
	unsigned int blockWidth = ImageWidth(image) / SHUFF_WIDTH_DIV;
	unsigned int blockHeight = ImageHeight(image) / SHUFF_HEIGHT_DIV;

	unsigned int firstBlockX = (firstBlockNum % SHUFF_WIDTH_DIV) * blockWidth;
	unsigned int firstBlockY = (firstBlockNum / SHUFF_HEIGHT_DIV) * blockHeight;

	unsigned int secondBlockX = (secondBlockNum % SHUFF_WIDTH_DIV) * blockWidth;
	unsigned int secondBlockY = (secondBlockNum / SHUFF_HEIGHT_DIV) * blockHeight;
	
	for(unsigned int y = 0; y < blockHeight; ++y) {
		for(unsigned int x = 0; x < blockWidth; ++x) {
			char redTemp = GetPixelR(image, firstBlockX + x, firstBlockY + y);
			char greenTemp = GetPixelG(image, firstBlockX + x, firstBlockY + y);	
			char blueTemp = GetPixelB(image, firstBlockX + x, firstBlockY + y);
			
			SetPixelR(image, firstBlockX + x, firstBlockY + y ,
						 GetPixelR(image, secondBlockX + x, secondBlockY + y));
			SetPixelG(image, firstBlockX + x, firstBlockY + y ,
						 GetPixelG(image, secondBlockX + x, secondBlockY + y));
			SetPixelB(image, firstBlockX + x, firstBlockY + y ,
						 GetPixelB(image, secondBlockX + x, secondBlockY + y));

			SetPixelR(image, secondBlockX + x, secondBlockY + y, redTemp);
			SetPixelG(image, secondBlockX + x, secondBlockY + y, greenTemp);
			SetPixelB(image, secondBlockX + x, secondBlockY + y, blueTemp);
		}
	}
}

IMAGE* Shuffle(IMAGE* image)
{
	// x // y = row
	// x % y = column
	srand(time(NULL));

	int blocks[16];

	for(unsigned int i = 0; i < 16; ++i) {
		blocks[i] = i;
	}

	// Shuffle the array.
	for(unsigned int i = 0; i < 16; ++i) {
		unsigned int swap_i = rand() % 16;

		int temp = blocks[i];
		blocks[i] = blocks[swap_i];
		blocks[swap_i] = temp;
	}

	// Go through array in pairs and swap the blocks
	for(unsigned int i = 0; i < 16; i += 2) {
		swapBlocks(image, blocks[i], blocks[i + 1]);
	}

	return image;
}

