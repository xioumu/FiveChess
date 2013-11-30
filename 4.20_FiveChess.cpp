// FiveChess.cpp : Defines the entry point for the console application.
// 	 circle(x*SIDE + BL,y*SIDE + BH,QI+2);

#include <iostream>
#include <graphics.h>  
#include "stdio.h"
#include <conio.h>
#include <io.h> 
#include "time.h"

#define ZL 800  //总边长
#define ZH 600
#define CL 760  //次右下点
#define CH 560
#define BL 40  //次左上点
#define BH 80
#define SIDE 40 //格子边长
#define QI 17 // 棋子半径
#define DB 1
#define MAXN 200000000
#define TWO 200
#define VTWO 50
#define THREE 1000
#define VTHREE 400
#define FOUR 20000
#define VFOUR 1000

long xn,yn,now,win;
long map[500][500],bian[9][2]={{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};  // 1为白子（人），2为红子（电脑）
long left[500][500],up[500][500],lxie[500][500],rxie[500][500];
long vleft[500][500],vup[500][500],vlxie[500][500],vrxie[500][500];

long ok(long x,long y)
{
     if(x>=0 && x<=xn && y>=0 && y<=yn) return 1;
	 else return 0;
}

void HuaQi(long x,long y,long cl)
{
     
  if(cl == 1) { setcolor(WHITE); setfillstyle(WHITE, SOLID_FILL, NULL); }
  else { setcolor(RED);  setfillstyle(RED, SOLID_FILL, NULL); }
     
	 fillcircle(BL + x*SIDE , BH + y*SIDE , QI);

}
void QiPan()
{
	 long i,j,k,r,w;
	 setcolor(LIGHTGRAY);

	 for(i=0;i<=xn;i++) line(BL + i*SIDE , BH , BL + i*SIDE , CH);
	 for(i=0;i<=yn;i++) line(BL , BH + i*SIDE , CL , BH + i*SIDE);

	 for(i=0;i<=xn;i++) 
	   for(j=0;j<=yn;j++)
		 if(map[j][i] != 0)
		   HuaQi(i,j,map[j][i]);
}

void HuaNow(long x,long y)
{
     long xx,yy,i;
     setcolor(WHITE);
     xx = x*SIDE + BL;  yy = y*SIDE + BH;
     for(i=1;i<8;i+=2)
	 { 
	   line(xx + 21*bian[i][0] , yy + 21*bian[i][1] , xx + 15*bian[i][0] , yy + 15*bian[i][1]);
	 }
}

void init()
{
	 long i,j,k,r,w;
	 long t;
	 t = time(NULL);
	 srand(t);

	 xn = (CL-BL) / SIDE;
	 yn = (CH-BH) / SIDE;
	 memset(map,0,sizeof(map));
	 now = 1 ; win = 0;
	 cleardevice();

     FlushMouseMsgBuffer();
	 if(DB) { map[1][1] = 1; map[1][2] = 2; map[0][0]=1; map[2][2] = 1; map[1][3] = 1; map[0][4] = 1; map[2][1] = 2;}
     QiPan(); 
	 HuaNow(2,5);
}
void MoveMouse(long x,long y)
{    
     cleardevice();
	 QiPan();
     HuaNow(x,y);
}
void PressMouse(long x,long y)
{
     if(map[y][x] != 0) return ;

     map[y][x] = 1;
	 now = 2;

     cleardevice();
	 QiPan();
	 HuaNow(x,y);
}

long Pan()
{
	 long i,j,k,r,w;
	 memset(left,0,sizeof(left));
	 memset(up,0,sizeof(up));
     memset(lxie,0,sizeof(lxie));
	 memset(rxie,0,sizeof(rxie));

	 for(i=0;i<=yn;i++) 
	   for(j=0;j<=xn;j++)
	   {
		 if(i != 0 && map[i][j] != 0 && map[i-1][j] == map[i][j] ) up[i][j] = up[i-1][j] + 1;
		 if(j != 0 && map[i][j] != 0 && map[i][j-1] == map[i][j] ) left[i][j] = left[i][j-1] + 1;
		 if(i != 0 && j != 0 && map[i][j] != 0 && map[i][j] == map[i-1][j-1] ) lxie[i][j] = lxie[i-1][j-1] + 1;
		 if(i != 0 && j != xn && map[i][j] != 0 && map[i][j] == map[i-1][j+1] ) rxie[i][j] = rxie[i-1][j+1] + 1;

		 if(up[i][j] == 4 || left[i][j] == 4 || lxie[i][j] == 4 || rxie[i][j] == 4) 
		 { 
		   win = map[i][j];
		   return 1;
		 }
	   }

     return 0;
}
void End()
{
     setcolor(RED);
	 setfont(30, 0,"宋体");
     if(win == 1) 
	 {  
	    char ss[100] = " you win! ";
        outtextxy(320, 30, ss);
	 }
	 else 
	 {
	    char ss[100] = " you lose! ";
		outtextxy(320, 30, ss);
	 }
	 char sh[100] = "请按回车键重来";
	 outtextxy(290 , 60 , sh);
}
long GuJia(long m) /*m为正,下步h走*/
{    
     long i,j,k,r,w,sum=0,h;
	 long num[10][3],vnum[10][3];
	 memset(left,0,sizeof(left));
	 memset(up,0,sizeof(up));
     memset(lxie,0,sizeof(lxie));
	 memset(rxie,0,sizeof(rxie));
	 memset(vleft,0,sizeof(vleft));
	 memset(vup,0,sizeof(vup));
	 memset(vrxie,0,sizeof(vrxie));
	 memset(vlxie,0,sizeof(vlxie));
     memset(num,0,sizeof(num));
	 memset(vnum,0,sizeof(vnum));

	 for(i=0;i<=yn;i++) 
	   for(j=0;j<=xn;j++)
		 if(map[i][j] != 0)
		 { 
		   left[i][j] = up[i][j] = lxie[i][j] = rxie[i][j] = 1;
		   if(i != 0)
		   {
			  if(map[i-1][j] == map[i][j])
			  {
			    up[i][j] = up[i-1][j] + 1;
				vup[i][j] = vup[i-1][j];
			  }
			  else vup[i][j] = 1;
			  if(i == yn || map[i+1][j] != map[i][j])
			  {
				if(vup[i][j] == 0 && map[i+1][j] == 0) num[ up[i][j] ][ map[i][j] ]++;
				else if(map[i+1][j] == 0 || vup[i][j] == 0)  vnum[ up[i][j] ][ map[i][j] ]++;
			  }


			  if(j != 0 && map[i-1][j-1] == map[i][j])
			  {
				lxie[i][j] = lxie[i][j] + 1;
				vlxie[i][j] = vlxie[i][j];
			  }
			  else vlxie[i][j] = 1;
			  if(i == yn || j == xn || map[i+1][j+1] != map[i][j])
			  {
				if(vlxie[i][j] == 0 && map[i+1][j+1] == 0) num[ up[i][j] ][ map[i][j] ]++;
				else if(vlxie[i][j] == 0 || map[i+1][j+1] == 0) vnum[ up[i][j] ][ map[i][j] ]++;
			  }


			  if(j != yn && map[i-1][j+1] == map[i][j])
			  {
				rxie[i][j] = rxie[i][j] + 1;
				vrxie[i][j] = vrxie[i][j];
			  }
			  else vrxie[i][j] = 1;
			  if(j == 0 || i == yn || map[i+1][j-1] != map[i][j])
			  {
				if(vrxie[i][j] == 0 && map[i+1][j-1] == 0) num[ up[i][j] ][ map[i][j] ]++;
				else if(vrxie[i][j] == 0 || map[i+1][j-1] == 0) vnum[ up[i][j] ][ map[i][j] ]++;
			  }
		   }
		   else vup[i][j] = vlxie[i][j] = vrxie[i][j] = 1;


		   if(j != 0 && map[i][j-1] == map[i][j]) 
		   {
			 left[i][j] = left[i][j-1] + 1 ;
			 vleft[i][j] = vleft[i][j-1];
		   }
		   else vleft[i][j] = 1;	 
		   if(j == yn || map[i][j+1] != map[i][j])
		   {
			 if(vleft[i][j] == 0 && map[i][j+1] == 0) num[ up[i][j] ][ map[i][j] ]++;
			 else if(vleft[i][j] == 0 && map[i][j+1] == 0) vnum[ up[i][j] ][ map[i][j] ]++;

		   }
		 }
    
    h = m%2 + 1;
	if(vnum[5][h] + num[5][h] > 0) return -MAXN;
	if(vnum[5][m] + num[5][m] > 0) return MAXN;
	if(vnum[4][h] + num[4][h] > 0) return -MAXN;
    if(num[4][h] > 0) return MAXN;
	
}
void Computer()
{    
     long i,j,k;
}
void solve()
{
     MOUSEMSG m;	
	 long i,j,k,r,w,x,y;
	 long nowx=-1,nowy=-1;
     while(1)
	 {
	    m = GetMouseMsg();
	    x = ( m.x - (BL-SIDE/2) ) / SIDE;
	    y = ( m.y - (BH-SIDE/2) ) / SIDE;
	    if( ok(x,y) )
		{  
	 	  switch(m.uMsg)
		  {
		  	   case WM_MOUSEMOVE:     //移动
				   if(  nowx != x || nowy != y )  MoveMouse(x,y);
				   break;

			   case WM_LBUTTONDOWN:  //按下
			  	   PressMouse(x,y);
				   Computer();
				   break;
		  }
		  nowx = x; nowy = y;  
		  if( Pan() ) break;
		}
     }
	 End();
}

int main()
{
    char c;
    initgraph(ZL , ZH);
	do
	{ 
	  
	  init();
	  solve();
	  fflush(stdin);
	  c = getchar() ;
	}
    while(c != 'q');
	closegraph();  
	return 0;
}

