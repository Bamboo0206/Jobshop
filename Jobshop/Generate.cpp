#include"zqy.h"
//采用基于工序的编 码方式进行染色体编码 



extern struct product{
	int total_time;//总时间 
	int order;//工序总个数 
	int time[100];
	int machine[100];
}pro[100];

extern int product_num,machine_num ;
extern int DNA_SIZE;
extern int temp_pop[100][200];
extern int countZQY;

int Pnum,Mnum;
int Time[200];

int RemainTotalTime[100];//每个工件剩余总时间//局部全局 
int DNA[180][200],pop[100][180];
int DNAnum;

//U[0][i]可调度工序的开始时间（当前第一个工序的开始时间），U[1][i]该可调度工序的序号，从0开始。
//U内为最早可能开工时间 



void Generate(void);

void InitativeDispatch(int);//主动调度 //完成一条DNA 
void NoDelayDispatch(int row);//无延迟调度 
void RandomDNA(int row); //随机形成一条DNA 

int SelectRule(int *candidate,int C_size,int U[][100]);//从多个符的合条件工序中选一个 
int MWR(int *candidate,int C_size,int U[][100]); //Most work remaining  剩余操作的总加工时间最长的工件先加工。
int SPT(int *candidate,int C_size,int U[][100]); //Shortest processing time  具有最短加工时间的（当前第一个）操作先加工
int RSP(int *candidate,int C_size,int U[][100]); //Randomly Select Prosess  随机选择工序
/*以上返回值均为选定的工件*/



void Generate(void)
{
	Pnum=product_num;
	Mnum=machine_num;
	int rdm,ppl=0,col=0;//random,population
	int i;//用于循环 	
	
		DNAnum=DNA_SIZE;
//	printf("1");
	
	//srand(time(NULL));//设置种子
		
//	printf("2");
	while(ppl<POP_SIZE) 
	{
		/*录入（重置） 剩余总加工时长数组。*/
		for(i=0;i<Pnum;i++)
			RemainTotalTime[i]=pro[i].total_time; 
		
		/*选一个工序，制作一条DNA*/
		
			rdm=rand()%10;//产生一个随机数0-9
			///*需要修改*/rdm=6; 
			//printf("%d",rdm); 
			if(rdm<=3) //0.4概率，选用主动调度 
			InitativeDispatch(ppl);
			else if(rdm>=6) //0.4概率，选用 无延迟 
			NoDelayDispatch(ppl);
			else //0.2概率，随机形成DNA 
			RandomDNA(ppl); 
		ppl++; 
	}
	/*debug*/
/*	int row;
	for(row=0;row<POP_SIZE;row++)
/*	{
		printf("pop[%d]",row);
		for(col=0;col<DNA_SIZE;col++){
			printf("%d ",pop[row][col]);
		}
	*	putchar('\n');
	}*/
	/*Debug*/
	int h,minT=99999,loc;
	for(h=0;h<POP_SIZE;h++)
	{
		if(minT>Time[h])
		{
			minT=Time[h];
			loc=h;
		}
	}
	for(h=0;h<DNA_SIZE;h++)//复制到temp里 
	{
		temp_pop[countZQY][h]=pop[loc][h];
	}
		printf("\nminT=%d\n",minT);
	//printf("GENERATE DONE\n");
}

void InitativeDispatch(int row)//主动调度 
{
	int col=0;
	int i,minTe=99999,Mselected;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[50]={0};/*初始化U*/
	
	
	
	while(col<DNAnum)//U内还有未安排工序
	{
	
		 
		int Porder;
		for(i=0,minTe=99999;i<Pnum;i++)
		{
			Porder=U[1][i];
			if(U[1][i]<pro[i].order)
			if(minTe>(U[0][i]+pro[i].time[Porder])) 
			{
				minTe=U[0][i]+pro[i].time[Porder];
				Mselected=pro[i].machine[Porder];
			}
		}
	for(i=0,countC=0;i<Pnum;i++)//选择候选人 
	{
		Porder=U[1][i];
		if(U[1][i]<pro[i].order)
		if(pro[i].machine[Porder]==Mselected&&U[0][i]<=minTe)
		{
			candidate[countC]=i+1;
			countC++;
		}
	}
	if(countC>1) 
		candidate[0]=SelectRule(candidate,countC,U);
	
	/*把基因加入DNA*/ 
	pop[row][col]=candidate[0];
	col++;
		
	/*更新U*/ 
		/*刷新最早可能开工时间*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U组和机器时间最大值，选定的工件，选定工件调度的工序，选定工件工序所需的机器 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*找U组和机器时间最大值*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*刷新时间*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//刷新U内时间 
	M[P_machine]=U[0][Pselected-1];//刷新机器时间 
			/*刷新在该机器上工作的其他工件的开工时间*/
	int P_other_order;
	for(i=0;i<Pnum;i++)
	{
		P_other_order=U[1][i];
		if(P_other_order<pro[i].order)
		if(pro[i].machine[P_other_order]==P_machine)
			if(U[0][i]<M[P_machine])
				U[0][i]=M[P_machine];
	}
	U[1][Pselected-1]++;
	
	
			/*debug*/
	//	int h;
	/*	for(h=0;h<Pnum;h++) 
		{
			printf("U[0][%d]=%d ",h,U[0][h]);
		}
		putchar('\n');
		for(h=0;h<Pnum;h++) 
		{
			printf("U[1][%d]=%d ",h,U[1][h]);
		}
		putchar('\n');
	/*	for(h=0;h<Mnum;h++) 
		{
			printf("M[%d]=%d ",h,M[h]);
		}
		putchar('\n');
		putchar('\n');*/
	
	} 
	
	
			/*debug*/
	/*	int h;
		for(h=0;h<DNAnum;h++) 
		{
			printf("%d ",pop[row][h]);
		}
		putchar('\n');*/
	
		
		/*一个输出时间的代码*/
		int finalT=0;
		for(i=0;i<Pnum;i++) 
		{
			if(U[0][i]>finalT)
			finalT=U[0][i];
		}
		//	printf("U[]max=%d\n",finalT);
		for(i=0;i<Mnum;i++) 
		{
		//	printf("M[]=%d\t",M[i]);
			if(M[i]>finalT)
			finalT=M[i];
		}
		//putchar('\n');
		Time[row]=finalT;
		//printf("DNA:%d\tTIME:%d\tID\n",row,finalT);
 } 

void NoDelayDispatch(int row)//无延迟调度 
{
	int col=0;
	int i,minTs=99999,Mselected;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[50]={0};/*初始化U*/
	int Porder;
	
	while(col<DNAnum)//U内还有未安排工序
	{
		
	for(i=0,minTs=99999;i<Pnum;i++)//计算U中工序最早可能开工时间minTs 
	{
		Porder=U[1][i];
		if(U[1][i]<pro[i].order)
			if(minTs>U[0][i])
			{
				minTs=U[0][i];
				Mselected=pro[i].machine[Porder];
			}
	}
	/*for(i=0;i<Mnum;i++)
	{
		if(M[i]==minTs)//选择一台最早开工时间为minTs 的机器 Mselected 
		{
			Mselected=i;
			break;
		}	
	}*/
	for(i=0,countC=0;i<Pnum;i++)
	{
		Porder=U[1][i];
		if(U[1][i]<pro[i].order){
		if(pro[i].machine[Porder]==Mselected&&U[0][i]==minTs)
		{
			candidate[countC]=i+1;
			countC++;
		}
		}
	}
	if(countC>1) 
		candidate[0]=SelectRule(candidate,countC,U);
	
	/*把基因加入DNA*/ 
	pop[row][col]=candidate[0];
	col++;

	/*更新U*/ 
		/*刷新最早可能开工时间*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U组和机器时间最大值，选定的工件，选定工件调度的工序，选定工件工序所需的机器 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*找U组和机器时间最大值*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*刷新时间*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//刷新U内时间 
	M[P_machine]=U[0][Pselected-1];//刷新机器时间 
			/*刷新在该机器上工作的其他工件的开工时间*/
	int P_other_order;
	for(i=0;i<Pnum;i++)
	{
		P_other_order=U[1][i];
		if(P_other_order<pro[i].order)
		if(pro[i].machine[P_other_order]==P_machine)
			if(U[0][i]<M[P_machine])
				U[0][i]=M[P_machine];
	}
	U[1][Pselected-1]++;
		/*debug*/
		int h;
	/*	for(h=0;h<Pnum;h++) 
		{
			printf("U[0][%d]=%d ",h,U[0][h]);
		}
		putchar('\n');
		for(h=0;h<Pnum;h++) 
		{
			printf("U[1][%d]=%d ",h,U[1][h]);
		}
		putchar('\n');
	/*	for(h=0;h<Mnum;h++) 
		{
			printf("M[%d]=%d ",h,M[h]);
		}
		putchar('\n');
		putchar('\n');*/
	
	} 
	
	
			/*debug*/
	/*	int h;
		for(h=0;h<DNAnum;h++) 
		{
			printf("%d ",pop[row][h]);
		}
		putchar('\n');
	
	
		
		/*下面插播一个输出时间的代码*/
		int finalT=0;
		for(i=0;i<Pnum;i++) 
		{
			if(U[0][i]>finalT)
			finalT=U[0][i];
		}
		for(i=0;i<Mnum;i++) 
		{
			if(M[i]>finalT)
			finalT=M[i];
		}
		Time[row]=finalT;
		//printf("DNA:%d\tTIME:%d\tNDD\n",row,finalT);
 } 

void RandomDNA(int row) //随机形成一条DNA 
{
	int i,j,count=0,col=0;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[100]={0};/*初始化U*/
	
	while(col<DNAnum)//U内还有未安排工序
	{
		
		/*录入candidate*/
		int Porder;
		for(i=0,countC=0;i<Pnum;i++)
		{
			Porder=U[1][i];
			if(Porder<pro[i].order)//？？？ 
			{
				candidate[countC]=i+1;
				countC++;
			}
		}
		if(countC>1)
		candidate[0]=RSP(candidate,countC,U);
		
		pop[row][col]=candidate[0];
		col++;

	/*更新U*/ 
		/*刷新最早可能开工时间*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U组和机器时间最大值，选定的工件，选定工件调度的工序，选定工件工序所需的机器 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*找U组和机器时间最大值*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*刷新时间*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//刷新U内时间 
	M[P_machine]=U[0][Pselected-1];//刷新机器时间 
		/*刷新在该机器上工作的其他工件的开工时间*/
	int P_other_order;
	for(i=0;i<Pnum;i++)
	{
		P_other_order=U[1][i];
		if(pro[i].machine[P_other_order]==P_machine)
			if(U[0][i]<M[P_machine])
				U[0][i]=M[P_machine];
	}
	
	U[1][Pselected-1]++;
	
	
		/*debug*/
		/*int h;
		for(h=0;h<Pnum;h++) 
		{
			printf("U[0][%d]=%d ",h,U[0][h]);
		}
		putchar('\n');
		for(h=0;h<Pnum;h++) 
		{
			printf("U[1][%d]=%d ",h,U[1][h]);
		}
		putchar('\n');
		for(h=0;h<Mnum;h++) 
		{
			printf("M[%d]=%d ",h,M[h]);
		}
		putchar('\n');
		putchar('\n');*/
	
	}
	
	
			/*debug*/
	/*	int h;
		for(h=0;h<DNAnum;h++) 
		{
			printf("%d ",pop[row][h]);
		}
		putchar('\n');
	
		
	
	
	
		
		/*下面插播一个输出时间的代码*/
		int finalT=0;
		for(i=0;i<Pnum;i++) 
		{
			if(U[0][i]>finalT)
			finalT=U[0][i];
		}
		for(i=0;i<Mnum;i++) 
		{
			if(M[i]>finalT)
			finalT=M[i];
		}
		Time[row]=finalT;
		//printf("DNA:%d\tTIME:%d\tRDNA\n",row,finalT);
 } 


int SelectRule(int *candidate,int C_size,int U[][100]) 
{	 
	int i,Cselected,rdm;
		rdm=rand()%10;//产生一个随机数0-9
			
			if(rdm<=3) //0.4概率，选用规则MWR 
			Cselected=MWR(candidate,C_size,U);
			else if(rdm>=6) //0.4概率，选用规则SPT 
			Cselected=SPT(candidate,C_size,U);
			else //0.2概率，随机选择工序 
			Cselected=RSP(candidate,C_size,U);
	
	return Cselected;
}

int MWR(int *candidate,int C_size,int U[][100]) //Most work remaining  剩余操作的总加工时间最长的工件先加工。
{
	int i,gene,maxT=0;
	int cdd_num;//候选工件 工件号 
	/*选择剩余总加工时长的工件的（当前第一个？）工序，加入基因 */
	/*从candidate中选择*/
	for(i=0;i<C_size;i++)
	{
		cdd_num=candidate[i];
		if(maxT<RemainTotalTime[cdd_num-1])
		{
			maxT=RemainTotalTime[cdd_num-1];
			gene=cdd_num;
		}
	}

	/*更新 剩余总加工时长数组。（减掉时间 */
	int Porder;
	Porder=U[1][gene-1];
	RemainTotalTime[gene-1]-=pro[gene-1].time[Porder];
	
	return gene;
 } 

int SPT(int *candidate,int C_size,int U[][100]) //Shortest processing time  具有最短加工时间的操作先加工
{
	/*找每个工件当前第一个工序，最短时间的加入DNA*/
	//要不把U[]传进来？用到order？ 
	
	int minT=99999,Pmin,i;//最小时间，最小时间对应工件，
	int Pcdd,Porder;//当前候选工件 ,候选工件可调度工序号 
	for(i=0;i<C_size;i++)
	{
		Pcdd=candidate[i];
		Porder=U[1][Pcdd]; 
		if(pro[Pcdd-1].time[Porder]<minT)
		{
			minT=pro[Pcdd-1].time[Porder];
			Pmin=Pcdd;
		 } 
	}
	
	/*更新*/
	/*更新 剩余总加工时长数组。（减掉时间 */
	Porder=U[1][Pmin-1];//选定产品可调度工序号（从0开始 
	RemainTotalTime[Pmin-1]-=pro[Pmin-1].time[Porder];
	
	return Pmin; 
}
 
int RSP(int *candidate,int C_size,int U[][100]) //Randomly Select Prosess  随机选择工序
{
	/*在candidate中随机选一个加入DNA(其实还是只能抽每个工件的当前第一个工序）*/
	/*从candidate里抽一个啊！*/
	int rdm,i,Pselected;
	
		
	rdm=rand()%C_size;
	Pselected=candidate[rdm]; 
	
	//更新 
	/*更新 剩余总加工时长数组。（减掉时间 */
	int Porder;
	Porder=U[1][Pselected-1];
	RemainTotalTime[Pselected-1]-=pro[Pselected-1].time[Porder];
	
	return Pselected;
} 
