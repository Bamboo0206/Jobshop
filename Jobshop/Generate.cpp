#include"zqy.h"
//���û��ڹ���ı� �뷽ʽ����Ⱦɫ����� 



extern struct product{
	int total_time;//��ʱ�� 
	int order;//�����ܸ��� 
	int time[100];
	int machine[100];
}pro[100];

extern int product_num,machine_num ;
extern int DNA_SIZE;
extern int temp_pop[100][200];
extern int countZQY;

int Pnum,Mnum;
int Time[200];

int RemainTotalTime[100];//ÿ������ʣ����ʱ��//�ֲ�ȫ�� 
int DNA[180][200],pop[100][180];
int DNAnum;

//U[0][i]�ɵ��ȹ���Ŀ�ʼʱ�䣨��ǰ��һ������Ŀ�ʼʱ�䣩��U[1][i]�ÿɵ��ȹ������ţ���0��ʼ��
//U��Ϊ������ܿ���ʱ�� 



void Generate(void);

void InitativeDispatch(int);//�������� //���һ��DNA 
void NoDelayDispatch(int row);//���ӳٵ��� 
void RandomDNA(int row); //����γ�һ��DNA 

int SelectRule(int *candidate,int C_size,int U[][100]);//�Ӷ�����ĺ�����������ѡһ�� 
int MWR(int *candidate,int C_size,int U[][100]); //Most work remaining  ʣ��������ܼӹ�ʱ����Ĺ����ȼӹ���
int SPT(int *candidate,int C_size,int U[][100]); //Shortest processing time  ������̼ӹ�ʱ��ģ���ǰ��һ���������ȼӹ�
int RSP(int *candidate,int C_size,int U[][100]); //Randomly Select Prosess  ���ѡ����
/*���Ϸ���ֵ��Ϊѡ���Ĺ���*/



void Generate(void)
{
	Pnum=product_num;
	Mnum=machine_num;
	int rdm,ppl=0,col=0;//random,population
	int i;//����ѭ�� 	
	
		DNAnum=DNA_SIZE;
//	printf("1");
	
	//srand(time(NULL));//��������
		
//	printf("2");
	while(ppl<POP_SIZE) 
	{
		/*¼�루���ã� ʣ���ܼӹ�ʱ�����顣*/
		for(i=0;i<Pnum;i++)
			RemainTotalTime[i]=pro[i].total_time; 
		
		/*ѡһ����������һ��DNA*/
		
			rdm=rand()%10;//����һ�������0-9
			///*��Ҫ�޸�*/rdm=6; 
			//printf("%d",rdm); 
			if(rdm<=3) //0.4���ʣ�ѡ���������� 
			InitativeDispatch(ppl);
			else if(rdm>=6) //0.4���ʣ�ѡ�� ���ӳ� 
			NoDelayDispatch(ppl);
			else //0.2���ʣ�����γ�DNA 
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
	for(h=0;h<DNA_SIZE;h++)//���Ƶ�temp�� 
	{
		temp_pop[countZQY][h]=pop[loc][h];
	}
		printf("\nminT=%d\n",minT);
	//printf("GENERATE DONE\n");
}

void InitativeDispatch(int row)//�������� 
{
	int col=0;
	int i,minTe=99999,Mselected;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[50]={0};/*��ʼ��U*/
	
	
	
	while(col<DNAnum)//U�ڻ���δ���Ź���
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
	for(i=0,countC=0;i<Pnum;i++)//ѡ���ѡ�� 
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
	
	/*�ѻ������DNA*/ 
	pop[row][col]=candidate[0];
	col++;
		
	/*����U*/ 
		/*ˢ��������ܿ���ʱ��*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U��ͻ���ʱ�����ֵ��ѡ���Ĺ�����ѡ���������ȵĹ���ѡ��������������Ļ��� 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*��U��ͻ���ʱ�����ֵ*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*ˢ��ʱ��*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//ˢ��U��ʱ�� 
	M[P_machine]=U[0][Pselected-1];//ˢ�»���ʱ�� 
			/*ˢ���ڸû����Ϲ��������������Ŀ���ʱ��*/
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
	
		
		/*һ�����ʱ��Ĵ���*/
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

void NoDelayDispatch(int row)//���ӳٵ��� 
{
	int col=0;
	int i,minTs=99999,Mselected;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[50]={0};/*��ʼ��U*/
	int Porder;
	
	while(col<DNAnum)//U�ڻ���δ���Ź���
	{
		
	for(i=0,minTs=99999;i<Pnum;i++)//����U�й���������ܿ���ʱ��minTs 
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
		if(M[i]==minTs)//ѡ��һ̨���翪��ʱ��ΪminTs �Ļ��� Mselected 
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
	
	/*�ѻ������DNA*/ 
	pop[row][col]=candidate[0];
	col++;

	/*����U*/ 
		/*ˢ��������ܿ���ʱ��*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U��ͻ���ʱ�����ֵ��ѡ���Ĺ�����ѡ���������ȵĹ���ѡ��������������Ļ��� 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*��U��ͻ���ʱ�����ֵ*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*ˢ��ʱ��*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//ˢ��U��ʱ�� 
	M[P_machine]=U[0][Pselected-1];//ˢ�»���ʱ�� 
			/*ˢ���ڸû����Ϲ��������������Ŀ���ʱ��*/
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
	
	
		
		/*����岥һ�����ʱ��Ĵ���*/
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

void RandomDNA(int row) //����γ�һ��DNA 
{
	int i,j,count=0,col=0;
	int candidate[100]={0},countC=0;
	int U[2][100]={{0},{0}},M[100]={0};/*��ʼ��U*/
	
	while(col<DNAnum)//U�ڻ���δ���Ź���
	{
		
		/*¼��candidate*/
		int Porder;
		for(i=0,countC=0;i<Pnum;i++)
		{
			Porder=U[1][i];
			if(Porder<pro[i].order)//������ 
			{
				candidate[countC]=i+1;
				countC++;
			}
		}
		if(countC>1)
		candidate[0]=RSP(candidate,countC,U);
		
		pop[row][col]=candidate[0];
		col++;

	/*����U*/ 
		/*ˢ��������ܿ���ʱ��*/
	int MaxTstart=0,Pselected,/*Porder*/P_machine;//U��ͻ���ʱ�����ֵ��ѡ���Ĺ�����ѡ���������ȵĹ���ѡ��������������Ļ��� 
	Pselected=candidate[0];
	Porder=U[1][Pselected-1];
	P_machine=pro[Pselected-1].machine[Porder];
		/*��U��ͻ���ʱ�����ֵ*/
	MaxTstart=MaxTstart>U[0][Pselected-1]?MaxTstart:U[0][Pselected-1]; 
	MaxTstart=MaxTstart>M[P_machine]?MaxTstart:M[P_machine];
		/*ˢ��ʱ��*/
	U[0][Pselected-1]=MaxTstart+pro[Pselected-1].time[Porder];//ˢ��U��ʱ�� 
	M[P_machine]=U[0][Pselected-1];//ˢ�»���ʱ�� 
		/*ˢ���ڸû����Ϲ��������������Ŀ���ʱ��*/
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
	
		
	
	
	
		
		/*����岥һ�����ʱ��Ĵ���*/
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
		rdm=rand()%10;//����һ�������0-9
			
			if(rdm<=3) //0.4���ʣ�ѡ�ù���MWR 
			Cselected=MWR(candidate,C_size,U);
			else if(rdm>=6) //0.4���ʣ�ѡ�ù���SPT 
			Cselected=SPT(candidate,C_size,U);
			else //0.2���ʣ����ѡ���� 
			Cselected=RSP(candidate,C_size,U);
	
	return Cselected;
}

int MWR(int *candidate,int C_size,int U[][100]) //Most work remaining  ʣ��������ܼӹ�ʱ����Ĺ����ȼӹ���
{
	int i,gene,maxT=0;
	int cdd_num;//��ѡ���� ������ 
	/*ѡ��ʣ���ܼӹ�ʱ���Ĺ����ģ���ǰ��һ���������򣬼������ */
	/*��candidate��ѡ��*/
	for(i=0;i<C_size;i++)
	{
		cdd_num=candidate[i];
		if(maxT<RemainTotalTime[cdd_num-1])
		{
			maxT=RemainTotalTime[cdd_num-1];
			gene=cdd_num;
		}
	}

	/*���� ʣ���ܼӹ�ʱ�����顣������ʱ�� */
	int Porder;
	Porder=U[1][gene-1];
	RemainTotalTime[gene-1]-=pro[gene-1].time[Porder];
	
	return gene;
 } 

int SPT(int *candidate,int C_size,int U[][100]) //Shortest processing time  ������̼ӹ�ʱ��Ĳ����ȼӹ�
{
	/*��ÿ��������ǰ��һ���������ʱ��ļ���DNA*/
	//Ҫ����U[]���������õ�order�� 
	
	int minT=99999,Pmin,i;//��Сʱ�䣬��Сʱ���Ӧ������
	int Pcdd,Porder;//��ǰ��ѡ���� ,��ѡ�����ɵ��ȹ���� 
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
	
	/*����*/
	/*���� ʣ���ܼӹ�ʱ�����顣������ʱ�� */
	Porder=U[1][Pmin-1];//ѡ����Ʒ�ɵ��ȹ���ţ���0��ʼ 
	RemainTotalTime[Pmin-1]-=pro[Pmin-1].time[Porder];
	
	return Pmin; 
}
 
int RSP(int *candidate,int C_size,int U[][100]) //Randomly Select Prosess  ���ѡ����
{
	/*��candidate�����ѡһ������DNA(��ʵ����ֻ�ܳ�ÿ�������ĵ�ǰ��һ������*/
	/*��candidate���һ������*/
	int rdm,i,Pselected;
	
		
	rdm=rand()%C_size;
	Pselected=candidate[rdm]; 
	
	//���� 
	/*���� ʣ���ܼӹ�ʱ�����顣������ʱ�� */
	int Porder;
	Porder=U[1][Pselected-1];
	RemainTotalTime[Pselected-1]-=pro[Pselected-1].time[Porder];
	
	return Pselected;
} 
