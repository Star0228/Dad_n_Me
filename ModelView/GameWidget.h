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
#include "../View/View_draw.h"



class GameWidget : public QWidget {
Q_OBJECT

private:
    View_draw view;

    QImage background;

    //敌人
    std::vector<Common> smallObjects;
    Boss boss;

    //玩家
    Player player;

    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;



public:
    explicit GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png") {
        if (background.isNull()) {
            qDebug() << "Failed to load background image!";
        }
        timer = new QTimer(this);
        view = View_draw();
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);
        player = Player(640, 360,  12); // 初始化玩家位置和速度
        boss = Boss();
        setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
    }

    ~GameWidget() override {

    }

protected:
    void paintEvent(QPaintEvent* event) override { //虚函数重写
        QPainter painter(this);
        painter.drawImage(0, 0, background);

        for (Common& common : smallObjects) {
            view.draw(common,painter, 1000 / 144, playerSignal);
        }

        view.draw(player,painter, 1000 /144);

        view.draw(boss,player,painter, 1000 / 144); // 绘制玩家
    }

    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key())
        {
            case Qt::Key_Left:
                player.moveLeft();
                break;
            case Qt::Key_Right:
                player.moveRight();
                break;
            case Qt::Key_Up:
                player.moveUp();
                break;
            case Qt::Key_Down:
                player.moveDown();
                break;
            case Qt::Key_S:
                view.Reset_idx_pl_atk();
                player.attack();
                break;
        }
    }

private slots:
    void updateGame() {
        //管理小怪的生成
//        if (std::rand() % 100 < 2) { // 按概率生成小怪
//            int startY = std::rand() % 720; // 随机生成 Y 坐标
//            if (startY >= 200 && startY <= 600)
//            {
//                smallObjects.emplace_back(0, startY);
//            }
//        }

        testLoop++;

        if (testLoop % 500 == 0) {
            playerSignal = 80;
        } else {
            if (playerSignal > 0) {
                playerSignal--;
            }
        }


        for (auto it = smallObjects.begin(); it != smallObjects.end();) {
            if (it->GetIsHit() && view.Get_Idx_Common_Hit() == view.Get_anim_Common_hit()->GetFrameCount() - 1) {
                it = smallObjects.erase(it); // 使用 erase 删除元素，并更新迭代器
            } else {
                ++it;
            }
        }


        // 移动所有未处于 hit 动画的 Common 对象
        for (Common& small : smallObjects) {
            if (playerSignal == 0) {
                small.move();
            }
        }

        boss.checkHurt(player);
        boss.move(player);

        update();
    }
};
#endif //DAD_N_ME_GAMEWIDGET_H
