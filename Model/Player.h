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

#include "../View/Animation.h"



class Player {
private:
    Point position;
    float speed;
    bool FacingRight;
    int hit_timer = 0;
    bool isAttacking = false;
public:

    Player(float startX = 640, float startY = 360,  float speed = 12)
            : position{startX, startY}, speed(speed), FacingRight(true) {}

    void moveLeft() {
        position.x -= speed;
        FacingRight = false;
    }

    void moveRight() {
        position.x += speed;
        FacingRight = true;
    }

    void moveUp() {
        position.y -= speed;
    }

    void moveDown() {
        position.y += speed;
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
