/*#include<windows.h>   //创建线程函数需要操作系统函数
#include<process.h>   //创建线程函数头文件
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h> 
#include<time.h>*/

#include"zqy.h"
int CountTimes;//使用前需置零 //在main函数里置零 
extern int OutputRepair;//输出检修指令的同步锁  
extern int StopSignal; 
extern void fixGantt(void);
extern void putstate(void);
extern struct repair
{
	int point;
	int machine_num;
	int fix_time;
}fix;

unsigned __stdcall Timekeeping(void* signal)//计时函数 
//线程函数的返回值是指定类型，形参也只能有一个
{
	while(StopSignal!=1)//调用前置零即可 
	{
		//fixGantt();
		putstate();
		CountTimes+=2;
		Sleep(2000);
	} 
	
	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}
