//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_ANIMATION_H
#define DAD_N_ME_ANIMATION_H

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

#include "ResourceManager.h"

struct Point {
    float x;
    float y;
};

class Animation {
public:
    int interval;
    std::vector<QImage> runFrameList;
    std::vector<QImage> hitFrameList;
    std::vector<QImage> attackFrameList; // 新添加的攻击动画帧列表


    Animation(const QString& pathRun, const QString& pathHit, int numRun, int numHit, int interval, int attackFrames = 0)
            : interval(interval)
    {
        for (int i = 1; i <= numRun; ++i) {
            QString pathFile = pathRun.arg(i);
            QImage frame = ResourceManager::getInstance().getImage(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load run frame:" << pathFile;
            }
            runFrameList.push_back(frame);
        }
        for (int i = 1; i <= numHit; ++i) {
            QString pathFile = pathHit.arg(i);
            QImage frame = ResourceManager::getInstance().getImage(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load hit frame:" << pathFile;
            }
            hitFrameList.push_back(frame);
        }

        if (attackFrames == 1) { // 此时表示需要载入Boss的攻击模组
            // 初始化攻击帧列表
            // boss的攻击帧数为14
            for (int i = 1; i <= 14; ++i) {
                QString pathFile = QString("../resource/Enemy_boss/attack/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
                //std::cout << attackFrameList.size() << std::endl;
            }
        }
        else if (attackFrames == 2) // 此时需要载入玩家的攻击模组
        {
            for (int i = 1; i <= 21; ++i) {
                QString pathFile = QString("../attack/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
            }
        }
    }

    void displayRun(QPainter& painter, int x, int y, int timer, int idxRunFrame, bool facingRight = true) {
        if (runFrameList.empty()) return;
        QImage frame = runFrameList[idxRunFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }

    void displayHit(QPainter& painter, int x, int y, int timer, int idxHitFrame, bool facingRight = true) {
        if (hitFrameList.empty()) return;
        QImage frame = hitFrameList[idxHitFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }

    void displayAttack(QPainter& painter, int x, int y, int timer, int idxAttackFrame, bool facingRight = true) {
        if (attackFrameList.empty()) return;
        QImage frame = attackFrameList[idxAttackFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }

    int getInterval() const {
        return interval;
    }

    int getRunFrameCount() const {
        return runFrameList.size();
    }

    int getHitFrameCount() const {
        return hitFrameList.size();
    }

    int getAttackFrameCount() const {
        return attackFrameList.size();
    }
};


#endif //DAD_N_ME_ANIMATION_H
