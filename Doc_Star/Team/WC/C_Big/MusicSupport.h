#ifndef MUSIC_H_
#define MUSIC_H_

#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include"extgraph.h"
#include"simpio.h"
#include"random.h"
#include"strlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <math.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <imgui.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")


/*打开音乐*/ 
void PlayMusic();

/*关闭音乐*/ 
void CloseMusic();

/*功能：获取音乐状态。  0---音乐未播放   1---音乐正在播放*/ 
int GetMusicState();



#endif 

