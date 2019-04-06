#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>

#define HEIGHT 20   //20像素高
#define GAP 30      //30像素间隔

#define PIXELPERT 0.5 //单位时间0.5像素

#define TPS 3     //每秒对应的加工时间，验收时为3 

struct recordfix
{
	int start[100];
	int end[100];
}machinefix[50]={{0},{0}}; 

//int TTTIMES;   在main中定义，初始为0
extern int TTTIMES; 
extern int machine_num;

struct liufan
{
	int begintime[100];
	int endtime[100];
	int num[100];
	int order[100];
}lff[50]={{0},{0},{0},{0}};  

//边框函数，开始动态输出前draw 
void drawline(void)
{
	/*
	initgraph(500,500);
	setbkcolor(RGB(0xFF,0xFF,0xFF));//设置背景色 
	setcolor(BLACK);//设置画笔颜色为黑色
	*/ 
	//首先画出基本框架    
	int i,y,x=0;
	char out[10]={'0'};
	y=(machine_num+1)*GAP+100;
	/*画边框 
	line(1,STARTY,1,STARTY+LONG);//左竖 
	line(1,STARTY,STARTY+WIDE,STARTY);//上横 
	line(1,STARTY+LONG,STARTY+WIDE,STARTY+LONG);//下横 
	line(STARTY+WIDE,1,STARTY+WIDE,STARTY+LONG);//右竖 
	*/ 
	//画基础线 
	/*
	setfont(14,7,"Times New Roman");
	line(20,STARTY+3,20,STARTY+machine_num*GAP);
	char num[10];
	for(i=0;i<machine_num;i++)
	{
		
	    sprintf(num,"M%d",i);
		outtextxy(5,i*GAP,num);//对应机器序号为 i
		line(20,(i+1)*GAP,WIDE-5,(i+1)*GAP);
	}
	*/
	for(i=0;i<machine_num;i++)
	{
		outtextxy(x,y,"M");
		sprintf(out,"%d",i);
		outtextxy(x+12,y,out);
		line(30,y+20,700,y+20);   
		x=0;
		y+=GAP; 
	}
	
	FILE *optr=fopen("output1.txt","r");
	int c,j;
	char ch;
    int count=0;
	
	double time_use;
	int all_time;
	
	if(optr==NULL)
	    outtextxy(0,0,"Can't open output file!");
	else
	{
		 
		while(!feof(optr))
		{
			for(j=0;j<machine_num;j++)
			{
				fscanf(optr,"M%d",&c);
				for(i=0;fgetc(optr)==' ';i++)
				{
					fscanf(optr,"(%d,%d-%d,%d)",&lff[c].begintime[i],&lff[c].num[i],&lff[c].order[i],&lff[c].endtime[i]);
					count++;
				}
			}
			if(j==machine_num) break;
		}
		fscanf(optr,"Time Used:%lf\nEND Time:%d",&time_use,&all_time);
		
	}
	fclose(optr);

	optr=fopen("lff.txt","w");
	
	    int n;
	
	    for(i=0;i<machine_num;i++)
    	{
    		fprintf(optr,"M%d ",i);
    		for(n=0;lff[i].endtime[n];n++)
    		{
    			if(lff[i].endtime[n]!=lff[i].begintime[n])
    			fprintf(optr,"(%d,%d-%d,%d) ",lff[i].begintime[n],lff[i].num[n],lff[i].order[n],lff[i].endtime[n]);
    		}
    		fputc('\n',optr);
	    } 
    return ;
}

//动态输出甘特图 
extern int CountTimes;//从0开始，每次+2 
/*
typedef struct timefinal
 {   
     int num[100];//该机器上加工的产品序号 
     int order[100];//产品工序号 
     int begintime[100];//每次加工的开始时间 
     int endtime[100];//每次加工的结束时间 
 }ftime;
extern ftime finaltime[50];
*/
extern int StopSignal; 
extern struct colors
{
    int count1;
    int count2;
    int count3;
}color[30]; 

int FLAG[100][2]={{0},{0}}; //初始没有检修 


void fixGantt(void)
{
 	xyprintf(700,1000,"%d",lff[0].begintime[0]);
	 //输出甘特 
	char out[20];
	int a,b,c;
	int t=CountTimes;
	int i,flag,j;
	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setfont(50,0,"Times New Roman");
	xyprintf(900,800,"不是我1"); 
	for(i=0;i<machine_num;i++)//循环输出每个机器的甘特 
	{
		xyprintf(100,800,"不是我2");
		flag=0;
		a=(machine_num+1)*30+50+(i+1)*GAP-HEIGHT;
	    b=(machine_num+1)*30+50+(i+1)*GAP;
			
		//若此段时间为检修时间
		if(machinefix[i].end[TTTIMES]!=0&&t*TPS>=machinefix[i].start[TTTIMES])	
		{
			xyprintf(700,800,"不是我3");
			if(machinefix[i].end[TTTIMES]>=(t+2)*TPS)//此2S对应时长内，检修未结束
			{
				setcolor(BLACK);//设置画笔颜色为黑色 
				bar(20+t*TPS*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);
			
				flag=1;
			}
			else if(machinefix[i].end[TTTIMES]<(t+2)*TPS) //此2S对应时间内，检修结束
			{
				c=machinefix[i].end[TTTIMES]-t*TPS;
				setcolor(BLACK);//设置画笔颜色为黑色
				bar(20+t*TPS*PIXELPERT,a,20+c*PIXELPERT,b);//加工区域
				
				TTTIMES++; 
				flag=2;
			}
			if(machinefix[i].start[TTTIMES]==0)
		    FLAG[i][0]=0;//若检修，检修结束 	
		}
		 
			
		//若此段时间为加工时间
		else
		{
		    
	    	xyprintf(700,800,"不是我4");
			for(j=0;j<100&&flag==0;j++) 
		    {
				int savecolor=lff[i].num[j];
				setcolor(RGB(color[savecolor].count1,color[savecolor].count2,color[savecolor].count3));//根据加工产品序号确定颜色！！！！！ 
				if(lff[i].begintime[j]<=t*TPS)//若开始加工时间小于t 
		    	{
					if(lff[i].endtime[j]>=(t+2)*TPS)//结束时间晚于本次2s 
				    { 
						bar(20+t*TPS*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);//加工区域 
	    	            flag=1;
					}
					else//结束于本次刷新结束之前 
					{
						c=lff[i].endtime[j]-t*TPS;//进行时间 
						bar(20+t*TPS*PIXELPERT,a,20+c*PIXELPERT,b);//加工区域
						
						setcolor(WHITE);//设置字体颜色为白色
			            sprintf(out,"%d",lff[i].order[j]);
	                    rectprintf(20+lff[i].begintime[j]*PIXELPERT,a,lff[i].endtime[j]*PIXELPERT,b,out);
			            
			            flag=1;
					}
			    } 
			    else  if(lff[i].begintime[j]<=(t+2)*TPS)//若开始加工时间在两次刷新之间 
			    {
					if(lff[i].endtime[j]>=(t+2)*TPS)//结束时间晚于本次2s 
				    {
						bar(20+lff[i].begintime[j]*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);//加工区域 
					}
					else//结束于本次刷新结束之前 
					{
						c=lff[i].endtime[j]-t*TPS;//进行时间 
						bar(20+lff[i].begintime[j]*PIXELPERT,a,20+c*PIXELPERT,b);//加工区域
						 
						setcolor(WHITE);//设置字体颜色为白色
			            sprintf(out,"%d",lff[i].order[j]);
	                    rectprintf(20+lff[i].begintime[j]*PIXELPERT,a,lff[i].endtime[j]*PIXELPERT,b,out);
			            //setcolor(BLACK);//设置画笔颜色为黑色    
					}
					flag=1; 
				}
				if(lff[i].begintime[j]>t*TPS)//当 遍历到的开始时间在当前刷新开始时间之后，停止遍历
				flag=1;
				if(lff[i].begintime[j]==0)//遍历结束
				flag=2; 
			}
			if(flag==2)
			FLAG[i][1]=0;//序号为i的机器若加工，已经结束加工	
		} 
    }
    for(i=0,flag=0;i<machine_num&&flag==0;i++)
	{
		if(FLAG[i][0]==1||FLAG[i][1]==1)
		flag=1;
	} 
    if(flag==0)//退出循环的条件是全都为1 
    StopSignal=1;
	return ;
}

extern int DNA_SIZE;
extern int BEST[200];  //?????????????????????

extern struct repair
{
	int point; //point为检修输入时间节点
	int machine_num;  //检修机器序号 
	int fix_time;  //检修时长 
}fix;


extern int tf[180]; 

extern struct product{
	int total_time;
	int order;
	int time[100];
	int machine[100];
}pro[100];


int mtimes[100]={0};//储存该机器检修次数 

void timechange(void)//若有检修输入，更改时间 
{
 	int m,place,t,p,flag;
	m=fix.machine_num;
	t=fix.fix_time; 
	p=fix.point;
	FLAG[m][0]=1; 
	
	for(place=0,flag=0;lff[m].endtime[place]!=0&&flag==0;place++)//搜索对应时间，判断是否对产品有影响   //flag==0退出，说明遍历到结束 
 	{
 	    if(lff[m].begintime[place]<t)
		{
		 	if(lff[m].endtime[place]>t)//在产品加工时间内 
		 	flag=1;
			if(lff[m].endtime[place]<t);
			//继续循环 
	    } 
	    else  //begin>=t
		{
			if(lff[m].endtime[place+1]!=0&&t<lff[m].begintime[place+1])//开始于间隔
			{
				if((t+p)>lff[m].begintime[place+1])
				flag=2;//影响后续 
				if((t+p)<=lff[m].begintime[place+1])
				flag=3;//不影响后边工序 
			} 
			if(lff[m].endtime[place+1]==0);
			 //下一步会退出循环 
		} 
	}//若flag==0则是因遍历完毕退出循环，不影响加工 
	//确定了一个place，flag 
	
    if(flag==0||flag==3||flag==2)
    {

    	//直接补充检修部分
    	machinefix[m].start[mtimes[m]]=p;
    	machinefix[m].end[mtimes[m]]=p+t;
    }
 	else//flag==1
 	{
 		//补充检修部分，在本次加工结束之后 
    	machinefix[m].start[mtimes[m]]=lff[m].endtime[place];
    	machinefix[m].end[mtimes[m]]=lff[m].endtime[place]+t;
	}
	mtimes[m]++;
	
	if(flag==0||flag==3)//不会影响加工，不需更改

	return;
	else //会影响后续加工 ，更改时间 
	{
		int a=lff[m].num[place+1];//找到的有影响的第一个工件 
		int b=lff[m].order[place+1];// 找到的有影响的第一个工件的工序号 
		
		int time[3][100]={{0},{0}};//初始化为零 
	    int i=0,k=0,g=0;//i读DNA;k存读到的DNA是几号工件;g存机器序号*/ 
	    int j[100]={0},h[100]={0};/*j[k]计工序；h[g]计该机器加工的第几个产品*/ 
	    
	    int counttt=0;
	    for(i=0;counttt<=b;i++)
	    {
	    	if((BEST[i]-1)==a)
	    	counttt++;
		}
	    counttt=i;//确定该工序对应DNA位置
		 
	    for(i=0;BEST[i]!=0;i++)
	    {
		    k=BEST[i]-1;//读DNA确定工件序号 
	       	g=pro[k].machine[j[k]];//存机器序号
			//更改检修信息之前的部分，复制
			if(i<counttt) //不需更改
			{
				time[1][k]=lff[g].endtime[h[g]];
				time[2][g]=time[1][k];
			}
			else if(i==counttt) //增添差额时间 
			{
				 
				if(flag==1)//检修point在加工时间段内 
			    {
			    	lff[g].endtime[h[g]]=lff[g].endtime[h[g]-1]+t+pro[k].time[j[k]]; 
				} 
				/*{
					if(time[2][g]<lff[g].endtime[h[g]]+fix.fix_time)
					time[2][g]=lff[g].endtime[h[g]]+fix.fix_time;//机器空闲时刻 在原时间基础上 拖后 
				 }*/ 
				 else//flag==2，检修结束会耽搁时间 
				/* {
				    if(time[2][g]<fix.fix_time+fix.point;)
				    time[2][g]=fix.fix_time+fix.point;//机器空闲时刻为 接收到信号的时刻时间+检修时长 
				}
				*/
				{
					lff[g].endtime[h[g]]=p+t+pro[k].time[j[k]];
				}
				
				time[1][k]=lff[g].endtime[h[g]];
				time[2][g]= time[1][k];
			}


		    else //更改检修信息后，照常翻译 
		    {
			    /* 
			    k=BEST[i]-1;//读DNA确定工件序号 
	        	g=pro[k].machine[j[k]];//存机器序号 
	        	*/
	        	lff[g].order[h[g]]=j[k];//产品工序号 
	        	lff[g].num[h[g]]=k;//记录产品序号 
	        	if(time[1][k]>=time[2][g])//若需要等待产品上一步完成 
	        	{
	        		lff[g].begintime[h[g]]=time[1][k];//储存开始时间 
	        		time[1][k]+=pro[k].time[j[k]];//产品时间数组中，相应产品时间增加
		        	time[2][g]=time[1][k];//确定机器完成该工序的时间 
	    	    }
    	    	else//若需要等待机器空闲 
	        	{
	        		lff[g].begintime[h[g]]=time[2][g];//储存开始时间 
	        		time[2][g]+=pro[k].time[j[k]];//机器时间数组中，相应机器时间增加 
	        	    time[1][k]=time[2][g];//确定工件完成该工序的时间 
	        	}
	        	lff[g].endtime[h[g]]=time[1][k];//储存结束时间 
	        }
	    	h[g]++;//确定num位置
	    	j[k]++;//确定哪个工件的哪一步
	    } 
	    
	    FILE *optr=fopen("lff.txt","w");
	
	    int n;
	
	    for(i=0;i<machine_num;i++)
    	{
    		fprintf(optr,"M%d ",i);
    		for(n=0;lff[i].endtime[n];n++)
    		{
    			if(lff[i].endtime[n]!=lff[i].begintime[n])
    			fprintf(optr,"(%d,%d-%d,%d) ",lff[i].begintime[n],lff[i].num[n],lff[i].order[n],lff[i].endtime[n]);
    		}
    		fputc('\n',optr);
	    }
		fclose(optr);    
		return ;
	}
} 



void readfile(void)//读文件 
{
	FILE *optr=fopen("output1.txt","r");
	int c,i,j;
	char ch;
    int count=0;
	
	double time_use;
	int all_time;
	
	if(optr==NULL)
	    outtextxy(0,0,"Can't open output file!");
	else
	{
		 
		while(!feof(optr))
		{
			for(j=0;j<machine_num;j++)
			{
				fscanf(optr,"M%d",&c);
				for(i=0;fgetc(optr)==' ';i++)
				{
					fscanf(optr,"(%d,%d-%d,%d)",&lff[c].begintime[i],&lff[c].num[i],&lff[c].order[i],&lff[c].endtime[i]);
					count++;
				}
			}
			if(j==machine_num) break;
		}
		fscanf(optr,"Time Used:%lf\nEND Time:%d",&time_use,&all_time);
		
	}
	fclose(optr);

	optr=fopen("lff.txt","w");
	
	    int n;
	
	    for(i=0;i<machine_num;i++)
    	{
    		fprintf(optr,"M%d ",i);
    		for(n=0;lff[i].endtime[n];n++)
    		{
    			if(lff[i].endtime[n]!=lff[i].begintime[n])
    			fprintf(optr,"(%d,%d-%d,%d) ",lff[i].begintime[n],lff[i].num[n],lff[i].order[n],lff[i].endtime[n]);
    		}
    		fputc('\n',optr);
	    }
	    fclose(optr);
	return; 
}

int findend(void);
int findend(void)
{
	int a,i,j;
	a=lff[0].endtime[0];
	for(i=0;i<machine_num;i++)
	{
		for(j=0;!(lff[i].endtime[j]!=0&&lff[i].endtime[j+1]==0);j++);
		if(a<lff[i].endtime[j])
		a=lff[i].endtime[j];
	}
	return a;
}

int whattime[100]={0};

void putstate(void)//输出机器状态 
{
	int i;
	int t=CountTimes;
	int x=5,y=500;
	char out[10];
	int end=findend();
	int flag=0;
	
	//刷新这片区域
	setfillcolor(WHITE);
	bar(x,y,700,900);
	 
	//输出机器状态 
	setcolor(BLACK); 
	
	int stop[100]={0}; 
	for(i=0;i<machine_num;i++)
	{
		int j; 
		//xyprintf();
	    //若此段时间为检修时间
		if(machinefix[i].end[whattime[i]]!=0&&t*TPS>machinefix[i].start[whattime[i]])	
		{
			sprintf(out,"检修"); 
			xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-machinefix[i].start[whattime[i]],machinefix[i].end[whattime[i]]-machinefix[i].start[whattime[i]]);
		    if((t+2)*TPS>=machinefix[i].end[whattime[i]])//若本次刷新之后，检修结束；计次加一 
		    whattime[i]++;
		    if(machinefix[i].end[whattime[i]]==0)
		    FLAG[i][0]=0;//若检修，可能的检修已结束
		}

		
		 
		//若此段时间为加工时间或空闲 
		else
		{
			for(j=0,flag=0;j<100&&flag==0;j++)
			{
				if(lff[i].begintime[j]<=t*TPS&&lff[i].endtime[j]>t*TPS)//若找到这段时间 
				{
					sprintf(out,"加工");
					xyprintf(x,y,"%d %d%s %d-%d %d %d\n",t*TPS,i,out,lff[i].num[j],lff[i].order[j],t*TPS-lff[i].begintime[j],lff[i].endtime[j]-lff[i].begintime[j]);
			        flag=1; 
				} 
				else
				{
					
					if(lff[i].begintime[j]>t*TPS)//当 遍历到的开始时间在当前刷新开始时间之后，停止遍历
				    {
				    	flag=2;//退出条件 
				        sprintf(out,"空闲");
					    xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-lff[i].endtime[j-1],lff[i].begintime[j]-lff[i].endtime[j-1]);
					} 
				    if(lff[i].endtime[j]==0)//遍历结束
			        {
			    	    sprintf(out,"空闲");
					    xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-lff[i].endtime[j-1],end-lff[i].endtime[j-1]);
					    flag=3;
			            FLAG[i][1]=1;//可能的加工工序均已完成 
				    }
				}
			
			}
		}
		
	    x=5;
 	    y+=20; 
	}
	//setcolor(BLACK);
	//
	
	//bar(5,500,100,700);
	for(i=0,flag=0;i<machine_num&&flag==0;i++)
    	{
    		if(FLAG[i][0]==1||FLAG[i][1]==0)
    		flag=1;
    	} 
    //bar(150,500,200,700);
    /*if(flag==0)//退出循环的条件是全都为1 
    stop[i]=1;
	for(i=0,flag=0;i<machine_num&&flag==0;i++) 
	{
		if(stop[i]==0)
    	flag=1;
	}*/
	
	if(flag==0)
	{
		StopSignal=1;
	//	setcolor(BLACK);
	//	bar(300,500,400,600);
	}
	return;
} 
