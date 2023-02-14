#include <stdio.h>                                                  
#include <unistd.h>        
#include <errno.h>                                               
                                 
struct period_struct{                  
   int period;
   int execution_time;
   int num_of_periods;
};

#define SET_PERIODPARAMS(period,exec_time,num_of_periods) syscall(341,period,exe
#define GET_PERIODPARAMS(periodstr) syscall(342,periodstr);        

int main(){            
	int i;

	printf("Try set a execution time bigger than the period\n");
	i=SET_PERIODPARAMS(1,2,3);

	if(i==22){printf("Given exec_time is grater than the period\n");
	}else{printf("A exec_time grater than the period was set!\n");
	}

	printf("Before entering kernel (to set period params)\n");
	i=SET_PERIODPARAMS(2,1,3);
	if(i==22){printf("Given exec_time is grater than the period\n");}
	printf("Back in user level (seted period params)\n\n\n");

	struct period_struct periodstr;

	printf("Before entering kernel(to get period params)\n");
	GET_PERIODPARAMS(&periodstr);
	printf("After entering kernel(per:%d,exec_time:%d,nop:%d)\n",periodstr.period,periodstr.execution_time,periodstr.num_of_periods);
	return 1;
}