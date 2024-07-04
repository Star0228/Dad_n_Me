
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <vector>
#include <cmath>

const int SMALL_AY_NUM = 8;
const int IMG_INTERVAL = 30;

struct Point {
    int x;
    int y;
};

class Animation {
private:
    int timer = 0;
    int idxRunFrame = 0;
    int idxHitFrame = 0;
    int interval = 0;

    std::vector<QImage> runFrameList;
    std::vector<QImage> hitFrameList;

public:
    Animation(const QString& pathRun, const QString& pathHit, int numRun, int numHit, int interval)
        : interval(interval)
    {
        for (int i = 0; i < numRun; ++i) {
            QString pathFile = pathRun.arg(i);
            QImage frame(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load run frame:" << pathFile;
            }
            runFrameList.push_back(frame);
        }
        for (int i = 0; i < numHit; ++i) {
            QString pathFile = pathHit.arg(i);
            QImage frame(pathFile);
            if (frame.isNull()) {
                qDebug() << "Failed to load hit frame:" << pathFile;
            }
            hitFrameList.push_back(frame);
        }
    }

    void displayRun(QPainter& painter, int x, int y, int delta) {
        timer += delta;
        if (timer >= interval) {
            idxRunFrame = (idxRunFrame + 1) % runFrameList.size();
            timer = 0;
        }
        painter.drawImage(x, y, runFrameList[idxRunFrame]);
    }

    void displayHit(QPainter& painter, int x, int y, int delta) {
        timer += delta;
        if (timer >= interval + 20) {
            idxHitFrame = (idxHitFrame + 1) % hitFrameList.size();
            timer = 0;
        }
        painter.drawImage(x, y, hitFrameList[idxHitFrame]);
    }
};

class Small {
private:
    const int SPEED = 2;
    Animation* animLeft;
    Animation* animRight;
    Point position = {0, 500};

public:
    Small() {
        animLeft = new Animation("../img_small/left_%1.png", "../img_small/right_hit_%1.png", 8, 4, IMG_INTERVAL);
        animRight = new Animation("../img_small/right_%1.png", "../img_small/right_hit_%1.png", 8, 4, IMG_INTERVAL);
    }

    ~Small() {
        delete animLeft;
        delete animRight;
    }

    void move() {
        position.x += SPEED;
    }

    void draw(QPainter& painter, int delta, int playerSignal) {
        if (playerSignal > 0) {
            animLeft->displayHit(painter, position.x, position.y, delta);
        } else {
            animLeft->displayRun(painter, position.x, position.y, delta);
        }
    }
};

class GameWidget : public QWidget {
    Q_OBJECT

private:
    QImage background;
    Small test1;
    int testLoop = 0;
    int playerSignal = 0;
    QTimer* timer;

public:
    GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png") {
        if (background.isNull()) {
            qDebug() << "Failed to load background image!";
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        qDebug() << "paintEvent triggered";
        QPainter painter(this);
        painter.drawImage(0, 0, background);
        test1.draw(painter, 1000 / 144, playerSignal);
    }

private slots:
    void updateGame() {
        testLoop++;

        if (testLoop % 100 == 0) {
            playerSignal = 24;
        } else {
            if (playerSignal > 0) {
                playerSignal--;
            }
        }

        if (playerSignal == 0) {
            test1.move();
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
