#include <stdlib.h>
#include <stdio.h>

int main(int args,char* argv[]){

        char start,curr;
        int counter=0,i,loops;

        if(*argv[1]=='e'){
                curr=getchar();
                while(curr!='\n'){
                        counter=0;
                        start=curr;
                        while(start==curr){
                                counter++;
                                curr=getchar();
                        }
                        printf("%d%c",counter,start);
                }
                printf("\n");

        }else if(*argv[1]=='d'){
                
                do{
                        loops=0;
                        while (1){
                                curr=getchar();
                                if(curr>47 && curr<58){
                                        loops*=10;
                                        loops+=curr-48;
                                }else{
                                        break;
                                }
                        }
                        for(i=0;i<loops;i++){
                                printf("%c",curr);
                        }
                }while(curr!='\n');
                printf("\n");
        }
}