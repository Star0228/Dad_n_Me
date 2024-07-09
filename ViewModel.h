//
// Created by Thorin on 2024/7/9.
//

#pragma once

#include <QObject>
#include <QTimer>
#include "Models.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr)
        : QObject(parent),
          timer(new QTimer(this)),
          player(nullptr),
          boss(nullptr),
          playerSignal(0),
          testLoop(0) {

        connect(timer, &QTimer::timeout, this, &GameViewModel::updateGame);
        timer->start(1000 / 144);

        animLeftSmall = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);
        animRightSmall = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);

        animBoss = new Animation("../img_boss/%1.png", "../img_boss/hit_%1.png", 8, 14, IMG_INTERVAL, 1);
        animPlayer = new Animation("../img_player/%1.png", "../img_player/hit_%1.png", 8, 14, IMG_INTERVAL, 2);

        player = new Player(100, 100, animPlayer, 3);
        boss = new Boss(animBoss);

        for (int i = 0; i < 20; i++) {
            auto smallEnemy = Small(100 + i * 50, 200, animLeftSmall, animRightSmall);
            smallEnemies.push_back(std::move(smallEnemy));
        }
    }

    ~GameViewModel() override {
        delete animLeftSmall;
        delete animRightSmall;
        delete animBoss;
        delete animPlayer;
    }

    void handleKeyPress(int key) {
        switch (key) {
            case Qt::Key_Left:
                player->moveLeft();
                break;
            case Qt::Key_Right:
                player->moveRight();
                break;
            case Qt::Key_Up:
                player->moveUp();
                break;
            case Qt::Key_Down:
                player->moveDown();
                break;
            case Qt::Key_Space:
                player->attack();
                break;
            default:
                break;
        }
    }

    void handleKeyRelease(int key) {
        Q_UNUSED(key);
    }

    Player* getPlayer() const {
        return player;
    }

    std::vector<Small>& getSmallEnemies() {
        return smallEnemies;
    }

    Boss* getBoss() const {
        return boss;
    }

signals:
    void gameUpdated();

private slots:
    void updateGame() {
        for (auto& small : smallEnemies) {
            small.move();
        }

        boss->move(player);
        boss->checkHurt(player);

        emit gameUpdated();
    }

private:
    QTimer* timer;
    Player* player;
    Boss* boss;
    Animation* animLeftSmall;
    Animation* animRightSmall;
    Animation* animBoss;
    Animation* animPlayer;

    std::vector<Small> smallEnemies;
    int playerSignal;
    int testLoop;
};
