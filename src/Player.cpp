//
// Created by 16579 on 2024/7/3.
//

#include "Player.h"
#include <graphics.h>
#include <string>



void Player::show(int& frame) {
    IMAGE img_player;
    if(state == walk_r){
        std::string path = "../resource/Player/walk_r/" + std::to_string((frame)%11+1) + ".png";
        loadimage(&img_player,path.c_str());
        putimage(0,0,&img_player);
    }

}
