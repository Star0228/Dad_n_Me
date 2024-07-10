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

class GameViewModel : public QWidget {
    Q_OBJECT

public:
    explicit GameViewModel(QWidget* parent = nullptr);
    ~GameViewModel() override;

    Player* getPlayer() const { return player; }
    const QVector<Common>& getSmallEnemies() const { return smallObjects; }
    Boss* getBoss() const { return boss; }
    Background *getBackground() const {return background; }
public slots:
    void handleKeyPress(int key);
    void handleKeyRelease(int key);

signals:
    void gameUpdated();

public slots:
    void updateGame();

private:
    void addObstacles();

    QVector<Common> smallObjects;
    Boss* boss;
    Background* background;
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
