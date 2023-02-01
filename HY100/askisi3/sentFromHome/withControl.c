#include <stdio.h>

#define SIZE 10

int main(int args,char *argv[]){

        int i,j,act_size,sum=1,isUpperD=1;
        int arr[SIZE][SIZE]={0};

        if(strcmp(argv[1],"-create")==0){
                act_size = atoi(argv[2]);

                if(act_size>10 || act_size<2){
                        printf("Not valid array size");
                        return 0;
                }

                printf("  %d\n",act_size);

                for(i=0;i<act_size;i++){        
                        for(j=i;j<act_size;j++){
                                arr[i][j]=(rand()%7)+1;
                        }
                        for(j=0;j<act_size;j++){
                                printf("  %d",arr[i][j]);
                        }
                        printf("\n");
                }

        }else if(strcmp(argv[1],"-calculate")==0){

                scanf("%d",&act_size);

                for(i=0;i<act_size;i++){        
                        for(j=0;j<act_size;j++){
                                scanf("%d ",&arr[i][j]);
                        }
                        for(j=0;j<i;j++){
								if(arr[i][j] != 0){
										isUpperD = 0;
						}
                    }
                }

                if(!isUpperD){printf("\nThe array isn't upper diagonal\n\n");}

                for(i=0;i<act_size;i++){
                        sum*= arr[i][i];
                }

                printf("%d\n",sum);
        }
}

