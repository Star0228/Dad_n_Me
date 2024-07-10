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
    Background(const QColor& color = Qt::gray) : backgroundColor(color), obstaclePlaced(false) {
            obstacleImage = ResourceManager::getInstance().getImage("E:\\Dad_n_Me\\resource\\background\\house_brown.png");
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
            int obstacleY = 50, obstacleX = 100;
            painter->drawImage(obstacleX, obstacleY, obstacleImage);
            obstaclePlaced = true; // 标记已放置障碍物
        }
    }
};

#endif //DAD_N_ME_BACKGROUND_H
