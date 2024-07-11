
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

    // Connect view signals to ViewModel slots
    QObject::connect(&gameWidget, &GameWidget::keyPressed, &viewModel, &GameViewModel::handleKeyPress);
    //QObject::connect(&gameWidget, &GameWidget::keyReleased, &viewModel, &GameViewModel::handleKeyRelease);
    //QObject::connect(&viewModel, &GameViewModel::gameUpdated, &view, &View_draw::update);


    return app.exec();
}


#include "main.moc"
