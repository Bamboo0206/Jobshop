/*#include<stdio.h>
#include<stdlib.h>
#include<time.h>*/
#include"zqy.h"

#define POP_SIZE 100 
#define Pc 0.8
extern int DNA[180][200],pop[100][180];
int BEST[200]={0};
extern int DNA_SIZE;
extern double fit[180];
extern int product_num,machine_num;

void selectwst(double fit[180])
{
	int i,k,j;
	double temp[180] = { 0 };//各DNA的适应度比值 
	double Ran;//随机数 
	double F,sum;//F：总适应度，sum：前k个比值之和 
   // srand(time(NULL));
    for( i=0 ; i < POP_SIZE*(1+Pc) ; i++)
        F+=fit[i];
    for( i=0 ; i < POP_SIZE*(1+Pc) ; i++)
        temp[i]=(double)fit[i] / F;
    Ran=(double)rand()/(RAND_MAX+1.0);
    for( i=0 ; i < POP_SIZE ; i++)
   {
   	    //sum=0; 
        for( k =0; k < POP_SIZE*(1+Pc) ; k++ )
        {
            sum+=temp[k];
            if(sum<Ran && sum+temp[k+1]>=Ran)
            {
            	for(j = 0; j < DNA_SIZE; j ++ )
                    pop[i][j]=DNA[k+1][j];
			}
        }
    }
    
   	 	/*debug*/
/*	 	int h,zq;
	for(zq=0;zq<100;zq++)
	{
		int count_time1[200]={0},count_time2[200]={0};

		printf("\npop[%d]: ",zq);
		for(h=0;h<DNA_SIZE;h++)
		{
			count_time1[pop[zq][h]-1]++;
		 } 
		for(h=0;h<product_num;h++)
		{
			printf("%d ",count_time1[h]);
		 } 
	 	 putchar('\n');
		for(h=0;h<150;h++)
		{
			printf("%d ",pop[zq][h]);
		 } 
		 putchar('\n');
	}*/
	// printf("\n\nselect done!!!\n\n");
	
	
} 

void selectoutput(int DNA[180][200],double fit[180])
{
	double rate[180]={0};
	int i,best;
	double height;

	height=fit[0];
	for(i=0;i<180;i++)
	{
		if(fit[i]>height)
		 {
		 	 best=i;
		 	 height=fit[i];
			}  
	}
	
	for(i=0;i<200;i++)
	{
	    BEST[i]=DNA[best][i];
	   // printf("%d ",BEST[i]);
	}
	//printf("\n\n");

	return ;
}


    
  
