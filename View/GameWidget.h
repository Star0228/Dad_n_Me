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

#include "../Common/Boss.h"
#include "../Common/Simple.h"
#include "../Common/Player.h"
#include "../Common/Background.h"
#include "../View/View_draw.h"




class GameWidget : public QWidget {
    Q_OBJECT
private:
    View_draw* view;
    Background* background;
    std::map<int,Simple>* smallEnemies; // 指针类型
    int countSimple = 0;
    const int maxNumSimple = 10;
    Boss* boss;
    QVector<QRect>* obstacles; // 指针类型
    Player* player;
    int* playerSignal;
    QTimer* timer;
    int gameState = 0;//0 represents normal, 1 represent win , 2 represents lose

public:
    explicit GameWidget(QWidget* parent = nullptr,
                        Background* bg = nullptr,
                        std::map<int,Simple>* commons = nullptr,
                        Boss* b = nullptr,
                        QVector<QRect>* obs = nullptr,
                        Player* p = nullptr,
                        int* pSignal = nullptr,
                        View_draw* v = nullptr)
        : QWidget(parent), background(bg), smallEnemies(commons), boss(b),
        obstacles(obs), player(p),playerSignal(pSignal), view(v) {
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
    void keyPressed();
    void KeyReleased();
    void KeyLeft();
    void KeyRight();
    void KeyUp();
    void KeyDown();
    void KeyS();
    void ResetGame();
protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        if (background) {
            view->draw(*background,&painter, rect(),gameState);
        }

        if (smallEnemies) {
            for (auto& pair : *smallEnemies) {
                view->draw(pair.first, pair.second, painter, 1000 / 288, *playerSignal);
            }
        }

        if (player) {
            view->draw(*player, painter, 1000 / 288);
        }

        if (boss && player && background->getBossHealth()>0) {
            view->draw(*boss, *player, *background, painter, 1000 / 288);
        }
    }
    void keyReleaseEvent(QKeyEvent *event) override {
        emit KeyReleased();
    }
    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key()) {
            case Qt::Key_Left:
                emit KeyLeft();
            break;
            case Qt::Key_Right:
                emit KeyRight();
            break;
            case Qt::Key_Up:
                emit KeyUp();
            break;
            case Qt::Key_Down:
                emit KeyDown();
            break;
            case Qt::Key_S:
                emit KeyS();
            break;
            case Qt::Key_R:
                timer->start();
                countSimple = 0;
                gameState = 0;
                emit ResetGame();
            break;
        }
    }

private slots:
    void updateGame() {
        if (smallEnemies) {
            // 管理小怪的生成
            if (countSimple < maxNumSimple && std::rand() % 100 < 3) { //按概率生成小怪
                int startY = std::rand() % 720; // 随机生成 Y 坐标
                if (startY >= 400 && startY <= 600) {
                    countSimple ++;
                    int newId = smallEnemies->empty() ? 0 : smallEnemies->rbegin()->first+1;
                    smallEnemies->emplace(newId, Simple(0, startY));
                }
            }

            for (auto it = smallEnemies->begin(); it != smallEnemies->end();) {
                if (it->second.GetIsHit() && view->Get_Idx_Common_Hit()[it->first] >= 12) {
                    it = smallEnemies->erase(it); //使用 erase 删除元素，并更新迭代器
                    view->Get_Idx_Common_Hit()[it->first] = 0; //删除后对应帧归零
                }
                else {
                    ++it;
                }
            }

            // 移动所有未处于 hit 动画的 Common 对象
            for (auto& pair : *smallEnemies) {
                Simple& small = pair.second;
                if ( playerSignal && *playerSignal == 0) {
                    QScreen *screen = QGuiApplication::primaryScreen();
                    QRect screenGeometry = screen->geometry();
                    int width = screenGeometry.width();
                    int height = screenGeometry.height();
                    small.move(*obstacles,width,height);
                }
            }
        }

        //检查boss是否受到击打
        if (boss && player) {
            boss->checkHurt(*player,*background);
            boss->move(*player);
        }

        //检查主角是否受击打
        if(player){
            player->checkHurt(*background, boss->Getposition().x, boss->Getposition().y, boss->isAttacking);
        }

        //检查小怪是否受到击打
        for (auto& pair : *smallEnemies) {
            Simple& small = pair.second;
            small.checkHurt(*player);
        }
        //回复精力
        player->refillPatience(*background);
        boss->refillPatience(*background);
        update(); // 请求重绘
        if(background->getPlayerHealth()<=0){
            timer->stop();
            gameState = 2;
        }else if(background->getBossHealth()<=0 && smallEnemies->size()==0){
            timer->stop();
            gameState = 1;
        }
    }
};

#endif //DAD_N_ME_GAMEWIDGET_H
