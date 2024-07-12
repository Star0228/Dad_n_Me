#ifndef DAD_N_ME_BACKGROUND_H
#define DAD_N_ME_BACKGROUND_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRectF>
#include <QVector>
#include "Common.h"
#include "ResourceManager.h"
#include "Animation.h"

class Background {
public:
    QColor backgroundColor; // 背景颜色
    QVector<QImage> obstacleImages;   // 障碍物图片
    std::vector<QPoint> obPositions;    // 障碍物位置
    QVector<QImage> backgroundImages;
    std::vector<QPoint> bgPositions;    // 障碍物位置
    QRectF healthBarRect;   // 血条
    QRectF patienceBarRect; // 精力条
    float health = 1.0;
    float patience = 1.0;

public:
    Background(const QColor& color = Qt::white) : backgroundColor(color) {
        initializeObstacles(); // 初始化障碍物
        initializeBackgrounds();
        healthBarRect = QRectF(25, 25, 200, 20);
        patienceBarRect = QRectF(25, 60, 200, 20);
    }

    void draw(QPainter* painter, const QRectF& rect, bool showHealthBar) {
        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);



        for (const auto& pos : bgPositions) {
            int index = &pos - &bgPositions[0]; // 计算当前位置的索引
            painter->drawImage(pos, backgroundImages[index]);
        }

        // 绘制障碍物
        for (const auto& pos : obPositions) {
            int index = &pos - &obPositions[0]; // 计算当前位置的索引
            painter->drawImage(pos, obstacleImages[index]);
        }

        // 绘制血条和精力条
        if (showHealthBar) {
            drawProgressBar(painter, healthBarRect, health, Qt::red);
            drawProgressBar(painter, patienceBarRect, patience, Qt::green);
        }
    }

    void addObstacles(QVector<QRect>* obstacles) {
        for (const auto& pos : obPositions) {
            int index = &pos - &obPositions[0]; // 计算当前位置的索引
            obstacles->append(QRect(pos, obstacleImages[index].size()));
        }
    }

private:
    void initializeObstacles() {
        // 添加障碍物图片和位置
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/house_brown.png"));
        obPositions.push_back(QPoint(50, 50));
    }

    void drawProgressBar(QPainter* painter, const QRectF& rect, float value, const QColor& color) {
        QPen borderPen(Qt::black);
        borderPen.setWidth(3);
        borderPen.setStyle(Qt::SolidLine);
        painter->setPen(borderPen);
        painter->drawRect(rect);

        QRectF innerRect = rect.adjusted(3, 3, -3, -3);
        QRectF barRect = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * value, innerRect.height());
        painter->fillRect(barRect, color);
    }

    void initializeBackgrounds() {
        backgroundImages.append(ResourceManager::getInstance().getImage("../resource/background/bush1.png"));
        bgPositions.push_back(QPoint(400, 400));

        backgroundImages.append(ResourceManager::getInstance().getImage("../resource/background/grand.png"));
        bgPositions.push_back(QPoint(600, 200));
    }
};

#endif // DAD_N_ME_BACKGROUND_H
