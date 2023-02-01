#include <stdio.h>
#include <stdlib.h>

struct student{
    char name[32];
    char surname[32];
    int am;
    float grade;    
};

int main(int args,char *argv[]){
    
    char buffer[32];
    FILE *fpin, *fpout;
    int size,i,j,max=0,min=0,iavg100,comp;
    float *grades,sum=0;
    struct student *starr;

    /*CHECKING FOR INVALID ARGUEMENTS*/
    if(args!=3){
        printf("Invalid arguements!\n");
        return 0;
    }

    /*OPENING THE TWO FILES*/
    if(!(fpin=fopen(argv[1], "r"))){
        fprintf(stderr, "Error opening input file (%s), exiting...\n",argv[1]);
        return -1;
    }
    if(!(fpout=fopen(argv[2], "w"))){
        fprintf(stderr, "Error opening output file (%s), exiting...\n",argv[1]);
        return -1;
    }

    /*CREATING THE ARRAYS*/
    fscanf(fpin,"%d",&size);
    starr=(struct student*)malloc(sizeof(struct student)*size);/*STUDENTS ARRAY*/
    grades=(float*)malloc(sizeof(float)*size);/*USED TO SORT THE STUDENTS LATER ON*/
    
    /*COPYING THE INPUT FILE INTO THE ARRAY*/
    for(i=0;i<size;i++){
        fscanf(fpin,"%s",buffer);
        for(j=0;j<32;j++){ starr[i].name[j] = buffer[j]; }
        fscanf(fpin,"%s",buffer);
        for(j=0;j<32;j++){ starr[i].surname[j] = buffer[j]; }
        fscanf(fpin,"%d %f",&starr[i].am,&starr[i].grade);
        grades[i]=starr[i].grade; 

        /*CALCULATING MAX AND MIN STUDENT*/
        if(starr[max].grade<starr[i].grade){max=i;}
        else if(starr[max].grade==starr[i].grade){if(starr[max].am>starr[i].am){max=i;}}
        
        if(starr[min].grade>starr[i].grade){min=i;}
        else if(starr[min].grade==starr[i].grade){if(starr[min].am>starr[i].am){min=i;}}
        
        sum+=starr[i].grade;
    }

    /*PRINTING MAX, MIN, AVG IN THE FILE*/
    fprintf(fpout,"max: %s %s %d %g\n",starr[max].name,starr[max].surname,starr[max].am,starr[max].grade);
    fprintf(fpout,"min: %s %s %d %g\n",starr[min].name,starr[min].surname,starr[min].am,starr[min].grade);
    
    iavg100 = ((sum/(float)size)*100);
    fprintf(fpout,"average: %g\n",(float)iavg100/100);

    /*COMPARING AND PRINTING ALL STUDENTS*/
    for(i=0;i<size;i++){
        comp=0;
        while(1){
            if(grades[comp]==1000){comp++;}else{break;}
        }
        for(j=0;j<size;j++){
            if(grades[comp]>grades[j]){comp=j;}else if(grades[comp]==grades[j]){if(starr[comp].am>starr[j].am){comp=j;}}
        }
        fprintf(fpout,"%s %s %d %g\n",starr[comp].name,starr[comp].surname,starr[comp].am,starr[comp].grade);
        grades[comp]=1000;
    }
}