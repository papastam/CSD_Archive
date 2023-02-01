/*Xristos Papastamos
       csd4569
  assignment1-hy255*/


#include <stdio.h>

void fillarr(char arr[256][3]){
	int i=0;
	for(i=0;i<256;i++){
		arr[i][0]=i;
		arr[i][1]='\0';
		arr[i][2]='\0';
	}

	/*lowercase*/
	arr[225][0]='a';
	arr[226][0]='v';
	arr[227][0]='g';
	arr[228][0]='d';
	arr[229][0]='e';
	arr[230][0]='z';
	arr[231][0]='h';
	arr[232][0]='8';
	arr[233][0]='i';
	arr[234][0]='k';
	arr[235][0]='l';
	arr[236][0]='m';
	arr[237][0]='n';

	arr[238][0]='k';
	arr[238][1]='s';
	
	arr[239][0]='o';
	arr[240][0]='p';
	arr[241][0]='r';
	arr[242][0]='s';
	arr[243][0]='s';
	arr[244][0]='t';
	arr[245][0]='y';
	arr[246][0]='f';
	arr[247][0]='x';
	
	arr[248][0]='p';
	arr[248][1]='s';
	
	arr[249][0]='w';

	/*uppercase*/
	arr[193][0]='A';
	arr[194][0]='V';
	arr[195][0]='G';
	arr[196][0]='D';
	arr[197][0]='E';
	arr[198][0]='Z';
	arr[199][0]='H';
	arr[200][0]='8';
	arr[201][0]='I';
	arr[202][0]='K';
	arr[203][0]='L';
	arr[204][0]='M';
	arr[205][0]='N';

	arr[206][0]='K';
	arr[206][1]='S';
	
	arr[207][0]='O';
	arr[208][0]='P';
	arr[209][0]='R';
	arr[211][0]='S';
	arr[212][0]='T';
	arr[213][0]='Y';
	arr[214][0]='F';
	arr[215][0]='X';
	
	arr[216][0]='P';
	arr[216][1]='S';
	
	arr[217][0]='W';

	/*lowercase tonous*/
	arr[220][0]='a';
	arr[220][1]='\'';
	arr[221][0]='e';
	arr[221][1]='\'';
	arr[222][0]='h';
	arr[222][1]='\'';
	arr[223][0]='i';
	arr[223][1]='\'';
	arr[252][0]='o';
	arr[252][1]='\'';
	arr[253][0]='y';
	arr[253][1]='\'';
	arr[254][0]='w';
	arr[254][1]='\'';

	/*uppercase tonous*/
	arr[182][0]='\'';
	arr[182][1]='A';
	arr[184][0]='\'';
	arr[184][1]='E';
	arr[185][0]='\'';
	arr[185][1]='H';
	arr[186][0]='\'';
	arr[186][1]='I';
	arr[188][0]='\'';
	arr[188][1]='O';
	arr[190][0]='\'';
	arr[190][1]='Y';
	arr[191][0]='\'';
	arr[191][1]='W';

	/*dialytika*/
	arr[192][0]='i';
	arr[192][1]='\'';
	arr[192][2]='"';
	
	arr[218][0]='I';
	arr[218][1]='"';

	arr[219][0]='Y';
	arr[219][1]='"';

	arr[224][0]='y';
	arr[224][1]='\'';
	arr[224][2]='"';

	arr[250][0]='i';
	arr[250][1]='"';

	arr[251][0]='y';
	arr[251][1]='"';
}

int custom_putchar(int currchar){
	int i=0;
	char transarr[256][3];
	fillarr(transarr);
	for(i=0;i<3;i++){
		if(transarr[currchar][i]!='\0'){
			putchar(transarr[currchar][i]);
		}
	}
	return 1;
}

enum FSM_state {st_def, st_M, st_N, st_m, st_n} state;

enum FSM_state def_funct(int currchar){

	switch(currchar){
		case 204: /*M*/
			return st_M;
			break;
		case 236: /*m*/
			return st_m;
			break;
		case 205: /*N*/
			return st_N;
			break;
		case 237: /*n*/
			return st_n;
			break;
		default:
			custom_putchar(currchar);
			return st_def;
			break;

	}
}

enum FSM_state M_funct(int currchar){

	switch(currchar){
		case 208: /*P*/
		case 240: /*p*/
			custom_putchar('B');
			return st_def;
			break;
		case 205: /*N*/
			custom_putchar('M');
			return st_N;
			break;
		case 237: /*n*/
			custom_putchar('M');
			return st_n;
			break;
		case 204: /*M*/
			custom_putchar('M');
			return st_M;
			break;
		case 236: /*m*/
			custom_putchar('M');
			return st_m;
			break;
		default:
			custom_putchar('M');
			custom_putchar(currchar);
			return st_def;
			break;
	}
}

enum FSM_state m_funct(int currchar){

	switch(currchar){
		case 208: /*P*/
		case 240: /*p*/
			custom_putchar('b');
			return st_def;
			break;
		case 205: /*n*/
			custom_putchar('m');
			return st_N;
			break;
		case 237: /*n*/
			custom_putchar('m');
			return st_n;
			break;
		case 204: /*M*/
			custom_putchar('m');
			return st_M;
			break;
		case 236: /*m*/
			custom_putchar('m');
			return st_m;
			break;
		default:
			custom_putchar('m');
			custom_putchar(currchar);
			return st_def;
			break;
	}
}

enum FSM_state N_funct(int currchar){

	switch(currchar){
		case 212: /*T*/
		case 244: /*t*/
			custom_putchar('D');
			return st_def;
			break;
		case 205: /*N*/
			custom_putchar('N');
			return st_N;
			break;
		case 237: /*n*/
			custom_putchar('N');
			return st_n;
			break;
		case 204: /*M*/
			custom_putchar('N');
			return st_M;
			break;
		case 236: /*m*/
			custom_putchar('N');
			return st_m;
			break;
		default:
			custom_putchar('N');
			custom_putchar(currchar);
			return st_def;
			break;
	}
}

enum FSM_state n_funct(int currchar){

	switch(currchar){
		case 212: /*T*/
		case 244: /*t*/
			custom_putchar('d');
			return st_def;
			break;
		case 205: /*N*/
			custom_putchar('n');
			return st_N;
			break;
		case 237: /*n*/
			custom_putchar('n');
			return st_n;
			break;
		case 204: /*M*/
			custom_putchar('n');
			return st_M;
			break;
		case 236: /*m*/
			custom_putchar('n');
			return st_m;
			break;
		default:
			custom_putchar('n');
			custom_putchar(currchar);
			return st_def;
			break;
	}
}

enum FSM_state (*action[])(int currchar) = {def_funct,M_funct,N_funct,m_funct,n_funct};

int main(void){
	int currchar;
	enum FSM_state state = st_def;
	while((currchar = getchar())!=EOF){		
		state = (action[state])(currchar);
	}
	return 1;
}
