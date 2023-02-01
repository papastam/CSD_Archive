#include <stdio.h>

int main(){

	int i;
	long len=0;

	long out,inpt2,inpt;
	scanf("%d",&inpt);
	inpt2 = inpt;

	out=inpt%10;
	inpt /= 10;

	while(inpt2!=0){
		len++;
		inpt2 /= 10;
	}

	for(i=len-1;i>0;i--){
		out *= 10;
		out += inpt%10;
		inpt /= 10;
	}

	printf("%d\n",out);


}
