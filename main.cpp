#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <vector>
#include <cmath>
#include <QKeyEvent>

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
    int interval = 0;

    std::vector<QImage> runFrameList;

public:
    Animation(const QString& pathRun, int numRun, int interval)
        : interval(interval)
    {
        for (int i = 0; i < numRun; ++i) {
            QString pathFile = pathRun.arg(i);
            QImage frame(pathFile);
            if (frame.isNull()) {
                qDebug() << "无法加载跑动帧:" << pathFile;
            }
            runFrameList.push_back(frame);
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
};

class Small {
private:
    const int SPEED = 2;
    Animation* animLeft;
    Point position = {0, 500};
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

public:
    Small() {
        animLeft = new Animation("../img_small/left_%1.png", 8, IMG_INTERVAL);
    }

    ~Small() {
        delete animLeft;
    }

    void setMoveLeft(bool value) { moveLeft = value; }
    void setMoveRight(bool value) { moveRight = value; }
    void setMoveUp(bool value) { moveUp = value; }
    void setMoveDown(bool value) { moveDown = value; }

    void move() {
        if (moveLeft) {
            position.x -= SPEED;
        }
        if (moveRight) {
            position.x += SPEED;
        }
        if (moveUp) {
            position.y -= SPEED;
        }
        if (moveDown) {
            position.y += SPEED;
        }
    }

    void draw(QPainter& painter, int delta) {
        animLeft->displayRun(painter, position.x, position.y, delta);
    }
};

class GameWidget : public QWidget {
    Q_OBJECT

private:
    QImage background;
    Small test1;
    int testLoop = 0;
    QTimer* timer;

public:
    GameWidget(QWidget* parent = nullptr) : QWidget(parent), background("test.png") {
        if (background.isNull()) {
            qDebug() << "无法加载背景图片!";
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
        timer->start(1000 / 144);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        qDebug() << "paintEvent 触发";
        QPainter painter(this);
        painter.drawImage(0, 0, background);
        test1.draw(painter, 1000 / 144);
    }

    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key()) {
        case Qt::Key_W:
            test1.setMoveUp(true);
            break;
        case Qt::Key_A:
            test1.setMoveLeft(true);
            break;
        case Qt::Key_S:
            test1.setMoveDown(true);
            break;
        case Qt::Key_D:
            test1.setMoveRight(true);
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        switch (event->key()) {
        case Qt::Key_W:
            test1.setMoveUp(false);
            break;
        case Qt::Key_A:
            test1.setMoveLeft(false);
            break;
        case Qt::Key_S:
            test1.setMoveDown(false);
            break;
        case Qt::Key_D:
            test1.setMoveRight(false);
            break;
        default:
            QWidget::keyReleaseEvent(event);
        }
    }

private slots:
    void updateGame() {
        testLoop++;
        test1.move();
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

