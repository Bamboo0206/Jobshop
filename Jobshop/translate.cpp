#include<stdio.h>
#include<stdlib.h>

//#include"zqy.h"
#define POP_SIZE 180 
extern int DNA_SIZE;
extern int product_num;  
extern int machine_num;
extern int DNA[180][200]; 

int tf[180]={0}; 

extern struct product{
	int total_time;
	int order;
	int time[100];
	int machine[100];
}pro[100];

int size=100;

void translate(void)//直接调用DNA[POP_SIZE][DNA_SIZE],time[POP_SIZE] 
{
   /* int i,j;
	for(i=0;i<180;i++)
	{
		printf("%d\n",i);
		for(j=0;j<200;j++)
		printf("%d ",DNA[i][j]);
		printf("\n");
	}*/
	int a;//i读取每条DNA并储存时间
   // printf("BEGIN TRANSLATE!\n"); 
	for(a=0;a<180;a++)
	{
		int t[3][100]={{0},{0}};
	    int i=0,k=0,g=0;//i读DNA;k存读到的DNA是几号工件;g存机器序号*/ 
        int j[100]={0};/*j[k]计工序*/
        
        for(i=0;DNA[a][i]!=0;i++)
       	{
           	//数组从0开始存！！！！！！ 
			k=DNA[a][i]-1;//读DNA确定工件序号 （数组-1） 
        	g=pro[k].machine[j[k]];//存机器序号(数组（-1），末尾再+1)
			//j[k]++;//确定哪个工件的哪一步
        	if(t[1][k]>=t[2][g])//若需要等待产品上一步完成 
        	{
        		t[1][k]+=pro[k].time[j[k]];//产品时间数组中，相应产品时间增加
       			t[2][g]=t[1][k];//确定机器完成该工序的时间 
       		}
       		else//若需要等待机器空闲 
       		{
        		t[2][g]+=pro[k].time[j[k]];//机器时间数组中，相应机器时间增加 
        	    t[1][k]=t[2][g];//确定工件完成该工序的时间 
           	}
           	j[k]++;//确定哪个工件的哪一步
       	}
        /*int flag=0;
		for(i=0;i<product_num&&flag==0;i++)
        {
        	if(j[i]!=pro[i].order)
        	flag=1;
		}
		if(flag==0)
		{  */
			int maxi=0;//确定最终时间 
       	    int p,q;
		    for(p=1,q=0;q<product_num;q++)
            {
	         	if(t[p][q]>maxi)
	         	maxi=t[p][q];
         	}
            tf[a]=maxi;
		/*}
		if(flag==1)
		{
			tf[a]=0;
			for(i=0;i<200;i++)
			DNA[a][i]=0;
		}*/
    }
    //printf("translate finish\n");
   int i; 
   printf("\n\n"); 
    for(i=0;i<180;i++)
    {
    	printf("%d\t",tf[i]);
	}
	printf("translatefinish!\n");
	return ; 
}

