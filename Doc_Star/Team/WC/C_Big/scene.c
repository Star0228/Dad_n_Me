#include "scene.h"
#include "path.h"
#include "CreatMap.h"

extern int n;
extern int Map[1600];
extern int start_x,start_y,now_x,now_y,end_x,end_y;
extern int next_x,next_y; 
int count_step = 0;
static int isnextstep = 0;
static int iscolor = -1;
static string fcolor;
static int isopen = 0;
static int model = 0;
static int isedit = 0; 
int TipRoad = 0;
int coin_existence = 0;


struct buttonstatus{
	double x,y,width,height; /*各个按钮的位置坐标*/ 
	string color;
}pb[19]={                    /*pb:pozition of button 的缩写*/
    {0.0,8.5,2.0,0.5,"Red"},             /*0号：菜单*/ 
    {0.0,8.0,2.0,0.5,"Black"},           /*1号：保存地图*/
    {0.0,7.5,2.0,0.5,"Black"},           /*2号：打开地图*/
    {0.0,7.0,2.0,0.5,"Black"},           /*3号：随机新建*/
    {13.0,1.0,1.0,0.5,"Black"},          /*4号：返回主界面*/
    {13.0,8.5,1.99,0.5,"Black"},         /*5号：使用说明*/
    {13.0,0.5,1.0,0.5,"Black"},          /*6号：退出程序*/
    {6.68,4.0,1.0,0.5,"Black"},          /*7号：开始游戏*/
    {0.0,7.0,2.0,0.5,"Black"},           /*8号：编辑地图*/
    {1.0,8.5,2.0,0.5,"Blue"},            /*9号：下一步提示*/
	{5.68,4.0,1.0,0.5,"Black"},          /*10号：沙漠古堡*/
	{7.68,4.0,1.0,0.5,"Black"},          /*11号：雨林秘境*/ 
	{13.0,8.0,1.99,0.5,"Black"},         /*12号：Music*/
	{2.0,8.5,2.0,0.5,"Black"},           /*13号：难度选择*/ 
    {2.0,8.0,2.0,0.5,"Black"},           /*14号：简单*/
    {2.0,7.5,2.0,0.5,"Black"},           /*15号：中等*/
    {2.0,7.0,2.0,0.5,"Black"},           /*16号：困难*/
    {3.0,8.5,2.0,0.5,"Blue"},           /*17号：可视化*/
    {5.0,8.5,2.0,0.5,"Blue"},           /*18号：最优路线*/      
};


void Display2(){
	DisplayClear();
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	if(iscolor != -1){
		fcolor = pb[iscolor].color;
		pb[iscolor].color = "Red";
	}
	
	if(isopen)    Gamestatus = sceneB5;
	
	SetPenColor("Blue");
	drawBox(pb[12].x,pb[12].y,pb[12].width,pb[12].height,0,"Music",'C',pb[12].color);
	
	switch(Gamestatus){
		
		/*  场景A:初始界面  */       
        case sceneA1:
        	
			SetPenColor("Blue");
			drawBox(pb[1].x,pb[1].y,pb[1].width,pb[1].height,0,"保存地图 (Ctrl+0)",'C',pb[1].color);
			
			SetPenColor("Blue");
			drawBox(pb[2].x,pb[2].y,pb[2].width,pb[2].height,0,"打开地图 (Ctrl+p)",'C',pb[2].color);
						
			SetPenColor("Blue");
			drawBox(pb[8].x,pb[8].y,pb[8].width,pb[8].height,0,"编辑地图 (Ctrl+k)",'C',pb[8].color);
				
		case sceneA0:
			
			SetPenColor("Blue");
			drawBox(pb[13].x,pb[13].y,pb[13].width,pb[13].height,0,"难度选择",'C',pb[13].color);

            SetPenColor("Blue");
			drawBox(pb[0].x,pb[0].y,pb[0].width,pb[0].height,0,"菜单",'C',"Red");
			
			SetPenColor("Blue");
			drawBox(pb[7].x,pb[7].y,pb[7].width,pb[7].height,0,"开始游戏",'C',pb[7].color);
			
			SetPenColor("Blue");
			drawBox(pb[6].x,pb[6].y,pb[6].width,pb[6].height,0,"退出",'C',pb[6].color);
			
			SetPenColor("Blue");
			drawBox(pb[5].x,pb[5].y,pb[5].width,pb[5].height,0,"使用说明 (Ctrl+j)",'C',pb[5].color);
			
			SetPenColor("Blue");
			MovePen(0,9);
			DrawLine(15,0);
			MovePen(0,8.5);
			DrawLine(15,0);
			
            MovePen(5.5,5);
            SetPointSize(60);
            DrawTextString("迷宫游戏");
            SetPointSize(15);
            
            HBITMAP background  = readBmpImage("0003.bmp");
            drawBmp(background,w/2-0.25,h/2+1.75,w*0.75,h*0.75,SRCAND);
            
			break;									
		
		case sceneB1:
			
		    SetPenColor("Blue");
			drawBox(pb[14].x,pb[14].y,pb[14].width,pb[14].height,0,"简单",'C',pb[14].color);
			
			SetPenColor("Blue");
			drawBox(pb[15].x,pb[15].y,pb[15].width,pb[15].height,0,"中等",'C',pb[15].color);
			
			SetPenColor("Blue");
			drawBox(pb[16].x,pb[16].y,pb[16].width,pb[16].height,0,"困难",'C',pb[16].color);
			
		    break;
		    
		case sceneB2:
		/*  场景B2:使用说明  */
		    SetPenColor("Black");
		    MovePen(1.0,8.0);
		    DrawTextString("使用说明：");
			SetPenColor("Blue");
			drawBox(pb[4].x,pb[4].y,pb[4].width,pb[4].height,0,"返回主界面",'C',pb[4].color);
			break;
			
		case sceneB3:
		/*  场景B3:地图保存  */
		    creatfile(Map);
		    exit(0);
			
		case sceneB4:
			CreatFrame(cx,cy,Line); 
			DrawMap();
			
			SetPenColor("Blue");
			drawBox(pb[4].x,pb[4].y,pb[4].width,pb[4].height,0,"开始游戏",'C',pb[4].color);
		    break;
			
		case sceneC:case sceneC1:
			//Visible();
			if(Gamestatus == sceneC){
			    GameStatusC();
			}else{ 
			    GameStatusC1();
			} 
            	
				
		   if(TipRoad) DrawTipRoad();
		   if(isnextstep){
				FindNextStep();
		        HBITMAP one  = readBmpImage("0002.bmp");
                drawBmp(one,next_x*Line+cx+0.5*Line,cy-next_y*Line-0.5*Line,Line,Line,SRCAND);
			}      
			     
			SetPenColor("Blue");
			drawBox(pb[4].x,pb[4].y,pb[4].width,pb[4].height,0,"返回主界面",'C',pb[4].color);
			char str[4];
			itoa(count_step,str,10);
			char str0[10] = "步数：  ";
			strcat(str0,str);
			 
			drawBox(2.0,h-2.0,1.75,1.25,0,str0,'C',"Black");
			
			SetPenColor("Black");
			SetPointSize(35);
			drawBox(pb[9].x,pb[9].y,pb[9].width,pb[9].height,0,"下一步",'C',pb[9].color);
			
			SetPenColor("Black");
			drawBox(pb[17].x,pb[17].y,pb[17].width,pb[17].height,0,"可视化",'C',pb[17].color);
			
			SetPenColor("Black");
			drawBox(pb[18].x,pb[18].y,pb[18].width,pb[18].height,0,"最优路线",'C',pb[18].color);
			
			SetPointSize(15);
			if(now_x == end_x && now_y == end_y){
				Gamestatus = sceneD;
			}
		    break;
		    
		
	
            
//			SetPenColor("Blue");
//			drawBox(pb[4].x,pb[4].y,pb[4].width,pb[4].height,0,"返回主界面",'C',pb[4].color);
//			char str_s[4];
//			itoa(count_step,str_s,10);
//			char str_s0[10] = "步数：  ";
//			strcat(str_s0,str_s);
//			 
//			drawBox(2.0,h-2.0,1.75,1.25,0,str_s0,'C',"Black");
//			
//			SetPenColor("Black");
//			SetPointSize(35);
//			drawBox(pb[9].x,pb[9].y,pb[9].width,pb[9].height,0,"下一步",'C',pb[9].color);
//			SetPointSize(15);
			
//		    break;			
			
				
		case sceneD:
            GameEnding();
			break;

        case sceneB5:
        	
		    SetPenColor("Blue");
			drawBox(pb[10].x,pb[10].y,pb[10].width,pb[10].height,0,"沙漠古堡",'C',pb[10].color);
			
			SetPenColor("Blue");
			drawBox(pb[11].x,pb[11].y,pb[11].width,pb[11].height,0,"雨林秘境",'C',pb[11].color);
				
            break;
	}
	if(iscolor != -1){
		pb[iscolor].color = fcolor;
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	DisplayClear();
	iscolor = -1;
	
	mouse_x = ScaleXInches(x);           /*单位转化 */
	mouse_y = ScaleYInches(y);
	double w=GetWindowWidth();
	double h=GetWindowHeight();
	
	double cx = 0.5*w-Size5*0.5;
	double cy = 0.5*h+Size5*0.5;
	
	if(inbutton(mouse_x,mouse_y,pb[12].x,pb[12].y,pb[12].width,pb[12].height))
		iscolor = 12;

	switch(Gamestatus){                  /*鼠标操纵界面切换 */
		case sceneA1:                    /*首界面切换到次级界面 */ 
			    
		        if(inbutton(mouse_x,mouse_y,pb[5].x,pb[5].y,pb[5].width,pb[5].height)){
		        	iscolor = 5;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneB2;
		        }
		        if(inbutton(mouse_x,mouse_y,pb[1].x,pb[1].y,pb[1].width,pb[1].height)){
		        	iscolor = 1;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
		    	    Gamestatus = sceneB3;
	    	    }
	    	    if(inbutton(mouse_x,mouse_y,pb[8].x,pb[8].y,pb[8].width,pb[8].height)){
	    	    	iscolor = 8;
	    	    	
	    	    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
	    	    	isedit = 1;
		    	    Gamestatus = sceneB1;
	    	    }
				if(inbutton(mouse_x,mouse_y,pb[2].x,pb[2].y,pb[2].width,pb[2].height)){
					iscolor = 2;
					
					if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
					char* file_path = get_file_path();
					/*传到地图中*/
					FILE *file;
					file = fopen(file_path, "r");
					
					fscanf(file, "%d", &now_x);
				    fscanf(file, "%d", &now_y);
			        fscanf(file, "%d", &end_x);
			        fscanf(file, "%d", &end_y);
			        //fscanf(file, "%d", &key_existence);
					fscanf(file, "%d", &n);
					
					int i;
					for (i = 0; i < n*n; i++) {
                        fscanf(file, "%d", &Map[i]);
                    }
                    if(file != NULL)    isopen = 1;
                    free(file_path);
                    fclose(file);
	    	    }
				if(inbutton(mouse_x,mouse_y,pb[7].x,pb[7].y,pb[7].width,pb[7].height)){
					iscolor = 7;
					
					if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneC;
		        }   	
		        
		        
	                  /*关闭菜单 */
	        if(!(inbutton(mouse_x,mouse_y,pb[8].x,pb[8].y,pb[8].width,pb[8].height*4))){
			    Gamestatus = sceneA0;
		    }
		    break;
		    
		case sceneB2:         /*从使用说明返回首界面 */ 
			
			    if(inbutton(mouse_x,mouse_y,pb[4].x,pb[4].y,pb[4].width,pb[4].height)){
			    	iscolor = 4;
			    	
			    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneA0;
		        }
		    break;
		    
		case sceneA0:
			    if(inbutton(mouse_x,mouse_y,pb[0].x,pb[0].y,pb[0].width,pb[0].height)){
			        Gamestatus = sceneA1;
		        }		        
		        
		        if(inbutton(mouse_x,mouse_y,pb[5].x,pb[5].y,pb[5].width,pb[5].height)){
		        	iscolor = 5;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneB2;
		        }
		        if(inbutton(mouse_x,mouse_y,pb[6].x,pb[6].y,pb[6].width,pb[6].height)){
		        	iscolor = 6;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        exit(0);
		        }
		        if(inbutton(mouse_x,mouse_y,pb[7].x,pb[7].y,pb[7].width,pb[7].height)){
		        	iscolor = 7;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneB1;
		        }
		        if(inbutton(mouse_x,mouse_y,pb[13].x,pb[13].y,pb[13].width,pb[13].height)){
		        	iscolor = 13;
		        	
		        	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneB1;
		        }
		    break;
		
		case sceneB4:
			if(event==BUTTON_DOWN){
   		        if (button == LEFT_BUTTON){
                    Map[(int)(((mouse_x-cx)/Line)+(floor((cy-mouse_y)/Line))*n)] = 1;
   		        }else if (button == RIGHT_BUTTON){
		            Map[(int)(((mouse_x-cx)/Line)+(floor((cy-mouse_y)/Line))*n)] = 0;
   		        }                        /*编辑地图*/
				
				
				if(inbutton(mouse_x,mouse_y,pb[4].x,pb[4].y,pb[4].width,pb[4].height)){
				    isedit = 0;	
			        Gamestatus = sceneC;
		        }                        /*开始游戏*/ 
			}
			
			if(inbutton(mouse_x,mouse_y,pb[4].x,pb[4].y,pb[4].width,pb[4].height)){	
			        iscolor = 4;
		    } 
			break;
			
		case sceneC:	case sceneC1:

			    if(inbutton(mouse_x,mouse_y,pb[4].x,pb[4].y,pb[4].width,pb[4].height)){
			    	iscolor = 4;
			    	
			    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			        Gamestatus = sceneA0;
		        }
		        if(inbutton(mouse_x,mouse_y,pb[9].x,pb[9].y,pb[9].width,pb[9].height)){
		        	iscolor = 9;
		        	
			    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
		        	isnextstep = 1;
		        }
		        if(inbutton(mouse_x,mouse_y,pb[17].x,pb[17].y,pb[17].width,pb[17].height)){
		        	iscolor = 17;
		        	
			    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			    	else {
			    		startTimer(3,200);
					}
			    	
		        }
		        if(inbutton(mouse_x,mouse_y,pb[18].x,pb[18].y,pb[18].width,pb[18].height)){
		        	iscolor = 18;
		        	
			    	if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			    	else {
			    		//startTimer(3,200); 
			    		//Display2();
			    		//DrawTipRoad();
			    		TipRoad = 1;
					}
			    	
		        }
		    break;
		
		case sceneB1:
		    if(inbutton(mouse_x,mouse_y,pb[14].x,pb[14].y,pb[14].width,pb[14].height)){
		        iscolor = 14;
		        	
		        if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
		        n = 16;
			    if(isedit)      Gamestatus = sceneB4;
			    else            Gamestatus = sceneB5;
		    }
		    if(inbutton(mouse_x,mouse_y,pb[15].x,pb[15].y,pb[15].width,pb[15].height)){
		        iscolor = 15;
		        	
		        if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
		        n = 24;
			    if(isedit)      Gamestatus = sceneB4;
			    else            Gamestatus = sceneB5;
		    }
		    if(inbutton(mouse_x,mouse_y,pb[16].x,pb[16].y,pb[16].width,pb[16].height)){
		        iscolor = 16;
		        	
		        if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
		        n = 32;
			    if(isedit)      Gamestatus = sceneB4;
			    else            Gamestatus = sceneB5;
		    }
		    break;
			
		case sceneB5:
			if(inbutton(mouse_x,mouse_y,pb[10].x,pb[10].y,pb[10].width,pb[10].height)){//创建沙漠古堡 
		        iscolor = 10;
		        	
		        if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			    Gamestatus = sceneC;
                count_step = 0;
			    GameStatusC();
			    if(!isopen)      PrintMap_2();
			    isopen = 0;
		    }
		    if(inbutton(mouse_x,mouse_y,pb[11].x,pb[11].y,pb[11].width,pb[11].height)){//创建雨林秘境 
		        iscolor = 11;
		        	
		        if(event != BUTTON_DOWN || button != LEFT_BUTTON)   break;
			    Gamestatus = sceneC1;
			    count_step = 0;
                CreatPlayer();
                CreatEnd();
	            if(!isopen)       CreatMap();
	            isopen = 0;
		    }
		    break;
		 
	}
   

	Display2();
}

void creatfile(int a[]){
    FILE *file;
    int i = 1;
    char filename[20];

    // 循环检查文件是否存在，直到找到一个没用过的文件名
    while (1) {
        sprintf(filename, "地图%d.txt", i);
        file = fopen(filename, "r");
        if (file == NULL) {
            break;  // 文件不存在，退出循环
        }
        fclose(file);
        i++;
    }

    // 打开文件以进行写入
    file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }
    
    fprintf(file, "%d ", now_x);
    fprintf(file, "%d ", now_y);
    fprintf(file, "%d ", end_x);
    fprintf(file, "%d ", end_y);
    //fprintf(file, "%d ", key_existence);
    fprintf(file, "%d ", n);

    // 写入文本到文件
    for (i = 0; i < n*n; i++) {
        fprintf(file, "%d ", a[i]);
    }

    // 关闭文件
    fclose(file);
}

int inbutton(double mouse_x,double mouse_y,double x,double y,double width,double height){
	if(mouse_x>x && mouse_x<(x + width) && mouse_y>y && mouse_y<(y + height)){
		return 1;
	}else{
		return 0;
	}
}

char* get_file_path(){        /*调用文件选择对话框*/ 
    OPENFILENAME ofn;
    char file_name[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = file_name;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "选择文件";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        return _strdup(file_name);
    }

    return NULL;
}

void KeyboardEventProcess(int key,int event){
	
	
	if(Gamestatus == sceneC){
		if(!event)    isnextstep = 0;
	}
	
	
	if(Gamestatus != sceneA0 && Gamestatus != sceneA1) return;
	if(key == VK_CONTROL){
		isCtrl = !event;			
	}
	if(isCtrl){
		switch(key){
			
			case 'o':case 'O':
				Gamestatus = sceneB3;
				break;
				
			case 'j':case 'J':
				Gamestatus = sceneB2;
				break;
				
			
			case 'k':case 'K':
				Gamestatus = sceneB1;
				isedit = 1;
				break;
				
			case 'p':case 'P':
			{
				char* file_path = get_file_path();
			    /*传到地图中*/
			    FILE *file;
			    file = fopen(file_path, "r");
			    
			    fscanf(file, "%d", &now_x);
				fscanf(file, "%d", &now_y);
			    fscanf(file, "%d", &end_x);
			    fscanf(file, "%d", &end_y);
			    //fscanf(file, "%d", &key_existence);
			    fscanf(file, "%d", &n);
			    
			    
			    int i;
			    for (i = 0; i < n*n; i++) {
                    fscanf(file, "%d", &Map[i]);
                }
                if(file != NULL)    isopen = 1;
                free(file_path);
                fclose(file);
				break;
			}
			
		}	
	} 
	Display2();
	return;
}

void CharEventProcess(char key){
	if(Gamestatus != sceneC && Gamestatus != sceneC1)   return;
	if(key=='a' || key=='A'){
		int fx=now_x-1,fy=now_y;
		if(fx<0 || Map[fx+fy*n]==1) return ;
		else{
			now_x=fx;
			now_y=fy;
			count_step +=1;
		}
	}
	else if(key=='w' || key=='W'){
		int fx=now_x,fy=now_y-1;
		if(fy<0 || Map[fx+fy*n]==1) return ;
		else{
			now_x=fx;
			now_y=fy;
			count_step +=1;
		}
	}
	else if(key=='d' || key=='D'){
		int fx=now_x+1,fy=now_y;
		if(fx>=n || Map[fx+fy*n]==1) return ;
		else{
			now_x=fx;
			now_y=fy;
			count_step +=1;
		}
	} 
	else if(key=='s' || key=='S'){
		int fx=now_x,fy=now_y+1;
		if(fy>=n || Map[fx+fy*n]==1) return ;
		else{
			now_x=fx;
			now_y=fy;
			count_step +=1;
		}
	}
	FindNextStep(); 
	Display2();
	 
	return ;
}

