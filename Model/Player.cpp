#include "Structure.h"

Player::Player(float startX, float startY, Animation* playerAnim, int speed)
    : position{startX, startY}, anim(playerAnim), speed(speed), facingRight(true) {
    rect = QRect(position.x, position.y, 100, 300);
}

bool Player::checkCollision(const QRect& newRect, const QVector<QRect>& obstacles) {
    for (const QRect& obstacle : obstacles) {
        if (newRect.intersects(obstacle)) {
            return true;
        }
    }
    return false;
}

void Player::moveLeft(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(-speed, 0);
    if (!checkCollision(newRect, obstacles)) {
        position.x -= speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::moveRight(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(speed, 0);
    if (!checkCollision(newRect, obstacles)) {
        position.x += speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::moveUp(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(0, -speed);
    if (!checkCollision(newRect, obstacles)) {
        position.y -= speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::moveDown(const QVector<QRect>& obstacles) {
    QRect newRect = rect.translated(0, speed);
    if (!checkCollision(newRect, obstacles)) {
        position.y += speed;
        rect.moveTo(position.x, position.y);
    }
}

void Player::attack() {
    isAttacking = true;
    timer = 0;
    idxAttackFrame = 0;
    attackFrameCounter = 21;
}

void Player::draw(QPainter& painter, int delta) {
    timer += delta;

    if (attackFrameCounter == 20) {
        isAttacking = false;
    }

    if (attackFrameCounter > 0) {
        if (timer >= anim->getInterval()) {
            idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
            timer = 0;
            attackFrameCounter--;
        }
        anim->displayAttack(painter, position.x, position.y - 70, timer, idxAttackFrame, facingRight);
    } else {
        if (timer >= anim->getInterval()) {
            idxRunFrame = (idxRunFrame + 1) % anim->getRunFrameCount();
            timer = 0;
        }
        anim->displayRun(painter, position.x, position.y, timer, idxRunFrame, facingRight);
    }
}

Point Player::getPosition() const {
    return position;
}