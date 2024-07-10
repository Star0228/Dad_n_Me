
#include <QApplication>
#include "View/GameWidget.h"
#include "ModelView/ViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    std::vector<Common> commons;
    Boss boss;
    QVector<QRect> obstacles;
    Background bg = Background(Qt::blue);
    Player player(640, 360, 12);
    int playerSignal = 0;
    View_draw view;
    /*ViewModel*/
    GameViewModel viewModel = GameViewModel(nullptr, &player, &boss, &bg, &obstacles, &commons);
    /*View*/
    GameWidget gameWidget(nullptr, &bg, &commons, &boss, &obstacles, &player, &playerSignal, &view, &viewModel);
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}


#include "main.moc"
