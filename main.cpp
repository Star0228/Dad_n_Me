
#include <QApplication>
#include "View/GameWidget.h"
#include "ViewModel/ViewModel.h"

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

    QObject::connect(&gameWidget, &GameWidget::KeyLeft, &viewModel, &GameViewModel::handleKeyLeft);
    QObject::connect(&gameWidget, &GameWidget::KeyRight, &viewModel, &GameViewModel::handleKeyRight);
    QObject::connect(&gameWidget, &GameWidget::KeyUp, &viewModel, &GameViewModel::handleKeyUp);
    QObject::connect(&gameWidget, &GameWidget::KeyDown, &viewModel, &GameViewModel::handleKeyDown);
    QObject::connect(&gameWidget, &GameWidget::KeyS, &viewModel, &GameViewModel::handleKeyS);
    return app.exec();
}


#include "main.moc"
