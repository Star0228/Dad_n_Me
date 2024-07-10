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
#include "../View/ResourceManager.h"
class Background {
public:
    QColor backgroundColor; // 背景颜色
    QImage obstacleImage;   // 障碍物图片
    bool obstaclePlaced;    // 是否已经放置障碍物

public:
    Background(const QColor& color = Qt::white) : backgroundColor(color), obstaclePlaced(true) {
            obstacleImage = ResourceManager::getInstance().getImage("../resource/background/house_brown.png");
    }

    // void setObstacleImage(const QString& imagePath) {
    //
    //     obstacleImage.load(imagePath);
    // }

    void draw(QPainter* painter, const QRectF& rect) {
        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);

        // 随机放置障碍物图片
        if (!obstaclePlaced) {
            std::cout << "fuck you!" << std::endl;
            // qreal obstacleX = QRandomGenerator::global()->bounded(rect.width() - obstacleImage.width());
            // qreal obstacleY = QRandomGenerator::global()->bounded(rect.height() - obstacleImage.height());
            obstaclePlaced = true; // 标记已放置障碍物
        }
        int obstacleY = 50, obstacleX = 100;
        painter->drawImage(obstacleX, obstacleY, obstacleImage);
    }
    void addObstacles(QVector<QRect>& obstacles){
        obstacles.append(QRect(50, 100, 50, 50));
        obstacles.append(QRect(400, 400, 50, 50));
    }
};

#endif //DAD_N_ME_BACKGROUND_H
