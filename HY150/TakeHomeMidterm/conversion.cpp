#include <stdio.h>

using namespace std;

float comp(char* c){
    if(c[1]=='m'||(c[0]=='m'&&c[1]=='\0')) {

        if (c[0] == 'T') {
            return 1000000000000;
        } else if (c[0] == 'G') {
            return 1000000000;
        } else if (c[0] == 'M') {
            return 1000000;
        } else if (c[0] == 'k') {
            return 1000;
        } else if (c[0] == 'd') {
            return 0.1;
        } else if (c[0] == 'c') {
            return 0.01;
        } else if (c[0] == 'm') {
            if (c[1] == 'm') {
                return 0.001;
            } else if (c[1] == '\0') {
                return 1;
            }
        } else if (c[0] == 'u') {
            return 0.000001;
        } else if (c[0] == 'n') {
            return 0.000000001;
        } else if (c[0] == 'p') {
            return 0.000000000001;
        }else{return -1;}

    }else{return -1;}
}

int main() {
    char c[2],inputstr[32];
    float f;

    do {
        scanf("%s", inputstr);

        if (inputstr[0] == 'q') {
            break;
        }else{
            sscanf(inputstr,"%f %s",&f,c);

            if(comp(c)==-1){
                printf("Unit not found!\n\n");
            }else{
                printf("%g m\n\n",f*comp(c));
            }
        }
    }while(1);

}

