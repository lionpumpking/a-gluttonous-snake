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
int a[h][w];   //����һ��������Ϊ����ʹ��
int s[h*w][2];  //������
int sl=4;      //�ߵĳ�ʼ����Ϊ3 
int fx;       //�ߵ��ƶ�����
bool eat=false;   //�Ƿ�Ե�ʳ�� 
int fs=0;      //��¼�����ĵ�ַ 




bool gameover()
{
	bool isgameover=false;
	int sx=s[0][0],sy=s[0][1]; //ȷ������
	if(sx==0||sx==h-1||sy==0||sy==w-1)
	     isgameover=true;
    for(int i=1; i<sl; i++)
	{
		if(s[i][0]==sx&&s[i][1]==sy)
		isgameover=true;
	} 
	return isgameover;
}


void init ()     //��ʼ����Ϸ
{
	srand((unsigned)time(NULL));
	
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�رչ�꣨�ٶȣ� 
	int i,j;
	for(i=0; i<h; i++)
	{
		a[i][0]=1;   //��ͼ��һ�� 
		a[i][w-1]=1;   //��ͼ���һ�� 
	}
	for(j=0; j<w; j++)
	{
		a[0][j]=1;    //��ͼ��һ�� 
		a[h-1][j]=1;  //��ͼ���һ�� 
	}
	s[0][0]=10;
	s[0][1]=20;     //��ͷ��ʼ�������� 
	for(i=1; i<4; i++)
	{
		s[i][0]=s[0][0]+i;
		s[i][1]=s[0][1];  //���������� 
	} 
	fx=right;
}


void gotoxy(int i , int j)  //�ƶ�  
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
	return 1;     //ɸѡʳ��ɷ��õط� 	
}


void food()
{
	int i,j;
	do
	{
		i=rand()%h;  //0��h������� 
		j=rand()%w;  //0��w������� 
	}
	while(check(i,j)==0);   //�ҵ�һ�����Է���ʳ��ĵط�
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
			printf(" ");    //��ͼ�м��ӡ�ո�  
			else
			printf("#");    //��ͼ��Ե��ӡ# 
		}
		printf("\n");      //���� 
	}
}


void she()
{
	int i;
	for(i=0; i<sl; i++)
	{
		gotoxy(s[i][0],s[i][1]);  //�����ŵ��ߵ�λ��
		printf("@");   //���� 
	}
}


void move()
{
	int i;
	gotoxy(s[sl-1][0],s[sl-1][1]);
	printf(" ");  //Ĩ����һ��β�͵ĺۼ� 
	if(eat)
	{
		sl++;
		eat=false;
	}
	for(i=sl-1; i>0; i--)
	{
		s[i][0]=s[i-1][0];
		s[i][1]=s[i-1][1];  //���ߵ�ǰ���������һ������ 
	}
	switch(fx)    //������� 
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
	printf("��ĵ÷�:%d",fs);
	gotoxy(0,90);
	printf("���ϣ�w����W");
	gotoxy(1,90);
	printf("���£�s����S");
	gotoxy(2,90);
	printf("����a����A");
	gotoxy(3,90);
	printf("���ң�d����D");
	gotoxy(4,90);
	printf("��ͣ��p����P");
	gotoxy(5,90);
	printf("��ʼ�ٶ�200");
	gotoxy(6,90);
	printf("�����ٶȣ�i����I");
	gotoxy(7,90);
	printf("�ӿ��ٶȣ�u����U");
	gotoxy(8,90);
	printf("��ͣ�����������");
	
}


void key()
{
	if(kbhit()!=0)   //�������������
	{
		char in;
		while(!kbhit()==0)  //��������һ��
		    in=getch();
		switch(in)     //������� 
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
				gotoxy(h,0);  //�ƶ���� 
				system("pause");  
				printf("                                   "); //���������������ʾ
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
	fsjl();    //��¼���� 
    printf("\n");
    system("pause"); 
    system("cls");
	init();    //����init����
	fsjl();    //��¼���� 
	map();     //����map���� 
	food();
	while(1==1)
	{
	she();     //����she����
	Sleep(time1);  //ֹͣ����200ms
	key();        //����key���� 
	move();     //����move���� 
	
	if(gameover())
	{
		system("cls");  //��� 
		printf("��ķ���Ϊ%d\n",fs);
		printf("Game over\n");
		system("pause");
		break; 
	}
	
	if(a[s[0][0]][s[0][1]]==-1)
	{
		eat=true;
		    fs+=10;
		    food();
		    a[s[0][0]][s[0][1]]=0;//ȥ��ʳ�� 
		    time1=time1*0.98; 
	}
	
	fsjl();
    }  	
	return 0;
} 
