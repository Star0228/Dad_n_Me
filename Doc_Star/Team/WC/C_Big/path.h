#ifdef PATH_H
#define PATH_H

#define TIMER_BLINK001 3
const int mseconds001 = 500;
#define MAXM  10000

int FindPath(int n,int Map[],int StartX,int StartY,int EndX,int EndY);
int FindNextStep();
void DrawNextStep();
void DrawTipRoad();//画出最优路线 
void TipTimerEvent(int TimeID);//可视化函数  ，   可视化完成一次后  ，使用startTimer()重新恢复 
void DrawTip(int i);//画出最优路线 
#endif
