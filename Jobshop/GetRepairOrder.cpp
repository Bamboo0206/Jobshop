/*#include <graphics.h>
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h> 
#include<windows.h>   //�����̺߳�����Ҫ����ϵͳ����
#include<process.h>   //�����̺߳���ͷ�ļ�
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
int OutputRepair;//main���������ָ���ͬ���� 
int StopSignal; 
//Ӧ�û���һ���������������ͬ���� 

//����Ҫ�Ѽ����������.cpp��Ķ���ճ��main�ﴴ���߳� 
unsigned __stdcall GetRepairOrder(void* pArguments)
{
	/*
	����ָ��ĸ�ʽΪ��
	<C><������> <�ո�><����ʱ��><\n>
	*/ 
	int signal=0;
	clock_t CurrentTime;
	
	setfont(50, 0, "����");
	setcolor(BLACK);
	outtextxy(1300,300,"������ʲô");
	setfillcolor(YELLOW); 
	bar(100,100,200,700);
        	char str[100];
	while(StopSignal!=1)//����ǰʱ��С����ʱ�� 
	{
		outtextxy(100,600,"���붫��");
		signal=getch();//�ȴ��û�����//ege����ĺ���
		setfillcolor(RED); 
		bar(500,100,600,300);
		if(signal=='C') 
		{ 
			    /*inputbox_getline("����һ���Ի���",
                    "�����\n����һ���ַ�����������س�",
                    str,
                    sizeof(str)/sizeof(*str));*/
            //outtextxy(1000,600,"???");
            setfillcolor(GREEN); 
		bar(1000,200,1200,500);
			inputbox_getline("����ָ������","���������ָ���ʽ����\n<������><�ո�><����ʱ��><�س�>",str,100);
			outtextxy(1100,700, str);
			sscanf(str,"%d %d",&fix.machine_num,&fix.fix_time);
		//	outtextxy(1300, 700,);
			//outtextxy(1400, 800, mc_time);
			
			setfillcolor(GREEN);
			bar(555,666,690,777); 
			CurrentTime=clock();
			fix.point=3*(int)(CurrentTime-start)/CLOCKS_PER_SEC;//��֮point������  
			//OutputRepair=1;
			
			/*�������״̬*/
			setfillcolor(WHITE);
			bar(1255,105,1525,295);	//��ո�������� 
			char RepairInfo[50];
			sprintf(RepairInfo,"���޻����ţ�%d\n����ʱ����%d",fix.machine_num,fix.fix_time);
			setcolor(BLACK);
			setfont(18, 0, "����");
			outtextxy(925,105,RepairInfo);
			
			
			timechange();
		}
	 } 
	 outtextxy(1500,300,"�˳�");
	 
	 _endthreadex(0);//�߳����ʱҪ����_endthread
	 return 0; 
}
