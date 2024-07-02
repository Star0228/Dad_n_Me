#include "CreatMap.h"
#include "scene.h"
#include "path.h"
#define MAXM 10000 

double cx,cy;
extern int next_x,next_y;
int start_x,start_y,end_x,end_y,now_x,now_y,coin_x,coin_y;
int n=30;
int Map[1600] = {};
extern int Path[MAXM][2];
extern int count_step,tot;
extern int coin_existence;
//extern buttonstatus pb[10];

void GetSize(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
}

//画正方形 
void DrawBox(double cx,double cy,double line){
	MovePen(cx,cy);
	DrawLine(line,0);
	DrawLine(0,-line);
	DrawLine(-line,0);
	DrawLine(0,line);
}

//画出填充颜色的正方形 
void FillBox(double cx,double cy,double line){
	MovePen(cx,cy); 
	StartFilledRegion(Density);
	    DrawLine(line,0);
	    DrawLine(0,-line);
	    DrawLine(-line,0);
	    DrawLine(0,line);
	EndFilledRegion();
	
}


//随机数生成地图数组 
void CreatMap(){
	int count_x,count_y;
	for(count_y = 0;count_y<n;count_y++){
		for(count_x = 0;count_x<n;count_x++){
			if (count_y*n+count_x == end_y*n+end_x||count_y*n+count_x == start_y*n+start_x) continue;
			Map[count_y*n+count_x] = Random();
			if(Map[count_y*n+count_x]) Map[count_y*n+count_x] = 0;
			else Map[count_y*n+count_x] = 1;
		}
	}
	if(!FindPath(n,Map,start_x,start_y,end_x,end_y)){
    	CreatMap(n);
    	
	}
	CreatCoin(); 
}


//随机数生成函数 
int Random(){
	int a;
    a = rand()%3;
    return a;
}


//画出地图边框 
void CreatFrame(double cx,double cy,double line){
	//SetPenColor("DesertColor_2");
	SetPenColor("ForestColor_2");
	FillBox(cx-Line,cy+Line,(n+2)*line);
	//SetPenColor("DesertColor_1");
	SetPenColor("ForestColor_1");
	FillBox(cx,cy,n*line);
}

//画出一个圆圈 
void CreatPoint(int x,int y,double Diameter){
	
    double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	MovePen(cx+Diameter+x*Diameter,cy-0.5*Diameter-y*Diameter);
	StartFilledRegion(Density);
	    DrawArc(Diameter/3,0,360);
    EndFilledRegion();
}

//初始化终点坐标 
void CreatEnd(){
	end_x = n-1-Random();
    end_y = n-1-Random();
    Map[end_y*n+end_x] = 0;
	
}

//初始化玩家坐标 
void CreatPlayer(){
	start_x = Random();
    start_y = Random();
    Map[start_y*n+start_x] = 0;
    now_x = start_x;
    now_y = start_y;
	
}

//交互式编辑地图 
void ManualEdit(){
	registerMouseEvent(MouseEventProcess);
}

//画出地图 
void DrawMap(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	CreatFrame(cx,cy,Line);

	int i,j; 
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){			
			if(Map[i*n+j]){
				SetPenColor("ForestColor_2");
				FillBox(cx+j*Line,cy-i*Line,Line);
				//SetPenColor("Black");
				//DrawBox(cx+j*Line,cy-i*Line,Line);
			}
		}			
	}
    PrintPlayer(Line);
    PrintEnd(Line);
}

//画出终点 
void PrintEnd(double Diameter){
	SetPenColor("Blue");
	CreatPoint(end_x,end_y,Diameter);
}


//画出玩家 
void PrintPlayer(double Diameter){
    SetPenColor("Violet");
	CreatPoint(now_x,now_y,Diameter);
}

void DrawMap_2(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	CreatFrame_2(cx,cy,Line);

	int i,j; 
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){			
			if(Map[i*n+j]){
				SetPenColor("DesertColor_2");
				FillBox(cx+j*Line,cy-i*Line,Line);
				//SetPenColor("Black");
				//DrawBox(cx+j*Line,cy-i*Line,Line);
			}
		}			
	}
    PrintPlayer(Line);
    PrintEnd(Line);
}


void CreatFrame_2(double cx,double cy,double line){
	
	SetPenColor("DesertColor_2");
	FillBox(cx-Line,cy+Line,(n+2)*line);
	SetPenColor("DesertColor_1");
	
	FillBox(cx,cy,n*line);
}

//交互单人模式 
void GameStatusC(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	HBITMAP background_1 = readBmpImage("0004.bmp");
    drawBmp(background_1,w/2,h/2,w,h,SRCAND);
    FindPath(n,Map,start_x,start_y,end_x,end_y);
	
	
//	if(now_y == end_y&&now_x == end_x){
//		SetPenColor("Green");
//        FillBox(cx-Line,cy+Line,(n+2)*Line);
//        drawBox(0.5*w-1,0.5*h-1,2,2,0,"成功通关!",'C',"Black");
//		return ;
//	}
	DrawMap_2();
	FindNextStep();
	if(coin_existence) PrintCoin();
} 
int maze[40][40];

void CreatMap_2() {

	int x,y;
    // Initialize maze with all walls
    for (y = 0; y < n; y++) {
        for (x = 0; x < n; x++) {
            maze[y][x] = 1;
        }
    }
    
    // Choose a random starting cell
    start_x = rand() % n;
    start_y = rand() % n;
    now_x = start_x;
    now_y = start_y;
    maze[start_y][start_x] = 0;
    
    // Initialize frontier with neighbors of starting cell
    int frontier[n*n][2];
    int num_frontier = 0;
    if (start_x > 0) {
        frontier[num_frontier][0] = start_x - 1;
        frontier[num_frontier][1] = start_y;
        num_frontier++;
    }
    if (start_x < n - 1) {
        frontier[num_frontier][0] = start_x + 1;
        frontier[num_frontier][1] = start_y;
        num_frontier++;
    }
    if (start_y > 0) {
        frontier[num_frontier][0] = start_x;
        frontier[num_frontier][1] = start_y - 1;
        num_frontier++;
    }
    if (start_y < n - 1) {
        frontier[num_frontier][0] = start_x;
        frontier[num_frontier][1] = start_y + 1;
        num_frontier++;
    }
    
    // Loop until there are no more cells in the frontier
    while (num_frontier > 0) {
        // Choose a random cell from the frontier
        int index = rand() % num_frontier;
        int x1 = frontier[index][0];
        int y1 = frontier[index][1];
        
        // Remove cell from frontier
        num_frontier--;
        frontier[index][0] = frontier[num_frontier][0];
        frontier[index][1] = frontier[num_frontier][1];
        
        // Check if cell can be added to the maze
        int num_walls = 0;
        if (x1 > 0 && maze[y1][x1-1] == 0) {
            num_walls++;
        }
        if (x1 < n - 1 && maze[y1][x1+1] == 0) {
            num_walls++;
        }
        if (y1 > 0 && maze[y1-1][x1] == 0) {
            num_walls++;
        }
        if (y1 < n - 1 && maze[y1+1][x1] == 0) {
            num_walls++;
        }
        if (num_walls == 1) {
            maze[y1][x1] = 0;
            if (x1 > 0 && maze[y1][x1-1] == 1) {
                frontier[num_frontier][0] = x1 - 1;
                frontier[num_frontier][1] = y1;
                num_frontier++;
            }
            if (x1 < n - 1 && maze[y1][x1+1] == 1) {
                frontier[num_frontier][0] = x1 + 1;
                frontier[num_frontier][1] = y1;
                num_frontier++;
            }
            if (y1 > 0 && maze[y1-1][x1] == 1) {
                frontier[num_frontier][0] = x1;
                frontier[num_frontier][1] = y1 - 1;
                num_frontier++;
            }
            if (y1 < n - 1 && maze[y1+1][x1] == 1) {
                frontier[num_frontier][0] = x1;
                frontier[num_frontier][1] = y1 + 1;
                num_frontier++;
            }
        }
        
        if(num_frontier == 0){
        	end_x = x1;
        	end_y = y1;
        	maze[y1][x1] = 0;
		} 
    }

    for(y=0;y<n;y++){
        for(x=0;x<n;x++){
            Map[y*n+x] = maze[y][x];
        }
    }

}

void PrintMap_2(){
    srand(time(NULL)); // Seed random number generator
    CreatMap_2();
    DrawMap();
    FindPath(n,Map,start_x,start_y,end_x,end_y);
    CreatCoin();
}

void Visual_Path(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	int count_path;
	for(count_path=1;count_path<=tot;count_path++){
		HBITMAP key  = readBmpImage("0002.bmp");
        drawBmp(key,Path[count_path][0]*Line+cx+0.5*Line,cy-Path[count_path][1]*Line-0.5*Line,Line,Line,SRCAND);
	}
}
//结束界面生成 
void GameEnding(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	
	int score = tot - count_step +100; 
	HBITMAP background = readBmpImage("0009.bmp");
    drawBmp(background,w/2,h/2,w,h,SRCAND);
    count_step = 0; 
    char str[4];
	itoa(score,str,10);
	char str0[20] = "您的得分： ";
    strcat(str0,str);
    
    MovePen (3.0,2.0);
    SetPointSize(45);
    SetPenColor("Red");
    DrawTextString(str0);
}

void GameStatusC1(){
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	HBITMAP background = readBmpImage("0007.bmp");
    drawBmp(background,w/2,h/2,w,h,SRCAND);
    FindPath(n,Map,start_x,start_y,end_x,end_y);
	
//	if(now_y == end_y&&now_x == end_x){
//		SetPenColor("Green");
//        FillBox(cx-Line,cy+Line,(n+2)*Line);
//        drawBox(0.5*w-1,0.5*h-1,2,2,0,"成功通关!",'C',"Black");
//		return ;
//	}

	DrawMap();
	FindNextStep();
	if(coin_existence) PrintCoin();
}
//初始化Map(全部归0)进行编辑前
void InitMap(){
	int i;
	for(i=0;i<32*32;i++){
		Map[i] = 0;
	}
} 

void CreatCoin(){
	int a = (rand()+1)%n;
	coin_x = Path[a][0];
	coin_y = Path[a][1];
    coin_existence = 1;
}

void PrintCoin(){
	HBITMAP coin  = readBmpImage("0002.bmp");
    drawBmp(coin,coin_x*Line+cx+0.5*Line,cy-coin_y*Line-0.5*Line,Line,Line,SRCAND);
}







