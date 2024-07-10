#ifndef VIEW_H
#define VIEW_H
#pragma once

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "../ModelView/GameViewModel.h"
#include "../Model/structure.h"

class View : public QWidget {
    Q_OBJECT

public:
    explicit View(GameViewModel* viewModel, QWidget* parent = nullptr)
        : QWidget(parent), viewModel(viewModel) {
        connect(viewModel, &GameViewModel::gameUpdated, this, QOverload<>::of(&View::update));
        setFocusPolicy(Qt::StrongFocus);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        drawBackground(&painter);
        draw(viewModel->getPlayer(), &painter);
        draw(viewModel->getSmallEnemies(), &painter);
        draw(viewModel->getBoss(), &painter);
    }

    void keyPressEvent(QKeyEvent* event) override {
        viewModel->handleKeyPress(event->key());
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        viewModel->handleKeyRelease(event->key());
    }

private:
    void drawBackground(QPainter* painter) {
        painter->drawImage(0, 0, QImage("background.png"));
    }

    void draw(Player* player, QPainter* painter) {
        if (player) {
            QImage frame = player->anim->runFrameList[0];  // Use the first frame as an example
            painter->drawImage(player->position.x, player->position.y, frame);
        }
    }

    void draw(const QVector<Common>& smallEnemies, QPainter* painter) {
        for (const auto& small : smallEnemies) {
            QImage frame = small.animLeft->runFrameList[0];  // Use the first frame as an example
            painter->drawImage(small.position.x, small.position.y, frame);
        }
    }

    void draw(Boss* boss, QPainter* painter) {
        if (boss) {
            QImage frame = boss->anim->runFrameList[0];  // Use the first frame as an example
            painter->drawImage(boss->position.x, boss->position.y, frame);
        }
    }

    GameViewModel* viewModel;
};

#endif //VIEW_H
