#include <stdio.h>
#include "FileIO.h"
#include "DIPS.h"
#include "Constants.h"

# define INPUT_LIMIT 100

void printMenu() {
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

char* getFilenameInput(char* prompt) {
	char* filename = (char*) malloc(INPUT_LIMIT * sizeof(char));

	printf("%s", prompt);
	// Get file name.
	fgets(filename, sizeof(filename), stdin); // 
	size_t last_index = strlen(filename) - 1;
	if(filename[last_index] == '\n') {
		filename[last_index] = '\0';
	}

	return filename;
}

void executeCommand(int option, unsigned char R[WIDTH][HEIGHT],
							    unsigned char G[WIDTH][HEIGHT],
							    unsigned char B[WIDTH][HEIGHT]) {
	switch(option) {
		case 1:
		{
			char* filename = getFilenameInput("Please input the file name to load (no extension): ");
			int result = LoadImage(filename, R, G, B);
			free(filename);

		    if(result == 0) {
		    	printf("Success!\n");
		    } else {
		    	printf("Failure!\n");
		    }

		    break;
		}
	}
}

int main(int argc, char** argv) {
	// the image
	unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];

	int option;
	char input[INPUT_LIMIT];
	do {
		printMenu();
		printf("Enter a numerical option: ");

		if(fgets(input, INPUT_LIMIT, stdin) && sscanf(input, "%d", &option)) {
			printf("Option chosen was: %d\n", option);
			executeCommand(option, R, G, B);
		} else {
			printf("Invalid choice. Enter # from 1-15.\n");
			option = 0;
		}

	} while(option != 15);

	return 0;
}
