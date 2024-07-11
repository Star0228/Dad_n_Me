#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "../Common/Player.h"
#include "../Common/Boss.h"
#include "../Common/Simple.h"
#include "../Common/Background.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr, Player* p = nullptr, Boss* b = nullptr, Background* bg = nullptr, QVector<QRect>* obs = nullptr, std::vector<Simple>* sp = nullptr)
        : QObject(parent), player(p), boss(b), background(bg), obstacles(obs), smallEnemies(sp) {}
    void handleKeyPress(int key);
    void handleKeyRelease(int key);
    void updateGame();

    Background* getBackground();
    Player* getPlayer();
    std::vector<Simple>* getSmallEnemies();
    Boss* getBoss();

    signals:
        void gameUpdated();

private:
    Background* background;
    Player* player;
    std::vector<Simple>* smallEnemies;
    Boss* boss;
    QVector<QRect>* obstacles; // 指针类型
};

#endif //VIEWMODEL_H
