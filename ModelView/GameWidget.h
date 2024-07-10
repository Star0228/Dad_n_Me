//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_GAMEWIDGET_H
#define DAD_N_ME_GAMEWIDGET_H

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


#include "../Model/Boss.h"
#include "../Model/Common.h"
#include "../Model/Player.h"
#include "../Model/Background.h"

const int SMALL_AY_NUM = 8;
const int IMG_INTERVAL = 30;


class GameWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameWidget(QWidget* parent = nullptr);
    ~GameWidget() override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void updateGame();

private:
    // QImage background;
    Background background;
    //敌人
    std::vector<Common> smallObjects;
    Boss boss;
    QVector<QRect> obstacles;
    //玩家
    Animation* animPlayer;
    Player* player;

    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;

    Animation* animLeftSmall;
    Animation* animRightSmall;
    Animation* animBoss;

    void addObstacles();
};
#endif //DAD_N_ME_GAMEWIDGET_H
