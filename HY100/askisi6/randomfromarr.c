#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(){
    
    int choise,arrdef[]={0,1,2,3};

    srand(time(0));

    choise=rand()%4;
    printf("%d ",arrdef[choise]);
    arrdef[choise]=-1;

    do{
        choise=rand()%4;
    }while(arrdef[choise]==-1);
    printf("%d ",arrdef[choise]);
    arrdef[choise]=-1;

    do{
        choise=rand()%4;
    }while(arrdef[choise]==-1);
    printf("%d ",arrdef[choise]);
    arrdef[choise]=-1;

    do{
        choise=rand()%4;
    }while(arrdef[choise]==-1);
    printf("%d \n",arrdef[choise]);
}