#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "mypgm.h"

int main(int argc, char* argv[]) {
/*
	Aufruf: (wahlweise)
	pgmop.elf <infile> [-o <outfile>] [ -norm | -invert ] [ | display ]
	Beispiel:
	pgmop.elf logo.bin.pgm -o normalized.bin.pgm -norm pgmop.elf logo.bin.pgm -o inverteded.bin.pgm -invert
*/

	int rv; 
	FILE* fp; 
	Image* im = NewPGM();
	
	fp = fopen("logo.bin.pgm", "r");
	if (!fp) {
		fprintf (stderr, "failed opening file");  
		exit(EXIT_FAILURE);
	}
	
	if( (rv = LoadPGM(fp, im)) ) {
		fprintf(stderr, "LoadPGM returns %i\n",rv);  
	}
	// everything ok
	
	printf("first couple bytes of the image data: %1x\n", (unsigned)(unsigned char)im->data[0][0]); 
	
	printf("loaded image of width %i and height %i to 'im'\n",im->width,im->height);

	//	unsigned short SavePGM(FILE * outfile, Image * outImg); 
	
	fp = fopen("saved.logo.bin.pgm","w+"); 
	SavePGM(fp, im); 

	FreePGM(im);
	//	unsigned short NormPGM(Image * inImg, Image * outImg); 
	//	unsigned short InvertPGM(Image * inImg, Image * outImg);
	return 0;
}