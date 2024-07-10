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
#include "ViewModel.h"

class GameWidget : public QWidget {
    Q_OBJECT
private:
    View_draw* view;
    Background* background;
    std::vector<Common>* Commons; // 指针类型
    Boss* boss;
    QVector<QRect>* obstacles; // 指针类型
    Player* player;
    int* playerSignal;
    QTimer* timer;
    GameViewModel* viewModel;

public:
    explicit GameWidget(QWidget* parent = nullptr,
                        Background* bg = nullptr,
                        std::vector<Common>* commons = nullptr,
                        Boss* b = nullptr,
                        QVector<QRect>* obs = nullptr,
                        Player* p = nullptr,
                        int* pSignal = nullptr,
                        View_draw* v = nullptr,
                        GameViewModel* vm = nullptr)
        : QWidget(parent), background(bg), Commons(commons), boss(b), obstacles(obs), player(p), playerSignal(pSignal), view(v), viewModel(vm) {
        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);

        if (background && obstacles) {
            background->addObstacles(*obstacles); // 添加障碍物
        }

        setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
    }

    ~GameWidget() override {
        delete timer;
        delete view;
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        if (background) {
            background->draw(&painter, rect());
        }

        if (Commons) {
            for (Common& common : *Commons) {
                view->draw(common, painter, 1000 / 288, *playerSignal);
            }
        }

        if (player) {
            view->draw(*player, painter, 1000 / 288);
        }

        if (boss && player) {
            view->draw(*boss, *player, painter, 1000 / 288);
        }
    }

    void keyPressEvent(QKeyEvent* event) override {
        viewModel->handleKeyPress(event->key());
    }

private slots:
    void updateGame() {
        if (Commons) {
            // 管理小怪的生成
            if (std::rand() % 100 < 2) { // 按概率生成小怪
                int startY = std::rand() % 720; // 随机生成 Y 坐标
                if (startY >= 200 && startY <= 600) {
                    Commons->emplace_back(0, startY);
                }
            }

            for (auto it = Commons->begin(); it != Commons->end();) {
                if (it->GetIsHit() && view->Get_Idx_Common_Hit() == view->Get_anim_Common_hit()->GetFrameCount() - 1) {
                    it = Commons->erase(it); // 使用 erase 删除元素，并更新迭代器
                } else {
                    ++it;
                }
            }

            // 移动所有未处于 hit 动画的 Common 对象
            for (Common& small : *Commons) {
                if (playerSignal && *playerSignal == 0) {
                    small.move();
                }
            }
        }

        if (boss && player) {
            boss->checkHurt(*player);
            boss->move(*player);
        }

        update(); // 请求重绘
    }
};

#endif //DAD_N_ME_GAMEWIDGET_H
