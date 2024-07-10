#ifndef VIEW_H
#define VIEW_H

#pragma once

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "../ModelView/GameViewModel.h"
#include "../Model/Structure.h"

class View : public QWidget {
    Q_OBJECT

public:
    explicit View(QWidget* parent = nullptr);
    GameViewModel *viewModel;
    QTimer* timer;
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private slots:
    void update();
private:
    void draw(Background *background, QPainter* painter, int delta);
    void draw(Player* player, QPainter* painter, int delta);
    void draw(const QVector<Common>& smallEnemies, QPainter* painter, int delta);
    void draw(Boss* boss, QPainter* painter, int delta);
};

#endif // VIEW_H
