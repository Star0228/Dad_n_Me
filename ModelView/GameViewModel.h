#ifndef DAD_N_ME_GAMEWIDGET_H
#define DAD_N_ME_GAMEWIDGET_H


#pragma once

#include <cmath>
#include <vector>
#include "../Model/Structure.h"
#include <QObject>
#include <QTimer>
#include <QVector>
#include <vector>
#include "../View/Animation.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr);
    ~GameViewModel();

    Player* getPlayer() const { return player; }
    const std::vector<Common>& getSmallEnemies() const { return smallObjects; }
    Boss* getBoss() const { return &boss; }

public slots:
    void handleKeyPress(int key);
    void handleKeyRelease(int key);

signals:
    void gameUpdated();

private slots:
    void updateGame();

private:
    void addObstacles();

    Background background;
    std::vector<Common> smallObjects;
    Boss boss;
    QVector<QRect> obstacles;
    Animation* animPlayer;
    Player* player;
    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;
    Animation* animLeftSmall;
    Animation* animRightSmall;
    Animation* animBoss;
};

#endif //DAD_N_ME_GAMEWIDGET_H
