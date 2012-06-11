#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRINGBUF 1024
#define SPACE 32
#define LINEBREAK 10

typedef unsigned char byte; // einen neuen Daten-Typ-Bezeichner "byte" definiert. 

int main ( int argc, char* argv[]) {


/********************************************************************************************/

	int c; 
	long width; 
	long height; 
FILE *filehandle; 
filehandle = fopen(argv[1],"rb"); 
if (!filehandle) {
	printf("file open fail. Corect Syntax: \n pgmnorm.elf <infile>	| display (pipe to: display)\n pgmnorm.elf <infile> -o <outfile>\n"); 
	exit(EXIT_FAILURE);
}

if ( (argc>3) && (strcmp(argv[3],"-o")) ) {
		
	// outfile stuff
	printf("file open successfull. outfile option chosen\n");	
 	
	}else
	 {
	// pipe input file to display
 	printf("file open successfull. pipe to display option chosen\n");

/********************************************************************************************/
	
	// parse binary pgn file to validate format, extract width, height, and greyvalue data array. 
	
	// read file bytewise
		int position = 1;
	// parse first line. Expecting P5, abort if not. P is 80, 5 is 53, newline is 10
	while ((c = fgetc(filehandle)) != 10) {
	 
		
	if( position == 1 && !(c == 80) ) {
		printf("argument is not binary PGM file> fail"); 
		exit(EXIT_FAILURE);
	}
	
	if( position == 2 && !(c == 53) ) {
		printf("argument is not binary PGM file> fail"); 
		exit(EXIT_FAILURE);
	}
	
	printf("so far so good\n"); 
	position ++; 
	// printf(" value: %i\n",c);
	}

/********************************************************************************************/

	// skip the next 3 lines. newline is 10
	for (int i=0; i<3; i++) {
		while ((c = fgetc(filehandle)) != 10){} 
	}


/********************************************************************************************/

	// now we're at the width. 32 is space, so read till 32 for width, and then till newline(=10) for height. oh dear. 
 	// construct the byte array that is the width byte by byte. 
	position=1; 
	// dirty fix> have to figure out how to determine the size of the bytearray sometime. this will only work if i know the values in advance... 
	char soonAnInt[]="0000"; 
while ((c = fgetc(filehandle)) != SPACE){
	soonAnInt[position] = c; 
	position++; 
	}

width = atoi(soonAnInt);

/********************************************************************************************/
	
	// now the height
	// reset position and char array helpers
	position=1; 
	memset(&soonAnInt[0], 0, sizeof(soonAnInt));
// and again, only here till line break 
	while ((c = fgetc(filehandle)) != LINEBREAK){
		soonAnInt[position] = c; 
		position++;
	}
height = atoi(soonAnInt);

printf("width is %lu and height is  %lu\n",width, height); 
/********************************************************************************************/


//printf ("width = %lu, height = %lu", width, height); 

// now we're getting the value range info, 255 / ignore till next newline 

while ((c = fgetc(filehandle)) != 10){}

// now let's read in the bytes for our image. 
}	
	
/********************************************************************************************/

// create matrix to hold image data

long i=0,j=0;

byte ** matrix; // Doppelzeiger .. ist ein Zeiger der auf ein Array von Zeigern verweist

// Allocation
matrix = (byte **) malloc(height*sizeof(byte *));
for(i=0;i<height;i++){
  	matrix[i]=(byte *) malloc(width*sizeof(byte));
}
/********************************************************************************************/

// fill the matrix with values

while ((c = fgetc(filehandle)) != EOF) {

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			matrix[i][j]=c;
		}
	}
}


/********************************************************************************************/

//  normalize magic

 /********************************************************************************************/

// write to file or pipe to stdout magic... 


/********************************************************************************************/


// dealloc
for(i=0;i<height;i++){
	free(matrix[i]);
}
	
free(matrix);
	  
/********************************************************************************************/



	return 0; 
}