//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_PLAYER_H
#define DAD_N_ME_PLAYER_H

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

#include "Common.h"
#include "Background.h"


class Player {
private:
    Point position;
    float speed;
    bool FacingRight;
    int hit_timer = 0;
    QRect rect;
    bool isAttacking = false;

public:
    bool ok2Attack = true;

    Player(float startX = 640, float startY = 360,  float speed = 12)
            : position{startX, startY}, speed(speed), FacingRight(true) {
        rect = QRect(startX, startY, 121, 130);
    }



    bool checkCollision(const QRect& newRect, const QVector<QRect>& obstacles) {
        for (const QRect& obstacle : obstacles) {
            if (newRect.intersects(obstacle)) {
                return true;
            }
        }
        return false;
    }

    void checkHurt(Background& background,float x,float y,bool hit) {
        float dx = position.x - x;
        float dy = position.y - y;
        float dist = std::sqrt(dx*dx + dy*dy);
        if (dist < 150 && hit) {
            background.health -= 0.01;
            //std::cout<<background.health<<std::endl;
        }
    }

    void moveLeft(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(-speed, 0);
        if (!checkCollision(newRect, obstacles)) {
            position.x -= speed;
            rect.moveTo(position.x, position.y);
        }
        FacingRight = false;
    }

    void moveRight(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(speed, 0);
        if (!checkCollision(newRect, obstacles)) {
            position.x += speed;
            rect.moveTo(position.x, position.y);
        }
        FacingRight = true;
    }

    void moveUp(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(0, -speed);
        if (!checkCollision(newRect, obstacles)) {
            position.y -= speed;
            rect.moveTo(position.x, position.y);
        }
    }

    void moveDown(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(0, speed);
        if (!checkCollision(newRect, obstacles)) {
            position.y += speed;
            rect.moveTo(position.x, position.y);
        }
    }

    void attack(Background& background) {
        if (background.patience >= 0.25)
        {
            background.patience -= 0.25;
            isAttacking = true;
            hit_timer = 0;
        }
    }

    void refillPatience(Background& background)
    {
        if (background.patience < 1.0)
        {
            background.patience += 0.0005;
        }
    }


    Point getPosition() const {
        return position;
    }
    int GetHitTimer()const{
        return hit_timer;
    }

    void AddTimer(int adder){
        hit_timer += adder;
    }

    void ResetTimer(){
        hit_timer = 0;
    }

    bool GetIsAttack(){
        return isAttacking;
    }

    void Change_Isattack(bool signal){
        isAttacking = signal;
    }

    bool GetFacingRight(){
        return FacingRight;
    }
};


#endif //DAD_N_ME_PLAYER_H
