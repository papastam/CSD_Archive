#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 10

struct student{
    char name[32];
    char surname[32];
    int am;
    float grade;    
};

void pritnSt(FILE *fp,struct student st){
    int int10x=(int)10*st.grade;
    if((st.grade*100)-int10x*10==0){fprintf(fp,"%s %s %d %.2f ((%f * %f = %f) - %d = %f)\n",st.name,st.surname,st.am,st.grade,st.grade,100.0,st.grade*100,int10x*10,(st.grade*100)-int10x*10);}
    else{fprintf(fp,"%s %s %d %.2f ((%f * %f = %f) - %d = %f)\n",st.name,st.surname,st.am,st.grade,st.grade,100.0,st.grade*100,int10x*10,(st.grade*100)-int10x*10);}       
}

int main(int args,char *argv[]){
    
    char buffer[32];
    FILE *fpin, *fpout;
    int size,i,j,max=0,min=0,comp;
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
    starr=(struct student*)malloc(sizeof(struct student)*size);
    grades=(float*)malloc(sizeof(float)*size);
    
    /*COPYING THE INPUT FILE INTO THE ARRAY*/
    for(i=0;i<size;i++){
        fscanf(fpin,"%s",buffer);
        for(j=0;j<32;j++){ starr[i].name[j] = buffer[j]; }
        fscanf(fpin,"%s",buffer);
        for(j=0;j<32;j++){ starr[i].surname[j] = buffer[j]; }
        fscanf(fpin,"%d %f",&starr[i].am,&starr[i].grade);
        grades[i]=starr[i].grade; 

        if(starr[max].grade<starr[i].grade){max=i;}
        else if(starr[max].grade==starr[i].grade){if(starr[max].am>starr[i].am){max=i;}}
        
        if(starr[min].grade>starr[i].grade){min=i;}
        else if(starr[min].grade==starr[i].grade){if(starr[min].am>starr[i].am){min=i;}}
        
        sum+=starr[i].grade;
    }

    /*PRINTING MAX, MIN, AVG IN THE FILE*/
    fprintf(fpout,"max: ");
    pritnSt(fpout,starr[max]);
    fprintf(fpout,"min: ");
    pritnSt(fpout,starr[min]);
    fprintf(fpout,"average: %.2f\n",sum/(float)size);

    /*COMPARING AND PRINTING ALL THENAMES*/
    for(i=0;i<size;i++){
        comp=0;
        while(1){
            if(grades[comp]==1000){comp++;}else{break;}
        }
        for(j=0;j<size;j++){
            if(grades[comp]>grades[j]){comp=j;}else if(grades[comp]==grades[j]){if(starr[comp].am>starr[j].am){comp=j;}}
        }
        pritnSt(fpout,starr[comp]);
        /*int10x=(int)10*starr[comp].grade;
        if((starr[comp].grade*100)-int10x*10==0){fprintf(fpout,"%s %s %d %.1f\n",starr[comp].name,starr[comp].surname,starr[comp].am,starr[comp].grade);}
        else{fprintf(fpout,"%s %s %d %.2f\n",starr[comp].name,starr[comp].surname,starr[comp].am,starr[comp].grade);}*/
        grades[comp]=1000;
    }
}