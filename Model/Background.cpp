#include "Structure.h"
// #include <iostream>

Background::Background(const QColor& color)
    : backgroundColor(color), obstaclePlaced(false) {
    obstacleImage = ResourceManager::getInstance().getImage("E:\\Dad_n_Me\\resource\\background\\house_brown.png");
}

void Background::draw(QPainter* painter, const QRectF& rect) {
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

