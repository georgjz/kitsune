#include "Kitsune.hpp"
#include "ui_kitsuneui.h"

Kitsune::Kitsune(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KitsuneUi)
{
    ui->setupUi(this);
}

Kitsune::~Kitsune()
{
    delete ui;
}
