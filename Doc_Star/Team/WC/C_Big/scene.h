#ifndef HEADER_FILE_NAME_H
#define HEADER_FILE_NAME_H

#include <windows.h>
#include <winuser.h>
#include "CreatMap.h" 
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include "CreatMap.h"


static double mouse_x,mouse_y;

typedef enum {
	sceneA0,       /*  场景A0:初始界面  无菜单*/
	sceneA1,       /*  场景A1:初始界面 有菜单 */
	sceneB1,       /*  场景B1:难度选择 */
	sceneB2,       /*  场景B2:使用说明  */
	sceneB3,       /*  场景B3:保存地图  */
	sceneB4,       /*场景B4：交互编辑地图*/
	sceneB5,       /*场景B5：模式选择*/
	sceneC,        /*场景C：沙漠古堡*/
	sceneC1,      /*场景C1：雨林秘境*/
	sceneD         /*场景D：结束游戏*/
} gamestatus;

static int Gamestatus = 0;
static int isCtrl= 0;
void MouseEventProcess(int x, int y, int button, int event);
void KeyboardEventProcess(int key,int event);
void CharEventProcess(char key);
void Display2();
void creatfile(int a[]);
int inbutton(double mouse_x,double mouse_y,double x,double y,double width,double height);
char* get_file_path(void);

#endif
