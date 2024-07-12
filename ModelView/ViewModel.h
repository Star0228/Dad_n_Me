#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "../Model/Player.h"
#include "../Model/Boss.h"
#include "../Model/Common.h"
#include "../Model/Background.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr)
        : QObject(parent) {

        std::vector<Common> smallEnemies;
        Boss boss;
        obstacles = new QVector<QRect> ;
        Background background = Background(Qt::blue);
        Player player(640, 360, 12);

        if (&background && obstacles) {
            background.addObstacles(obstacles); // 添加障碍物
        }
    }
    // void handleKeyPress(int key);
    // void handleKeyRelease(int key);
    // void updateGame();

    Background* getBackground();
    Player* getPlayer();
    std::vector<Common>* getSmallEnemies();
    Boss* getBoss();
    QVector<QRect>* getObstacles();
    signals:
        void gameUpdated();

    public slots:
        void handleKeyLeft();
        void handleKeyRight();
        void handleKeyUp();
        void handleKeyDown();
        void handleKeyS();
        void handleKeyRelease(int key);
        void updateGame();

private:
    Background background;
    Player player;
    std::vector<Common> smallEnemies;
    Boss boss;
    QVector<QRect>* obstacles;
};

#endif //VIEWMODEL_H
