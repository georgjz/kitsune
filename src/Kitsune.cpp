#include <QtWidgets>

#include "Kitsune.hpp"
#include "KitsuneTab.hpp"
#include "KitsuneImage.hpp"
#include "ui_kitsuneui.h"

Kitsune::Kitsune(QWidget *parent) :
    QMainWindow(parent),
    tileData(new KitsuneTileData),      // helper class
    scaleFactor(1.0f),
    ui(new Ui::KitsuneUi)
    // imageTabs(new QTabWidget(this)),   // centralWidget is parent of imageTabs
    // scrollArea(new QScrollArea),
{
    // set up UI. duh.
    ui->setupUi(this);
    this->setCentralWidget(ui->centralWidget);  // set central widget
    ui->centralWidget->hide();
    // ui->imageTabs->addTab(new QWidget(),"TAB 1");
    // ui->imageTabs->addTab(new QWidget(),"TAB 2");
    // set up scrollArea
    // scrollArea->setBackgroundRole(QPalette::Dark);
    // scrollArea->setWidget(kitImage);
    // scrollArea->setVisible(false);
    // scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

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

    // set standard path to pictures location, else to execution path
    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes =
        acceptMode == QFileDialog::AcceptOpen
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
void Kitsune::openImage()
{
    // create new Tab
    tabList << new KitsuneTab(this);
    // get file name and open it
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !tabList.last()->loadFile(dialog.selectedFiles().first())) {}

    // make latest tab visible, change title
    ui->imageTabs->insertTab(ui->imageTabs->currentIndex() + 1, // insert after current tab
                             tabList.last(),                    // add newly opened tab
                             tabList.last()->getFileName());    // tab text is file name
    ui->imageTabs->setCurrentWidget(tabList.last());            // change focus to new tab
    ui->centralWidget->show();                                  // make tab widget visible
}

//------------------------------------------------------------------------------
void Kitsune::saveAsImage()
{
    // kitImage->saveFile(QFileDialog::getSaveFileName(this, tr("Save File As"), ""));
}

//------------------------------------------------------------------------------
void Kitsune::exportPalette()
{
    // tileData->exportPalette(kitImage->getImage().colorTable());
}

//------------------------------------------------------------------------------
void Kitsune::exportTileSet()
{
    // tileData->exportTileSet(kitImage->getImage());
}

//------------------------------------------------------------------------------
void Kitsune::setBitFormat()
{
    if(QObject::sender()->objectName() == "_2bppAct")
    {
        ui->_2bppAct->setChecked(true);
        ui->_4bppAct->setChecked(false);
        tileData->setBitFormat(BitFormats::_2bpp);
    }


    if(QObject::sender()->objectName() == "_4bppAct")
    {
        ui->_2bppAct->setChecked(false);
        ui->_4bppAct->setChecked(true);
        tileData->setBitFormat(BitFormats::_4bpp);
    }
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
void Kitsune::closeTab(int tabIndex)
{
    ui->imageTabs->removeTab(tabIndex);
}

//------------------------------------------------------------------------------
void Kitsune::newTab(int tabIndex)
{
    // ui->imageTabs->removeTab(tabIndex);
}

//------------------------------------------------------------------------------
void Kitsune::connectActions()
{
    connect(ui->openAct, &QAction::triggered, this, &Kitsune::openImage);
    connect(ui->saveAsAct, &QAction::triggered, this, &Kitsune::saveAsImage);
    connect(ui->expPaletteAct, &QAction::triggered, this, &Kitsune::exportPalette);
    connect(ui->expTileSetAct, &QAction::triggered, this, &Kitsune::exportTileSet);
    connect(ui->exitAct, &QAction::triggered, this, &QWidget::close);
    connect(ui->_2bppAct, &QAction::triggered, this, &Kitsune::setBitFormat);
    connect(ui->_4bppAct, &QAction::triggered, this, &Kitsune::setBitFormat);
    connect(ui->aboutAct, &QAction::triggered, this, &Kitsune::about);
    connect(ui->aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);
    connect(ui->imageTabs, &QTabWidget::tabCloseRequested, this, &Kitsune::closeTab);
}
