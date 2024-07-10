#include "Structure.h"

Common::Common(float startX, float startY, Animation* animLeft, Animation* animRight)
    : position{startX, startY}, animLeft(animLeft), animRight(animRight) {}

Common::Common(Common&& other) noexcept
    : animLeft(nullptr), animRight(nullptr) {
    *this = std::move(other);
}

Common& Common::operator=(Common&& other) noexcept {
    if (this != &other) {
        position = other.position;
        isHit = other.isHit;
        animLeft = std::exchange(other.animLeft, nullptr);
        animRight = std::exchange(other.animRight, nullptr);
        timer = other.timer;
        idxRunFrame = other.idxRunFrame;
        idxHitFrame = other.idxHitFrame;
        isHit = other.isHit;
        isReversed = other.isReversed;
        speed = other.speed;
    }
    return *this;
}

void Common::move() {
    position.x += speed;
}

bool Common::hasFinishedHitAnimation() const {
    return isHit && idxHitFrame == animLeft->getHitFrameCount() - 1;
}

void Common::draw(QPainter& painter, int delta, int playerSignal) {
    timer += delta;
    if (playerSignal > 0) {
        isHit = 1;
    }
    if (isHit == 1) {
        if (timer >= animLeft->getInterval()) {
            idxHitFrame = (idxHitFrame + 1) % animLeft->getHitFrameCount();
            timer = 0;
        }
        animLeft->displayHit(painter, position.x, position.y - 100, timer, idxHitFrame);
    } else {
        if (timer >= animLeft->getInterval()) {
            idxRunFrame = (idxRunFrame + 1) % animLeft->getRunFrameCount();
            timer = 0;
        }
        animLeft->displayRun(painter, position.x, position.y, timer, idxRunFrame);
    }
}

Point Common::getPosition() const {
    return position;
}

void Common::checkCollision(const QRect& obstacle) {
    QRect playerRect(position.x, position.y, 10, 20);
    if (playerRect.intersects(obstacle)) {
        speed = -speed; // Reverse speed
        // isReversed = !isReversed; // Update reversed status
    }
}
