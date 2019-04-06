#include"zqy.h"

extern int product_num;
extern int machine_num; 

extern struct product{
	int total_time;
	int order;
	int time[100];
	int machine[100];
}pro[100];

struct timefinal
 {   
     int num[100];//该机器上加工的产品序号 
     int order[100];//产品工序号 
     int begintime[100];//每次加工的开始时间 
     int endtime[100];//每次加工的结束时间 
 }finaltime[50]={{0},{0},{0},{0}};

void transoutput(int BEST[])
{	
	int time[3][100]={{0},{0}};//初始化为零 
	int i=0,k=0,g=0;//i读DNA;k存读到的DNA是几号工件;g存机器序号*/ 
	int j[100]={0},h[100]={0};/*j[k]计工序；h[g]计该机器加工的第几个产品*/ 
	for(i=0;BEST[i]!=0;i++)
	{
		//0!!!
		k=BEST[i]-1;//读DNA确定工件序号 
		g=pro[k].machine[j[k]];//存机器序号 
		finaltime[g].order[h[g]]=j[k];//产品工序号    是从0开始的get 
		finaltime[g].num[h[g]]=k;//记录产品序号 
		if(time[1][k]>=time[2][g])//若需要等待产品上一步完成 
		{
			finaltime[g].begintime[h[g]]=time[1][k];//储存开始时间 
			time[1][k]+=pro[k].time[j[k]];//产品时间数组中，相应产品时间增加
			time[2][g]=time[1][k];//确定机器完成该工序的时间 
		}
		else//若需要等待机器空闲 
		{
			finaltime[g].begintime[h[g]]=time[2][g];//储存开始时间 
			time[2][g]+=pro[k].time[j[k]];//机器时间数组中，相应机器时间增加 
		    time[1][k]=time[2][g];//确定工件完成该工序的时间 
		}
		finaltime[g].endtime[h[g]]=time[1][k];//储存结束时间 
		h[g]++;//确定num位置
		j[k]++;//确定哪个工件的哪一步
		
	}
	return; 
} 
