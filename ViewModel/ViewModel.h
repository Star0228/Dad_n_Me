#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "../Common//Player.h"
#include "../Common/Boss.h"
#include "../Common/Simple.h"
#include "../Common/Background.h"

class GameViewModel : public QObject {
    Q_OBJECT

public:
    explicit GameViewModel(QObject* parent = nullptr)
        : QObject(parent) {

        std::map<int,Simple> smallEnemies;
        Boss boss;
        obstacles = new QVector<QRect> ;
        Background background = Background(Qt::blue);
        Player player(640, 360, 12);

        if (&background && obstacles) {
            background.addObstacles(obstacles); // 添加障碍物
        }
    }

    Background* getBackground();
    Player* getPlayer();
    std::map<int,Simple>* getSmallEnemies();
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
        void handleKeyRelease();
        void updateGame();
        void resetGame();

private:
    Background background;
    Player player;
    std::map<int,Simple> smallEnemies;
    Boss boss;
    QVector<QRect>* obstacles;
};

#endif //VIEWMODEL_H
