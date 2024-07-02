#include "CreatMap.h"
#include "scene.h" 
#include "path.h"
#include "ImageSupport.h"
#define   TIMER_BLINK001     3 
#define SRCAND (DWORD)0x008800C6
extern int n;
extern int Map[1600];
void TipTimerEvent(int TimeID);
void Main(){
    SetWindowTitle("√‘π¨”Œœ∑"); 
    InitGraphics();     
   // HBITMAP one  = readBmpImage("0488.bmp");
    //drawBmp(one,2.0,2.0,2.0,2.0,SRCAND);
    registerMouseEvent(MouseEventProcess);
    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
	registerTimerEvent(TipTimerEvent); 
    //registerTimeEvent(TIMER_BLINK001);
    //PlaySound(TEXT("60474460.wav"),NULL,SND_FILENAME | SND_ASYNC|SND_LOOP |SND_NODEFAULT);
} 



