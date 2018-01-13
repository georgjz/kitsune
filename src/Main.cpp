#include "Kitsune.hpp"
#include <QApplication>


//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // Mother of Dragons
    QApplication app(argc, argv);
    // 1. open and display file
    Kitsune *w { new Kitsune() };

    // enter main loop after initialization
    w->show();
    return app.exec();
    // 2. add file menue
    //      - open
    //      - quit
}
