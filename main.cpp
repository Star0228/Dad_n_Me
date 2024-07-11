
#include <QApplication>
#include "View/GameWidget.h"
#include "ModelView/ViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);



    int playerSignal = 0;
    View_draw view;
    /*ViewModel*/
    GameViewModel viewModel = GameViewModel(nullptr);
    /*View*/
    GameWidget gameWidget(nullptr,viewModel.getBackground(), viewModel.getSmallEnemies(), viewModel.getBoss(), viewModel.getObstacles(), viewModel.getPlayer(),  &playerSignal, &view);
    gameWidget.resize(1280, 720);
    gameWidget.show();

    return app.exec();
}


#include "main.moc"
