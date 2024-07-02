#ifndef _CREATMAP_H_
#define _CREATMAP_H_

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "path.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>
//#include <math.h>

#define Density    1.0
#define Size5      Line*n
#define Line       (6.0/n)
//#define Diameter   Line/2

void DrawBox(double cx,double cy,double line);
void FillBox(double cx,double cy,double line);
void CreatMap();
void CreatFrame(double cx,double cy,double line);
int Random();

void GameStatusC();
void GameStatusC1();
void CreatPoint(int x,int y,double Diameter);
void CreatPlayer();
void CreatEnd();
void ManualEdit();
void DrawMap();
//void MouseEventProcess(int x, int y, int button, int event);
void PrintEnd(double Diameter);
void PrintPlayer(double Diameter);
void PrintMap_2();
void CreatMap_2();
void Visual_Path();
void GameEnding();
void CreatFrame_2(double cx,double cy,double line);
void DrawMap_2();

#endif 
