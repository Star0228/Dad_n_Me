//
// Created by 16579 on 2024/7/9.
//

#include "Player.h"
void Player::reset(){
    position.x = 640;
    position.y = 360;
    hit_timer = 0;
}

bool Player::checkCollision(const QRect& newRect, const QVector<QRect>& obstacles) {
    for (const QRect& obstacle : obstacles) {
        if (newRect.intersects(obstacle)) {
            return true;
        }
    }
    return false;
}

void Player::checkHurt(Background& background,float x,float y,bool hit) {
    float dx = position.x - x;
    float dy = position.y - y;
    float dist = std::sqrt(dx*dx + dy*dy);
    if (dist < 120 && hit && background.getBossHealth()>0) {
        background.health_Player -= 0.005;
        background.patience_Boss -= 0.02;
        //std::cout<<background.health_Player<<std::endl;
    }
}

void Player::moveLeft(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(-speed, 0);
    if (!checkCollision(newRect, obstacles)) {
        position.x -= speed;
        rect.moveTo(position.x, position.y);
    }
    FacingRight = false;
}

void Player::moveRight(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(speed, 0);
    if (!checkCollision(newRect, obstacles)) {
        position.x += speed;
        rect.moveTo(position.x, position.y);
    }
    FacingRight = true;
}

void Player::moveUp(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(0, -speed);
    if (!checkCollision(newRect, obstacles)) {
        position.y -= speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::moveDown(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(0, speed);
    if (!checkCollision(newRect, obstacles)) {
        position.y += speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::attack(Background& background) {
    if (background.patience_Player >= 0.25)
    {
        background.patience_Player -= 0.25;
        isAttacking = true;
        hit_timer = 0;
    }
}

void Player::refillPatience(Background& background)
{
    if (background.patience_Player < 1.0)
    {
        background.patience_Player += 0.0005;
    }
}


Point Player::getPosition() const {
    return position;
}
int Player::GetHitTimer()const{
    return hit_timer;
}

bool Player::getIsMove(){
    return isMove;
}

void Player::setIsMove(bool signal){
    isMove = signal;
}

void Player::AddTimer(int adder){
    hit_timer += adder;
}

void Player::ResetTimer(){
    hit_timer = 0;
}

bool Player::GetIsAttack(){
    return isAttacking;
}

void Player::Change_Isattack(bool signal){
    isAttacking = signal;
}

bool Player::GetFacingRight(){
    return FacingRight;
}