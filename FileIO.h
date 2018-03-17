#ifndef FILE_IO_H
#define FILE_IO_H

#define MAX_LINE_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include "Constants.h"

/* read image from a file */
IMAGE* LoadImage(const char* fname);

/* save a processed image */
int SaveImage(const char* fname, const IMAGE* image);

#endif /* FILE_IO_H */
