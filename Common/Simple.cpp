//
// Created by 16579 on 2024/7/9.
//

#include "Simple.h"

void Simple::move(QVector<QRect> obstacles,int width,int height) {
    if(position.y >height-70||position.y < 250){
        speedY = -speedY;
    }
    if(position.x <0 ||position.x>width-80){
        speedX = -speedX;
    }
    for(auto it:obstacles){
        checkCollision(it);
    }

    position.y +=speedY;
    position.x += speedX;
}


Point Simple::getPosition() const {
    return position;
}

bool Simple::GetIsHit(){
    return isHit;
}

void Simple::Change_IsHit(bool signal){
    isHit = signal;
}

void Simple::checkHurt(Player& player) {
    float dx = position.x - player.getPosition().x;
    float dy = position.y - player.getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (player.GetIsAttack() && dist < 175)
    {
        isHit = true;
    }
}


int Simple::GetTimer(){
    return hit_timer;
}

bool Simple::GetFacingRight(){
    return FacingRight;
}

void Simple::AddTimer(int adder){
    hit_timer += adder;
}

void Simple::ResetTimer() {
    hit_timer = 0;
}
void Simple::checkCollision(const QRect& obstacle) {
    QRect playerRect(position.x, position.y, 10, 20);
    if (playerRect.intersects(obstacle)) {
        speedX = -speedX;
        speedY = -speedY;// 反转速度
        //isReversed = !isReversed; // 更新反向状态
    }
}