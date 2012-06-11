#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mypgm.h"

#define STRINGBUF 1024
#define SPACE 32
#define LINEBREAK 10
#define CHAR_P 80
#define CHAR_5 53

unsigned short LoadPGM(FILE * inFile, Image * inImg) {
	
	/********************************************************************************************/

	// parse binary pgn file to validate format, extract width, height, and greyvalue data array. 

	// read file bytewise
	int position = 1;
	int c; 
	// parse first line. Expecting P5, abort if not. P is 80, 5 is 53, linebreak is 10
	while ((c = fgetc(inFile)) != LINEBREAK) {

	if( position == 1 && !(c == CHAR_P) ) {
		printf("argument is not binary PGM file> fail\n"); 
		return 1;
	}

	if( position == 2 && !(c == CHAR_5) ) {
		printf("argument is not binary PGM file> fail\n"); 
		return 1; 
	}
	inImg->pgmType[position-1] = c;
	position ++; 
	}

	/********************************************************************************************/
	// skip the next 3 lines, those are comments.
	for (int i=0; i<3; i++) {
		while ((c = fgetc(inFile)) != LINEBREAK){} 
	}
	/********************************************************************************************/

	// now we're at the width. 32 is space, so read till 32 for width, and then till newline(=10) for height. 
 	// construct the byte array that is the width byte by byte. 
	position=0; 
	// dirty fix> have to figure out how to determine the size of the bytearray sometime. this will only work if i know the values in advance... 
	char soonAnInt[STRINGBUF];
	memset(&soonAnInt[0], 0, sizeof(soonAnInt));
	while ((c = fgetc(inFile)) != SPACE){
		soonAnInt[position] = c; 
		position++;
		if(position > STRINGBUF) {
				//freak out
		} 
	}
	inImg->width = atoi(soonAnInt);

	/********************************************************************************************/
	// now the height
	// reset position and char array helpers
	position=0; 
	memset(&soonAnInt[0], 0, sizeof(soonAnInt));
	// and again, only here till line break 
	while ((c = fgetc(inFile)) != LINEBREAK){
		soonAnInt[position] = c; 
		position++;
	}
	inImg->height = atoi(soonAnInt);

	/********************************************************************************************/
	// now we're getting the depth info, 255 / ignore till next newline 
	position=0; 
	memset(&soonAnInt[0], 0, sizeof(soonAnInt));
	while ((c = fgetc(inFile)) != LINEBREAK){
		soonAnInt[position] = c; 
		position++;
	}
	inImg->depth = atoi(soonAnInt);
	/********************************************************************************************/

	/********************************************************************************************/
	// allocate memory for inImg bytes
	int i=0,j=0;
	// Allocation
	inImg->data = (byte **) malloc(inImg->height*sizeof(byte*));
	for(i=0;i<inImg->height;i++){
	  	inImg->data[i]=(byte *) malloc(inImg->width*sizeof(byte));
	}
	/********************************************************************************************/
	// fill data with values
	
	for(i=0;i<inImg->height;i++) {
		//runs once for every line
		for(j=0;j<inImg->width;j++) {
			//runs once for every pixel inside that line, for each line.
			if ((c = fgetc(inFile)) != EOF) {
				inImg->data[i][j] = c;
			} else {
				inImg->data[i][j] = 0;
			}
		}
	}


	return 0; 
} 

unsigned short SavePGM(FILE * outFile, Image * outImg){
	
	// first put the pgm type info, followed by a LINEBREAK
	
	// convert chars in pgmtype to int
	
	fputc( outImg->pgmType[0], outFile );
	fputc( outImg->pgmType[1], outFile );
	fputc(LINEBREAK, outFile); 
	
	
	// fputc the comments here - not mandatory
	
	// width and height delimited by space
	
	fprintf(outFile, "%i %i", outImg->width, outImg->height );
	fputc(LINEBREAK, outFile);
	
	// bit depth
	
	fprintf(outFile, "%i", outImg->depth );
	fputc(LINEBREAK, outFile);
	
	// pixel byte data
	
	for(int i=0;i<outImg->height;i++){
		for(int j=0;j<outImg->width;j++){
			fputc(outImg->data[i][j], outFile); 
			printf("writing data[%i][%i] to file (%1x)\n", i,j,(unsigned)(unsigned char)outImg->data[i][j]); 
		}
	}
	
	fclose(outFile); 
	
	return 1; 
}

unsigned short NormPGM(Image * inImg, Image * outImg){
	
	// determine min and max values of inImg
	int maxVal=0; 
	int minVal=0; 
	
	for(int i=0;i<inImg->height;i++){
		for(int j=0;j<inImg->width;j++){
			int val = inImg->data[i][j]; 
			if (maxVal < val) {
				 maxVal = val;
			}
			if (minVal > val) {
				 minVal = val;
			}
		}
	}
	
	// allocate memory for outImg!!
	
	// normalize algorithm
	
	int oldRange = maxVal-minVal; 
	int val=0; 
	int scale=0; 
	for(int i=0;i<inImg->height;i++){
		for(int j=0;j<inImg->width;j++){
			val = inImg->data[i][j]; 
			scale = (val-minVal/oldRange); 
			val = inImg->depth*scale; 
			outImg->data[i][j] = val;
		}
	}
	
	/**************************dealloc************************************************************/
	for(int i=0;i<inImg->height;i++){
		free(inImg->data[i]);
	}
	free(inImg->data);
	/********************************************************************************************/
	
	return 1; 
}

unsigned short InvertPGM(Image * inImg, Image * outImg){
	
	for(int i=0;i<inImg->height;i++){
		for(int j=0;j<inImg->width;j++){
			int val = inImg->data[i][j]; 
			outImg->data[i][j] = inImg->depth-val;
		}
	}
	
	/**************************dealloc************************************************************/
	for(int i=0;i<inImg->height;i++){
		free(inImg->data[i]);
	}
	free(inImg->data);
	/********************************************************************************************/
	
	return 1; 
}

Image* NewPGM() {
	return calloc(1,sizeof(Image));
}

void FreePGM(Image* image) {
		// free any stuff pointed to by a struct Image
		for(int i=0;i<image->height;i++){
			free(image->data[i]);
		}
		free(image->data);
}

