#include <stdio.h>
#include "FileIO.h"
#include "DIPS.h"
#include "Image.h"
#include "Constants.h"

# define INPUT_LIMIT 100

void printMenu()
{
	printf("--------------------------------\n");
	printf(" 1:  Load a PPM image\n"
			" 2:  Save an image in PPM format\n"
			" 3:  Change a color image to black and white\n"
			" 4:  Make a negative of an image\n"
			" 5:  Color filter an image\n"
			" 6:  Sketch the edge of an image\n"
			" 7:  Shuffle an image\n"
			" 8:  Flip an image vertically\n"
			" 9:  Mirror an image vertically\n"
			" 10: Add border to the image\n"
			" 11: Add noise to an image\n"
			" 12: Sharpen an image\n"
			" 13: Posterize an image\n"
			" 14: Motion Blur\n"
			" 15: Exit\n");
}

char* getFilenameInput(char* prompt)
{	
	char* filename = (char*) malloc(INPUT_LIMIT * sizeof(char));

	printf("%s", prompt);
	// Get file name.
	fgets(filename, INPUT_LIMIT, stdin); // 
	size_t last_index = strlen(filename) - 1;
	if(filename[last_index] == '\n') {
		filename[last_index] = '\0';
	} else {
		//Flush buffer
		int ch;
		while(((ch = getchar()) !='\n') && ch != EOF);
	}

	return filename;
}

int getRGBInput(char* prompt)
{ 
	int value;
	char input[INPUT_LIMIT];
	while(1) {
		printf("%s", prompt);
		if(fgets(input, INPUT_LIMIT, stdin) && sscanf(input, "%d", &value) && value >= 0 && value <= 255) {
				return value;
		} else {
			printf("Invalid input. Enter a valid value from 0-255.\n");
			value = 0;
		}
	}
}

void printSuccessFailMessage(int resultCode)
{
    if(resultCode == 0) {
    	printf("Success!\n");
    } else {
    	printf("Failure!\n");
    }
}

void executeLoadFileCommand(IMAGE** image)
{
	char* filename = getFilenameInput("Please input the file name to load (no extension): ");
	IMAGE* newImage = NULL;
	newImage = LoadImage(filename);

	if(newImage != NULL) {
		DeleteImage(*image);
		*image = newImage;	
	} else {
		printf("Failed to load image.\n");
	}

	free(filename);

}

void executeSaveFileCommand(IMAGE** image)
{
	char* filename = getFilenameInput("Please input the file name to save to (no extension): ");
	int result = SaveImage(filename, *image);
	free(filename);
	printSuccessFailMessage(result);
}

void executeColorFilterCommand(IMAGE** image)
{
	int red_target = getRGBInput("Enter target Red component of color: ");
	int green_target = getRGBInput("Enter target Green component of color: ");
	int blue_target = getRGBInput("Enter target Blue component of color: ");
	int threshold = getRGBInput("Enter threshold for the color difference: ");
	int red_replace = getRGBInput("Enter replacement Red component of color: ");
	int green_replace = getRGBInput("Enter replacement Green component of color: ");
	int blue_replace = getRGBInput("Enter replacement Blue component of color: ");
	ColorFilter(*image, red_target, green_target, blue_target, threshold, red_replace, green_replace, blue_replace);
	printf("\"Color Filter\" operation is done!\n");
}


void executeCommand(int option, IMAGE** image)
{
	// Check for NULL image for options that require a loaded image
	if(option != 1 && option != 15 && *image == NULL) {
		printf("No image loaded to perform this operation!\n");
		return;
	}

	switch(option) {
		case 1:		// Load File
			executeLoadFileCommand(image); break;

		case 2:		// Save File
			executeSaveFileCommand(image); break;

		case 3: 		
			BlackNWhite(*image); 
			printf("\"Black & White\" operation is done!\n");
			break;

		case 4:
			Negative(*image);
			printf("\"Negative\" operation is done!\n");
			break;

		case 5:
			executeColorFilterCommand(image); break;

		case 6:
			Edge(*image);
			printf("\"Edge\" operation is done!\n");
			break;

		case 7:
			Shuffle(*image);
			printf("Shuffle operation is done!\n");
			break;

		case 8:
			VFlip(*image);
			printf("Vertical flip operation is done!\n");
			break;
	}
}


int main(int argc, char** argv)
{
	// the image
	IMAGE* image = NULL;
	int option;
	char input[INPUT_LIMIT];
	do {
		printMenu();
		printf("Enter a numerical option: ");

		if(fgets(input, INPUT_LIMIT, stdin) && sscanf(input, "%d", &option)) {
			executeCommand(option, &image);
		} else {
			printf("Invalid choice. Enter # from 1-15.\n");
			option = 0;
		}

	} while(option != 15);
	
	DeleteImage(image);
	return 0;
}
