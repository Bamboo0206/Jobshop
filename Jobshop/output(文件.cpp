//#include<stdio.h>
#include"zqy.h"
extern int product_num,machine_num;
extern double duration;

extern struct timefinal
 {   
     int num[100];//该机器上加工的产品序号 
     int order[100];//产品工序号 
     int begintime[100];//每次加工的开始时间 
     int endtime[100];//每次加工的结束时间 
 }finaltime[50];

void outputFILE(struct timefinal finaltime[50])
{
	FILE *optr=fopen("output1.txt","w");
	
	int i,n;
	int min;
	
	for(i=0;i<machine_num;i++)
	{
		fprintf(optr,"M%d ",i);
		for(n=0;finaltime[i].endtime[n];n++)
		{
			if(finaltime[i].endtime[n]!=finaltime[i].begintime[n])
			fprintf(optr,"(%d,%d-%d,%d) ",finaltime[i].begintime[n],finaltime[i].num[n],finaltime[i].order[n],finaltime[i].endtime[n]);
		}
		fputc('\n',optr);
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
	fprintf(optr,"Time Used:%lf\nEND Time:%d",duration,min);
	
	fclose(optr);
	return ;
}
