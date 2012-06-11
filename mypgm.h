/*  Rückgabewerte signalisieren Erfolg (> 0) oder Misserfolg (==0) 
InvertPGM soll die Grauwerte des Eingangs-Bildes invertieren !
*/

typedef unsigned char byte; // einen neuen Daten-Typ-Bezeichner "byte" definiert. 

typedef struct image {
	char pgmType[2]; // P5 for binary PGM 
	char** comments; // not mandatory
	unsigned short width;
	unsigned short height; 
	byte** data; // datamatrix for greyvalues
	unsigned short depth; // max grey value (255)
} Image;

unsigned short 	LoadPGM(FILE * infile, Image * inImg); 
unsigned short 	SavePGM(FILE * outfile, Image * outImg); 
unsigned short 	NormPGM(Image * inImg, Image * outImg); 
unsigned short 	InvertPGM(Image * inImg, Image * outImg);
Image* 			NewPGM();
void 			FreePGM(Image* i);
