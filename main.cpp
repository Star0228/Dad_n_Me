#include <QApplication>
#include "ModelView/GameViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GameViewModel gameWidget;
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}

//#include "main.moc"
