#include "ViewModel.h"

void GameViewModel::handleKeyPress(int key) {

}

void GameViewModel::handleKeyRelease(int key) {
    // 根据需要处理按键释放事件
}

void GameViewModel::updateGame() {
    // 更新游戏状态
    emit gameUpdated();
}

Background* GameViewModel::getBackground() {
    return background;
}

Player* GameViewModel::getPlayer() {
    return player;
}

std::vector<Simple>* GameViewModel::getSmallEnemies() {
    return smallEnemies;
}

Boss* GameViewModel::getBoss() {
    return boss;
}
