//#include<stdio.h>
#include"zqy.h"

extern int product_num;
extern int machine_num;
extern double duration;

extern struct timefinal
 {   
     int num[100];//�û����ϼӹ��Ĳ�Ʒ��� 
     int order[100];//��Ʒ����� 
     int begintime[100];//ÿ�μӹ��Ŀ�ʼʱ�� 
     int endtime[100];//ÿ�μӹ��Ľ���ʱ�� 
 }finaltime[50];

void output(struct timefinal finaltime[50])
{
	int i,n;
	int min;
	
	for(i=0;i<machine_num;i++)
	{
		printf("M%d ",i);
		for(n=0;finaltime[i].endtime[n];n++)
		{
			if(finaltime[i].endtime[n]!=finaltime[i].begintime[n])
			    printf("(%d,%d-%d,%d) ",finaltime[i].begintime[n],finaltime[i].num[n],finaltime[i].order[n],finaltime[i].endtime[n]);
			
		}
		printf("\n\n");
	}
	min=finaltime[0].endtime[0];
	for(i=0;i<machine_num;i++)
	{
		for(n=0;finaltime[i].endtime[n];n++)
		{
			if(finaltime[i].endtime[n]>min)
			    min=finaltime[i].endtime[n]; 
		}
	} 
	printf("Time Used:%lf\nEND Time:%d",duration,min);
 } 
