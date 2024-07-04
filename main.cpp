#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QStringList>
#include <QPainter> // 添加 QPainter 头文件

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 创建主窗口
    QWidget window;
    window.setWindowTitle("Image Walk Example");
    window.resize(800, 600); // 调整窗口大小

    // 创建一个标签来显示图片
    QLabel *imageLabel = new QLabel(&window);
    imageLabel->setAlignment(Qt::AlignCenter);  // 设置图片对齐方式为居中

    // 存储图片路径
    QStringList imagePaths = {
        "./resource/Enemy/run_r/1.png",
        "./resource/Enemy/run_r/2.png",
        "./resource/Enemy/run_r/3.png",
        "./resource/Enemy/run_r/4.png",
        "./resource/Enemy/run_r/5.png",
        "./resource/Enemy/run_r/6.png",
        "./resource/Enemy/run_r/7.png",
        "./resource/Enemy/run_r/8.png"
    };

    // 当前显示的图片索引
    int currentImageIndex = 0;
    int xOffset = 0;  // 用于记录图片的水平偏移量
    int yOffset = 0;  // 用于记录图片的垂直偏移量

    // 创建一个定时器，每隔一段时间更新一次图片
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        QPixmap pixmap(imagePaths[currentImageIndex]);
        if (!pixmap.isNull()) {
            // 调整图片的显示大小，以窗口的大小为准
            QPixmap scaledPixmap = pixmap.scaled(window.size(), Qt::KeepAspectRatio);

            // 计算在窗口内的偏移量
            xOffset += 5;  // 每次水平方向移动5个像素
            yOffset += 5;  // 每次垂直方向移动5个像素

            // 当偏移量超过窗口边界时，重置偏移量
            if (xOffset > window.width()) {
                xOffset = -scaledPixmap.width();  // 从窗口左侧开始显示
            }
            if (yOffset > window.height()) {
                yOffset = -scaledPixmap.height();  // 从窗口顶部开始显示
            }

            // 创建裁剪后的图像
            QPixmap croppedPixmap = scaledPixmap.copy(0, 0, scaledPixmap.width(), scaledPixmap.height());
            QPainter painter(&croppedPixmap); // 创建 QPainter 对象

            // 根据偏移量调整图像位置
            painter.translate(xOffset, yOffset);

            // 设置裁剪后的图像到标签
            imageLabel->setPixmap(croppedPixmap);
        }

        // 切换到下一张图片
        currentImageIndex = (currentImageIndex + 1) % imagePaths.size();
    });

    // 启动定时器，间隔时间为50毫秒
    timer.start(50);

    // 创建一个垂直布局并添加图片标签
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);

    // 将布局设置为主窗口的布局
    window.setLayout(layout);

    // 显示主窗口
    window.show();

    return QApplication::exec();
}