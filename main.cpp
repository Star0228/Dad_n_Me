
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
private:
    int interval;
    std::vector<QImage> runFrameList;
    std::vector<QImage> hitFrameList;

public:
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




class Small {
private:
    const int SPEED = 2;
    Animation* animLeft;
    Animation* animRight;
    Point position;
    int alive;

    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;

public:
    Small(int startX, int startY, Animation* animLeft, Animation* animRight)
        : position{startX, startY}, animLeft(animLeft), animRight(animRight) {}

    void move() {
        position.x += SPEED;
    }

    void draw(QPainter& painter, int delta, int playerSignal) {
        timer += delta;
        if (playerSignal > 0) {
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


class GameWidget : public QWidget {
    Q_OBJECT

private:
    QImage background;
    std::vector<Small> smallObjects;
    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;

    Animation* animLeft;
    Animation* animRight;

public:
    GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png") {
        if (background.isNull()) {
            qDebug() << "Failed to load background image!";
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);

        animLeft = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);
        animRight = new Animation("../img_small/%1.png", "../img_small/hit_%1.png", 8, 14, IMG_INTERVAL);

        for (int i = 0; i < 5; ++i) {
            smallObjects.emplace_back(0, 100+i*100, animLeft, animRight);
        }
    }

    ~GameWidget() {
        delete animLeft;
        delete animRight;
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.drawImage(0, 0, background);

        for (Small& small : smallObjects) {
            small.draw(painter, 1000 / 144, playerSignal);
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

        /*smallObjects.erase(std::remove_if(smallObjects.begin(), smallObjects.end(),
                                          [](Small& small) { return small.getPosition().x > 1280; }),
                           smallObjects.end());
        */

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
