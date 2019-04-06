#include "zqy.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

extern struct product{
	int total_time;//总时间 
	int order;//工序总个数 
	int time[100];
	int machine[100];
}pro[100];//产品加工信息 

extern struct timefinal{
	int num[100]; 
	int begintime[100];
	int endtime[100];
	int order[100];
}finaltime[50];//最终机器上的加工信息 

int DNA_SIZE;
int temp_pop[100][200];
int countZQY;//计数 
int TTTIMES;// 计算实际加工时长 
double duration;//程序运行所用时长 
clock_t start,finish;//程序开始结束时间 

extern int product_num,machine_num;
extern int DNA[180][200],pop[100][180];
extern double fit[180];
extern int BEST[200];//最优DNA序列 
extern int CountTimes;//计次 



extern void Generate(void);
extern void input(struct product pro[100]);
extern void Crossover(void);
extern void Mutate(void);
extern void selectwst(double fit[180]);
extern void selectoutput(int DNA[180][200],double fit[180]);
extern void output(struct timefinal finaltime[50]);
extern void translate(void);
extern void fitness(void);
extern void transoutput(int BEST[200]);
extern void inputFILE(struct product pro[100]);
extern void outputFILE(struct timefinal finaltime[50]);
extern void drawline(void);
extern void gante_w(void);
extern void readfile(void);
extern void Timekeeping(void);
extern void fixgante(void);
extern void outputfix(void);

//extern unsigned __stdcall GetRepairOrder(void* pArguments);

int main(int argc, char *argv[]) 
{
	start=clock();
	srand(time(NULL));//设置种子
	int i,h;

	inputFILE(pro);
	
	/*工序总量（DNA长度）*/	
	for(i=0,DNA_SIZE=0;i<product_num;i++)
		DNA_SIZE+=pro[i].order;
		
	for(countZQY=0;countZQY<100;countZQY++)
	{
		Generate();
	//	sleep(1);
	}
	for(countZQY=0;countZQY<POP_SIZE;countZQY++)
	{
	//	printf("\npop[%d]",countZQY);
		for(h=0;h<DNA_SIZE;h++)//复制到temp里 
		{
			pop[countZQY][h]=temp_pop[countZQY][h];
			//printf("%d ",pop[countZQY][h]);
		}	
	}
	for(i=0;i<100;i++)
	{		
		Crossover();
		Mutate();
		translate();
		fitness();
		selectwst(fit);
	}
	translate();
	fitness();
	selectoutput(DNA,fit);
    transoutput(BEST); 
    finish=clock();
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
	output(finaltime);
	outputFILE(finaltime);
	
	TTTIMES=0;
	initgraph(1600,900);//打开一个图形窗口界面
	setbkcolor(WHITE);
	setcolor(BLACK);
	gante_w();
	//bar(500,600,600,700);
	//drawline();
	getch();
	readfile();

	/*检修指令输出*/
	setfillcolor(BLACK);
	rectangle(1250,100,1530,300);//画矩形
	
	
	
	CountTimes=0;
	Timekeeping(); 
	//getch();
	//setcolor(BLACK);
	//bar(300,500,500,600);
	outputfix();
	fixgante();
	getch();
	//system("pause");
	closegraph();
	return 0;
}
