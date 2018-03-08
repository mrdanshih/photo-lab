#include "FileIO.h"

/*
	Loads the image from given file name fname into the RGB arrays.
	Returns 0 for success, >1 for different errors.

	1 = some unknown error occurred
	2 = unsupported file format
	3 = unsupported width
	4 = unsuppported height
	5 = unsupported image maximum value
	6 = carriage return expected.
 */ 
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) 
{
	FILE* file;
	//PPM header 
	char fileType[SLEN];
	int width, height, maxRGBVal;

	// For dealing with file names.
	char fname_temp[SLEN];
	char ftype[] = ".ppm";

	strcpy(fname_temp, fname);
	strcat(fname_temp, ftype);

	file = fopen(fname_temp, "r");

	if(!file) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return 1;
	}

	// Check header line 1 to be P6
	fscanf(file, "%79s", fileType);
	if(fileType[0] != 'P' || fileType[1] != '6' || fileType[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}

	// Check width
	fscanf(file, "%d", &width);
	if(width != WIDTH) {
		printf("\nUnsupported image width %d!\n", width);
        return 3;
	}

	//Check height
    fscanf(file, "%d", &height);
    if (height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", height);
        return 4;
    }

    //Check max value
    fscanf(file, "%d", &maxRGBVal);
    if (maxRGBVal != 255) {
        printf("\nUnsupported image maximum value %d!\n", maxRGBVal);
        return 5;
    }

    //Ensure ends in carriage return
    if ('\n' != fgetc(file)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }

    // Now read the file contents
    for(int y = 0; y < HEIGHT; ++y) {
    	for(int x = 0; x < WIDTH; ++x) {
    		R[x][y] = fgetc(file);
    		G[x][y] = fgetc(file);
    		B[x][y] = fgetc(file);
    	}
    }

    if(ferror(file)) {
    	printf("\nFile error while reading from file!\n");
        return 7;
    }

    printf("%s was read.\n", fname_temp);
    fclose(file);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE* file;
	char ftype[] = ".ppm";
	char fname_full[SLEN];
	strcpy(fname_full, fname);
	strcat(fname_full, ftype);

	file = fopen(fname_full, "w");

	if(!file) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}

	fprintf(file, "P6\n");
	fprintf(file, "%d %d\n", WIDTH, HEIGHT);
	fprintf(file, "255\n");

	for(int y = 0; y < HEIGHT; ++y) {
		for(int x = 0; x < WIDTH; ++x) {
			fputc(R[x][y], file);
			fputc(G[x][y], file);
			fputc(B[x][y], file);
		}
	}

	if(ferror(file)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}

	fclose(file);
	printf("%s was saved, \n", fname_full);
	return 0;
}