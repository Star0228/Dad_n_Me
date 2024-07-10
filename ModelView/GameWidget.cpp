//
// Created by 16579 on 2024/7/9.
//

#include "GameWidget.h"
// GameWidget.cpp
#include "GameWidget.h"
#include <QKeyEvent>
#include <QPainter>
#include <cstdlib>

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent), boss(nullptr), player(nullptr) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
    timer->start(1000 / 144);

    animLeftSmall = new Animation("../resource/Enemy_common/run/%1.png", "../resource/Enemy_common/is_hit/hit_%1.png", 8, 14, IMG_INTERVAL);
    animRightSmall = new Animation("../resource/Enemy_common/run/%1.png", "../resource/Enemy_common/is_hit/hit_%1.png", 8, 14, IMG_INTERVAL);

    animBoss = new Animation("../resource/Enemy_boss/run/%1.png", "../resource/Enemy_boss/is_hit/%1.png", 8, 14, IMG_INTERVAL, 1);

    animPlayer = new Animation("../resource/Player/run/%1.png", "../resource/Player/walk/%1.png", 6, 11, IMG_INTERVAL, 2);

    boss = Boss(animBoss);

    player = new Player(640, 360, animPlayer, 12);
    setFocusPolicy(Qt::StrongFocus);

    addObstacles(); // 添加障碍物
}

GameWidget::~GameWidget() {
    delete animLeftSmall;
    delete animRightSmall;
    delete animBoss;
    delete player; // 记得释放 player
}

void GameWidget::addObstacles() {
    obstacles.append(QRect(50, 100, 50, 50));
    obstacles.append(QRect(400, 400, 50, 50));
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    background.draw(&painter, rect());

    for (Common& common : smallObjects) {
        common.draw(painter, 1000 / 144, playerSignal);
        for (const QRect& obstacle : obstacles) common.checkCollision(obstacle);
    }

    for (const QRect& obstacle : obstacles) {
        painter.fillRect(obstacle, Qt::red);
    }

    boss.draw(painter, 1000 / 144, player);
    // painter.drawImage(200, 300, background.obstacleImage);
    player->draw(painter, 1000 / 144);
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            player->moveLeft(obstacles);
            break;
        case Qt::Key_Right:
            player->moveRight(obstacles);
            break;
        case Qt::Key_Up:
            player->moveUp(obstacles);
            break;
        case Qt::Key_Down:
            player->moveDown(obstacles);
            break;
        case Qt::Key_S:
            player->attack();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void GameWidget::updateGame() {
    if (std::rand() % 100 < 2) {
        int startY = std::rand() % 720;
        if (startY >= 200 && startY <= 600) {
            smallObjects.emplace_back(0, startY, animLeftSmall, animRightSmall);
        }
    }

    testLoop++;

    if (testLoop % 500 == 0) {
        playerSignal = 80;
    } else {
        if (playerSignal > 0) {
            playerSignal--;
        }
    }

    for (auto it = smallObjects.begin(); it != smallObjects.end();) {
        if (it->hasFinishedHitAnimation()) {
            it = smallObjects.erase(it);
        } else {
            ++it;
        }
    }

    for (Common& small : smallObjects) {
        if (playerSignal == 0) {
            small.move();
        }
    }

    boss.checkHurt(player);
    boss.move(player);

    update();
}
