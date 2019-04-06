/*
Step1   随机划分工件集{1, 2, 3,……, n}为两个非空的子集 J1 和J2。
Step2   复制 Parent1 包含在 J1 的工件到 children，Parent2 包含在 J1 的工件到 Children2，保留它们的位置。
Step3   复制 Parent2 包含在 J2 的工件到 Children1，Parent1 包含在 J2 的工件到Children2，保留它们的顺序。
*/

#include"zqy.h"


extern int DNA[180][200],pop[100][180];
extern int DNA_SIZE,product_num;	

void Crossover(void);
void POX(int parent1,int parent2,int C_loc); 


void Crossover(void)
{
	int c_ppl=0,parent1,parent2; //children population 
	
	/*需要把pop里的DNA复制到DNA里？*/
	int row,col;
//	printf("DNA SIZE %d \n",DNA_SIZE);
	
	for(row=0;row<POP_SIZE;row++)
	{
		//printf("pop[%d]",row);
		//for(col=0;col<DNA_SIZE;col++){
		//	printf("%d ",pop[row][col]);
		//}
	//	putchar('\n');
		for(col=0;col<DNA_SIZE;col++){
			DNA[row][col]=pop[row][col];
		}
			
			/*debug*/
	/*int h;
	printf("\nDNA[%d]: ",row);
	for(h=0;h<DNA_SIZE;h++)
	{
		printf("%d ",DNA[row][h]);
	 } 
	 putchar('\n');*/
	}
	
	/*生成子代*/
//	srand(time(NULL));//设置种子
	c_ppl=0; 
	while(c_ppl<POP_SIZE*Pc) //未完成所有交叉,生成全部子代 
	{
		/*抽一个基因出来变异？*/
		parent1=rand()%POP_SIZE;//抽两个DNA 
		parent2=rand()%POP_SIZE;
		POX(parent1,parent2,c_ppl+POP_SIZE);//传入两个DNA（的位置）
		c_ppl+=2;
	 } 
//	printf("crossover DONE\n");
}

void POX(int parent1,int parent2,int C_loc)
{
	int child1,child2,rdm; 
	
	/*随机划分product[]*/
	int i,k,J1[100]={0},J2[100]={0},count1=0,count2=0; 
	while((count1+count2)<product_num)
	{
		rdm=rand()%2;
		if(rdm==1)
		{
			J1[count1]=count1+count2+1;
			count1++;
		}
		else
		{
			J2[count2]=count1+count2+1;
			count2++;
		}
	}
			/*debug*/
/*	int h;
	printf("\nJ1[]: ");
	for(h=0;h<count1;h++)
	{
		printf("%d ",J1[h]);
	 } 
	 printf("\nJ2[]: ");
	for(h=0;h<count2;h++)
	{
		printf("%d ",J2[h]);
	 } */
	
	
	/*找到两个child的位置*/
	child1=C_loc;
	child2=C_loc+1;
	
	/*复制 Parent1 包含在 J1 的工件到 child1，Parent2 包含在 J1 的工件到 Child2，保留它们的位置。位置！！！*/
	/*复制 Parent2 包含在 J2 的工件到 Child1，Parent1 包含在 J2 的工件到Child2，保留它们的顺序。*/
	int find;
	int loc1[200]={0},loc2[200]={0};
	for(i=0;i<DNA_SIZE;i++)
	{
		find=0;
		for(k=0;k<count1;k++)
		{
			if(pop[parent1][i]==J1[k])
			{
				find=1;
				break;
			}
			else
				find=0;
		}
			if(find==1)/*复制 Parent1 包含在 J1 的工件到 child1保留它们的位置。位置！！！*/
			{
				DNA[child1][i]=pop[parent1][i];
				loc1[i]=1;
			}
	}
	/*debug*/
	//int h;
/*	printf("\nchild[%d]: ",child1);
	for(h=0;h<DNA_SIZE;h++)
	{
		printf("%d ",DNA[child1][h]);
	 } */
	for(i=0;i<DNA_SIZE;i++)/*复制 Parent2 包含在 J1 的工件到 Child2，保留它们的位置。位置！！！*/
	{
		find=0;
		for(k=0;k<count1;k++)
		{
			if(pop[parent2][i]==J1[k])
			{
				find=1;
				break;
			}
			else
				find=0;
		}
			if(find==1)
			{
				DNA[child2][i]=pop[parent2][i];
				loc2[i]=1;
			}
	}
	
	for(i=0;i<DNA_SIZE;i++)/*复制 Parent2 包含在 J2 的工件到 Child1，保留它们的顺序。*/
	{
			find=0;
		for(k=0;k<count2;k++)
		{
			if(pop[parent2][i]==J2[k])
			{
				find=2;
				break;
			}
			else
				find=0;
		}
			if(find==2)
			{
				int a;
				for(a=0;a<DNA_SIZE;a++)
				{
					if(loc1[a]==0)
					{
						DNA[child1][a]=pop[parent2][i];
						loc1[a]=1;
						break;
					}
				}
			}
	}
	for(i=0;i<DNA_SIZE;i++)/*复制 Parent1 包含在 J2 的工件到Child2，保留它们的顺序。*/
	{
			find=0;
		for(k=0;k<count2;k++)
		{
			if(pop[parent1][i]==J2[k])
			{
				find=2;
				break;
			}
			else
				find=0;
		}
			if(find==2)
			{
				int a;
				for(a=0;a<DNA_SIZE;a++)
				{
					if(loc2[a]==0)
					{
						DNA[child2][a]=pop[parent1][i];
						loc2[a]=1;
						break;
					}
				}
			}
	}
	/*debug*/
//	int h,count_time1[200]={0},count_time2[200]={0};
/*	printf("\nchild[%d]: ",child1);
	for(h=0;h<DNA_SIZE;h++)
	{
		printf("%d ",DNA[child1][h]);
	 } 
	 printf("\nchild[%d]: ",child2);
	for(h=0;h<DNA_SIZE;h++)
	{
		printf("%d ",DNA[child2][h]);
	 } */
/*	printf("\nchild[%d]: ",child1);
	for(h=0;h<DNA_SIZE;h++)
	{
		count_time1[DNA[child1][h]-1]++;
	 } 
	for(h=0;h<product_num;h++)
	{
		printf("%d ",count_time1[h]);
	 } 
	 printf("\nchild[%d]: ",child2);
	for(h=0;h<DNA_SIZE;h++)
	{
		count_time2[DNA[child2][h]-1]++;
	 } 
	for(h=0;h<product_num;h++)
	{
		printf("%d ",count_time2[h]);
	 } */
}
