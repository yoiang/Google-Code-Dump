#include <stdio.h>
#include <stdlib.h>

int main (int iargc, char **argv)
{
	if (iargc < 3)
	{
		printf("format: stuffer.exe <list file> <filesize>\n") ;
		return 1 ;
	}
	FILE *pFile = fopen(argv[1], "r") ;
	FILE *pCreate ;
	char szCreate[256] ;
	double  dSize = strtod(argv[2], NULL) ;
	if (pFile == 0) 
	{
		printf("error opening %s\n", argv[1]) ;
		return 1 ;
	}
	while (!feof(pFile))
	{
		fscanf(pFile, "%s", szCreate) ;
		if (feof(pFile)) break ;
		pCreate = fopen(szCreate, "w") ;
		printf("%s\n", szCreate) ;
		for (double iTrav = 0 ; iTrav < dSize ; iTrav ++)
		{
			fprintf(pCreate, "a") ;
		}
		fclose(pCreate) ;
	}
	fclose(pFile) ;
	return 0 ;
}