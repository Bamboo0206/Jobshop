#include"zqy.h"
int CountTimes;//使用前需置零 //在main函数里置零 
//extern int StopSignal;
//extern clock_t start,finish;
extern void timechange(void);

extern clock_t start,finish;
//extern int CountTimes;
int OutputRepair;//main里输出检修指令的同步锁 
int StopSignal; 

extern void fixGantt(void);
extern void putstate(void);
extern void fixgante(void);

struct repair
{
	int point;//输入检修的时间点 
	int machine_num;//检修机器号 
	int fix_time;//检修时长 
}fix;

void Timekeeping(void)
{
	clock_t CurrentTime;
	//	setcolor(YELLOW); 
	//	bar(700,300,800,400);
	//clock_t CurrentTime;
	int flag=0;
	while(flag==0)
	{	
			
		
		int signal;
		char str[100];
		if ( kbhit() ) 
		signal= getch();
		if(signal=='C') 
		{ 
            //outtextxy(1000,600,"???");
            //setfillcolor(GREEN); 
			//bar(1000,200,1200,500);
			inputbox_getline("检修指令输入","请输入检修指令，格式如下\n<机器号><空格><检修时长><回车>",str,100);
			//outtextxy(1100,700, str);
			sscanf(str,"%d %d",&fix.machine_num,&fix.fix_time);
			
			//setfillcolor(GREEN);
			//bar(555,666,690,777); 
			CurrentTime=clock();
			fix.point=3*(int)(CurrentTime-start)/CLOCKS_PER_SEC;//谜之point？？？  
			//OutputRepair=1;
			
			/*输出机器状态*/
			setfillcolor(WHITE);
			bar(1255,105,1525,295);	//清空该输出区域 
			char RepairInfo[100];
			sprintf(RepairInfo,"检修机器号：%d  检修时长：%d",fix.machine_num,fix.fix_time);
			setcolor(BLACK);
			setfont(18, 0, "宋体");
			outtextxy(1255,105,RepairInfo);
			signal=0; 
			
			
			timechange();
		}
	 putstate();
		
			CountTimes+=2;
		Sleep(100);
//	setcolor(BLACK);
//	xyprintf(1100,500,"%d",StopSignal);
		if(StopSignal==1)
		{
		//	getch();
		//bar(300,5,400,100);
		//	return;
			flag=2333;
		//break;
	//	fixgante();
		}
			
		
	}
//	setcolor(GREEN);
	//xyprintf(1100,500,"MDZZ");
		//bar(1100,500,1200,600);
	return;
}
