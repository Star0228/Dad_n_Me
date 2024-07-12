//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_GAMEWIDGET_H
#define DAD_N_ME_GAMEWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "../Model/Boss.h"
#include "../Model/Common.h"
#include "../Model/Player.h"
#include "../View/View_draw.h"
#include "../Model/Background.h"

class GameWidget : public QWidget {
    Q_OBJECT
private:
    View_draw* view;
    Background* background;
    std::map<int,Common>* smallEnemies; // 指针类型
    Boss* boss;
    QVector<QRect>* obstacles; // 指针类型
    Player* player;
    int* playerSignal;
    QTimer* timer;

public:
    explicit GameWidget(QWidget* parent = nullptr,
                        Background* bg = nullptr,
                        std::map<int,Common>* commons = nullptr,
                        Boss* b = nullptr,
                        QVector<QRect>* obs = nullptr,
                        Player* p = nullptr,
                        int* pSignal = nullptr,
                        View_draw* v = nullptr)
        : QWidget(parent), background(bg), smallEnemies(commons), boss(b), obstacles(obs), player(p), playerSignal(pSignal), view(v) {
        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);
        setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
    }

    ~GameWidget() override {
        delete timer;
        delete view;
    }
signals:
    void keyPressed(int key);
    void keyReleased(int key);

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        if (background) {
            background->draw(&painter, rect());
        }

        if (smallEnemies) {
            for (auto& pair : *smallEnemies) {
                view->draw(pair.first, pair.second, painter, 1000 / 288, *playerSignal);
            }
        }

        if (player) {
            view->draw(*player, painter, 1000 / 288);
        }

        if (boss && player) {
            //view->draw(*boss, *player, painter, 1000 / 288);
        }
    }

    void keyPressEvent(QKeyEvent* event) override {
        emit keyPressed(event->key());
    }

private slots:
    void updateGame() {
        if (smallEnemies) {
            // 管理小怪的生成
            if (std::rand() % 100 < 3) { //按概率生成小怪
                int startY = std::rand() % 720; // 随机生成 Y 坐标
                if (startY >= 400 && startY <= 600) {
                    int newId = smallEnemies->empty() ? 0 : smallEnemies->rbegin()->first+1;
                    smallEnemies->emplace(newId, Common(0, startY));
                }
            }

            for (auto it = smallEnemies->begin(); it != smallEnemies->end();) {
                if (it->second.GetIsHit() && view->Get_Idx_Common_Hit()[it->first] >= 12) {
                    it = smallEnemies->erase(it); //使用 erase 删除元素，并更新迭代器
                    view->Get_Idx_Common_Hit()[it->first] = 0; //删除后对应帧归零
                }
                else if (it->second.getPosition().x >= 1200) { //此时超出了边框
                    it = smallEnemies->erase(it); //使用 erase 删除元素，并更新迭代器
                    view->Get_Idx_Common_Hit()[it->first] = 0; //删除后对应帧归零
                }

                else {
                    ++it;
                }
            }

            // 移动所有未处于 hit 动画的 Common 对象
            for (auto& pair : *smallEnemies) {
                Common& small = pair.second;
                if (playerSignal && *playerSignal == 0) {
                    small.move();
                }
            }
        }

        //检查boss是否受到击打
        if (boss && player) {
            boss->checkHurt(*player);
            boss->move(*player);
        }

        //检查小怪是否受到击打
        for (auto& pair : *smallEnemies) {
            Common& small = pair.second;
            small.checkHurt(*player);
        }

        update(); // 请求重绘
    }
};

#endif //DAD_N_ME_GAMEWIDGET_H
