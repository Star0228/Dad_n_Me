#include "../ModelView/ViewModel.h"
#include <iostream>
void GameViewModel::handleKeyPress(int key) {
    //std::cout << obstacles.size() << std::endl;
    switch (key) {

        case Qt::Key_Left:
            player.moveLeft(*obstacles);
        break;
        case Qt::Key_Right:
            player.moveRight(*obstacles);
        break;
        case Qt::Key_Up:
            player.moveUp(*obstacles);
        break;
        case Qt::Key_Down:
            player.moveDown(*obstacles);
        break;
        case Qt::Key_S:
            player.attack();
        break;
    }
}

void GameViewModel::handleKeyRelease(int key) {
    // 根据需要处理按键释放事件
}

void GameViewModel::updateGame() {
    // 更新游戏状态
    emit gameUpdated();
}

Background* GameViewModel::getBackground() {
    return &background;
}

Player* GameViewModel::getPlayer() {
    return &player;
}

std::vector<Common>* GameViewModel::getSmallEnemies() {
    return &smallEnemies;
}

Boss* GameViewModel::getBoss() {
    return &boss;
}

QVector<QRect>* GameViewModel::getObstacles() {
    return obstacles;
}