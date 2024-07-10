#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../View/Animation.h"
#include "../View/ResourceManager.h"

class Common {
public:
    const float SPEED = 2;
    float speed = SPEED; // Current speed, can be positive or negative
    Animation* animLeft;
    Animation* animRight;
    Point position{};

    int isHit = 0;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

    bool isReversed = false; // Whether the speed is reversed


    Common(float startX, float startY, Animation* animLeft, Animation* animRight);
    Common(Common&& other) noexcept;
    Common& operator=(Common&& other) noexcept;

    void move();
    bool hasFinishedHitAnimation() const;
    void draw(QPainter& painter, int delta, int playerSignal);
    Point getPosition() const;
    void checkCollision(const QRect& obstacle);
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
    QRect rect;
    bool isAttacking = false;
    int attackFrameCounter = 0;

    Player(float startX, float startY, Animation* playerAnim, int speed);

    bool checkCollision(const QRect& newRect, const QVector<QRect>& obstacles);
    void moveLeft(const QVector<QRect>& obstacles);
    void moveRight(const QVector<QRect>& obstacles);
    void moveUp(const QVector<QRect>& obstacles);
    void moveDown(const QVector<QRect>& obstacles);
    void attack();
    void draw(QPainter& painter, int delta);
    Point getPosition() const;
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

    Boss(Animation* animBoss);

    Boss(Boss&& other) noexcept;

    Boss& operator=(Boss&& other) noexcept;

    void move(Player* player);
    void checkHurt(Player* player);
    void draw(QPainter& painter, int delta, Player* player);
};



class Background {
public:
    QColor backgroundColor; // 背景颜色
    QImage obstacleImage;   // 障碍物图片
    bool obstaclePlaced;    // 是否已经放置障碍物

    Background(const QColor& color = Qt::gray);

    void draw(QPainter* painter, const QRectF& rect);
};

#endif //STRUCTURE_H
