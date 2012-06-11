


/*  Rückgabewerte signalisieren Erfolg (> 0) oder Misserfolg (==0) 
InvertPGM soll die Grauwerte des Eingangs-Bildes invertieren !
*/

unsigned short LoadPGM(FILE * infile, Image * inImg); 

unsigned short SavePGM(FILE * outfile, Image * outImg); 

unsigned short NormPGM(Image * inImg, Image * outImg); 

unsigned short InvertPGM(Image * inImg, Image * outImg);

