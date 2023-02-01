#include <stdlib.h>
#include <stdio.h>

int main(){

        int size,comp,sum,curr,cont,magic=1,i,j,k,l;
        int** arr;

        /*ARRAY SCANNING PHASE*/
        scanf("%d",&size);
        comp=(size*((size*size)+1))/2;

        arr = (int**)malloc(sizeof(int*)*size);

        for(i=0;i<size;i++){
                *(arr+i)=(int*)malloc(sizeof(int)*size);

                if(!*(arr+i)){return 0;}

                for(j=0;j<size;j++){
                        scanf("%d",(*(arr+i)+j));
                }
        }

        /*ARRAY PROCESSING PHASE*/

        /*ROWS*/
        for(i=0;i<size;i++){
                sum=0;
                for(j=0;j<size;j++){
                        sum+=*(*(arr+i)+j);
                }
                printf("ROW %d %s\n",i+1,sum==comp?"YES":"NO");
                if(!(sum==comp)){magic=0;}
        }

        /*COLUMNS"*/
        for(i=0;i<size;i++){
                sum=0;
                for(j=0;j<size;j++){
                        sum+=*(*(arr+j)+i);
                }
                printf("COLUMN %d %s\n",i+1,sum==comp?"YES":"NO");;
                if(!(comp==sum)){magic=0;}
        }

        /*DIAGS*/
        for(i=0;i<2;i++){
                sum=0;
                for(j=0;j<size;j++){
                        sum+=i?*(*(arr+j)+size-j-1):*(*(arr+j)+j);
                }
                printf("DIAG%d %s\n",i+1,sum==comp?"YES":"NO");
                if(!(comp==sum)){magic=0;}
	}

        /*UNIQUE*/

        /*k is for [1,size^2]*/
        for(k=1;k<(size*size)+1;k++){
                cont=0;
                /*i and j itterates the array (arr[i][j])*/
                for(i=0;i<size;i++){
                        for(j=0;j<size;j++){
                                /*printf("%d==%d(%d:%d) %s\n",k,arr[i][j],i,j,k==arr[i][j]?"TRUE":"FALSE");*/
                                if(k==arr[i][j]){
                                        cont=1;
                                        break;
                                }else if(i==size-1 && j==size-1){
                                        printf("UNIQUE NO\nMAGIC NO\n");
                                        return 0;
                                }
                        }
                        if(cont){break;}
                }
        }
        printf("UNIQUE YES\nMAGIC %s\n",magic?"YES":"NO");


        /*for(i=0;i<size;i++){
                for(j=0;j<size;j++){
                        first = 1;
                        for(k=i;k<size;k++){
                                for(l=j;l<size;l++){
                                        if(first == 1){
                                                first = 0;
                                                continue;
                                        }
                                        /*printf("arr[%d][%d]\n", k, l);
                                        if(*(*(arr+i)+j)==*(*(arr+k)+l)){
                                                /*printf("%d:%d %d:%d\n",i,j,k,l);
                                                printf("UNIQUE NO\nMAGIC NO\n");
                                                return 0;
                                        }
                                }
                        }
                }
        }
        printf("UNIQUE YES\nMAGIC %s\n",magic?"YES":"NO");
        */
}

