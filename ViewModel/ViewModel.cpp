#include "../ViewModel/ViewModel.h"


void GameViewModel::handleKeyLeft() {
    player.setIsMove(true);
    player.moveLeft(*obstacles);
}

void GameViewModel::handleKeyRight() {
    player.setIsMove(true);
    player.moveRight(*obstacles);
}

void GameViewModel::handleKeyUp() {
    player.setIsMove(true);
    player.moveUp(*obstacles);
}

void GameViewModel::handleKeyDown() {
    player.setIsMove(true);
    player.moveDown(*obstacles);
}

void GameViewModel::handleKeyS() {
    player.setIsMove(true);
    player.attack(background);
}

void GameViewModel::handleKeyRelease() {
    player.setIsMove(false);
}

void GameViewModel::updateGame() {
    // 更新游戏状态
    emit gameUpdated();
}

void GameViewModel::resetGame() {
    background.reset();
    player.reset();
    smallEnemies.clear();
    boss.reset();
}

Background* GameViewModel::getBackground() {
    return &background;
}

Player* GameViewModel::getPlayer() {
    return &player;
}

std::map<int,Simple>* GameViewModel::getSmallEnemies() {
    return &smallEnemies;
}

Boss* GameViewModel::getBoss() {
    return &boss;
}

QVector<QRect>* GameViewModel::getObstacles() {
    return obstacles;
}