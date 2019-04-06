#include"zqy.h"

extern int DNA[180][200];
extern int product_num,machine_num ;
extern int DNA_SIZE;

void Mutate(void)
{
//	printf("\nMUTATE beging!\n\n");
	int i=0,row,col1,col2,count,swap;
	//	srand(time(NULL));//设置种子
	while(i<(POP_SIZE*(1+Pc))*Pm)
	{
		/*抽一个DNA出来变异？*/
		row=rand()%(int)((1+Pc)*POP_SIZE); 
		for(count=0;count<100;count++)
		{
			col1=rand()%DNA_SIZE;
			col2=rand()%DNA_SIZE;
			
			swap=DNA[row][col1];
			DNA[row][col1]=DNA[row][col2];
			DNA[row][col2]=swap;
		}
		
		i++; 
		/*debug*/
/*	int h;
	printf("\nmutate=%d DNA[%d]: ",i,row);
	for(h=0;h<DNA_SIZE;h++)
	{
		printf("%d ",DNA[row][h]);
	 } */
	 
	 } 
	 	/*debug*/
/*	 	int h,zq;
		for(zq=0;zq<180;zq++)
	{
		int count_time1[200]={0},count_time2[200]={0};

	printf("\nDNA[%d]: ",zq);
	for(h=0;h<DNA_SIZE;h++)
	{
		count_time1[DNA[zq][h]-1]++;
	 } 
	for(h=0;h<product_num;h++)
	{
		printf("%d ",count_time1[h]);
	 } 
	}*/
//	 printf("\n\nmutate done!!!\n\n");
 } 
