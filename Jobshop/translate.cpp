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

void translate(void)//ֱ�ӵ���DNA[POP_SIZE][DNA_SIZE],time[POP_SIZE] 
{
   /* int i,j;
	for(i=0;i<180;i++)
	{
		printf("%d\n",i);
		for(j=0;j<200;j++)
		printf("%d ",DNA[i][j]);
		printf("\n");
	}*/
	int a;//i��ȡÿ��DNA������ʱ��
   // printf("BEGIN TRANSLATE!\n"); 
	for(a=0;a<180;a++)
	{
		int t[3][100]={{0},{0}};
	    int i=0,k=0,g=0;//i��DNA;k�������DNA�Ǽ��Ź���;g��������*/ 
        int j[100]={0};/*j[k]�ƹ���*/
        
        for(i=0;DNA[a][i]!=0;i++)
       	{
           	//�����0��ʼ�棡���������� 
			k=DNA[a][i]-1;//��DNAȷ��������� ������-1�� 
        	g=pro[k].machine[j[k]];//��������(���飨-1����ĩβ��+1)
			//j[k]++;//ȷ���ĸ���������һ��
        	if(t[1][k]>=t[2][g])//����Ҫ�ȴ���Ʒ��һ����� 
        	{
        		t[1][k]+=pro[k].time[j[k]];//��Ʒʱ�������У���Ӧ��Ʒʱ������
       			t[2][g]=t[1][k];//ȷ��������ɸù����ʱ�� 
       		}
       		else//����Ҫ�ȴ��������� 
       		{
        		t[2][g]+=pro[k].time[j[k]];//����ʱ�������У���Ӧ����ʱ������ 
        	    t[1][k]=t[2][g];//ȷ��������ɸù����ʱ�� 
           	}
           	j[k]++;//ȷ���ĸ���������һ��
       	}
        /*int flag=0;
		for(i=0;i<product_num&&flag==0;i++)
        {
        	if(j[i]!=pro[i].order)
        	flag=1;
		}
		if(flag==0)
		{  */
			int maxi=0;//ȷ������ʱ�� 
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

