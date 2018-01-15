#include "Kitsune.hpp"
#include <QApplication>


//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // Mother of Dragons
    QApplication app(argc, argv);
    Kitsune *kitsune { new Kitsune() };
    // enter main loop after initialization
    kitsune->show();
    return app.exec();
}
