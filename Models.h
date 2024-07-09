//
// Created by Thorin on 2024/7/9.
//
#pragma once

#include <QImage>
#include <QHash>
#include <QString>
#include <vector>
#include <cmath>
#include <QDebug>

const int SMALL_AY_NUM = 8;
const int IMG_INTERVAL = 30;

struct Point {
    float x;
    float y;
};

class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    QImage getImage(const QString& path) {
        if (!imageCache.contains(path)) {
            QImage image(path);
            if (image.isNull()) {
                qDebug() << "Failed to load image:" << path;
            } else {
                imageCache[path] = image;
            }
        }
        return imageCache.value(path);
    }

private:
    ResourceManager() {}
    ~ResourceManager() = default;

    QHash<QString, QImage> imageCache;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
};

class Animation {
public:
    int interval;
    std::vector<QImage> runFrameList;
    std::vector<QImage> hitFrameList;
    std::vector<QImage> attackFrameList;

    Animation(const QString& pathRun, const QString& pathHit, int numRun, int numHit, int interval, int attackFrames = 0)
        : interval(interval)
    {
        for (int i = 1; i <= numRun; ++i) {
            QString pathFile = pathRun.arg(i);
            QImage frame = ResourceManager::getInstance().getImage(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load run frame:" << pathFile;
            }
            runFrameList.push_back(frame);
        }
        for (int i = 1; i <= numHit; ++i) {
            QString pathFile = pathHit.arg(i);
            QImage frame = ResourceManager::getInstance().getImage(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load hit frame:" << pathFile;
            }
            hitFrameList.push_back(frame);
        }

        if (attackFrames == 1) {
            for (int i = 1; i <= 14; ++i) {
                QString pathFile = QString("../img_boss_attack/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
            }
        }
        else if (attackFrames == 2) {
            for (int i = 1; i <= 21; ++i) {
                QString pathFile = QString("../img_player_attack/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
            }
        }
    }

    int getInterval() const {
        return interval;
    }

    int getRunFrameCount() const {
        return runFrameList.size();
    }

    int getHitFrameCount() const {
        return hitFrameList.size();
    }

    int getAttackFrameCount() const {
        return attackFrameList.size();
    }
};

class Player {
public:
    Animation* anim;
    Point position;
    float speed;
    bool facingRight;
    int timer = 0;

    int idxRunFrame = 0;
    int idxAttackFrame = 0;

    bool isAttacking = false;
    int attackFrameCounter = 0;

    Player(float startX, float startY, Animation* playerAnim, int speed)
        : position{startX, startY}, anim(playerAnim), speed(speed), facingRight(true) {}

    void moveLeft() {
        position.x -= speed;
        facingRight = false;
    }

    void moveRight() {
        position.x += speed;
        facingRight = true;
    }

    void moveUp() {
        position.y -= speed;
    }

    void moveDown() {
        position.y += speed;
    }

    void attack() {
        isAttacking = true;
        timer = 0;
        idxAttackFrame = 0;
        attackFrameCounter = 21;
    }

    Point getPosition() const {
        return position;
    }
};

class Small {
public:
    const float SPEED = 2;
    Animation* animLeft;
    Animation* animRight;
    Point position{};

    int isHit = 0;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

public:
    Small(float startX, float startY, Animation* animLeft, Animation* animRight)
        : position{startX, startY}, animLeft(animLeft), animRight(animRight) {}

    Small(Small&& other) noexcept
        : animLeft(nullptr), animRight(nullptr) {
        *this = std::move(other);
    }

    Small& operator=(Small&& other) noexcept {
        if (this != &other) {
            position = other.position;
            isHit = other.isHit;
            animLeft = std::exchange(other.animLeft, nullptr);
            animRight = std::exchange(other.animRight, nullptr);
            timer = other.timer;
            idxRunFrame = other.idxRunFrame;
            idxHitFrame = other.idxHitFrame;
            isHit = other.isHit;
        }
        return *this;
    }

    void move() {
        position.x += SPEED;
    }

    bool hasFinishedHitAnimation() const {
        return isHit && idxHitFrame == animLeft->getHitFrameCount() - 1;
    }

    Point getPosition() const {
        return position;
    }
};

class Boss {
public:
    const float SPEED = 1;
    Animation* anim;
    Point position{};

    int currentBlood = 100;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;
    int idxAttackFrame = 0;

    bool facingRight = true;

    bool isHit = false;
    int hitFrameCount = 0;

public:
    Boss(Animation* animBoss)
        : anim(animBoss)
    {
        position.x = 1100;
        position.y = 300;
    }

    Boss(Boss&& other) noexcept
        : anim(std::exchange(other.anim, nullptr)),
          position(other.position),
          currentBlood(other.currentBlood),
          timer(other.timer),
          idxRunFrame(other.idxRunFrame),
          idxHitFrame(other.idxHitFrame),
          idxAttackFrame(other.idxAttackFrame)
    {}

    Boss& operator=(Boss&& other) noexcept {
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

    void move(Player* player) {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dx < 0) {
            facingRight = true;
        } else {
            facingRight = false;
        }
        if (dist < 120) {
            facingRight = true;
            return;
        }

        position.x -= SPEED * dx / dist;
        position.y -= SPEED * dy / dist;
    }

    void checkHurt(Player* player) {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (player->isAttacking && dist < 300) {
            currentBlood -= 10;
            isHit = true;
            hitFrameCount = 14;
        }
    }
};

