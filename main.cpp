
#include <QApplication>
#include "ModelView/GameWidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GameWidget gameWidget;
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}

//#include "main.moc"
