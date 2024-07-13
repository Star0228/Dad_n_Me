//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_BACKGROUND_H
#define DAD_N_ME_BACKGROUND_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRectF>
#include <QRandomGenerator>
#include "Common.h"
#include "ResourceManager.h"
#include "Animation.h"

class Background {
public:
    QColor backgroundColor; // 背景颜色
    QVector<QImage> obstacleImages;   // 障碍物图片
    bool obstaclePlaced;    // 是否已经放置障碍物
    std::vector<Point> positions;


    QRectF healthRectPlayer;   //人物血条
    QRectF healthRectBoss;   //人物血条
    QRectF patienceRectPlayer;   //Boss精力条
    QRectF patienceRectBoss;    //Boss精力条

    float health_Player = 1.0;
    float patience_Player = 1.0;

    float health_Boss = 1.0;
    float patience_Boss = 1.0;
public:
    Background(const QColor& color = Qt::white) : backgroundColor(color), obstaclePlaced(true){
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/house_brown.png"));
        positions.push_back({50, 50});
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/bush1.png"));
        positions.push_back({400,400});
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/win.png"));
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/gameover.png"));

        healthRectPlayer = QRectF(25, 25, 200, 20);
        healthRectBoss = QRectF(600,25,200,20);
        patienceRectPlayer = QRectF(25, 60, 200, 20);
        patienceRectBoss = QRectF(600, 60, 200, 20);
    }

    float getPlayerHealth(){
        return health_Player;
    }

    float getBossHealth(){
        return health_Boss;
    }

    void reset(){
        health_Player = 1.0;
        patience_Player = 1.0;
        health_Boss = 1.0;
        patience_Boss = 1.0;
    }


    void draw(QPainter* painter, const QRectF& rect,int gameState) {
        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);

        for(int i = 0; i < 2 ; i++) {
            painter->drawImage(positions[i].x, positions[i].y, obstacleImages[i]);
        }
        if(gameState == 1){
            painter->drawImage(600,400,obstacleImages[2]);
        }else if(gameState ==2){
            painter->drawImage(600,400,obstacleImages[3]);
        }

        // 绘制血条和精力条
        QPen borderPen(Qt::black); // 设置边框颜色为黑色
        borderPen.setWidth(3);     // 设置边框宽度为3个像素，可以根据需要调整粗细
        borderPen.setStyle(Qt::SolidLine); // 设置边框线条样式为实线
        painter->setPen(borderPen);

        // 绘制血条边框
        painter->drawRect(healthRectPlayer);
        painter->drawRect(healthRectBoss);

        // 绘制血条内部（红色部分）
        QRectF innerRect = healthRectPlayer.adjusted(3, 3, -3, -3); // 调整内部矩形，留出边框宽度的空间
        QRectF healthRectPlayer = QRectF(innerRect.x(), innerRect.y(), health_Player>0?innerRect.width() * health_Player:0, innerRect.height());
        painter->fillRect(healthRectPlayer, Qt::red);

        innerRect = healthRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF healthRectBoss = QRectF(innerRect.x()+innerRect.width() * (1-health_Boss), innerRect.y(), health_Boss>0?innerRect.width() * health_Boss:0, innerRect.height());
        painter->fillRect(healthRectBoss, Qt::red);


        painter->drawRect(patienceRectPlayer);
        painter->drawRect(patienceRectBoss);
        //绘制绿色精力条
        innerRect = patienceRectPlayer.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF patienceRectPlayer = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * patience_Player, innerRect.height());
        painter->fillRect(patienceRectPlayer, Qt::green);

        innerRect = patienceRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF patienceRectBoss = QRectF(innerRect.x()+innerRect.width() * (1-patience_Boss), innerRect.y(), innerRect.width() * patience_Boss, innerRect.height());
        painter->fillRect(patienceRectBoss,Qt::green);
    }

    void addObstacles(QVector<QRect>* obstacles){
        obstacles->append(QRect(50, 50, obstacleImages[0].width(), obstacleImages[0].height()));
        obstacles->append(QRect(400, 400, obstacleImages[1].width(), obstacleImages[1].height()));
    }
};

#endif //DAD_N_ME_BACKGROUND_H
