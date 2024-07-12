#include "../ModelView/ViewModel.h"

void GameViewModel::handleKeyLeft() {
    player.moveLeft(*obstacles);
}

void GameViewModel::handleKeyRight() {
    player.moveRight(*obstacles);
}

void GameViewModel::handleKeyUp() {
    player.moveUp(*obstacles);
}

void GameViewModel::handleKeyDown() {
    player.moveDown(*obstacles);
}

void GameViewModel::handleKeyS() {
    player.attack();
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