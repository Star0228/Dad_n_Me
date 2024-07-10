#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "../Model/Player.h"
#include "../Model/Boss.h"
#include "../Model/Common.h"
#include "../Model/Background.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr, Player* p = nullptr, Boss* b = nullptr, Background* bg = nullptr, QVector<QRect>* obs = nullptr, std::vector<Common>* co = nullptr)
        : QObject(parent), player(p), boss(b), background(bg), obstacles(obs), smallEnemies(co) {}
    void handleKeyPress(int key);
    void handleKeyRelease(int key);
    void updateGame();

    Background* getBackground();
    Player* getPlayer();
    std::vector<Common>* getSmallEnemies();
    Boss* getBoss();

    signals:
        void gameUpdated();

private:
    Background* background;
    Player* player;
    std::vector<Common>* smallEnemies;
    Boss* boss;
    QVector<QRect>* obstacles; // 指针类型
};

#endif //VIEWMODEL_H
