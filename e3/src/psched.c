#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
 
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
typedef void (*sighandler_t)(int);
void sigcat(){
	//+1
	setpriority(PRIO_PROCESS, getpid(), getpriority(PRIO_PROCESS, 0) + 1);
}
void sigzat(){
	//-1
	setpriority(PRIO_PROCESS, getpid(), getpriority(PRIO_PROCESS, 0) - 1);
}
void nothing() {}
int main(int argc, char *argv[])
{
	int i,j,status;
	int pid; //存放进程号
	struct sched_param p[2]; //设置调度策略时使用的数据结构
	//signal(SIGINT, (sighandler_t)sigcat);
	//signal(SIGTSTP, (sighandler_t)sigzat);
	for(i=0; i<2;i++){
		//取进程优先数放在调度策略数据结构中
		p[i].sched_priority = 10;
	}
	pid = fork();
	if(pid < 0){
    	printf("failed!");
	}
	else if(pid > 0){
    		signal(SIGINT, (sighandler_t)sigcat);
    		signal(SIGTSTP, (sighandler_t)nothing);
    		sched_setscheduler(getpid(), SCHED_OTHER, &p[0]);
		setpriority(PRIO_PROCESS, getpid(), 10);
		sleep(1);
		for(i = 0; i < 10; i++){
			printf("parent PID = %d, priority = %d, scheduler = %d\n", getpid(),getpriority(PRIO_PROCESS, 0), sched_getscheduler(getpid()));
			// if(i % 4 == 2) {
			printf("父进程挂起，按 Ctrl + C 为其优先数加一\n");
			pause();
			// }
			sleep(1);
		}
	}
	//各子进程循环报告其优先数和调度策略
	else{
    		signal(SIGTSTP, (sighandler_t)sigzat);
    		signal(SIGINT, (sighandler_t)nothing);
    		sched_setscheduler(getpid(), SCHED_OTHER, &p[1]);
		setpriority(PRIO_PROCESS, getpid(), 10);
		sleep(1);
		//每隔 1 妙报告一次进程号和优先级
		for(i=0; i<10; i++){
			printf("Child PID = %d priority= %d scheduler = %d\n",getpid(),getpriority(PRIO_PROCESS,0), sched_getscheduler(getpid()));
			//if(i % 4 == 1) {
			printf("子进程挂起，按 Ctrl + Z 为其优先数减一\n");
			pause();
			//}
			sleep(1);
		}
		exit( EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}
