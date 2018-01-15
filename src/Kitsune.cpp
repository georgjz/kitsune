#include <QtWidgets>
#include <QAction>

#include "Kitsune.hpp"
#include "KitsuneImage.hpp"
#include "ui_kitsuneui.h"

Kitsune::Kitsune(QWidget *parent) :
    QMainWindow(parent),
    kitImage(new KitsuneImage),
    scrollArea(new QScrollArea),
    scaleFactor(1.0f),
    ui(new Ui::KitsuneUi)
{
    // set up UI. duh.
    ui->setupUi(this);
    // set up scrollArea
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(kitImage);
    scrollArea->setVisible(false);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setCentralWidget(scrollArea);

    connectActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3/5);
}

Kitsune::~Kitsune()
{
    delete ui;
}

//------------------------------------------------------------------------------
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("png");
}

//------------------------------------------------------------------------------
// private members
//------------------------------------------------------------------------------
void Kitsune::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !kitImage->loadFile(dialog.selectedFiles().first())) {}
    scrollArea->setVisible(true);
}

//------------------------------------------------------------------------------
void Kitsune::process()
{
    // call kitImage to process output
    kitImage->processImage();
}

//------------------------------------------------------------------------------
void Kitsune::about()
{
    QMessageBox::about(this, tr("About Kitsune"),
            tr("<p>Kitsune 0.2-prealpha</p> "
               "<p>Pixel Graphic and Tilemap Tool for SNES Developers</p>"
               "<p>{license}</p> "
               "<p>Copyright (C) 2018 Georg Ziegler</p>"));
}

//------------------------------------------------------------------------------
void Kitsune::connectActions()
{
    connect(ui->openAct, &QAction::triggered, this, &Kitsune::open);
    connect(ui->processAct, &QAction::triggered, this, &Kitsune::process);
    connect(ui->exitAct, &QAction::triggered, this, &QWidget::close);
    connect(ui->aboutAct, &QAction::triggered, this, &Kitsune::about);
    connect(ui->aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);
}
