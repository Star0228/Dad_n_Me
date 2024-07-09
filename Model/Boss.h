//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_BOSS_H
#define DAD_N_ME_BOSS_H

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
#include "Player.h"


class Boss
{
private:
    const float SPEED = 1;
    Animation* anim;
    Point position{};

    int currentBlood = 100;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;
    int idxAttackFrame = 0;

    bool facingRight = true;

    bool isHit = false;
    int hitFrameCount = 0;

public:
    Boss(Animation* animBoss)
            : anim(animBoss)
    {
        position.x=1100;
        position.y=300;
    }

    // 实现移动构造函数和移动赋值运算符
    Boss(Boss&& other) noexcept
            : anim(std::exchange(other.anim, nullptr)),
              position(other.position),
              currentBlood(other.currentBlood),
              timer(other.timer),
              idxRunFrame(other.idxRunFrame),
              idxHitFrame(other.idxHitFrame),
              idxAttackFrame(other.idxAttackFrame)
    {}

    // Move assignment operator
    Boss& operator=(Boss&& other) noexcept {
        if (this != &other) {
            anim = std::exchange(other.anim, nullptr);
            position = other.position;
            currentBlood = other.currentBlood;
            timer = other.timer;
            idxRunFrame = other.idxRunFrame;
            idxHitFrame = other.idxHitFrame;
            idxAttackFrame = other.idxAttackFrame;
            // Additional members to move if needed
        }
        return *this;
    }

    void move(Player* player)
    {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dx < 0)
        {
            facingRight = true;
        }else
        {
            facingRight = false;
        }
        if (dist < 120)
        {
            facingRight = true;
            return;
        }

        position.x -= SPEED * dx / dist;
        position.y -= SPEED * dy / dist;
    }

    void checkHurt(Player* player)
    {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (player->isAttacking && dist < 300)
        {
            currentBlood -= 10;
            isHit = true;
            hitFrameCount = 14;
        }
    }

    void draw(QPainter& painter, int delta, Player* player)
    {
        // 计算boss和player的距离
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (hitFrameCount == 0)
        {
            isHit = false;
        }

        // 首先判断boss是否收到攻击
        timer += delta;
        if (isHit == true && hitFrameCount > 0)
        {
            if (timer >= anim->getInterval()) {
                idxHitFrame = (idxHitFrame + 1) % anim->getHitFrameCount();
                timer = 0;
                hitFrameCount --;
            }
            anim->displayHit(painter, position.x, position.y - 20, timer, idxHitFrame, facingRight);
        }
        else if (dist < 120)
        {
            if (timer >= anim->getInterval()) {
                idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
                timer = 0;
            }
            anim->displayAttack(painter, position.x, position.y, timer, idxAttackFrame, facingRight);
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
};





#endif //DAD_N_ME_BOSS_H
