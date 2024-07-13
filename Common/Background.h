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
#include "ResourceManager.h"
#include "Animation.h"

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
    QVector<QImage> obstacleImages;   // 障碍物图片
    std::vector<QPoint> obPositions;    // 障碍物位置
    QVector<QImage> backgroundImages;
    std::vector<QPoint> bgPositions;    // 障碍物位置

public:
    Background(const QColor &color = QColor(173, 216, 230)) : backgroundColor(color) {
        initializeObstacles(); // 初始化障碍物
        initializeBackgrounds();
        healthRectPlayer = QRectF(25, 25, 200, 20);
        healthRectBoss = QRectF(600, 25, 200, 20);
        patienceRectPlayer = QRectF(25, 60, 200, 20);
        patienceRectBoss = QRectF(600, 60, 200, 20);
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

    void addObstacles(QVector<QRect>* obstacles) {
        for (const auto& pos : obPositions) {
            int index = &pos - &obPositions[0]; // 计算当前位置的索引
            obstacles->append(QRect(pos, obstacleImages[index].size()));
        }
    }

    void draw(QPainter *painter, const QRectF &rect, int gameState) {
        // 绘制背景颜色
        painter->fillRect(rect, backgroundColor);

        for (const auto &pos: bgPositions) {
            int index = &pos - &bgPositions[0]; // 计算当前位置的索引
            painter->drawImage(pos, backgroundImages[index]);
        }

        if(gameState == 1){
            painter->drawImage(600,400,ResourceManager::getInstance().getImage("../resource/background/win.png"));
        }else if(gameState ==2){
            painter->drawImage(600,400,ResourceManager::getInstance().getImage("../resource/background/gameover.png"));
        }

        // 绘制障碍物
        for (const auto &pos: obPositions) {
            int index = &pos - &obPositions[0]; // 计算当前位置的索引
            painter->drawImage(pos, obstacleImages[index]);
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
        QRectF healthRectPlayer = QRectF(innerRect.x(), innerRect.y(),
                                         health_Player > 0 ? innerRect.width() * health_Player : 0, innerRect.height());
        painter->fillRect(healthRectPlayer, Qt::red);

        innerRect = healthRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF healthRectBoss = QRectF(innerRect.x() + innerRect.width() * (1 - health_Boss), innerRect.y(),
                                       health_Boss > 0 ? innerRect.width() * health_Boss : 0, innerRect.height());
        painter->fillRect(healthRectBoss, Qt::red);

        painter->drawRect(patienceRectPlayer);
        painter->drawRect(patienceRectBoss);
        //绘制绿色精力条
        innerRect = patienceRectPlayer.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF patienceRectPlayer = QRectF(innerRect.x(), innerRect.y(), innerRect.width() * patience_Player,
                                           innerRect.height());
        painter->fillRect(patienceRectPlayer, Qt::green);

        innerRect = patienceRectBoss.adjusted(3, 3, -3, -3); //调整内部矩形，留出边框宽度的空间
        QRectF patienceRectBoss = QRectF(innerRect.x() + innerRect.width() * (1 - patience_Boss), innerRect.y(),
                                         innerRect.width() * patience_Boss, innerRect.height());
        painter->fillRect(patienceRectBoss, Qt::green);
    }

    void initializeObstacles() {
        // 添加障碍物图片和位置
        obstacleImages.append(ResourceManager::getInstance().getImage("../resource/background/house_brown.png"));
        obPositions.push_back(QPoint(50, 50));
    }

    void initializeBackgrounds() {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        QImage grandPic = QImage("../resource/background/grand.png");
        for (int j = 1; j < 3; j++) {
            for (int i = 0; i * (grandPic.width() - 10) < screenGeometry.width(); i++) {
                backgroundImages.append(ResourceManager::getInstance().getImage("../resource/background/grand.png"));
                bgPositions.push_back(
                        QPoint(i * (grandPic.width() - 10), screenGeometry.height() - j * (grandPic.height() - 20)));
            }
        }
    }

};


#endif //DAD_N_ME_BACKGROUND_H
