#include "Structure.h"

Boss::Boss(Animation* animBoss)
    : anim(animBoss) {
    position.x = 1100;
    position.y = 300;
}

Boss::Boss(Boss&& other) noexcept
    : anim(std::exchange(other.anim, nullptr)),
      position(other.position),
      currentBlood(other.currentBlood),
      timer(other.timer),
      idxRunFrame(other.idxRunFrame),
      idxHitFrame(other.idxHitFrame),
      idxAttackFrame(other.idxAttackFrame) {}

Boss& Boss::operator=(Boss&& other) noexcept {
    if (this != &other) {
        anim = std::exchange(other.anim, nullptr);
        position = other.position;
        currentBlood = other.currentBlood;
        timer = other.timer;
        idxRunFrame = other.idxRunFrame;
        idxHitFrame = other.idxHitFrame;
        idxAttackFrame = other.idxAttackFrame;
    }
    return *this;
}

void Boss::move(Player* player) {
    float dx = position.x - player->position.x;
    float dy = position.y - player->position.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    facingRight = dx < 0;

    if (dist < 120) {
        return;
    }

    position.x -= SPEED * dx / dist;
    position.y -= SPEED * dy / dist;
}

void Boss::checkHurt(Player* player) {
    float dx = position.x - player->position.x;
    float dy = position.y - player->position.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (player->isAttacking && dist < 300) {
        currentBlood -= 10;
        isHit = true;
        hitFrameCount = 14;
    }
}

void Boss::draw(QPainter& painter, int delta, Player* player) {
    float dx = position.x - player->position.x;
    float dy = position.y - player->position.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (hitFrameCount == 0) {
        isHit = false;
    }

    timer += delta;
    if (isHit && hitFrameCount > 0) {
        if (timer >= anim->getInterval()) {
            idxHitFrame = (idxHitFrame + 1) % anim->getHitFrameCount();
            timer = 0;
            hitFrameCount--;
        }
        anim->displayHit(painter, position.x, position.y - 20, timer, idxHitFrame, facingRight);
    } else if (dist < 120) {
        if (timer >= anim->getInterval()) {
            idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
            timer = 0;
        }
        anim->displayAttack(painter, position.x, position.y, timer, idxAttackFrame, facingRight);
    } else {
        if (timer >= anim->getInterval()) {
            idxRunFrame = (idxRunFrame + 1) % anim->getRunFrameCount();
            timer = 0;
        }
        anim->displayRun(painter, position.x, position.y, timer, idxRunFrame, facingRight);
    }
}
