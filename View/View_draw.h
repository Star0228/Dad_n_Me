//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_VIEW_DRAW_H
#define DAD_N_ME_VIEW_DRAW_H

#include "../Common/Player.h"
#include "../Common/Simple.h"
#include "../Common/Boss.h"

#include "../Common/Animation.h"

const int IMG_INTERVAL = 30;


class View_draw {
private:
    Animation* anim_Common_run;
    Animation* anim_Common_hit;
    Animation* anim_Boss_run;
    Animation* anim_Boss_hit;
    Animation* anim_Boss_attack;
    Animation* anim_Player_walk;
    Animation* anim_Player_run;
    Animation* anim_Player_stand;
    Animation* anim_Player_hit;
    Animation* anim_Player_attack;
    int Idx_Player_attack = 0; // frame id
    int Idx_Player_run = 0;
    int Idx_Player_stand = 0;
    int Idx_Boss_Run = 0;
    int Idx_Boss_Hit = 0;
    int Idx_Boss_Attack = 0;
    int Idx_Common_Run[1000] = {0};
    int Idx_Common_Hit[1000] = {0};


public:
    void Reset_idx_pl_atk();

    int* Get_Idx_Common_Hit(); //小怪需要返回数组指针

    Animation* Get_anim_Common_hit();
    View_draw(){
        anim_Common_run = new Animation("../resource/Enemy_common/run/%1.png", 8, IMG_INTERVAL);
        anim_Common_hit = new Animation("../resource/Enemy_common/is_hit/hit_%1.png", 15, IMG_INTERVAL);

        anim_Boss_run = new Animation("../resource/Enemy_boss/run/%1.png", 8,  IMG_INTERVAL);
        anim_Boss_hit = new Animation("../resource/Enemy_boss/is_hit/%1.png", 14,  IMG_INTERVAL);
        anim_Boss_attack = new Animation("../resource/Enemy_boss/attack/%1.png", 14,  IMG_INTERVAL);

        anim_Player_run = new Animation("../resource/Player/run/%1.png",6, IMG_INTERVAL);
        anim_Player_walk = new Animation("../resource/Player/walk/%1.png",11, IMG_INTERVAL);
        anim_Player_stand = new Animation("../resource/Player/stand/%1.png",11, IMG_INTERVAL);
        anim_Player_attack = new Animation("../resource/Player/attack/%1.png",22, IMG_INTERVAL);

    }
    //player
    void draw(Player& player,QPainter& painter, int delta);
    //simple
    void draw(int bondNum, Simple& simple, QPainter& painter, int delta, int playerSignal);
    //boss
    void draw(Boss& boss,Player& player,Background& background,QPainter& painter, int delta);

//    void draw(const Background bg,QPainter& painter, int delta);

};


#endif //DAD_N_ME_VIEW_DRAW_H
