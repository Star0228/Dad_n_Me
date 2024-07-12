#ifndef DAD_N_ME_BOSS_H
#define DAD_N_ME_BOSS_H

#include <QWidget>
#include <QDebug>
#include <cmath>
#include <vector>
#include <cmath>
#include <iostream>

#include "../View/Animation.h"
#include "Player.h"


class Boss
{
private:
    const int SPEED = 1;
    Point position{};

    int currentBlood = 100;

    int hit_timer = 0;
    bool FacingRight = true;
    bool isHit = false;

public:
    Boss(float startx = 1100,float starty =300){
        position.x = startx;
        position.y = starty;
    }

    // 实现移动构造函数和移动赋值运算符
    Boss(Boss&& other) noexcept
            : position(other.position),
              currentBlood(other.currentBlood),
              hit_timer(other.hit_timer)
    {}

    // Move assignment operator
    Boss& operator=(Boss&& other) noexcept {
        if (this != &other) {
            position = other.position;
            currentBlood = other.currentBlood;
            hit_timer = other.hit_timer;
            // Additional members to move if needed
        }
        return *this;
    }

    void move(Player& player)
    {
        float dx = position.x - player.getPosition().x;
        float dy = position.y - player.getPosition().y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dx < 10)
        {
            FacingRight = true;
        }else
        {
            FacingRight = false;
        }

        if (dist > 100)
        {
            position.x -= SPEED * dx / dist;
            position.y -= SPEED * dy / dist;
        }
    }

    void checkHurt(Player& player)
    {
        float dx = position.x - player.getPosition().x;
        float dy = position.y - player.getPosition().y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (player.GetIsAttack() && dist < 300)
        {
            currentBlood -= 10;
            isHit = true;
        }
    }

    Point Getposition(){
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





#endif //DAD_N_ME_BOSS_H
