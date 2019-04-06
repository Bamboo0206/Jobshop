#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>

#define HEIGHT 20   //20���ظ�
#define GAP 30      //30���ؼ��

#define PIXELPERT 0.5 //��λʱ��0.5����

#define TPS 3     //ÿ���Ӧ�ļӹ�ʱ�䣬����ʱΪ3 

struct recordfix
{
	int start[100];
	int end[100];
}machinefix[50]={{0},{0}}; 

//int TTTIMES;   ��main�ж��壬��ʼΪ0
extern int TTTIMES; 
extern int machine_num;

struct liufan
{
	int begintime[100];
	int endtime[100];
	int num[100];
	int order[100];
}lff[50]={{0},{0},{0},{0}};  

//�߿�������ʼ��̬���ǰdraw 
void drawline(void)
{
	/*
	initgraph(500,500);
	setbkcolor(RGB(0xFF,0xFF,0xFF));//���ñ���ɫ 
	setcolor(BLACK);//���û�����ɫΪ��ɫ
	*/ 
	//���Ȼ����������    
	int i,y,x=0;
	char out[10]={'0'};
	y=(machine_num+1)*GAP+100;
	/*���߿� 
	line(1,STARTY,1,STARTY+LONG);//���� 
	line(1,STARTY,STARTY+WIDE,STARTY);//�Ϻ� 
	line(1,STARTY+LONG,STARTY+WIDE,STARTY+LONG);//�º� 
	line(STARTY+WIDE,1,STARTY+WIDE,STARTY+LONG);//���� 
	*/ 
	//�������� 
	/*
	setfont(14,7,"Times New Roman");
	line(20,STARTY+3,20,STARTY+machine_num*GAP);
	char num[10];
	for(i=0;i<machine_num;i++)
	{
		
	    sprintf(num,"M%d",i);
		outtextxy(5,i*GAP,num);//��Ӧ�������Ϊ i
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

//��̬�������ͼ 
extern int CountTimes;//��0��ʼ��ÿ��+2 
/*
typedef struct timefinal
 {   
     int num[100];//�û����ϼӹ��Ĳ�Ʒ��� 
     int order[100];//��Ʒ����� 
     int begintime[100];//ÿ�μӹ��Ŀ�ʼʱ�� 
     int endtime[100];//ÿ�μӹ��Ľ���ʱ�� 
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

int FLAG[100][2]={{0},{0}}; //��ʼû�м��� 


void fixGantt(void)
{
 	xyprintf(700,1000,"%d",lff[0].begintime[0]);
	 //������� 
	char out[20];
	int a,b,c;
	int t=CountTimes;
	int i,flag,j;
	
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setfont(50,0,"Times New Roman");
	xyprintf(900,800,"������1"); 
	for(i=0;i<machine_num;i++)//ѭ�����ÿ�������ĸ��� 
	{
		xyprintf(100,800,"������2");
		flag=0;
		a=(machine_num+1)*30+50+(i+1)*GAP-HEIGHT;
	    b=(machine_num+1)*30+50+(i+1)*GAP;
			
		//���˶�ʱ��Ϊ����ʱ��
		if(machinefix[i].end[TTTIMES]!=0&&t*TPS>=machinefix[i].start[TTTIMES])	
		{
			xyprintf(700,800,"������3");
			if(machinefix[i].end[TTTIMES]>=(t+2)*TPS)//��2S��Ӧʱ���ڣ�����δ����
			{
				setcolor(BLACK);//���û�����ɫΪ��ɫ 
				bar(20+t*TPS*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);
			
				flag=1;
			}
			else if(machinefix[i].end[TTTIMES]<(t+2)*TPS) //��2S��Ӧʱ���ڣ����޽���
			{
				c=machinefix[i].end[TTTIMES]-t*TPS;
				setcolor(BLACK);//���û�����ɫΪ��ɫ
				bar(20+t*TPS*PIXELPERT,a,20+c*PIXELPERT,b);//�ӹ�����
				
				TTTIMES++; 
				flag=2;
			}
			if(machinefix[i].start[TTTIMES]==0)
		    FLAG[i][0]=0;//�����ޣ����޽��� 	
		}
		 
			
		//���˶�ʱ��Ϊ�ӹ�ʱ��
		else
		{
		    
	    	xyprintf(700,800,"������4");
			for(j=0;j<100&&flag==0;j++) 
		    {
				int savecolor=lff[i].num[j];
				setcolor(RGB(color[savecolor].count1,color[savecolor].count2,color[savecolor].count3));//���ݼӹ���Ʒ���ȷ����ɫ���������� 
				if(lff[i].begintime[j]<=t*TPS)//����ʼ�ӹ�ʱ��С��t 
		    	{
					if(lff[i].endtime[j]>=(t+2)*TPS)//����ʱ�����ڱ���2s 
				    { 
						bar(20+t*TPS*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);//�ӹ����� 
	    	            flag=1;
					}
					else//�����ڱ���ˢ�½���֮ǰ 
					{
						c=lff[i].endtime[j]-t*TPS;//����ʱ�� 
						bar(20+t*TPS*PIXELPERT,a,20+c*PIXELPERT,b);//�ӹ�����
						
						setcolor(WHITE);//����������ɫΪ��ɫ
			            sprintf(out,"%d",lff[i].order[j]);
	                    rectprintf(20+lff[i].begintime[j]*PIXELPERT,a,lff[i].endtime[j]*PIXELPERT,b,out);
			            
			            flag=1;
					}
			    } 
			    else  if(lff[i].begintime[j]<=(t+2)*TPS)//����ʼ�ӹ�ʱ��������ˢ��֮�� 
			    {
					if(lff[i].endtime[j]>=(t+2)*TPS)//����ʱ�����ڱ���2s 
				    {
						bar(20+lff[i].begintime[j]*PIXELPERT,a,20+(t+2)*TPS*PIXELPERT,b);//�ӹ����� 
					}
					else//�����ڱ���ˢ�½���֮ǰ 
					{
						c=lff[i].endtime[j]-t*TPS;//����ʱ�� 
						bar(20+lff[i].begintime[j]*PIXELPERT,a,20+c*PIXELPERT,b);//�ӹ�����
						 
						setcolor(WHITE);//����������ɫΪ��ɫ
			            sprintf(out,"%d",lff[i].order[j]);
	                    rectprintf(20+lff[i].begintime[j]*PIXELPERT,a,lff[i].endtime[j]*PIXELPERT,b,out);
			            //setcolor(BLACK);//���û�����ɫΪ��ɫ    
					}
					flag=1; 
				}
				if(lff[i].begintime[j]>t*TPS)//�� �������Ŀ�ʼʱ���ڵ�ǰˢ�¿�ʼʱ��֮��ֹͣ����
				flag=1;
				if(lff[i].begintime[j]==0)//��������
				flag=2; 
			}
			if(flag==2)
			FLAG[i][1]=0;//���Ϊi�Ļ������ӹ����Ѿ������ӹ�	
		} 
    }
    for(i=0,flag=0;i<machine_num&&flag==0;i++)
	{
		if(FLAG[i][0]==1||FLAG[i][1]==1)
		flag=1;
	} 
    if(flag==0)//�˳�ѭ����������ȫ��Ϊ1 
    StopSignal=1;
	return ;
}

extern int DNA_SIZE;
extern int BEST[200];  //?????????????????????

extern struct repair
{
	int point; //pointΪ��������ʱ��ڵ�
	int machine_num;  //���޻������ 
	int fix_time;  //����ʱ�� 
}fix;


extern int tf[180]; 

extern struct product{
	int total_time;
	int order;
	int time[100];
	int machine[100];
}pro[100];


int mtimes[100]={0};//����û������޴��� 

void timechange(void)//���м������룬����ʱ�� 
{
 	int m,place,t,p,flag;
	m=fix.machine_num;
	t=fix.fix_time; 
	p=fix.point;
	FLAG[m][0]=1; 
	
	for(place=0,flag=0;lff[m].endtime[place]!=0&&flag==0;place++)//������Ӧʱ�䣬�ж��Ƿ�Բ�Ʒ��Ӱ��   //flag==0�˳���˵������������ 
 	{
 	    if(lff[m].begintime[place]<t)
		{
		 	if(lff[m].endtime[place]>t)//�ڲ�Ʒ�ӹ�ʱ���� 
		 	flag=1;
			if(lff[m].endtime[place]<t);
			//����ѭ�� 
	    } 
	    else  //begin>=t
		{
			if(lff[m].endtime[place+1]!=0&&t<lff[m].begintime[place+1])//��ʼ�ڼ��
			{
				if((t+p)>lff[m].begintime[place+1])
				flag=2;//Ӱ����� 
				if((t+p)<=lff[m].begintime[place+1])
				flag=3;//��Ӱ���߹��� 
			} 
			if(lff[m].endtime[place+1]==0);
			 //��һ�����˳�ѭ�� 
		} 
	}//��flag==0�������������˳�ѭ������Ӱ��ӹ� 
	//ȷ����һ��place��flag 
	
    if(flag==0||flag==3||flag==2)
    {

    	//ֱ�Ӳ�����޲���
    	machinefix[m].start[mtimes[m]]=p;
    	machinefix[m].end[mtimes[m]]=p+t;
    }
 	else//flag==1
 	{
 		//������޲��֣��ڱ��μӹ�����֮�� 
    	machinefix[m].start[mtimes[m]]=lff[m].endtime[place];
    	machinefix[m].end[mtimes[m]]=lff[m].endtime[place]+t;
	}
	mtimes[m]++;
	
	if(flag==0||flag==3)//����Ӱ��ӹ����������

	return;
	else //��Ӱ������ӹ� ������ʱ�� 
	{
		int a=lff[m].num[place+1];//�ҵ�����Ӱ��ĵ�һ������ 
		int b=lff[m].order[place+1];// �ҵ�����Ӱ��ĵ�һ�������Ĺ���� 
		
		int time[3][100]={{0},{0}};//��ʼ��Ϊ�� 
	    int i=0,k=0,g=0;//i��DNA;k�������DNA�Ǽ��Ź���;g��������*/ 
	    int j[100]={0},h[100]={0};/*j[k]�ƹ���h[g]�Ƹû����ӹ��ĵڼ�����Ʒ*/ 
	    
	    int counttt=0;
	    for(i=0;counttt<=b;i++)
	    {
	    	if((BEST[i]-1)==a)
	    	counttt++;
		}
	    counttt=i;//ȷ���ù����ӦDNAλ��
		 
	    for(i=0;BEST[i]!=0;i++)
	    {
		    k=BEST[i]-1;//��DNAȷ��������� 
	       	g=pro[k].machine[j[k]];//��������
			//���ļ�����Ϣ֮ǰ�Ĳ��֣�����
			if(i<counttt) //�������
			{
				time[1][k]=lff[g].endtime[h[g]];
				time[2][g]=time[1][k];
			}
			else if(i==counttt) //������ʱ�� 
			{
				 
				if(flag==1)//����point�ڼӹ�ʱ����� 
			    {
			    	lff[g].endtime[h[g]]=lff[g].endtime[h[g]-1]+t+pro[k].time[j[k]]; 
				} 
				/*{
					if(time[2][g]<lff[g].endtime[h[g]]+fix.fix_time)
					time[2][g]=lff[g].endtime[h[g]]+fix.fix_time;//��������ʱ�� ��ԭʱ������� �Ϻ� 
				 }*/ 
				 else//flag==2�����޽����ᵢ��ʱ�� 
				/* {
				    if(time[2][g]<fix.fix_time+fix.point;)
				    time[2][g]=fix.fix_time+fix.point;//��������ʱ��Ϊ ���յ��źŵ�ʱ��ʱ��+����ʱ�� 
				}
				*/
				{
					lff[g].endtime[h[g]]=p+t+pro[k].time[j[k]];
				}
				
				time[1][k]=lff[g].endtime[h[g]];
				time[2][g]= time[1][k];
			}


		    else //���ļ�����Ϣ���ճ����� 
		    {
			    /* 
			    k=BEST[i]-1;//��DNAȷ��������� 
	        	g=pro[k].machine[j[k]];//�������� 
	        	*/
	        	lff[g].order[h[g]]=j[k];//��Ʒ����� 
	        	lff[g].num[h[g]]=k;//��¼��Ʒ��� 
	        	if(time[1][k]>=time[2][g])//����Ҫ�ȴ���Ʒ��һ����� 
	        	{
	        		lff[g].begintime[h[g]]=time[1][k];//���濪ʼʱ�� 
	        		time[1][k]+=pro[k].time[j[k]];//��Ʒʱ�������У���Ӧ��Ʒʱ������
		        	time[2][g]=time[1][k];//ȷ��������ɸù����ʱ�� 
	    	    }
    	    	else//����Ҫ�ȴ��������� 
	        	{
	        		lff[g].begintime[h[g]]=time[2][g];//���濪ʼʱ�� 
	        		time[2][g]+=pro[k].time[j[k]];//����ʱ�������У���Ӧ����ʱ������ 
	        	    time[1][k]=time[2][g];//ȷ��������ɸù����ʱ�� 
	        	}
	        	lff[g].endtime[h[g]]=time[1][k];//�������ʱ�� 
	        }
	    	h[g]++;//ȷ��numλ��
	    	j[k]++;//ȷ���ĸ���������һ��
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



void readfile(void)//���ļ� 
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

void putstate(void)//�������״̬ 
{
	int i;
	int t=CountTimes;
	int x=5,y=500;
	char out[10];
	int end=findend();
	int flag=0;
	
	//ˢ����Ƭ����
	setfillcolor(WHITE);
	bar(x,y,700,900);
	 
	//�������״̬ 
	setcolor(BLACK); 
	
	int stop[100]={0}; 
	for(i=0;i<machine_num;i++)
	{
		int j; 
		//xyprintf();
	    //���˶�ʱ��Ϊ����ʱ��
		if(machinefix[i].end[whattime[i]]!=0&&t*TPS>machinefix[i].start[whattime[i]])	
		{
			sprintf(out,"����"); 
			xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-machinefix[i].start[whattime[i]],machinefix[i].end[whattime[i]]-machinefix[i].start[whattime[i]]);
		    if((t+2)*TPS>=machinefix[i].end[whattime[i]])//������ˢ��֮�󣬼��޽������ƴμ�һ 
		    whattime[i]++;
		    if(machinefix[i].end[whattime[i]]==0)
		    FLAG[i][0]=0;//�����ޣ����ܵļ����ѽ���
		}

		
		 
		//���˶�ʱ��Ϊ�ӹ�ʱ������ 
		else
		{
			for(j=0,flag=0;j<100&&flag==0;j++)
			{
				if(lff[i].begintime[j]<=t*TPS&&lff[i].endtime[j]>t*TPS)//���ҵ����ʱ�� 
				{
					sprintf(out,"�ӹ�");
					xyprintf(x,y,"%d %d%s %d-%d %d %d\n",t*TPS,i,out,lff[i].num[j],lff[i].order[j],t*TPS-lff[i].begintime[j],lff[i].endtime[j]-lff[i].begintime[j]);
			        flag=1; 
				} 
				else
				{
					
					if(lff[i].begintime[j]>t*TPS)//�� �������Ŀ�ʼʱ���ڵ�ǰˢ�¿�ʼʱ��֮��ֹͣ����
				    {
				    	flag=2;//�˳����� 
				        sprintf(out,"����");
					    xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-lff[i].endtime[j-1],lff[i].begintime[j]-lff[i].endtime[j-1]);
					} 
				    if(lff[i].endtime[j]==0)//��������
			        {
			    	    sprintf(out,"����");
					    xyprintf(x,y,"%d %d%s      %d %d\n",t*TPS,i,out,t*TPS-lff[i].endtime[j-1],end-lff[i].endtime[j-1]);
					    flag=3;
			            FLAG[i][1]=1;//���ܵļӹ����������� 
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
    /*if(flag==0)//�˳�ѭ����������ȫ��Ϊ1 
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
