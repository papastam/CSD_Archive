#include <stdio.h>

int main(){
	int inpt;
	int i,j,k;

	scanf("%d",&inpt);
	for(i=1;i<inpt+1;i++){
		for(j=0;j<inpt-i;j++){printf(" ");}
		for(k=0;k<(2*(i-1))+1;k++){printf("*");}
		printf("\n");
	}

	for(i=inpt-1;i>0;i--){
		for(j=0;j<inpt-i;j++){printf(" ");}
		for(k=0;k<1+((i-1)*2);k++){printf("*");}
		printf("\n");
	}

	return 0;
}
