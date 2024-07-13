//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_BACKGROUND_H
#define DAD_N_ME_BACKGROUND_H

#include <QScreen>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRectF>
#include <QColor>
#include <QVector>
#include "Common.h"

//QColor lightBlue(173, 216, 230); // 使用RGB值定义浅蓝色


class Background {
public:
    QColor backgroundColor; // 背景颜色
    QRectF healthRectPlayer;   //人物血条
    QRectF healthRectBoss;   //人物血条
    QRectF patienceRectPlayer;   //Boss精力条
    QRectF patienceRectBoss;    //Boss精力条

    float health_Player = 1.0;
    float patience_Player = 1.0;
    float health_Boss = 1.0;
    float patience_Boss = 1.0;

public:
    Background(const QColor &color = QColor(173, 216, 230)) : backgroundColor(color) {
        healthRectPlayer = QRectF(25, 25, 200, 20);
        healthRectBoss = QRectF(1450, 25, 200, 20);
        patienceRectPlayer = QRectF(25, 60, 200, 20);
        patienceRectBoss = QRectF(1450, 60, 200, 20);
    }

    void reset() {
        health_Player = 1.0;
        patience_Player = 1.0;
        health_Boss = 1.0;
        patience_Boss = 1.0;
    }

    float getPlayerHealth(){
        return health_Player;
    }

    float getBossHealth(){
        return health_Boss;
    }

    float getPlayerPatience(){
        return patience_Player;
    }

    float getBossPatience(){
        return patience_Boss;
    }

    QColor getBgcolor(){
        return backgroundColor;
    }

    QRectF getHealthRectPlayer(){
        return healthRectPlayer;
    }
    QRectF getHealthRectBoss(){
        return healthRectBoss;
    }
    QRectF getPatienceRectPlayer(){
        return patienceRectPlayer;
    }
    QRectF getPatienceRectBoss(){
        return patienceRectBoss;
    }


    void addObstacles(QVector<QRect>* obstacles) {
        obstacles->append(QRect(50,-80, 473,372));
    }

};


#endif //DAD_N_ME_BACKGROUND_H
