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


    QRectF healthBarRect;   //血条
    QRectF patienceBarRect;   //精力条

    float health = 1.0;
    float patience = 1.0;

public:
    Background(const QColor& color = Qt::white) : backgroundColor(color), obstaclePlaced(true){
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/house_brown.png"));
        positions.push_back({50, 50});
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/bush1.png"));
        positions.push_back({400,400});


        healthBarRect = QRectF(25, 25, 200, 20);
        patienceBarRect = QRectF(25, 60, 200, 20);
    }


    void draw(QPainter* painter, const QRectF& rect, bool showHealthBar) {
        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);

        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);


        for(int i = 0; i < 2 ; i++) {
            painter->drawImage(positions[i].x, positions[i].y, obstacleImages[i]);
        }

        // 绘制血条和精力条
        if (showHealthBar) {
            QPen borderPen(Qt::black); // 设置边框颜色为黑色
            borderPen.setWidth(3);     // 设置边框宽度为3个像素，可以根据需要调整粗细
            borderPen.setStyle(Qt::SolidLine); // 设置边框线条样式为实线
            painter->setPen(borderPen);

            // 绘制血条边框
            painter->drawRect(healthBarRect);

            // 绘制血条内部（红色部分）
            QRectF innerRect = healthBarRect.adjusted(3, 3, -3, -3); // 调整内部矩形，留出边框宽度的空间
            QRectF healthRect = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * health, innerRect.height());
            painter->fillRect(healthRect, Qt::red);

            painter->drawRect(patienceBarRect);
            innerRect = patienceBarRect.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
            QRectF patienceRect = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * patience, innerRect.height());
            painter->fillRect(patienceRect, Qt::green);

        }
    }




    void addObstacles(QVector<QRect>* obstacles){
        obstacles->append(QRect(50, 50, obstacleImages[0].width(), obstacleImages[0].height()));
        obstacles->append(QRect(400, 400, obstacleImages[1].width(), obstacleImages[1].height()));
    }
};

#endif //DAD_N_ME_BACKGROUND_H
