
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <cmath>
#include <vector>
#include <cmath>
#include <QHash>
#include <cstdlib>
#include <iostream>
#include <QKeyEvent>

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
    std::vector<QImage> attackFrameList; // 新添加的攻击动画帧列表


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

        if (attackFrames == 1) { // 此时表示需要载入Boss的攻击模组
            // 初始化攻击帧列表
            // boss的攻击帧数为14
            for (int i = 1; i <= 14; ++i) {
                QString pathFile = QString("../img_boss_attack/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
                //std::cout << attackFrameList.size() << std::endl;
            }
        }
        else if (attackFrames == 2) // 此时需要载入玩家的攻击模组
        {
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

    void displayRun(QPainter& painter, int x, int y, int timer, int idxRunFrame, bool facingRight = true) {
        if (runFrameList.empty()) return;
        QImage frame = runFrameList[idxRunFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }

    void displayHit(QPainter& painter, int x, int y, int timer, int idxHitFrame, bool facingRight = true) {
        if (hitFrameList.empty()) return;
        QImage frame = hitFrameList[idxHitFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
    }

    void displayAttack(QPainter& painter, int x, int y, int timer, int idxAttackFrame, bool facingRight = true) {
        if (attackFrameList.empty()) return;
        QImage frame = attackFrameList[idxAttackFrame];
        if (!facingRight)
        {
            frame = frame.mirrored(true, false);
        }
        painter.drawImage(x, y, frame);
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

    void draw(QPainter& painter, int delta) {
        timer += delta;

        if (attackFrameCounter == 20)
        {
            isAttacking = false;
        }

        //首先判定是否正在攻击
        if (attackFrameCounter > 0)
        {
            if (timer >= anim->getInterval()) {
                idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
                timer = 0;
                attackFrameCounter --;
            }
            anim->displayAttack(painter, position.x, position.y - 70, timer, idxAttackFrame, facingRight); // 调整了y方向参数来保证图片显示位置的一致性
        }
        else
        {
            if (timer >= anim->getInterval()) {
                idxRunFrame = (idxRunFrame + 1) % anim->getRunFrameCount();
                timer = 0;
            }
            anim->displayRun(painter, position.x, position.y, timer, idxRunFrame, facingRight);
        }
    }

    Point getPosition() const {
        return position;
    }
};


class Small {
private:
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

    // 移动构造函数
    Small(Small&& other) noexcept
        : animLeft(nullptr), animRight(nullptr) {
        *this = std::move(other);
    }

    // 移动赋值运算符
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


    void draw(QPainter& painter, int delta, int playerSignal) {
        timer += delta;
        if (playerSignal > 0)
        {
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

    Point getPosition() const {
        return position;
    }
};


class Boss
{
private:
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
        position.x=1100;
        position.y=300;
    }

    // 实现移动构造函数和移动赋值运算符
    Boss(Boss&& other) noexcept
        : anim(std::exchange(other.anim, nullptr)),
          position(other.position),
          currentBlood(other.currentBlood),
          timer(other.timer),
          idxRunFrame(other.idxRunFrame),
          idxHitFrame(other.idxHitFrame),
          idxAttackFrame(other.idxAttackFrame)
    {}

    // Move assignment operator
    Boss& operator=(Boss&& other) noexcept {
        if (this != &other) {
            anim = std::exchange(other.anim, nullptr);
            position = other.position;
            currentBlood = other.currentBlood;
            timer = other.timer;
            idxRunFrame = other.idxRunFrame;
            idxHitFrame = other.idxHitFrame;
            idxAttackFrame = other.idxAttackFrame;
            // Additional members to move if needed
        }
        return *this;
    }

    void move(Player* player)
    {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dx < 0)
        {
            facingRight = true;
        }else
        {
            facingRight = false;
        }
        if (dist < 120)
        {
            facingRight = true;
            return;
        }

        position.x -= SPEED * dx / dist;
        position.y -= SPEED * dy / dist;
    }

    void checkHurt(Player* player)
    {
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (player->isAttacking && dist < 300)
        {
            currentBlood -= 10;
            isHit = true;
            hitFrameCount = 14;
        }
    }

    void draw(QPainter& painter, int delta, Player* player)
    {
        // 计算boss和player的距离
        float dx = position.x - player->position.x;
        float dy = position.y - player->position.y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (hitFrameCount == 0)
        {
            isHit = false;
        }

        // 首先判断boss是否收到攻击
        timer += delta;
        if (isHit == true && hitFrameCount > 0)
        {
            if (timer >= anim->getInterval()) {
                idxHitFrame = (idxHitFrame + 1) % anim->getHitFrameCount();
                timer = 0;
                hitFrameCount --;
            }
            anim->displayHit(painter, position.x, position.y - 20, timer, idxHitFrame, facingRight);
        }
        else if (dist < 120)
        {
            if (timer >= anim->getInterval()) {
                idxAttackFrame = (idxAttackFrame + 1) % anim->getAttackFrameCount();
                timer = 0;
            }
            anim->displayAttack(painter, position.x, position.y, timer, idxAttackFrame, facingRight);
        }
        else
        {
            if (timer >= anim->getInterval()) {
                idxRunFrame = (idxRunFrame + 1) % anim->getRunFrameCount();
                timer = 0;
            }
            anim->displayRun(painter, position.x, position.y, timer, idxRunFrame, facingRight);
        }
    }
};






class GameWidget : public QWidget {
    Q_OBJECT

private:
    QImage background;

    //敌人
    std::vector<Small> smallObjects;
    Boss boss;

    //玩家
    Animation* animPlayer;
    Player* player;

    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;

    Animation* animLeftSmall;
    Animation* animRightSmall;
    Animation* animBoss;

public:
    explicit GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png"), boss(nullptr) {
        if (background.isNull()) {
            qDebug() << "Failed to load background image!";
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);

        animLeftSmall = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);
        animRightSmall = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);

        animBoss = new Animation("../img_boss_run/%1.png", "../img_boss_hit/%1.png", 8, 14, IMG_INTERVAL, 1);

        animPlayer = new Animation("../resource/Player/run_r/%1.png", "../resource/Player/walk_r/%1.png", 6, 11, IMG_INTERVAL, 2);

        boss = Boss(animBoss);

        player = new Player(640, 360, animPlayer, 12); // 初始化玩家位置和速度
        setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
    }

    ~GameWidget() override {
        delete animLeftSmall;
        delete animRightSmall;
        delete animBoss;
    }

protected:
    void paintEvent(QPaintEvent* event) override { //虚函数重写
        QPainter painter(this);
        painter.drawImage(0, 0, background);

        for (Small& small : smallObjects) {
            //small.draw(painter, 1000 / 144, playerSignal);
        }

        boss.draw(painter, 1000 /144, player);

        player->draw(painter, 1000 / 144); // 绘制玩家
    }

    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key())
        {
        case Qt::Key_Left:
            player->moveLeft();
            break;
        case Qt::Key_Right:
            player->moveRight();
            break;
        case Qt::Key_Up:
            player->moveUp();
            break;
        case Qt::Key_Down:
            player->moveDown();
            break;
        case Qt::Key_S:
            player->attack();
            break;
        }
    }

private slots:
    void updateGame() {
        //管理小怪的生成
        if (std::rand() % 100 < 2) { // 按概率生成小怪
            int startY = std::rand() % 720; // 随机生成 Y 坐标
            if (startY >= 200 && startY <= 600)
            {
                smallObjects.emplace_back(0, startY, animLeftSmall, animRightSmall);
            }
        }

        testLoop++;

        if (testLoop % 500 == 0) {
            playerSignal = 80;
        } else {
            if (playerSignal > 0) {
                playerSignal--;
            }
        }


        for (auto it = smallObjects.begin(); it != smallObjects.end();) {
            if (it->hasFinishedHitAnimation()) {
                it = smallObjects.erase(it); // 使用 erase 删除元素，并更新迭代器
            } else {
                ++it;
            }
        }


        // 移动所有未处于 hit 动画的 Small 对象
        for (Small& small : smallObjects) {
            if (playerSignal == 0) {
                small.move();
            }
        }

        boss.checkHurt(player);
        boss.move(player);

        update();
    }
};


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GameWidget gameWidget;
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}

#include "main.moc"
