//
// Created by 16579 on 2024/7/2.
//
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <string>
#include <iostream>
#include "include/Player.h"





enum game_state{
    running = 1,
    stop = 0
};
int main()
{

#pragma region Variant

    const int Frequency = 30;
    const DWORD frequency_tick = 1000/Frequency;
    game_state State = running;
    ExMessage msg;
    DWORD start_time,end_time,delta_time;
    static int frame = 0;
    Player player;
    IMAGE bg_1;

#pragma endregion


#pragma region logic function

#pragma endregion

#pragma region paint

    initgraph(600, 600);
    BeginBatchDraw();

    while (State == running){
        start_time = GetTickCount();

//        while(peekmessage(&msg)){
//
//        }

        loadimage(&bg_1,"../resource/background/house_brown.png");

        cleardevice();
        player.show(frame);
        putimage(200,200,&bg_1);
        frame++;
        FlushBatchDraw();


        end_time = GetTickCount();
        delta_time = end_time - start_time;
        if(delta_time < frequency_tick){
            Sleep(frequency_tick - delta_time);
        }
    }
    EndBatchDraw();

#pragma endregion
    return 0;
}