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


// class Common {
// private:
//     const float SPEED = 2;
//     Animation* animLeft;
//     Animation* animRight;
//     Point position{};
//
//     int isHit = 0;
//
//     int timer = 0;
//     int idxRunFrame = 0;
//     int idxHitFrame = 0;
//
// public:
//     Common(float startX, float startY, Animation* animLeft, Animation* animRight)
//             : position{startX, startY}, animLeft(animLeft), animRight(animRight) {}
//
//     // 移动构造函数
//     Common(Common&& other) noexcept
//             : animLeft(nullptr), animRight(nullptr) {
//         *this = std::move(other);
//     }
//
//     // 移动赋值运算符
//     Common& operator=(Common&& other) noexcept {
//         if (this != &other) {
//             position = other.position;
//             isHit = other.isHit;
//             animLeft = std::exchange(other.animLeft, nullptr);
//             animRight = std::exchange(other.animRight, nullptr);
//             timer = other.timer;
//             idxRunFrame = other.idxRunFrame;
//             idxHitFrame = other.idxHitFrame;
//             isHit = other.isHit;
//         }
//         return *this;
//     }
//
//     void move() {
//         position.x += SPEED;
//     }
//
//     bool hasFinishedHitAnimation() const {
//         return isHit && idxHitFrame == animLeft->getHitFrameCount() - 1;
//     }
//
//
//     void draw(QPainter& painter, int delta, int playerSignal) {
//         timer += delta;
//         if (playerSignal > 0)
//         {
//             isHit = 1;
//         }
//         if (isHit == 1) {
//             if (timer >= animLeft->getInterval()) {
//                 idxHitFrame = (idxHitFrame + 1) % animLeft->getHitFrameCount();
//                 timer = 0;
//             }
//             animLeft->displayHit(painter, position.x, position.y - 100, timer, idxHitFrame);
//         } else {
//             if (timer >= animLeft->getInterval()) {
//                 idxRunFrame = (idxRunFrame + 1) % animLeft->getRunFrameCount();
//                 timer = 0;
//             }
//             animLeft->displayRun(painter, position.x, position.y, timer, idxRunFrame);
//         }
//     }
//
//     Point getPosition() const {
//         return position;
//     }
// };
#include <QPainter>
#include <utility> // for std::exchange

class Common {
private:
    const float SPEED = 2;
    float speed = SPEED; // 当前速度，可以为正或负
    Animation* animLeft;
    Animation* animRight;
    Point position{};

    int isHit = 0;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

    bool isReversed = false; // 速度是否反向

public:
    Common(float startX, float startY, Animation* animLeft, Animation* animRight)
        : position{startX, startY}, animLeft(animLeft), animRight(animRight) {}

    // 移动构造函数
    Common(Common&& other) noexcept
        : animLeft(nullptr), animRight(nullptr) {
        *this = std::move(other);
    }

    // 移动赋值运算符
    Common& operator=(Common&& other) noexcept {
        if (this != &other) {
            position = other.position;
            isHit = other.isHit;
            animLeft = std::exchange(other.animLeft, nullptr);
            animRight = std::exchange(other.animRight, nullptr);
            timer = other.timer;
            idxRunFrame = other.idxRunFrame;
            idxHitFrame = other.idxHitFrame;
            isHit = other.isHit;
            isReversed = other.isReversed;
            speed = other.speed;
        }
        return *this;
    }

    void move() {
        position.x += speed;
    }

    bool hasFinishedHitAnimation() const {
        return isHit && idxHitFrame == animLeft->getHitFrameCount() - 1;
    }

    void draw(QPainter& painter, int delta, int playerSignal) {
        timer += delta;
        if (playerSignal > 0) {
            isHit = 1;
        }
        if (isHit == 1) {
            if (timer >= animLeft->getInterval()) {
                idxHitFrame = (idxHitFrame + 1) % animLeft->getHitFrameCount();
                timer = 0;
            }
            animLeft->displayHit(painter, position.x, position.y - 100, timer, idxHitFrame);
        } else {
            if (timer >= animLeft->getInterval()) {
                idxRunFrame = (idxRunFrame + 1) % animLeft->getRunFrameCount();
                timer = 0;
            }
            animLeft->displayRun(painter, position.x, position.y, timer, idxRunFrame);
        }
    }

    Point getPosition() const {
        return position;
    }

    void checkCollision(const QRect& obstacle) {
        QRect playerRect(position.x, position.y, 10, 20);
        if (playerRect.intersects(obstacle)) {
            speed = -speed; // 反转速度
            //isReversed = !isReversed; // 更新反向状态
        }
    }
};


#endif //DAD_N_ME_COMMON_H
