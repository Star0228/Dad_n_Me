
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include "View/GameWidget.h"
#include "ViewModel/ViewModel.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Initialize player signal
    int playerSignal = 0;

    // Initialize view
    View_draw view;

    // Initialize ViewModel
    GameViewModel viewModel(nullptr);

    // Get primary screen geometry
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Initialize and set up the GameWidget
    GameWidget gameWidget(nullptr,
                          viewModel.getBackground(),
                          viewModel.getSmallEnemies(),
                          viewModel.getBoss(),
                          viewModel.getObstacles(),
                          viewModel.getPlayer(),
                          &playerSignal,
                          &view);

    // Set GameWidget size to screen size
    gameWidget.resize(screenGeometry.size());

    // Show the GameWidget
    gameWidget.show();

    // Connect key signals to the corresponding slots in the ViewModel
    QObject::connect(&gameWidget, &GameWidget::KeyReleased, &viewModel, &GameViewModel::handleKeyRelease);
    QObject::connect(&gameWidget, &GameWidget::KeyLeft, &viewModel, &GameViewModel::handleKeyLeft);
    QObject::connect(&gameWidget, &GameWidget::KeyRight, &viewModel, &GameViewModel::handleKeyRight);
    QObject::connect(&gameWidget, &GameWidget::KeyUp, &viewModel, &GameViewModel::handleKeyUp);
    QObject::connect(&gameWidget, &GameWidget::KeyDown, &viewModel, &GameViewModel::handleKeyDown);
    QObject::connect(&gameWidget, &GameWidget::KeyS, &viewModel, &GameViewModel::handleKeyS);
    QObject::connect(&gameWidget, &GameWidget::ResetGame, &viewModel, &GameViewModel::resetGame);

    // Start the Qt event loop
    return app.exec();
}

//#include "main.moc"  // Include the MOC-generated implementation for signal/slot connections
