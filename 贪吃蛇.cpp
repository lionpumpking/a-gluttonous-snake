#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


#define h 25
#define w 85
#define up 0
#define down 1
#define left 2
#define right 3

int time1=200;
int a[h][w];   //定义一个数组作为坐标使用
int s[h*w][2];  //数据组
int sl=4;      //蛇的初始长度为3 
int fx;       //蛇的移动方向
bool eat=false;   //是否吃到食物 
int fs=0;      //记录分数的地址 




bool gameover()
{
	bool isgameover=false;
	int sx=s[0][0],sy=s[0][1]; //确定坐标
	if(sx==0||sx==h-1||sy==0||sy==w-1)
	     isgameover=true;
    for(int i=1; i<sl; i++)
	{
		if(s[i][0]==sx&&s[i][1]==sy)
		isgameover=true;
	} 
	return isgameover;
}


void init ()     //初始化游戏
{
	srand((unsigned)time(NULL));
	
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//关闭光标（百度） 
	int i,j;
	for(i=0; i<h; i++)
	{
		a[i][0]=1;   //地图第一列 
		a[i][w-1]=1;   //地图最后一列 
	}
	for(j=0; j<w; j++)
	{
		a[0][j]=1;    //地图第一行 
		a[h-1][j]=1;  //地图最后一行 
	}
	s[0][0]=10;
	s[0][1]=20;     //蛇头初始坐标设置 
	for(i=1; i<4; i++)
	{
		s[i][0]=s[0][0]+i;
		s[i][1]=s[0][1];  //蛇身体坐标 
	} 
	fx=right;
}


void gotoxy(int i , int j)  //移动  
{   
    COORD position={j,i};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position); 
}



int check(int ii,int jj)
{
	if(a[ii][jj]==1)
	    return 0;
	int i;
	if(ii==s[i][0]&&jj==s[i][1])
	   return 0;
	return 1;     //筛选食物可放置地方 	
}


void food()
{
	int i,j;
	do
	{
		i=rand()%h;  //0到h的随机数 
		j=rand()%w;  //0到w的随机数 
	}
	while(check(i,j)==0);   //找到一个可以放置食物的地方
	a[i][j]=-1;
	gotoxy(i,j);
	printf("&");
	 
} 

void map()
{ 
    gotoxy(0,0);
	int i,j;
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			if(a[i][j]==0)  
			printf(" ");    //地图中间打印空格  
			else
			printf("#");    //地图边缘打印# 
		}
		printf("\n");      //换行 
	}
}


void she()
{
	int i;
	for(i=0; i<sl; i++)
	{
		gotoxy(s[i][0],s[i][1]);  //将光标放到蛇的位置
		printf("@");   //画蛇 
	}
}


void move()
{
	int i;
	gotoxy(s[sl-1][0],s[sl-1][1]);
	printf(" ");  //抹除上一个尾巴的痕迹 
	if(eat)
	{
		sl++;
		eat=false;
	}
	for(i=sl-1; i>0; i--)
	{
		s[i][0]=s[i-1][0];
		s[i][1]=s[i-1][1];  //将蛇的前面坐标给后一节身体 
	}
	switch(fx)    //方向控制 
	{
		case up :
			s[0][0]--;
			break;
		case down :
			s[0][0]++;
			break;
		case left :
			s[0][1]--;
			break;
		case right :
			s[0][1]++;
			break;
		
	}
}

void fsjl()
{
	gotoxy(27,5);
	printf("你的得分:%d",fs);
	gotoxy(0,90);
	printf("向上：w或者W");
	gotoxy(1,90);
	printf("向下：s或者S");
	gotoxy(2,90);
	printf("向左：a或者A");
	gotoxy(3,90);
	printf("向右：d或者D");
	gotoxy(4,90);
	printf("暂停：p或者P");
	gotoxy(5,90);
	printf("初始速度200");
	gotoxy(6,90);
	printf("降低速度：i或者I");
	gotoxy(7,90);
	printf("加快速度：u或者U");
	gotoxy(8,90);
	printf("暂停后按任意键继续");
	
}


void key()
{
	if(kbhit()!=0)   //如果键盘有输入
	{
		char in;
		while(!kbhit()==0)  //输入的最后一个
		    in=getch();
		switch(in)     //方向控制 
		{
			case 's' :
			case 'S' :
				if(fx!=up)
				   fx=down;
				break;
		    case 'w' :
		    case 'W' :
			    if(fx!=down)
				   fx=up;
				break;
		    case 'a' :
			case 'A' :
			    if(fx!=right)
				   fx=left;
				break;
			case 'd' :
			case 'D' :
			    if(fx!=left)
				   fx=right; 
				break;
			case 'p' :
			case 'P' :
				gotoxy(h,0);  //移动光标 
				system("pause");  
				printf("                                   "); //消除按任意键的提示
				break; 
			case 'u' :
			case 'U' :
				time1-=50;
				break;
			case 'i' :
			case 'I' :
				time1+=50;
				break;
		} 
	} 
}


int main ()
{
	system("color F0");
	fsjl();    //记录分数 
    printf("\n");
    system("pause"); 
    system("cls");
	init();    //调用init函数
	fsjl();    //记录分数 
	map();     //调用map函数 
	food();
	while(1==1)
	{
	she();     //调用she函数
	Sleep(time1);  //停止运行200ms
	key();        //调用key函数 
	move();     //调用move函数 
	
	if(gameover())
	{
		system("cls");  //清除 
		printf("你的分数为%d\n",fs);
		printf("Game over\n");
		system("pause");
		break; 
	}
	
	if(a[s[0][0]][s[0][1]]==-1)
	{
		eat=true;
		    fs+=10;
		    food();
		    a[s[0][0]][s[0][1]]=0;//去掉食物 
		    time1=time1*0.98; 
	}
	
	fsjl();
    }  	
	return 0;
} 
