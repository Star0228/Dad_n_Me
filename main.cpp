
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
// private:
//     int interval;
//     std::vector<QImage> runFrameList;
//     std::vector<QImage> hitFrameList;

public:
    int interval;
    std::vector<QImage> runFrameList;
    std::vector<QImage> hitFrameList;
    Animation(const QString& pathRun, const QString& pathHit, int numRun, int numHit, int interval)
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
    }

    void displayRun(QPainter& painter, int x, int y, int timer, int idxRunFrame) {
        if (runFrameList.empty()) return;
        painter.drawImage(x, y, runFrameList[idxRunFrame]);
    }

    void displayHit(QPainter& painter, int x, int y, int timer, int idxHitFrame) {
        if (hitFrameList.empty()) return;
        painter.drawImage(x, y, hitFrameList[idxHitFrame]);
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


// class Small {
// private:
//     const int SPEED = 2;
//     Animation* animRun;
//     Point position;
//     int alive;
//
//     int timer = 0;
//     int idxRunFrame = 0;
//     int idxHitFrame = 0;
//
// public:
//     Small(int startX, int startY, Animation* animRun)
//         : position{startX, startY}, animRun(animRun) {}
//
//     void move() {
//         position.x += SPEED;
//     }
//
//     void draw(QPainter& painter, int delta, int playerSignal) {
//         timer += delta;
//         if (playerSignal > 0) {
//             if (timer >= animRun->getInterval()) {
//                 idxHitFrame = (idxHitFrame + 1) % animRun->getHitFrameCount();
//                 timer = 0;
//             }
//             animRun->displayHit(painter, position.x, position.y - 100, timer, idxHitFrame);
//         } else {
//             if (timer >= animRun->getInterval()) {
//                 idxRunFrame = (idxRunFrame + 1) % animRun->getRunFrameCount();
//                 timer = 0;
//             }
//             animRun->displayRun(painter, position.x, position.y, timer, idxRunFrame);
//         }
//     }
//
//     Point getPosition() const {
//         return position;
//     }
// };

class Small {
private:
    const int SPEED = 2;
    Animation* animRun;
    Point position;
    bool facingRight;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

public:
    Small(int startX, int startY, Animation* animRun)
        : position{startX, startY}, animRun(animRun), facingRight(true) {}

    void move() {
        position.x += SPEED;
    }

    void draw(QPainter& painter, int delta, int playerSignal) {
        timer += delta;
        if (playerSignal > 0) {
            if (timer >= animRun->getInterval()) {
                idxHitFrame = (idxHitFrame + 1) % animRun->getHitFrameCount();
                timer = 0;
            }
            QImage frame = animRun->hitFrameList[idxHitFrame];
            if (!facingRight) {
                frame = frame.mirrored(true, false); // 左右翻转
            }
            painter.drawImage(position.x, position.y - 100, frame);
        } else {
            if (timer >= animRun->getInterval()) {
                idxRunFrame = (idxRunFrame + 1) % animRun->getRunFrameCount();
                timer = 0;
            }
            QImage frame = animRun->runFrameList[idxRunFrame];
            if (!facingRight) {
                frame = frame.mirrored(true, false); // 左右翻转
            }
            painter.drawImage(position.x, position.y, frame);
        }
    }

    Point getPosition() const {
        return position;
    }

    void setFacingRight(bool facingRight) {
        this->facingRight = facingRight;
    }
};


class GameWidget : public QWidget {
    Q_OBJECT

private:
    QImage background;
    std::vector<Small> smallObjects;
    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;

    //Animation* animLeft;
    Animation* animRun;
    Animation* playerRun;
    Player* player;

public:
    GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png") {
        if (background.isNull()) {
            qDebug() << "Failed to load background image!";
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);
        animRun = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);
        playerRun = new Animation("../resource/Player/run_r/%1.png", "../resource/Player/walk_r/%1.png", 6, 11, IMG_INTERVAL);

        for (int i = 0; i < 5; ++i) {
            smallObjects.emplace_back(0, 100+i*100, animRun);
        }

        player = new Player(640, 360, playerRun, 5); // 初始化玩家位置和速度
        setFocusPolicy(Qt::StrongFocus); // 设置焦点策略以接收键盘事件
    }

    ~GameWidget() {
        delete animRun;
        delete playerRun;
        delete player;
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.drawImage(0, 0, background);

        for (Small& small : smallObjects) {
            small.draw(painter, 1000 / 144, playerSignal);
        }

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
        testLoop++;

        if (testLoop % 100 == 0) {
            playerSignal = 80;
        } else {
            if (playerSignal > 0) {
                playerSignal--;
            }
        }

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