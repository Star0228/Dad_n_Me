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
    window.setWindowTitle("Image and Button Example");
    window.resize(80000, 60000); // 调整窗口大小

    // // 创建一个按钮
    // QPushButton *button = new QPushButton("Hello world!", &window);

    // 创建一个标签来显示图片
    QLabel *imageLabel = new QLabel(&window);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // 设置图片对齐方式

    // 存储图片路径
    QStringList imagePaths = {
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\1.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\2.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\3.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\4.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\5.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\6.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\7.png",
        "E:\\new_proj\\Dad_n_Me\\resource\\Enemy\\run_r\\8.png"
    };

    // 当前显示的图片索引
    int currentImageIndex = 0;
    int xOffset = 0;  // 用于记录图片的水平偏移量

    // 创建一个定时器，每隔一段时间更新一次图片
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        QPixmap pixmap(imagePaths[currentImageIndex]);
        if (!pixmap.isNull()) {
            int width = pixmap.width();
            int height = pixmap.height();

            // 计算在窗口内的偏移量
            xOffset += 10;  // 每次移动10个像素
            if (xOffset > window.width()) {
                xOffset = -width;  // 从窗口左侧开始显示
            }
            currentImageIndex = (currentImageIndex + 1) % imagePaths.size();  // 切换到下一张图片
            // 创建裁剪后的图像
            QPixmap croppedPixmap = pixmap.copy(0, 0, width, height);
            QPainter painter(&croppedPixmap); // 创建 QPainter 对象

            // 根据偏移量调整图像位置
            painter.translate(xOffset, 0);

            // 设置裁剪后的图像到标签
            imageLabel->setPixmap(croppedPixmap);
        }
    });

    // 启动定时器，间隔时间为50毫秒
    timer.start(50);

    // 创建一个垂直布局并添加按钮和图片标签
    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(button);
    layout->addWidget(imageLabel);

    // 将布局设置为主窗口的布局
    window.setLayout(layout);

    // 显示主窗口
    window.show();


    return QApplication::exec();
}