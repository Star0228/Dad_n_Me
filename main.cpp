#include <QApplication>
#include "ModelView/GameViewModel.h"
#include "View/View.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create GameViewModel instance
    //GameViewModel VM;

    // Create View instance with GameViewModel
    View view;

    view.resize(1280, 720);

    // Show the view
    view.show();

    // Start the application event loop
    return app.exec();
}

#include "main.moc"

