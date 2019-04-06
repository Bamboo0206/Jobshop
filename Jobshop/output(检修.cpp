#include<graphics.h>
#include<string.h>
#include<stdlib.h> 
#include<stdio.h>
#include<time.h> 
extern int product_num,machine_num;
extern double duration;

/*extern struct timefinal
{   
    int num[100];//该机器上加工的产品序号 
    int order[100];//产品工序号 
    int begintime[100];//每次加工的开始时间 
    int endtime[100];//每次加工的结束时间 
 }finaltime[50];
 */
 
extern struct recordfix
{
	int start[100];
	int end[100];
}machinefix[50];
 
 
void outputfix()
{
	
	struct finalmachine{   
        int num[100];//该机器上加工的产品序号 
        int order[100];//产品工序号 
        int begintime[100];//每次加工的开始时间 
        int endtime[100];//每次加工的结束时间 
        int process_num;
    }fma[50];
	
    FILE *dptr=fopen("lff.txt","r");
	
	int c,i,j;
	char ch;
    int count=0;
	
	double time_use;
	int all_time;
	
	if(dptr==NULL)
	    outtextxy(0,0,"Can't open output file!");
	else
	{
		 
		while(!feof(dptr))
		{
			for(j=0;j<machine_num;j++)
			{
				fscanf(dptr,"M%d",&c);
				for(i=0;fgetc(dptr)==' ';i++)
				{
					fscanf(dptr,"(%d,%d-%d,%d)",&fma[c].begintime[i],&fma[c].num[i],&fma[c].order[i],&fma[c].endtime[i]);
					count++;
				}
				fma[c].process_num=count-1;
				count=0;
			}
			if(j==machine_num) break;
		}
		//fscanf(optr,"Time Used:%lf\nEND Time:%d",&time_use,&all_time);
		
	}
	fclose(dptr);
	
	
	 
	FILE *optr=fopen("output2.txt","w");
	
	int n;
	int min;
	
	for(i=0;i<machine_num;i++)
	{
		fprintf(optr,"M%d ",i);
		for(n=0;fma[i].endtime[n];n++)
		{
			
			 
			
			if(fma[i].endtime[n]!=fma[i].begintime[n])
			fprintf(optr,"(%d,%d-%d,%d) ",fma[i].begintime[n],fma[i].num[n],fma[i].order[n],fma[i].endtime[n]);
			
			
			//检修需求输出
			for(j=0;machinefix[i].end[j]!=0;j++)
			{
				if(machinefix[i].start[j]<fma[i].begintime[n+1] && machinefix[i].start[j]>=fma[i].endtime[n])
				    fprintf(optr,"(%d,检修,%d)",machinefix[i].start[j],machinefix[i].end[j]); 
			}
		}
		fputc('\n',optr);
	}
	
	min=fma[0].endtime[0];
	for(i=0;i<machine_num;i++)
	{
		for(n=0;fma[i].endtime[n];n++)
		{
			if(fma[i].endtime[n]>min)
			    min=fma[i].endtime[n]; 
		}
	} 
	fprintf(optr,"Time Used:%lf\nEND Time:%d",duration,min);
	
	fclose(optr);

} 
