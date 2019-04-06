#include <iostream>

#include<graphics.h>
#include<string.h>
#include<stdlib.h> 
#include<stdio.h>
#include<time.h> 



extern struct colors{
    	int count1;
    	int count2;
    	int count3;
	}color[30]; 
extern int machine_num,product_num;	

extern struct recordfix
{
	int start[100];
	int end[100];
}machinefix[50]; 
	
	
void fixgante()

{
	int i,j,x,y;
	int count;
	
		//setcolor(BLACK);
		//bar(1300,500,1400,600);
	
	/*    测试    */ 
//	initgraph(1300,700);//打开一个图形窗口界面
	
//	setbkcolor(WHITE);
/*	setcolor(BLACK);
	
	struct colors{
    	int count1;
    	int count2;
    	int count3;
	}color[30];
	
	
	int machine_num=10;
	int one,two,three;
	one=0;
	two=50;
	three=100;
	for(i=0;i<30;i++)
	{
		color[i].count1=one+color[i].count1;
	    color[i].count2=two+color[i].count2;
	    color[i].count3=three+color[i].count3;
	    one=(one+10)%255;
	    two=(two+25)%255;
	    three=(three+88)%255;
	}
	
struct recordfix
{
	int start[100];
	int end[100];
}machinefix[50];

   machinefix[1].start[0]=180;
   machinefix[1].end[0]=230;
   */
	
	/*     测试    */ 
	
	FILE *gptr=fopen("lff.txt","r");
	
	int c;
	char ch;
    count=0;
    
    struct finalmachine{   
        int num[100];//该机器上加工的产品序号 
        int order[100];//产品工序号 
        int begintime[100];//每次加工的开始时间 
        int endtime[100];//每次加工的结束时间 
        int process_num;
    }fma[50]; 
	
	double time_use;
	int all_time;
	
	if(gptr==NULL)
	    outtextxy(0,0,"Can't open output2 file!");
	else
	{
		 
		while(!feof(gptr))
		{
			for(j=0;j<machine_num;j++)
			{
				fscanf(gptr,"M%d",&c);
				for(i=0;fgetc(gptr)==' ';i++)
				{
					fscanf(gptr,"(%d,%d-%d,%d)",&fma[c].begintime[i],&fma[c].num[i],&fma[c].order[i],&fma[c].endtime[i]);
					count++;
				}
				fma[c].process_num=count;
				count=0;
			}
			if(j==machine_num) break;
		}
		
		//fscanf(gptr,"Time Used:%lf\nEND Time:%d",&time_use,&all_time);
	}
	fclose(gptr);
	
	
	
	outtextxy(700,(machine_num+1)*30+70,"最终方案甘特图：(黑色为检修区域)");
	y=(machine_num+1)*30+90; 
	x=730;
	for(i=0;i<machine_num;i++)
	{
		/*outtextxy(x,y,"M");
		sprintf(mach,"%d",i);
		outtextxy(x+12,y,mach);*/
		
		xyprintf(700,y,"M%d",i);
		
		
		line(730,y+20,1200,y+20);//！！！！这里要改线的长度！！！！ careful 
		 
		 
		for(j=0;j<fma[i].process_num-1;j++)
	    {
	    	
	    	setfillcolor(EGERGB(color[fma[i].num[j]].count1,color[fma[i].num[j]].count2,color[fma[i].num[j]].count3));
	    	bar(x+fma[i].begintime[j]*0.5,y+5,x+fma[i].endtime[j]*0.5,y+20);
			//sprintf(out,"O%d%d",fma[i].num[j],fma[i].order[j]);
			//outtextxy(30+fma[i].begintime[j],y+5,out);	
		}   
		x=730;
		y=y+30; 
	 }
	 
	 
	 int min;
	 int n;
	 min=fma[0].endtime[0];
	for(i=0;i<machine_num;i++)
	{
		for(n=0;fma[i].endtime[n];n++)
		{
			if(fma[i].endtime[n]>min)
			    min=fma[i].endtime[n]; 
		}
	} 
	 
	 xyprintf(735,(machine_num+1)*60+70,"END Time: %d",min);
	 
	 
	//outtextxy(0,500,"到这了"); 
	y=(machine_num+1)*30+90; 
	x=730;
	 for(i=0;i<machine_num;i++)
	 {
	 	for(j=0;machinefix[i].start[j]!=0;j++)
	    {
	    	//if(i==1&&j==0) outtextxy(0,500,"到这了");
	 	    setfillcolor(BLACK);
	 	    bar(x+machinefix[i].start[j]*0.5,y+5,x+machinefix[i].end[j]*0.5,y+20); 
		}
		x=730;
		y=y+30; 
	 }
	 
	/*extern struct recordfix
    {
	int start[100];
	int end[100];
    }machinefix[50]; */
    
    
    /* 记得注释掉！！！！  */ 
    //getch();
	//closegraph();
	return ;
}
