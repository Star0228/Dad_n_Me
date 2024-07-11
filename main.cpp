
#include <QApplication>
#include "Common/Player.h"
#include "Common/Simple.h"
#include "Common/Boss.h"
#include "View/GameWidget.h"
#include "ViewModel/ViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Background bg;
    std::vector<Simple> simples;
    Boss boss;
    QVector<QRect> obstacles;
    Player player(640, 360, 12);
    int playerSignal = 0;
    View_draw view;
    /*View*/
    GameWidget gameWidget(nullptr, &bg, &simples, &boss, &obstacles, &player, &playerSignal, &view);
    /*ViewModel*/
    GameViewModel viewModel = GameViewModel(nullptr, &player, &boss, &bg, &obstacles, &simples);
            gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}


#include "main.moc"
