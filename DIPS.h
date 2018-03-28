#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Image.h"
#include "stdbool.h"
#include "Constants.h"

/* Change color image to black and white */
IMAGE* BlackNWhite(IMAGE* image);

/* Reverse image color */
IMAGE* Negative(IMAGE* image);

/* Color filter */
IMAGE* ColorFilter(IMAGE* image, int target_r, int target_g, int target_b, int threshold,
				int replace_r, int replace_g, int replace_b);

/* Edge Detection */
IMAGE* Edge(IMAGE* image);

/* Shuffle the image */
IMAGE* Shuffle(IMAGE* image);

#endif /* DIPS_H */