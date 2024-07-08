
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <vector>
#include <cmath>
#include <QHash>
#include <cstdlib>
#include <QKeyEvent>

const int SMALL_AY_NUM = 8;
const int IMG_INTERVAL = 30;

struct Point {
    int x;
    int y;
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


    Animation(const QString& pathRun, const QString& pathHit, int numRun, int numHit, int interval, bool hasAttackFrames = false)
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

        if (hasAttackFrames) {
            // 初始化攻击帧列表
            // boss的攻击帧数为14
            for (int i = 1; i <= 14; ++i) {
                QString pathFile = QString("../img_boss_hit/%1.png").arg(i);
                QImage frame = ResourceManager::getInstance().getImage(pathFile);
                if (frame.isNull()) {
                    qDebug() << "Failed to load attack frame:" << pathFile;
                }
                attackFrameList.push_back(frame);
            }
        }
    }

    void displayRun(QPainter& painter, int x, int y, int timer, int idxRunFrame) {
        if (runFrameList.empty()) return;
        painter.drawImage(x, y, runFrameList[idxRunFrame]);
    }

    void displayHit(QPainter& painter, int x, int y, int timer, int idxHitFrame) {
        if (hitFrameList.empty()) return;
        painter.drawImage(x, y, hitFrameList[idxHitFrame]);
    }

    void displayAttack(QPainter& painter, int x, int y, int timer, int idxAttackFrame) {
        if (attackFrameList.empty()) return;
        painter.drawImage(x, y, attackFrameList[idxAttackFrame]);
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




class Small {
private:
    const int SPEED = 2;
    Animation* animLeft;
    Animation* animRight;
    Point position{};

    int isHit = 0;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

public:
    Small(int startX, int startY, Animation* animLeft, Animation* animRight)
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
    const int SPEED = 2;
    Animation* anim;
    Point position{};

    int currentBlood = 100;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;
    int idxAttackFrame = 0;

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
    {
        // Additional members to move if needed
    }

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

    void draw(QPainter& painter, int delta, int playerSignal) {
        timer += delta;
        if (1)
        {
            if (timer >= anim->getInterval()) {
                idxHitFrame = (idxHitFrame + 1) % anim->getAttackFrameCount();
                timer = 0;
            }
            anim->displayAttack(painter, position.x, position.y, timer, idxHitFrame);
        }
    }
};


class Player {
private:
    Animation* playerRun;
    Point position;
    int speed;
    bool facingRight;
    int timer = 0;
    int idxRunFrame = 0;

public:
    Player(int startX, int startY, Animation* playerRun, int speed)
        : position{startX, startY}, playerRun(playerRun), speed(speed), facingRight(true) {}

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

    void draw(QPainter& painter, int delta) {
        timer += delta;
        if (timer >= playerRun->getInterval()) {
            idxRunFrame = (idxRunFrame + 1) % playerRun->getRunFrameCount();
            timer = 0;
        }

        QImage frame = playerRun->runFrameList[idxRunFrame];
        if (!facingRight) {
            frame = frame.mirrored(true, false); // 左右翻转
        }
        painter.drawImage(position.x, position.y, frame);
    }

    Point getPosition() const {
        return position;
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
    Animation* playerRun;
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

        animBoss = new Animation("../img_boss_run/%1.png", "../img_boss_hit/hit_%1.png", 8, 14, IMG_INTERVAL, true);

        playerRun = new Animation("../resource/Player/run_r/%1.png", "../resource/Player/walk_r/%1.png", 6, 11, IMG_INTERVAL);

        boss = Boss(animBoss);

        player = new Player(640, 360, playerRun, 5); // 初始化玩家位置和速度
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
            small.draw(painter, 1000 / 144, playerSignal);
        }

        boss.draw(painter, 1000 /144, playerSignal);

        player->draw(painter, 1000 / 144); // 绘制玩家
    }

    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key()) {
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
