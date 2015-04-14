/*
 * pctl.c
 * by Yuanhang Luo
 * 编写一个多进程并发执行程序。
 * 父进程每隔3秒重复建立两个子进程，首先创建的让其执行ls命令，
 * 之后创建执行ps命令，并控制ps命令总在ls命令之前进行。
*/

#include "pctl.h"
