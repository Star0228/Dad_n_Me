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
public:
    Animation* anim;
    Point position;
    float speed;
    bool facingRight;
    int timer = 0;

    int idxRunFrame = 0;
    int idxAttackFrame = 0;
    QRect rect;
    bool isAttacking = false;
    int attackFrameCounter = 0;

    Player(float startX, float startY, Animation* playerAnim, int speed)
            : position{startX, startY}, anim(playerAnim), speed(speed), facingRight(true) {
        // rect = QRect(position.x, position.y, anim->getFrameWidth(), anim->getFrameHeight());
        rect = QRect(position.x, position.y, 100, 300);
    }


    bool checkCollision(const QRect& newRect, const QVector<QRect>& obstacles) {
        for (const QRect& obstacle : obstacles) {
            if (newRect.intersects(obstacle)) {
                return true;
            }
        }
        return false;
    }

    void moveLeft(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(-speed, 0);
        if (checkCollision(newRect, obstacles)) std::cout << "FUCK!" << std::endl;
        if (!checkCollision(newRect, obstacles)) {
            position.x -= speed;
            rect.moveTo(position.x, position.y);
        }
    }

    void moveRight(const QVector<QRect>& obstacles) {
        QRect newRect = rect.translated(speed, 0);
        if (!checkCollision(newRect, obstacles)) {
            position.x += speed;
            rect.moveTo(position.x, position.y);
        }
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
    void attack() {
        isAttacking = true;
        timer = 0;
        idxAttackFrame = 0;
        attackFrameCounter = 21;
    }

    void draw(QPainter& painter, int delta) {
        timer += delta;

        if (attackFrameCounter == 20)
        {
            isAttacking = false;
        }

        //首先判定是否正在攻击
        if (attackFrameCounter > 0)
        {
            if (timer >= anim->getInterval()) {
                idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
                timer = 0;
                attackFrameCounter --;
            }
            anim->displayAttack(painter, position.x, position.y - 70, timer, idxAttackFrame, facingRight); // 调整了y方向参数来保证图片显示位置的一致性
        }
        else
        {
            if (timer >= anim->getInterval()) {
                idxRunFrame = (idxRunFrame + 1) % anim->getRunFrameCount();
                timer = 0;
            }
            anim->displayRun(painter, position.x, position.y, timer, idxRunFrame, facingRight);
        }
    }

    Point getPosition() const {
        return position;
    }
};


#endif //DAD_N_ME_PLAYER_H
