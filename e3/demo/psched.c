/*
*  psched.c
*  by Yuanhang Luo
*  父进程创建3个子进程为他们设置不同的优先级和调度策略
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
	int i,j,status;
	int pid[3];
	struct sched_param p[3];

	for(i=0; i<3; i++)
	{
		if((pid[i]=fork())>0)
		{
			p[i].sched_priority=(argv[i+1]!=NULL)?atoi(argv[i+1]):10;
			sched_setscheduler(pid[i],(argv[i+4] != NULL)?atoi(argv[i+4]):SCHED_OTHER,&p[i]);
			//父进程设置子进程的优先数,如果命令行第 1,2,3 参数指定了 3 个优先数则按指定的数设置,否则都为 10
			setpriority(PRIO_PROCESS,pid[i],(argv[i+1] != NULL) ? atoi(argv[i+1]):10);
		}
		else{
			sleep(1);//每隔 1 妙报告一次进程号和优先级
			for(i=0; i<10; i++){
				printf("Child PID = %d priority = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
				sleep(1);
			}
		}
		exit(EXIT_SUCCESS);
	}
	//父进程报告子进程调度策略后先行退出
	printf("My child %d policy is %d\n",pid[0],sched_getscheduler(pid[0]));
	printf("My child %d policy is %d\n",pid[1],sched_getscheduler(pid[1]));
	printf("My child %d policy is %d\n",pid[2],sched_getscheduler(pid[2]));
	return EXIT_SUCCESS;

}
