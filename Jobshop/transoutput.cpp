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
     int num[100];//�û����ϼӹ��Ĳ�Ʒ��� 
     int order[100];//��Ʒ����� 
     int begintime[100];//ÿ�μӹ��Ŀ�ʼʱ�� 
     int endtime[100];//ÿ�μӹ��Ľ���ʱ�� 
 }finaltime[50]={{0},{0},{0},{0}};

void transoutput(int BEST[])
{	
	int time[3][100]={{0},{0}};//��ʼ��Ϊ�� 
	int i=0,k=0,g=0;//i��DNA;k�������DNA�Ǽ��Ź���;g��������*/ 
	int j[100]={0},h[100]={0};/*j[k]�ƹ���h[g]�Ƹû����ӹ��ĵڼ�����Ʒ*/ 
	for(i=0;BEST[i]!=0;i++)
	{
		//0!!!
		k=BEST[i]-1;//��DNAȷ��������� 
		g=pro[k].machine[j[k]];//�������� 
		finaltime[g].order[h[g]]=j[k];//��Ʒ�����    �Ǵ�0��ʼ��get 
		finaltime[g].num[h[g]]=k;//��¼��Ʒ��� 
		if(time[1][k]>=time[2][g])//����Ҫ�ȴ���Ʒ��һ����� 
		{
			finaltime[g].begintime[h[g]]=time[1][k];//���濪ʼʱ�� 
			time[1][k]+=pro[k].time[j[k]];//��Ʒʱ�������У���Ӧ��Ʒʱ������
			time[2][g]=time[1][k];//ȷ��������ɸù����ʱ�� 
		}
		else//����Ҫ�ȴ��������� 
		{
			finaltime[g].begintime[h[g]]=time[2][g];//���濪ʼʱ�� 
			time[2][g]+=pro[k].time[j[k]];//����ʱ�������У���Ӧ����ʱ������ 
		    time[1][k]=time[2][g];//ȷ��������ɸù����ʱ�� 
		}
		finaltime[g].endtime[h[g]]=time[1][k];//�������ʱ�� 
		h[g]++;//ȷ��numλ��
		j[k]++;//ȷ���ĸ���������һ��
		
	}
	return; 
} 
