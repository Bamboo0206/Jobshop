#include<stdio.h>
#include<math.h>
//#include"zqy.h"
#define POP_SIZE 180 

double fit[180]={0};
extern int tf[180];

/*float powf(float x,float y);x^y
double fabs(double);//绝对值  */ 

int maxi(int tf[]);//max
int mini(int tf[]);//min       /*time[POP_SIZE]储存translate结束得到的各DNA时间*/

double max(double a,double b);//find out the max

int maxi(int tf[])
{
	int a,i=0; 
	a=tf[0];//a=maxi
	for(i=0;i<POP_SIZE;i++)
	{
		if(tf[i]>a)
		a=tf[i];
	}
	//返回最大值
	return a; 
}
int mini(int tf[])
{
	int a,i=0; 
	a=tf[0];//a=mini
	for(i=0;i<POP_SIZE;i++)
	{
		if(tf[i]<a)
		a=tf[i];
	}
	return a;//返回最小值 
}

double max(double a,double b)
{
	if(a<=b)
	return b;
	else
	return a;
}

void fitness()
{
	double a=0;
	int i=0,m=0,M=0;
	M=maxi(tf);
	m=mini(tf);
	a=max(0.5,(double)(M-m)/20);
	for(i=0;i<POP_SIZE;i++)
	{
		if(fabs(tf[i]-m)>a)
		fit[i]=(double)1/(1+powf((double)fabs(tf[i]-m)/a,2));
		else
		fit[i]=1-(double)fabs(tf[i]-m)/(2*a);
		//printf("%.3lf\t",fit[i]);
	}
	
	return ;
 } 
