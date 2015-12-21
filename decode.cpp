#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin2dec(int i)
{
	int dec = 0, n = 0;

	while (i)
	{
		dec += (i % 10) * (1 << n);
		i /= 10;
		n++;
	}

	return dec;
}

void main()
{
	char str[MAX_PATH] = { 0, };
	char bin[MAX_PATH], *ptr;
	int num, i = 0;

    gets(bin);
    for(i=0, ptr = bin; i==0 || *(ptr-1) != '\0'; ptr += 8, i++) {
		num = atoi(ptr);
		str[i] = bin2dec(num);
    }
    printf("%s \n", str);

    system("pause");
}
