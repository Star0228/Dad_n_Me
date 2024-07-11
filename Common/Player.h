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



class Player {
private:
    Point position;
    float speed;
    bool FacingRight;
    int hit_timer = 0;
    QRect rect;
    bool isAttacking = false;
public:

    Player(float startX = 640, float startY = 360,  float speed = 12)
            : position{startX, startY}, speed(speed), FacingRight(true) {
        rect = QRect(startX, startY, 50, 100);
    }



    bool checkCollision(const QRect& newRect, const QVector<QRect>& obstacles) {
        for (const QRect& obstacle : obstacles) {
            std::cout << obstacle.left() << std::endl;
            if (newRect.intersects(obstacle)) {
                std::cout << "bitch" << std::endl;
                return true;
            }
        }
        return false;
    }

    void moveLeft(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(-speed, 0);
        std::cout << "bitch" << std::endl;
        std::cout << rect.height() << std::endl;
        // std::cout << rect.left() << std::endl;
        for (QRect ob : obstacles) std::cout << ob.left() << std::endl;
        // if (checkCollision(newRect, obstacles)) std::cout << "FUCK!" << std::endl;
        if (!checkCollision(newRect, obstacles)) {
            position.x -= speed;
            rect.moveTo(position.x, position.y);
            //std::cout << "FUCK!" << std::endl;
        }
        FacingRight = false;
    }

    void moveRight(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(speed, 0);
        if (!checkCollision(newRect, obstacles)) {
            position.x += speed;
            rect.moveTo(position.x, position.y);
            //std::cout << "FUCK!" << std::endl;
        }
        FacingRight = true;
    }

    void moveUp(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(0, -speed);
        if (!checkCollision(newRect, obstacles)) {
            position.y -= speed;
            rect.moveTo(position.x, position.y);
            //std::cout << "FUCK!" << std::endl;
        }
    }

    void moveDown(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(0, speed);
        if (!checkCollision(newRect, obstacles)) {
            position.y += speed;
            rect.moveTo(position.x, position.y);
            //std::cout << "FUCK!" << std::endl;
        }
    }
    void attack() {
        isAttacking = true;
        hit_timer = 0;
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
