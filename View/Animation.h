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
    std::vector<QImage> FrameList;

    Animation(const QString& path, int numFrame,int interval)
            : interval(interval)
    {
        for (int i = 1; i <= numFrame; ++i) {
            QString pathFile = path.arg(i);
            QImage frame = ResourceManager::getInstance().getImage(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load run frame:" << pathFile;
            }
            FrameList.push_back(frame);
        }
    }

    void Display(QPainter& painter, int x, int y, int idxRunFrame, bool facingRight = true) {
        if (FrameList.empty()) return;
        QImage frame = FrameList[idxRunFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }


    int GetInterval() const {
        return interval;
    }

    int GetFrameCount() const {
        return FrameList.size();
    }

};


#endif //DAD_N_ME_ANIMATION_H
