//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_SIMPLE_H
#define DAD_N_ME_SIMPLE_H

#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <cmath>
#include <vector>
#include <cmath>
#include <QHash>
#include <cstdlib>
#include <iostream>
#include <QKeyEvent>
#include <QPainter>
#include <utility> // for std::exchange

#include "Player.h"
#include "Common.h"

class Simple {
private:
    const float SPEED = 2;
    float speedX = SPEED; // 当前速度，可以为正或负
    float speedY = std::rand()%1?SPEED:-SPEED;
    Point position;

    bool isHit = false;

    int hit_timer = 0;
    bool FacingRight = true;

    bool isReversed = false; // 速度是否反向

public:
    Simple(float startX = 20, float startY = 200)
            : position{startX, startY} {}

    // 移动构造函数
    Simple(Simple&& other) noexcept{
        *this = std::move(other);
    }

    // 移动赋值运算符
    Simple& operator=(Simple&& other) noexcept {
        if (this != &other) {
            position = other.position;
            isHit = other.isHit;
            hit_timer = other.hit_timer;
            isHit = other.isHit;
            isReversed = other.isReversed;
        }
        return *this;
    }

    void move(QVector<QRect> obstacles,int width,int height) {
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


    Point getPosition() const {
        return position;
    }

    bool GetIsHit(){
        return isHit;
    }

    void Change_IsHit(bool signal){
        isHit = signal;
    }

    void checkHurt(Player& player) {
        float dx = position.x - player.getPosition().x;
        float dy = position.y - player.getPosition().y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (player.GetIsAttack() && dist < 175)
        {
            isHit = true;
        }
    }


    int GetTimer(){
        return hit_timer;
    }

    bool GetFacingRight(){
        return FacingRight;
    }

    void AddTimer(int adder){
        hit_timer += adder;
    }

    void ResetTimer() {
        hit_timer = 0;
    }
    void checkCollision(const QRect& obstacle) {
        QRect playerRect(position.x, position.y, 10, 20);
        if (playerRect.intersects(obstacle)) {
            speedX = -speedX;
            speedY = -speedY;// 反转速度
            //isReversed = !isReversed; // 更新反向状态
        }
    }
};


#endif //DAD_N_ME_SIMPLE_H
