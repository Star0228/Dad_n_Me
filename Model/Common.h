//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_COMMON_H
#define DAD_N_ME_COMMON_H

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

#include "../View/Animation.h"


class Common {
private:
    const float SPEED = 2;
    Point position{};

    bool isHit = false;

    int hit_timer = 0;
    bool FacingRight = true;

public:
    Common(float startX, float startY)
            : position{startX, startY} {}

    // 移动构造函数
    Common(Common&& other) noexcept{
        *this = std::move(other);
    }

    // 移动赋值运算符
    Common& operator=(Common&& other) noexcept {
        if (this != &other) {
            position = other.position;
            isHit = other.isHit;
            hit_timer = other.hit_timer;
            isHit = other.isHit;
        }
        return *this;
    }

    void move() {
        position.x += SPEED;
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

    int GetTimer(){
        return hit_timer;
    }

    bool GetFacingRight(){
        return FacingRight;
    }

    void AddTimer(int adder){
        hit_timer += adder;
    }

    void ResetTimer(){
        hit_timer = 0;
    }
};


#endif //DAD_N_ME_COMMON_H
