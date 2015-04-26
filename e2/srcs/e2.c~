/*
* e2.c
* by Yuanhang Luo
* 设有二元函数 f(x,y) = f(x) + f(y)
* 其中: 
*	f(x) = f(x-1) * x         (x >1)
*	f(x)=1                    (x=1)
*	f(y) = f(y-1) + f(y-2)    (y> 2)   
*	f(y)=1	                  (y=1,2)
* 请编程建立 3 个并发协作进程或线程,它们分别完成 f(x,y)、f(x)、f(y)
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>


void task1(int *);//线程1执行函数
void task2(int *);//线程2执行函数
void task3(int *);//线程3执行函数

int fx(int x);//计算f(x)
int fy(int y);//计算f(y)
int fxy(int x, int y);//计算f(x)+f(y)

int pipe1[2], pipe2[2], pipe3[2], pipe4[2];//存放四个无名管道号
pthread_t thrd1, thrd2, thrd3;//存放三个线程标识

//主函数
int main(int argc, char *argv[])
{
	int num1, num2, num3;
	int ret;
	//使用pipe()系统调用建立无名管道
	if(pipe(pipe1)<0){
		perror("pipe1 not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe2)<0){
		perror("pipe2 not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe3)<0){
		perror("pipe3 not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe4)<0){
		perror("pipe4 not create");
		exit(EXIT_FAILURE);
	}
	//使用pthread_create()建立进程
	num1 = 1;
	ret = pthread_create(&thrd1,NULL,(void *)task1,(void *)&num1);
	if(ret){
		perror("pthread_create:f(x)");
		exit(EXIT_FAILURE);
	}
	
	num2= 2;
	ret = pthread_create(&thrd2,NULL,(void *) task2,(void *)&num2);
	if(ret){
		perror("pthread_create:f(y)");
		exit(EXIT_FAILURE);
	}

	num3 = 3;
	ret = pthread_create(&thrd3,NULL,(void *)task3,(void *)&num3);
	if(ret){
		perror("pthread_create:f(x)+f(y)");
		exit(EXIT_FAILURE);
	}

	pthread_join(thrd3,NULL);
	pthread_join(thrd1,NULL);
	pthread_join(thrd3,NULL);
	pthread_join(thrd2,NULL);

	
	exit(EXIT_SUCCESS);
}
//线程1执行任务
void task1(int *num)
{
	int x = 1;
	
	do{
		printf("fx(%d)=%d\n",x++,fx(x));
		write(pipe1[1],&x,sizeof(int));
		read(pipe2[0],&x,sizeof(int));
	}while(x<=9);

	close(pipe1[1]);
	close(pipe2[0]);
}
//线程2执行任务
void task2(int *num)
{
	int y;
	do{
		read(pipe2[0],&y,sizeof(int));
		printf("fy(%d)=%d\n",y++,fy(y));
		write(pipe1[1],&y,sizeof(int));
	}while(y<=9);
	
	close(pipe1[1]);
	close(pipe2[0]);
}
//线程3执行任务
void task3(int *num)
{
	int x,y;
	do{
		read(pipe1[0],&x,sizeof(int));

		printf("fx(%d)+fy(%d)=%d\n",x,x,fxy(x,x));
		write(pipe2[1],&x,sizeof(int));

	}while(x<=9);

	close(pipe1[0]);
	close(pipe2[1]);
}

//计算f(x)
int fx(int x)
{
	if(x = 1)
		return 1;
	else{
		return fx(x-1)*x;
	}
}

//计算f(y)
int fy(int y)
{
	if(y == 1 || y == 2)
		return 1;
	else{
		return fy(y-1)+fy(y-2);
	}
}

//计算f(x)+f(y)
int fxy(int x, int y)
{
	return fx(x)+fy(y);
}

















