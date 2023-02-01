#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

char** move(char** map,int m,int n,int posm,int posn,int dir);

int main(){

    int posm=1,posn=-1;
    char **map;
    int m,n,i,j;

    srand(time(0));
    scanf("%d%d",&m,&n);

    /*CRATING A DEFAULT MAP*/
    map=(char**)malloc(sizeof(char*)*m);
    for(i=0;i<m;i++){
        *(map+i)=(char*)malloc(sizeof(char)*n);
        
        if(!*(map+i)){printf("malloc fail");return 0;}
        
        for(j=0;j<n;j++){
            map[i][j]='X';
        }
    }

    /*MAKING THE MOVES*/
    map=move(map,m,n,posm,posn,1);

    /*PRINTING THE MAP*/
    for(j=0;j<n;j++){
        for(i=0;i<m;i++){
            printf("%c ",map[i][j]);
        }
        printf("\n");
    }
}

char** move(char** map,int m,int n,int posm,int posn,int dir){

    int i,moves[]={0,1,2,3};
    int choice=-2;

    /*MAKING THE MOVE (IF POSSIBLE)*/
    switch (dir){
    case 0:
        if(posn<3||map[posm][posn-2]!='X'){
            return map;
        }else{
            map[posm][posn-1]=' ';
            map[posm][posn-2]=' ';
            posn-=2;
        }
        break;
    case 1:
        if(n-posn<=3||map[posm][posn+2]!='X'){
            return map;
        }else{
            map[posm][posn+1]=' ';
            map[posm][posn+2]=' ';
            posn+=2;
        }
        break;
    case 2:
        if(m-posm<=3||map[posm+2][posn]!='X'){
            return map;
        }else{
            map[posm+1][posn]=' ';
            map[posm+2][posn]=' ';
            posm+=2;
        }
        break;
    case 3:
        if(posm<3||map[posm-2][posn]!='X'){
            return map;
        }else{
            map[posm-1][posn]=' ';
            map[posm-2][posn]=' ';
            posm-=2;
        }
        break;
    }

    /*DECIDING ON THE NEXT MOVE*/
    choice = rand()%4;/*0-3*/
    map=move(map,m,n,posm,posn,moves[choice]); 
    moves[choice]=-1;

    do{
        choice = rand()%4;/*0-3*/
    }while(moves[choice]==-1);
    map=move(map,m,n,posm,posn,moves[choice]);
    moves[choice]=-1;

    do{
        choice = rand()%4;/*0-3*/
    }while(moves[choice]==-1);
    map=move(map,m,n,posm,posn,moves[choice]);
    moves[choice]=-1;

    for(i=0;i<4;i++){
        if(moves[i]!=-1){
            choice = moves[i];
            break;
        }
    }
    map=move(map,m,n,posm,posn,moves[i]);

    return map;
}