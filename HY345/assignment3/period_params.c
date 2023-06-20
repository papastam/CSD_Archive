#include <linux/kernel.h>
#include <linux/period_params.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm-generic/errno-base.h>
#include <asm/uaccess.h>

asmlinkage long sys_set_period_params(int period, int execution_time, int num_of_periods){
		
	struct task_struct *taskstr;
	taskstr=get_current();

	if(execution_time>=period){
		return EINVAL;
	}

	taskstr->period=period;
	taskstr->execution_time=execution_time;
	taskstr->num_of_periods=num_of_periods;

	printk("(set) Chris Papastamos 4569\n");
	return 1;
}

asmlinkage long sys_get_period_params(period_params * params){
	
	struct task_struct *taskstr;
	taskstr=get_current();

	access_ok(VERIFY_READ,params,sizeof(params));

	copy_to_user((void*) &params->period,(void*) &taskstr->period,sizeof(int));
	copy_to_user((void*) &params->num_of_periods,(void*) &taskstr->num_of_periods,sizeof(int));
	copy_to_user((void*) &params->execution_time,(void*) &taskstr->execution_time,sizeof(int));

	printk("(get) Chris Papastamos 4569\n");
	return 1;
}

