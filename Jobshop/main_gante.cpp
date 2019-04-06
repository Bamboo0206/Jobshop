

#include<graphics.h>
#include<string.h>
#include<stdlib.h> 
#include<stdio.h>
#include<time.h> 

#define HEIGHT 20   //20像素高
#define GAP 30      //30像素间隔

#define PIXELPERT 5 //单位时间5像素


#define WIDTH    400   //此部分甘特图所占区域  
#define LENTH     600  //  

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct colors{
    int count1;
	int count2;
	int count3;
}color[30];

void gante_w() {
	
	setfont(18, 0, "宋体");
	FILE *eptr=fopen("input.txt","r");
	srand(time(NULL));
	
	char pr[5],ma[5],ti[5];
	int m,n;
	int pr_num,ma_num;
    int count=0;
    int x=0,y=0;
    int i,j;
	
	struct goods{
	    int time[100];
    	int machine[100];
    	int order;
    }good[100]; 
	
	if(eptr==NULL)
	    outtextxy(0,0,"Can't open input file!");
	else
	{
		while(!feof(eptr))
		{
			fscanf(eptr,"%d %d",&pr_num,&ma_num);
			
			
			y=20;
			
			for(i=0;i<pr_num;i++)
			{
				fscanf(eptr,"%d %d",&good[i].machine[count],&good[i].time[count]);
				//pro[i].total_time+=pro[i].time[count];
				count++; 
				while(fgetc(eptr)==' ')//不知道一行的终止条件。。 
				{
					fscanf(eptr,"%d %d",&good[i].machine[count],&good[i].time[count]);
					//pro[i].total_time+=pro[i].time[count]; //一个产品的工序总时间 
					count++;
				}
				good[i].order=count;//共多少道工序 
				count=0;
			}
		}
		
	}
	fclose(eptr);
	

	
   
	 
	struct finalmachine{   
        int num[100];//该机器上加工的产品序号 
        int order[100];//产品工序号 
        int begintime[100];//每次加工的开始时间 
        int endtime[100];//每次加工的结束时间 
        int process_num;
    }fma[50]; 
     
	
	
	FILE *optr=fopen("output1.txt","r");
	
	int c;
	char ch;
    count=0;
    
    double time_use;
	int all_time;
	
	if(optr==NULL)
	    outtextxy(0,0,"Can't open output file!");
	else
	{
		 
		while(!feof(optr))
		{
			for(j=0;j<ma_num;j++)
			{
				fscanf(optr,"M%d",&c);
				for(i=0;fgetc(optr)==' ';i++)
				{
					fscanf(optr,"(%d,%d-%d,%d)",&fma[c].begintime[i],&fma[c].num[i],&fma[c].order[i],&fma[c].endtime[i]);
					count++;
				}
				fma[c].process_num=count;
				count=0;
			}
			if(j==ma_num) break;
		}
		
		fscanf(optr,"Time Used:%lf\nEND Time:%d",&time_use,&all_time);
	}
	fclose(optr);
	 
	/*
	initgraph(1300,700);//打开一个图形窗口界面
	
	setbkcolor(WHITE);
	setcolor(BLACK);
    
    setfillcolor(WHITE);
    //settextjustify(CENTER_TEXT,CENTER_TEXT);
    */
    int a,b,count1,count2,count3; 
    char out[20];
    char mach[10];
    

	
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
    
    
    outtextxy(0,0,"解决方案甘特图");
	y=20; 
	for(i=0;i<ma_num;i++)
	{
		outtextxy(x,y,"M");
		sprintf(mach,"%d",i);
		outtextxy(x+12,y,mach);
		line(30,y+20,620,y+20);
		for(j=0;j<fma[i].process_num-1;j++)
	    {
	    	setfillcolor(EGERGB(color[fma[i].num[j]].count1,color[fma[i].num[j]].count2,color[fma[i].num[j]].count3));
	    	bar(30+fma[i].begintime[j]*0.5,y+5,30+fma[i].endtime[j]*0.5,y+20);
			//sprintf(out,"O%d%d",fma[i].num[j],fma[i].order[j]);
			//outtextxy(30+fma[i].begintime[j],y+5,out);	
		}   
		x=0;
		y=y+30; 
	 }
	
	xyprintf(5,(ma_num+1)*30,"END Time: %d     Time Used: %lf",all_time,time_use);
	
	x=650;
	y=5;
	char prod[5];
	for(i=0;i<pr_num;i++)
	{
		outtextxy(x,y,"P");
		sprintf(prod,"%d",i);
		outtextxy(x+12,y,prod);
		setfillcolor(EGERGB(color[i].count1,color[i].count2,color[i].count3));
		bar(x+30,y,x+55,y+12);
		y=y+20;
	}
	
	
	//y=(ma_num+1)*30;
	
	outtextxy(750,0,"订单详情：");
	x=750;
	y=20;
	 
	sprintf(pr,"%d",pr_num);
	sprintf(ma,"%d",ma_num);
	outtextxy(x,y,pr);
	outtextxy(x+20,y,ma);
	y=40;
		for(n=0;n<pr_num;n++)
	   {
		     
		    for(m=0;m<good[n].order;m++)
		    {
		    	sprintf(ma,"%d",good[n].machine[m]);
		    	sprintf(ti,"%d",good[n].time[m]);
			    //printf("(%d,%d) ",pro[n].machine[m],pro[n].time[m]);
			    outtextxy(x,y,ma);
			    outtextxy(x+20,y,ti);
			    x=x+50;
		    }
		    y=y+18;
		    x=750;
	    }
	
	
	//getch();
	//closegraph();
	return ;
}
