#include "MainWindow.hpp"
#include <QApplication>


//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // Mother of Dragons
    QApplication app(argc, argv);
    // 1. open and display file
    MainWindow *w { new MainWindow() };
    w->show();

    return app.exec();
    // 2. add file menue
    //      - open
    //      - quit
}
