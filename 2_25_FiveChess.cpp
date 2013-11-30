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
#define TWO 20
#define VTWO 5
#define THREE 100
#define VTHREE 40
#define FOUR 2000
#define VFOUR 100
#define DE 4

long GuJia(long m);
void save();
void load();

typedef struct
{
  long x,y,sc;
}node;
node dui[250];
long rear,front;
long xn,yn,now,win;
long map[50][50],bian[9][2]={{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};  // 1为白子（人），2为红子（电脑）
long left[50][50],up[50][50],lxie[50][50],rxie[50][50];
long vleft[50][50],vup[50][50],vlxie[50][50],vrxie[50][50];
long score[2][10][3]={ { {0,0,0},  
                         {0,2,3},
					     {0,20,20},
					     {0,1000,4100},
                         {0,2000,200000000}
				       },
					   { {0,0,0},
					     {0,1,2},
					     {0,5,5},
					     {0,400,600},
					     {0,1000,200000000}
					   }
					 };


long ok(long x,long y)
{
     if(x>=0 && x<=xn && y>=0 && y<=yn) return 1;
	 else return 0;
}

void jin(node a,node dui[])
{
     long i,j;
}
void chu(node *a,node dui[])
{
     long i,j;
}

void kp(node dui[],long a,long b)
{
     long i=a,j=b,mid,k;
	 k = rand();
     if(i<j)
	 {  dui[0] = dui[k]; dui[k] = dui[i]; dui[i] = dui[0];
	    while(i<j)
		{  while(i<j && dui[0].sc <= dui[j].sc) j--;
		   dui[j] = dui[i];
		   while(i<j && dui[0].sc >= dui[i].sc) i++;
		   dui[i] = dui[j];
		} 
		kp(dui,a,i-1);
		kp(dui,i+1,b);
	 }
}
void save()
{
     FILE *output;
	 long i,j;
	 output = fopen("map.txt","w");
     for(i=0;i<=yn;i++,fprintf(output,"\n"))
	  for(j=0;j<=xn;j++)
	   fprintf(output,"%ld ",map[i][j]);
     fclose(output);
}
void load()
{
     FILE *input;
	 long i,j;
     input=fopen("map.txt","r");
	 for(i=0;i<=yn;i++)
	  for(j=0;j<=xn;j++)
	   fscanf(input,"%ld",&map[i][j]);
     fclose(input); 
}
void PrintQiPan(long x,long y,long m)
{    
     char ss[200]="\0";
	 itoa(GuJia(m),ss,10);
     outtextxy(90 , 30 , ss);
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
	 memset(map,0,sizeof(map));
	  
	 xn = (CL-BL) / SIDE;
	 yn = (CH-BH) / SIDE;
	 memset(map,0,sizeof(map));
	 now = 1 ; win = 0;
	 cleardevice();

     FlushMouseMsgBuffer();
	 //if(DB) { map[1][1] = 1; map[1][2] = 1; map[1][3]=1; }
	 //load();
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

     map[y][x] = now;
	 now = now%2 +1;
   
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
	 save();
}
long GuJia(long m) //m 为正，下步H走
{
     long i,j,k,h,t,t2,sum=0,mm,hh;
	 long xnn,ynn,xnn1,ynn1,xnn2,ynn2,xx,yy;
	 long dir[50][50][9],num[10][3][3],v[50][50][5];
     h = m%2 + 1;

	 memset(dir,0,sizeof(dir));
	 memset(num,0,sizeof(num));
	 memset(v,0,sizeof(v));
     
     for(i=0;i<=yn+1;i++) 
	   for(j=0;j<=xn+1;j++)
	     for(t=6;t<=9;t++)
	     {  
		    k = t%8;
		    xx = j + bian[k][0]; yy = i + bian[k][1];

			if(i == 8 && j == 13 && t == 7)
			  mm = 1;

			if( ok(xx,yy) && map[yy][xx] != 0 )
			{
			   if( ok(j,i) == 0 || ( map[i][j] != 0 && map[i][j] != map[yy][xx]) )
			   {  
			      v[yy][xx][ k%4 ]++;   
			      num[ dir[yy][xx][ k%4 ] ][ map[yy][xx] ][ v[yy][xx][ k%4 ] ]++;

				  if( ok(j,i) )  //不同子相遇
				  {
				    v[i][j][ k%4 ]++;
					dir[i][j][ k%4 ] = 1;
				  }
			   }
			   else if(map[i][j] == 0) //遇空子
			   {
			      num[ dir[yy][xx][ k%4 ] ][ map[yy][xx] ][ v[yy][xx][ k%4 ] ]++;
			   }
			   else if(map[i][j] == map[yy][xx]) //遇相同子
			   {
			      v[i][j][ k%4 ] = v[yy][xx][ k%4 ];
                  dir[i][j][ k%4 ] = dir[yy][xx][ k%4 ] + 1;
			   }
			}
            else if( ok(xx,yy) && map[yy][xx] == 0)
			{ 
			   if(ok(j,i) != 0 && map[i][j] != 0) //遇空子
			   {  
			      dir[i][j][ k%4 ] = 1; 
			   }
			}
			else if( ok(xx,yy) == 0) 
			{ 
			   if( ok(j,i) != 0 && map[i][j] != 0) //遇边界
			   {  
			      v[i][j][ k%4 ]++;
			      dir[i][j][ k%4 ] = 1; 
			   }
			}
	     }
     
	 for(i=5;i<=9;i++)
	   for(j=0;j<=2;j++) 
	     if(num[i][h][j] > 0) return -MAXN-1;
	     else if(num[i][m][j] > 0) return MAXN+1;

      for(j=0;j<=1;j++)
	    if(num[4][h][j] > 0) return -MAXN;

      if(num[4][m][0]) return MAXN;

	  for(i=1;i<=4;i++) 
	    for(j=0;j<=1;j++)
	    { 
	       sum += num[i][m][j] * score[j][i][1];
	       sum -= num[i][h][j] * score[j][i][2];
	    }
      return sum; 
}

void move(long x,long y,long oldmap[50][50],long oldnum[10][3][2],long m)
{
	 memcpy(oldmap,map,sizeof(map));
	 map[y][x] = m;
}
void recove(long oldmap[50][50],long oldnum[10][3][2])
{
	 memcpy(map,oldmap,sizeof(map));
}
long mx=0,my=0,xx=10,yy=10;
long Max(long top,long alpha,long beta);
long Min(long top,long alpha,long beta);
long Min(long top,long alpha,long beta)
{
     long i,j,k,xm,ym,m,h,r,w,dn=0;
	 long var;
	 long v[50][50],oldnum[10][3][2];
	 node dui[300];

   
	 if(top%2 == 1) { m = 2; h = 1;}
	 else { m = 1; h =2 ;}
	 if(top == DE)
	   return GuJia(2);
     
     for(i=0;i<=yn;i++) 
	   for(j=0;j<=xn;j++)
	     if(map[i][j] != 0)
	       for(k=0;k<7;k++)
		   {  
		      xm = j+bian[k][0]; ym = i+bian[k][1];
		      if(ok(xm,ym) && map[ym][xm] == 0) && v[ym][xm] == 0)
              { 
		         dui[++dn].x = xm;  
				 dui[dn].y = ym;
				 dui[dn].sc = GuJia(1);
				 v[ym][xm] = 1;
		      } 
		   }
  
     kp(dui,1,dn);

	 for(i=1;i<=dn;i++)
	 {
	    xm = dui[i].x;  ym = dui[i].y;
		move(xm,ym,m);
        if(-GuJia(1) <= -MAXN) return -GuJia(1); 
		var = Max(top+1 , bet , alpha)
	 }
 
	 for(i=0;i<=yn;i++) 
	  for(j=0;j<=xn;j++)
	   if(map[i][j] != 0) 
	   for(k=0;k<7;k++)
	   { xm = j+bian[k][0]; ym = i+bian[k][1];
	     if(ok(xm,ym) && map[ym][xm] == 0)
		 {
		   move(xm,ym,oldmap,oldnum,m);
		   if(-GuJia(1) <= -MAXN) return -GuJia(1); 
		   var = Max(top+1 , beta , alpha , xm , ym);

		   printf("%ld %ld %ld\n",var,xm,ym);
		   recove(oldmap,oldnum);
		   
		   if(var <= beta) 
		   { 
		     return beta; 
		   }
		   if(var < alpha)
		   { if(top == 1) {xx = xm; yy = ym;}
		     alpha = var;
		   } 
		 }
	   }  
    printf("\n==============================MIN\n");
    return alpha; 
}
long Max(long top,long alpha,long beta,long x,long y)
{
     long i,j,k,xm,ym,m,h,r,w;
	 long var;
	 long oldmap[50][50],oldnum[10][3][2];


	 if(top%2 == 1) { m = 2; h = 1;}
	 else { m = 1; h = 2;}
	 if(top == DE)
	   return -GuJia(1);

	 for(i=0;i<=yn;i++) 
	  for(j=0;j<=xn;j++)
	   if(map[i][j] != 0) 
	   for(k=0;k<=7;k++)
	   { xm = j+bian[k][0]; ym = i+bian[k][1];
	     
		 if(xm == 10 && ym == 7)
		  {
		    r=1;
		  }
	     if(ok(xm,ym) && map[ym][xm] == 0)
		 {
		   move(xm,ym,oldmap,oldnum,m);
		   if( GuJia(2) >= MAXN) 
		   {   if(top == 1) { xx = xm; yy = ym;}
		       return MAXN;
		   }

		   var = Min(top+1 , beta , alpha , xm , ym);

           printf("%ld %ld %ld\n",var,xm,ym);

		   recove(oldmap,oldnum);
		   
		   if(var >= beta) 
		   { 
		     return beta; 
		   }
		   if(var > alpha)
		   { if(top == 1) { xx = xm; yy = ym;}
		     alpha = var;
		   } 
		 }
	   }
    printf("\n==============================\n");
    return alpha;  
} 

void ComXia(long x,long y)
{
     long i,j;
	 printf("%ld\n",map[y][x]);

	 map[y][x] = 2;
	 now = 1;
     
	 //printf("%ld %ld\n",x,y);

	 cleardevice();
	 QiPan();
	 HuaNow(x,y);
}
void solve()
{
     MOUSEMSG m;	
	 long i,j,k,r,w,x,y,ox=-1,oy=-1;
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
                    if(ox == x && oy == y) break;
			  	    PressMouse(x,y);
                    ox = x; oy = y;
					PrintQiPan(x,y,1);
					//getch();
					if(Pan())break;

				    Max(1,-MAXN-2,MAXN+2,0,0);
				    ComXia(xx,yy);
					
					save();
					PrintQiPan(xx,yy,2);
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

