
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
    bool isMove = false;

public:
    bool ok2Attack = true;

    Player(float startX = 640, float startY = 360,  float speed = 12)
            : position{startX, startY}, speed(speed), FacingRight(true) {
        rect = QRect(startX, startY, 121, 130);
    }

    void reset();

    bool checkCollision(const QRect& newRect, const QVector<QRect>& obstacles);

    void checkHurt(Background& background,float x,float y,bool hit);

    void moveLeft(const QVector<QRect>& obstacles) ;

    void moveRight(const QVector<QRect>& obstacles);

    void moveUp(const QVector<QRect>& obstacles) ;

    void moveDown(const QVector<QRect>& obstacles) ;

    void attack(Background& background) ;

    void refillPatience(Background& background);


    Point getPosition() const ;
    int GetHitTimer()const;
    bool getIsMove();

    void setIsMove(bool signal);

    void AddTimer(int adder);

    void ResetTimer();

    bool GetIsAttack();

    void Change_Isattack(bool signal);

    bool GetFacingRight();
};


#endif //DAD_N_ME_PLAYER_H
