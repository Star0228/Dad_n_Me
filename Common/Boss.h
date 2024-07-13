#ifndef DAD_N_ME_BOSS_H
#define DAD_N_ME_BOSS_H

#include <QWidget>
#include <QDebug>
#include <cmath>
#include <vector>
#include <cmath>
#include <iostream>


#include "Player.h"
#include "Background.h"



class Boss
{
private:
    const int SPEED = 1;
    Point position{};
    int hit_timer = 0;
    bool FacingRight = true;
    bool isHit = false;

public:
    bool isAttacking = false;

    Boss(float startx = 1100,float starty =300){
        position.x = startx;
        position.y = starty;
    }

    // 实现移动构造函数和移动赋值运算符
    Boss(Boss&& other) noexcept
            : position(other.position),
              hit_timer(other.hit_timer)
    {}

    void reset();

    // Move assignment operator
    Boss& operator=(Boss&& other) noexcept {
        if (this != &other) {
            position = other.position;
            hit_timer = other.hit_timer;
            // Additional members to move if needed
        }
        return *this;
    }

    void move(Player& player);


    void attack(Background& background);

    void checkHurt(Player& player,Background& background);

    void refillPatience(Background& background);

    Point Getposition();

    bool GetIsHit();

    bool getIsAttack();

    void Change_IsHit(bool signal);

    int GetTimer();

    bool GetFacingRight();

    void AddTimer(int adder);

    void ResetTimer();
};



#endif //DAD_N_ME_BOSS_H
