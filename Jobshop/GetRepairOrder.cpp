/*#include <graphics.h>
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h> 
#include<windows.h>   //创建线程函数需要操作系统函数
#include<process.h>   //创建线程函数头文件
#include<time.h>*/

#include"zqy.h"

struct repair
{
	int point;
	int machine_num;
	int fix_time;
}fix;

extern void timechange(void);

extern clock_t start,finish;
extern int CountTimes;
int OutputRepair;//main里输出检修指令的同步锁 
int StopSignal; 
//应该还有一个与周期性输出的同步锁 

//还需要把检修输入测试.cpp里的东西粘到main里创建线程 
unsigned __stdcall GetRepairOrder(void* pArguments)
{
	/*
	检修指令的格式为：
	<C><机器号> <空格><检修时长><\n>
	*/ 
	int signal=0;
	clock_t CurrentTime;
	
	setfont(50, 0, "宋体");
	setcolor(BLACK);
	outtextxy(1300,300,"发生了什么");
	setfillcolor(YELLOW); 
	bar(100,100,200,700);
        	char str[100];
	while(StopSignal!=1)//当当前时间小于总时间 
	{
		outtextxy(100,600,"输入东西");
		signal=getch();//等待用户输入//ege库里的函数
		setfillcolor(RED); 
		bar(500,100,600,300);
		if(signal=='C') 
		{ 
			    /*inputbox_getline("这是一个对话框",
                    "请随便\n输入一串字符，输入完请回车",
                    str,
                    sizeof(str)/sizeof(*str));*/
            //outtextxy(1000,600,"???");
            setfillcolor(GREEN); 
		bar(1000,200,1200,500);
			inputbox_getline("检修指令输入","请输入检修指令，格式如下\n<机器号><空格><检修时长><回车>",str,100);
			outtextxy(1100,700, str);
			sscanf(str,"%d %d",&fix.machine_num,&fix.fix_time);
		//	outtextxy(1300, 700,);
			//outtextxy(1400, 800, mc_time);
			
			setfillcolor(GREEN);
			bar(555,666,690,777); 
			CurrentTime=clock();
			fix.point=3*(int)(CurrentTime-start)/CLOCKS_PER_SEC;//谜之point？？？  
			//OutputRepair=1;
			
			/*输出机器状态*/
			setfillcolor(WHITE);
			bar(1255,105,1525,295);	//清空该输出区域 
			char RepairInfo[50];
			sprintf(RepairInfo,"检修机器号：%d\n检修时长：%d",fix.machine_num,fix.fix_time);
			setcolor(BLACK);
			setfont(18, 0, "宋体");
			outtextxy(925,105,RepairInfo);
			
			
			timechange();
		}
	 } 
	 outtextxy(1500,300,"退出");
	 
	 _endthreadex(0);//线程完成时要调用_endthread
	 return 0; 
}
