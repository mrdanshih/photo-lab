#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include "Image.h"
#include "stdbool.h"
#include "Constants.h"

/* Change color image to black and white */
void BlackNWhite(IMAGE* image);

/* Reverse image color */
void Negative(IMAGE* image);

/* Color filter */
void ColorFilter(IMAGE* image, int target_r, int target_g, int target_b, int threshold,
				int replace_r, int replace_g, int replace_b);

/* Edge Detection */
void Edge(IMAGE* image);

#endif /* DIPS_H */