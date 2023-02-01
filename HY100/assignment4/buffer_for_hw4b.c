#include <stdio.h>
#include <stdlib.h>

#define CHUNK 40

int main(int args,char* argv[]){

        char *arr,*temparr;
        char temp;
        int i,rep=0;

        if(*argv[1]=='e'){
                arr=(char*)malloc(CHUNK);

                while(1){
                        /* aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa   */
                        temparr=(char*)malloc(CHUNK+1);

                        temparr[CHUNK] = '\0';  /*set an extra character ass the end of the array (\0)*/
                        temparr[CHUNK -1] = '\0';
                        temparr[0] = '\0';

                        scanf("%40s",temparr);
                        /*printf("temparr: %s\n",temparr);*/

                        if(temparr[0]=='\0'){ /*if whole chunk is empty*/
                                /*printf("TEST1\n");*/
                                break;
                        }else if(temparr[CHUNK-1]=='\0'){ /*if chunk is not full*/
                                arr=(char*)realloc(arr,((rep)*CHUNK)+CHUNK+1);
                                for(i=0;i<CHUNK;i++){
                                        arr[((rep)*CHUNK)+i]=temparr[i];
                                }
                                arr[((rep)*CHUNK)+CHUNK]='\0';
                                /*printf("/\\CASE 2\n");*/
                                break;
                        }else{
                                arr=(char*)realloc(arr,((rep)*CHUNK)+CHUNK+1);
                                /*printf("/\\CASE\n");*/
                                for(i=0;i<CHUNK;i++){
                                        arr[((rep)*CHUNK)+i]=temparr[i];
                                }
                                arr[((rep)*CHUNK)+CHUNK]='\0';
                        }
                /*printf("(rep: %d / arr: %s / arrsize: %d)\n",rep,arr,((rep)*CHUNK)+CHUNK);*/
                rep++;
                }
                printf("final arr: \n%s\n",arr);
        }
}