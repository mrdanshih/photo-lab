#include "FileIO.h"

/*
	Loads the image from given file name fname into the RGB arrays.
	Return NULL upon failure, else an IMAGE*.
	Returns 0 for success, >1 for different errors.

	1 = some unknown error occurred
	2 = unsupported file format
	3 = unsupported width
	4 = unsuppported height
	5 = unsupported image maximum value
	6 = carriage return expected.
 */ 
IMAGE* LoadImage(const char* fname)
{
	FILE* file;

	//PPM header  - image details.
	char fileType[SLEN];
	int width = 0, height = 0, maxRGBVal = 0;

	// For dealing with file names.
	char ftype[] = ".ppm";
	char fname_temp[strlen(ftype) + strlen(fname)];

	strcpy(fname_temp, fname);
	strcat(fname_temp, ftype);

	file = fopen(fname_temp, "r");

	if(!file) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return NULL;
	}

	// Read file parameters
	char linebuf[MAX_LINE_LEN];
	unsigned int parameter_index = 0; 

	while(parameter_index < 3 && fgets(linebuf, sizeof(linebuf), file)) {
		if(*linebuf == '#') continue;
		
		switch(parameter_index) {
			// File type - 	Check header line 1 to be P6
			case 0:
				sscanf(linebuf, "%79s", fileType);
				if(fileType[0] != 'P' || fileType[1] != '6' || fileType[2] != 0) {
					printf("\nUnsupported file format!\n");
					return NULL;
				}

			// Get width and height
			case 1:
				sscanf(linebuf, "%d %d", &width, &height);
				break;

			// Get max value
			case 2:
				sscanf(linebuf, "%d", &maxRGBVal);
				// Check max value
			    if (maxRGBVal != 255) {
			        printf("\nUnsupported image maximum value %d!\n", maxRGBVal);
			        return NULL;
			    }
				break;
			default:
				break;
		}
		++parameter_index;
	}

    // Create an image struct for saving the image to
    IMAGE* image = CreateImage(width, height);

    if(!image) {
    	printf("\nCould not create image!\n");
    	return NULL;
    }

    // Now read the file contents
    for(int y = 0; y < height; ++y) {
    	for(int x = 0; x < width; ++x) {
    		SetPixelR(image, x, y, fgetc(file));
    		SetPixelG(image, x, y, fgetc(file));
    		SetPixelB(image, x, y, fgetc(file));
    	}
    }

    if(ferror(file)) {
    	printf("\nFile error while reading from file!\n");
    	free(image);
        return NULL;
    }

    printf("%s was read.\n", fname_temp);
    fclose(file);
    return image;
}

int SaveImage(const char* fname, const IMAGE* image)
{
	FILE* file;
	char ftype[] = ".ppm";
	char fname_full[strlen(ftype) + strlen(fname)];
	strcpy(fname_full, fname);
	strcat(fname_full, ftype);

	file = fopen(fname_full, "w");

	if(!file) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}

	fprintf(file, "P6\n");
	fprintf(file, "%d %d\n", ImageWidth(image), ImageHeight(image));
	fprintf(file, "255\n");

	for(int y = 0; y < ImageHeight(image); ++y) {
		for(int x = 0; x < ImageWidth(image); ++x) {
			fputc(GetPixelR(image, x, y), file);
			fputc(GetPixelG(image, x, y), file);
			fputc(GetPixelB(image, x, y), file);
		}
	}

	if(ferror(file)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}

	fclose(file);
	printf("%s was saved.\n", fname_full);
	return 0;
}