#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

char** move(FILE *debugp,int rec,char** map,int m,int n,int posm,int posn,int dir);

int main(){

    int posm=1,posn=-1;
    char **map;
    int m,n,i,j;
    FILE *debugp;

    /*
    (0)/\
    (1)\/
    (2)->
    (3)<-
    */

    srand(time(0));
    scanf("%d%d",&m,&n);

    if(!(debugp=fopen("debug.txt", "w"))){
        fprintf(stderr, "Error opening input file (debug.txt), exiting...\n");
        return -1;
    }

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
    map=move(debugp,0,map,m,n,posm,posn,1);

    /*PRINTING THE MAP*/
    for(j=0;j<n;j++){
        for(i=0;i<m;i++){
            printf("%c ",map[i][j]);
        }
        printf("\n");
    }
}

char** move(FILE *debugp,int rec,char** map,int m,int n,int posm,int posn,int dir){

    int i,moves[]={0,1,2,3};
    int choice=-2;
    
    rec++;

    /*MAKING THE MOVE (IF POSSIBLE)*/
    switch (dir){
    case 0:
        if(posn<3||map[posm][posn-2]!='X'){
            fprintf(debugp,"FAIL\n");
            return map;
        }else{
            map[posm][posn-1]=' ';
            map[posm][posn-2]=' ';
            posn-=2;
        }
        break;
    case 1:
        if(n-posn<=3||map[posm][posn+2]!='X'){
            fprintf(debugp,"FAIL\n");
            return map;
        }else{
            map[posm][posn+1]=' ';
            map[posm][posn+2]=' ';
            posn+=2;
        }
        break;
    case 2:
        if(m-posm<=3||map[posm+2][posn]!='X'){
            fprintf(debugp,"FAIL\n");
            return map;
        }else{
            map[posm+1][posn]=' ';
            map[posm+2][posn]=' ';
            posm+=2;
        }
        break;
    case 3:
        if(posm<3||map[posm-2][posn]!='X'){
            fprintf(debugp,"FAIL\n");
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
    fprintf(debugp,"IN POS:(%d,%d) DOING MOVE:%d (REC:%d)\n",posm,posn,moves[choice],rec);
    map=move(debugp,rec,map,m,n,posm,posn,moves[choice]); 
    moves[choice]=-1;

    do{
        choice = rand()%4;/*0-3*/
    }while(moves[choice]==-1);
    fprintf(debugp,"IN POS:(%d,%d) DOING MOVE:%d (REC:%d)\n",posm,posn,moves[choice],rec);
    map=move(debugp,rec,map,m,n,posm,posn,moves[choice]);
    moves[choice]=-1;

    do{
        choice = rand()%4;/*0-3*/
    }while(moves[choice]==-1);
    fprintf(debugp,"IN POS:(%d,%d) DOING MOVE:%d (REC:%d)\n",posm,posn,moves[choice],rec);
    map=move(debugp,rec,map,m,n,posm,posn,moves[choice]);
    moves[choice]=-1;

    for(i=0;i<4;i++){
        if(moves[i]!=-1){
            choice = moves[i];
            break;
        }
    }
    fprintf(debugp,"IN POS:(%d,%d) DOING MOVE:%d (REC:%d)\n",posm,posn,moves[choice],rec);
    map=move(debugp,rec,map,m,n,posm,posn,moves[i]);

    return map;
}