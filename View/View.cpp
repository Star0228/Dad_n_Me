#include "View.h"

View::View(QWidget* parent)
    : QWidget(parent){
    viewModel = new GameViewModel;
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &View::update);
    timer->start(1000 / 144);
    //common build
    setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
}


void View::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    std::cout << "fuck" << std::endl;
    draw(viewModel->getBackground(), &painter, 1000/288);
    draw(viewModel->getPlayer(), &painter, 1000/288);
    draw(viewModel->getSmallEnemies(), &painter, 1000/288);
    draw(viewModel->getBoss(), &painter, 1000/288);
}

void View::keyPressEvent(QKeyEvent* event) {
    viewModel->handleKeyPress(event->key());
}

void View::keyReleaseEvent(QKeyEvent* event) {
    viewModel->handleKeyRelease(event->key());
}

void View::draw(Background *background, QPainter* painter, int delta = 1000/288) {
    painter->drawImage(0, 0, QImage("background.png"));
}

void View::draw(Player* player, QPainter* painter, int delta = 1000/288) {
    if (player) {
        QImage frame = player->anim->runFrameList[(player->idxRunFrame++)%6];  // Use the first frame as an example
        painter->drawImage(player->position.x, player->position.y, frame);
    }
}

void View::draw(const QVector<Common>& smallEnemies, QPainter* painter, int delta = 1000/288) {
    for (const auto& small : smallEnemies) {
        QImage frame = small.animLeft->runFrameList[0];  // Use the first frame as an example
        painter->drawImage(small.position.x, small.position.y, frame);
    }
}

void View::draw(Boss* boss, QPainter* painter, int delta = 1000/288) {
    if (boss) {
        QImage frame = boss->anim->runFrameList[boss->idxRunFrame++];  // Use the first frame as an example
        painter->drawImage(boss->position.x, boss->position.y, frame);
    }
}


void View::update() {
    viewModel->updateGame();
}
