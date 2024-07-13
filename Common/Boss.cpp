//
// Created by 16579 on 2024/7/9.
//

#include "Boss.h"

void Boss::reset(){
    position.x = 1100;
    position.y = 300;
    hit_timer = 0;
    isHit = false;
}


void Boss::move(Player& player)
{
    float dx = position.x - player.getPosition().x;
    float dy = position.y - player.getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (dx < 10)
    {
        FacingRight = true;
    }else
    {
        FacingRight = false;
    }

    if (dist > 100)
    {
        position.x -= SPEED * dx / dist;
        position.y -= SPEED * dy / dist;
    }
}


void Boss::attack(Background& background) {
    if (background.patience_Boss >= 0.25)
    {
        isAttacking = true;
    }

}

void Boss::checkHurt(Player& player,Background& background)
{
    float dx = position.x - player.getPosition().x;
    float dy = position.y - player.getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (player.GetIsAttack() && dist < 300)
    {
        background.health_Boss -= 0.001;
        isHit = true;
    }
}

void Boss::refillPatience(Background& background)
{
    if (background.patience_Boss < 1.0)
    {
        background.patience_Boss += 0.0005;
    }
}

Point Boss::Getposition(){
    return position;
}

bool Boss::GetIsHit(){
    return isHit;
}

bool Boss::getIsAttack(){
    return isAttacking;
}

void Boss::Change_IsHit(bool signal){
    isHit = signal;
}

int Boss::GetTimer(){
    return hit_timer;
}

bool Boss::GetFacingRight(){
    return FacingRight;
}

void Boss::AddTimer(int adder){
    hit_timer += adder;
}

void Boss::ResetTimer(){
    hit_timer = 0;
}