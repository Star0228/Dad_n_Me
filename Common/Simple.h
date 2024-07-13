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

    void move(QVector<QRect> obstacles,int width,int height) ;


    Point getPosition() const ;

    bool GetIsHit();

    void Change_IsHit(bool signal);

    void checkHurt(Player& player) ;


    int GetTimer();

    bool GetFacingRight();

    void AddTimer(int adder);

    void ResetTimer() ;
    void checkCollision(const QRect& obstacle) ;
};


#endif //DAD_N_ME_SIMPLE_H
