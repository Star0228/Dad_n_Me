#include <QApplication>
#include "GameWidget.h"
#include "ViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 创建 ViewModel 对象
    GameViewModel viewModel;

    // 创建 GameWidget 并传递 ViewModel 对象
    GameWidget gameWidget(&viewModel);
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}
