//#include<stdio.h>
#include"zqy.h"
int product_num,machine_num;
struct product{
	int total_time; 
	int order;
	int time[100];
	int machine[100];
}pro[100]; 
//struct product pro[100] = {0};


void inputFILE(struct product pro[100])
{
	FILE *fptr=fopen("input.txt","r");
	
	char ch;
	int i,count=0,n,m;
	
	if(fptr==NULL)
	    printf("Can't open file!\n");
	else{
		while(!feof(fptr))
		{
			fscanf(fptr,"%d %d",&product_num,&machine_num);	
			fgetc(fptr);
			
			for(i=0;i<product_num;i++)
			{
				//fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
				fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
				pro[i].total_time+=pro[i].time[count];
				count++; 
				while(fgetc(fptr)==' ')//��֪��һ�е���ֹ�������� 
				{
					//fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
					fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
					pro[i].total_time+=pro[i].time[count]; //һ����Ʒ�Ĺ�����ʱ�� 
					count++;
				}
				pro[i].order=count;//�����ٵ����� 
				count=0;
				
			}
		}
	}
	fclose(fptr);
	
	//��ӡһ���� 
/*	printf("%d %d\n",product_num,machine_num);
	for(n=0;n<product_num;n++)
	{
		printf("%d ",n);
		for(m=0
		;m<pro[n].order;m++)
		{
			printf("(%d,%d) ",pro[n].time[m],pro[n].machine[m]);
		}
		printf("\n");
		printf("%d\n",pro[n].order);
	}*/

	return ;
}
