#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "mypgm.h"

#define STRINGBUF 1024

int usage(char* s) {
	printf("usage: %s <infile> [-o <outfile>] [ -norm | -invert ]\n",s);
	return 1;
}

int main(int argc, char* argv[]) {

	int rv; 
	FILE* fp; 
	Image* im = NewPGM();
	Image* imOut = NewPGM();
	int normalizing = 0;
	int inverting = 0;
	char* outfilename = 0;

/*
	Aufruf: (wahlweise)
	pgmop.elf <infile> [-o <outfile>] [ -norm | -invert ]
	
	pgmop.elf infile.pgm -invert -o file.pgm
	Beispiel:
	pgmop.elf logo.bin.pgm -o normalized.bin.pgm -norm pgmop.elf logo.bin.pgm -o inverteded.bin.pgm -invert
*/

	if(argc == 1) {
		return(usage(argv[0]));
	}
	
	int i;
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			if(argv[i][1] == 'n') {
				normalizing = 1;
			} else if(argv[i][1] == 'i') {
				inverting = 1;
			} else if(argv[i][1] == 'o') {
				outfilename = argv[i+1];
			}
			
		}
	}
	
	// test for argc to determine options
	// case no optional arguments
	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf (stderr, "failed opening file");  
		return EXIT_FAILURE;
	}
	if( (rv = LoadPGM(fp, im)) ) {
		fprintf(stderr, "LoadPGM returns %i\n",rv);  
		return EXIT_FAILURE;
	}
	// FIXME fclose here before reassigning fp


	// everything ok

	
	if(inverting) {
		InvertPGM(im, imOut); 
	} else if(normalizing) {
		NormPGM(im, imOut);
	} else {
		imOut = im;
	}
	
	if(outfilename) {
		fp = fopen(outfilename,"w+"); 
		SavePGM(fp, imOut);
		// FIXME close file 	
	} else {
		PrintPGM(imOut);
	}	
	

	FreePGM(im);
	if(im != imOut) {
		FreePGM(imOut);		
	}
	return 0;
}