#include "path.h"
#include "CreatMap.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "ImageSupport.h"

#define TIMER_BLINK001 3
const int mseconds001 = 5000;
#define MAXM  10000


int next_x,next_y;
extern int now_x,now_y;
extern int Map[1600];
extern int n;
extern double cx,cy;
const int Turn[4][2]={
	{0,-1}, // Left
	{-1,0}, // Up
	{0,1}, // Right
	{1,0} //Down
};

int tot;
typedef struct{
	int x,y;
}Queue;
Queue que[MAXM];

int Path[MAXM][2],num;
int d[MAXM],last[MAXM],rank[MAXM],MaxRank;

int Calculate(int x,int y,int n){return x+y*n;}

void Inverse_Calculate(int tmp,int *ex,int *ey,int n){
	*ex=tmp/n;
	*ey=tmp%n;
	return ;
}
// return true if a certain path exists.

int FindPath(int n,int Map[],int StartX,int StartY,int EndX,int EndY){
	int u,nx,ny;
	memset(d,0x3f,sizeof(d));
	memset(last,0,sizeof(last));
	d[Calculate(EndX,EndY,n)]=1;
	int Head=0,Tail=0;
	que[Tail++]=(Queue){EndX,EndY};
	while(Head<Tail){
		nx=que[Head].x;
		ny=que[Head].y;
		++Head;
		for(u=0;u<4;++u){
			int fx=nx+Turn[u][0];
			int fy=ny+Turn[u][1];
			if(fx<0 || fx>=n || fy<0 || fy>=n) continue; 
			if(Map[Calculate(fx,fy,n)]==1 || d[Calculate(fx,fy,n)]!=0x3f3f3f3f) continue;
			else{
				d[Calculate(fx,fy,n)]=d[Calculate(nx,ny,n)]+1;
				last[Calculate(fx,fy,n)]=Calculate(nx,ny,n);
				que[Tail].x=fx;
				que[Tail].y=fy;
				++Tail;
			}
		}
	}
	if(d[Calculate(StartX,StartY,n)]==0x3f3f3f3f) return 0;
	nx=StartX,ny=StartY; tot=0;
	while(nx!=EndX || ny!=EndY){
		++tot;
		Path[tot][0]=nx;
		Path[tot][1]=ny;
		Inverse_Calculate(last[Calculate(nx,ny,n)],&nx,&ny,n);
	}
	memset(rank,0,sizeof(rank)); MaxRank=0;
	rank[Calculate(StartX,StartY,n)]=1;
	Head=Tail=0;
	que[Tail++]=(Queue){StartX,StartY};
	while(Head<Tail){
		nx=que[Head].x;
		ny=que[Head].y;
		++Head;
		for(u=0;u<4;++u){
			int fx=nx+Turn[u][0];
			int fy=ny+Turn[u][1];
			if(fx<0 || fx>=n || fy<0 || fy>=n) continue; 
			if(Map[Calculate(fx,fy,n)]==1 || rank[Calculate(fx,fy,n)]) continue;
			else{
				rank[Calculate(fx,fy,n)]=rank[Calculate(nx,ny,n)]+1;
				MaxRank=rank[Calculate(fx,fy,n)];
				que[Tail].x=fx;
				que[Tail].y=fy;
				++Tail;
			}
		}
	}
	return 1;
}
//运行这个程序前必须保证FindPath已经运行。 
//找不到会返回-1
 
void DrawNextStep(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	HBITMAP one  = readBmpImage("0002.bmp");
    drawBmp(one,next_x*Line+cx+0.5*Line,cy-next_y*Line-0.5*Line,Line,Line,SRCAND);
}

int FindNextStep(){
	/*
	static int tot=0;
	++tot;
	FILE *F1=fopen("out.txt","w");
	fprintf(F1,"%d %d %d\n",tot,next_x,next_y)； 
	fclose(F1);*/
	int u;
	for(u=0;u<4;++u){
		int fx=now_x+Turn[u][0];
		int fy=now_y+Turn[u][1];
		if(fx<0 || fx>=n || fy<0 || fy>=n) continue;
		if(Map[Calculate(fx,fy,n)]==1 || d[Calculate(fx,fy,n)]==0x3f3f3f3f) continue;
		if(d[Calculate(fx,fy,n)]==d[Calculate(now_x,now_y,n)]-1) {
			next_x = fx;
			next_y = fy;
			//DrawNextStep();
		    return fx+fy*n;
		}
	}
	return -1;
}


void TipTimerEvent(int TimeID){
	static int k = 1;
	int flag =0;
	int i;
	switch(TimeID){
		case TIMER_BLINK001:
			Display2();
			for(i=0;i<n*n;i++){
				if(rank[i] == k){
					flag = 1;
				}
				if(rank[i]<=k&&rank[i]>0){
					DrawTip(i);
				} 
			}
			k++;
	}
	if(!flag&&TimeID==TIMER_BLINK001) cancelTimer(TIMER_BLINK001);
}


//void Visible(){
//	int t=1; 
//	//InitConsole();
//	//printf("%d\n",MaxRank);
//	while(t<=MaxRank){
//		int u;
//		for(u=0;u<n*n;++u){
//			if(rank[u]==t) {
//			DrawTip(u); 
//			}//打印	
//			Sleep(25);
//		    Display2();
//		}
//		++t;
//
//	}
//	return ;
//}

void DrawTip(int i){
	int x = i%n ;
	int y = i/n ;
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	HBITMAP coin  = readBmpImage("0002.bmp");
    drawBmp(coin,x*Line+cx+0.5*Line,cy-y*Line-0.5*Line,Line,Line,SRCAND);
   // Map[x+y*n] = 1; 
}

void DrawTipRoad(){
	int i = 0;
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	for(i=1;i<=tot;i++){
		SetPenColor("Green");
		FillBox(cx+Path[i][0]*Line,cy-Path[i][1]*Line,Line);
	} 
}
	
