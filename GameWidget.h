//
// Created by Thorin on 2024/7/9.
//

#pragma once

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "viewmodel.h"

class GameWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameWidget(GameViewModel* viewModel, QWidget* parent = nullptr)
        : QWidget(parent), viewModel(viewModel) {
        connect(viewModel, &GameViewModel::gameUpdated, this, QOverload<>::of(&GameWidget::update));
        setFocusPolicy(Qt::StrongFocus);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        drawBackground(&painter);
        drawPlayer(&painter);
        drawSmallEnemies(&painter);
        drawBoss(&painter);
    }

    void keyPressEvent(QKeyEvent* event) override {
        viewModel->handleKeyPress(event->key());
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        viewModel->handleKeyRelease(event->key());
    }

private:
    void drawBackground(QPainter* painter) {
        // 假设你有一个背景图片
        painter->drawImage(0, 0, QImage("background.png"));
    }

    void drawPlayer(QPainter* painter) {
        Player* player = viewModel->getPlayer();
        if (player) {
            QImage frame = player->anim->runFrameList[0];  // 使用第一个帧作为示例
            painter->drawImage(player->position.x, player->position.y, frame);
        }
    }

    void drawSmallEnemies(QPainter* painter) {
        auto& smallEnemies = viewModel->getSmallEnemies();
        for (auto& small : smallEnemies) {
            QImage frame = small.animLeft->runFrameList[0];  // 使用第一个帧作为示例
            painter->drawImage(small.position.x, small.position.y, frame);
        }
    }

    void drawBoss(QPainter* painter) {
        Boss* boss = viewModel->getBoss();
        if (boss) {
            QImage frame = boss->anim->runFrameList[0];  // 使用第一个帧作为示例
            painter->drawImage(boss->position.x, boss->position.y, frame);
        }
    }

    GameViewModel* viewModel;
};
