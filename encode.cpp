#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE *fw = fopen("log.dat", "w");

	char dat[MAX_PATH];
	char bin[9] = { 0, };
	
	int i;
	
	scanf("%s", dat);
	// gets(dat);
	for(i=0; dat[i] != '\0'; i++) {
		_itoa(dat[i], bin, 2);
		fprintf(fw, "%s ", bin);
		memset(bin, 0, 9);
	}

	fclose(fw);
}
