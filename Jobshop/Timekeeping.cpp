/*#include<windows.h>   //�����̺߳�����Ҫ����ϵͳ����
#include<process.h>   //�����̺߳���ͷ�ļ�
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h> 
#include<time.h>*/

#include"zqy.h"
int CountTimes;//ʹ��ǰ������ //��main���������� 
extern int OutputRepair;//�������ָ���ͬ����  
extern int StopSignal; 
extern void fixGantt(void);
extern void putstate(void);
extern struct repair
{
	int point;
	int machine_num;
	int fix_time;
}fix;

unsigned __stdcall Timekeeping(void* signal)//��ʱ���� 
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{
	while(StopSignal!=1)//����ǰ���㼴�� 
	{
		//fixGantt();
		putstate();
		CountTimes+=2;
		Sleep(2000);
	} 
	
	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}
