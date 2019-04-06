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
				while(fgetc(fptr)==' ')//不知道一行的终止条件。。 
				{
					//fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
					fscanf(fptr,"%d %d",&pro[i].machine[count],&pro[i].time[count]);
					pro[i].total_time+=pro[i].time[count]; //一个产品的工序总时间 
					count++;
				}
				pro[i].order=count;//共多少道工序 
				count=0;
				
			}
		}
	}
	fclose(fptr);
	
	//打印一下下 
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
