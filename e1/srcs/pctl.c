/*
 * pctl.c
 * by Yuanhang Luo
 * 编写一个多进程并发执行程序。
 * 父进程每隔3秒重复建立两个子进程，首先创建的让其执行ls命令，
 * 之后创建执行ps命令，并控制ps命令总在ls命令之前进行。
*/

#include "pctl.h"

int main(int argc, char *argv[])
{
	int i;
	int pid_1, pid_2;//两个子进程
	int status_ls, status_ps;//两个子进程状态
	char *args_ls[] = {"/bin/ls", "-a", NULL};//ls命令
	char *args_ps[] = {"/bin/ps", "-l" ,NULL};//ps命令
	signal(SIGINT,(sighandler_t)sigcat);//键盘中断

	while(1){
		if((pid_1=fork())==0){//创建一个子进程
			pause();
			printf("CHILD 1_ps: RUNNING\n");
			printf("CHILD 1_ps: My pid is %d\n",getpid());
			printf("CHILD 1_ps: My father's pid is %d\n",getppid());
			status_ps = execve(args_ps[0],args_ps,NULL);//执行ps命令
		}
		else{
			pid_2 = fork();//创建第二个子进程
			if(pid_2 < 0){
				printf("Create ps Fail!\n");
				exit(EXIT_FAILURE);
			}
			else if(pid_2 == 0){
				pause();
				printf("CHILD 2_ls: RUNNING\n");
				printf("CHILD 2_ls: My pid is %d\n",getpid());
				printf("CHILD 2_ls: My father's pid is %d\n",getppid());
				status_ps = execve(args_ls[0],args_ls, NULL);//执行ls命令
			}
			else{
				printf("FATHER: RUNNING\n");
				printf("FATHER: My pid is: %d", getpid());

				if(kill(pid_1,SIGINT)>=0){
					waitpid(pid_1, &status_ls,0);//等待执行ls命令
					sleep(3);//等待3秒
					printf("FATHER: CHILD ps finished\n");
					if(kill(pid_2, SIGINT)>=0){
						waitpid(pid_2, &status_ls,0);
						printf("FATHER: CHILD ls finished.\n");
					}
				}
			}
		}
	}
	return EXIT_SUCCESS;
	
}


