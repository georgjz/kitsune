// The MIT License (MIT)
//
// Copyright (c) 2018 Georg Ziegler
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <QtWidgets>

#include "Kitsune.hpp"
#include "KitsuneTab.hpp"
#include "KitsuneImage.hpp"
#include "ui_kitsuneui.h"

Kitsune::Kitsune(QWidget *parent) :
    QMainWindow(parent),
    tileData(new KitsuneTileData),      // helper class
    ui(new Ui::KitsuneUi)
{
    // set up UI. duh.
    ui->setupUi(this);
    this->setCentralWidget(ui->centralWidget);  // set central widget
    ui->centralWidget->hide();

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
// private slot members
//------------------------------------------------------------------------------
/*!
 *  This method opens a new file in a new tab. It will create a new KitsuneTab
 *  object and adds it to the tabList, that keeps track of all tabs currently
 *  opened.
 */
void Kitsune::openImage()
{
    // create new Tab
    tabList << new KitsuneTab(this);
    // get file name and open it
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !tabList.last()->loadTabContent(dialog.selectedFiles().first())) {}

    // make latest tab visible, change title
    ui->imageTabs->insertTab(ui->imageTabs->currentIndex() + 1, // insert after current tab
                             tabList.last(),                    // add newly opened tab
                             tabList.last()->getFileName());    // tab text is file name
    ui->imageTabs->setCurrentWidget(tabList.last());            // change focus to new tab
    ui->centralWidget->show();                                  // make tab widget visible
}

//------------------------------------------------------------------------------
/*!
 *  This method will save the image in the current tab in any supported file
 *  format.
 */
void Kitsune::saveAsImage()
{
    // kitImage->saveFile(QFileDialog::getSaveFileName(this, tr("Save File As"), ""));
}

//------------------------------------------------------------------------------
/*!
 *  This method will open a dialog to export the color palette in BGR555 format
 *  in a .pal file that can be used in a SNES program. The export itseld is
 *  handled by KitsuneTileData.
 */
void Kitsune::exportPalette()
{
    // BUG: check for empty tabList
    // Get the current tab's image and export its palette
    KitsuneImage *image = tabList[ui->imageTabs->currentIndex()]->getTabContent();
    tileData->exportPalette(image->getImage().colorTable());
}

//------------------------------------------------------------------------------
/*!
 *  This method opens a dialog to export a tile set of the current tab. The
 *  export itself is handled by KitsuneTileData.
 */
void Kitsune::exportTileSet()
{
    // BUG: check for empty tabList
    // Get the current tab's image and export its tile set
    KitsuneImage *image = tabList[ui->imageTabs->currentIndex()]->getTabContent();
    tileData->exportTileSet(image->getImage());
}

//------------------------------------------------------------------------------
/*!
 *  Changes the bit format for the current tab. This controls what format
 *  the export functions of KitsuneTileData will use.
 */
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
/*!
 *  Resets the scale factor of the current tab.
 */
void Kitsune::zoomReset()
{
    // reset scale factor of current tab to 1.0
    KitsuneTab *currentTab = tabList[ui->imageTabs->currentIndex()];
    currentTab->setScaleFactor(1.0);
}

//------------------------------------------------------------------------------
/*!
 *  Increases the scale factor of the current tab.
 */
void Kitsune::zoomIn()
{
    // increase scale factor for current tab by 0.1
    KitsuneTab *currentTab = tabList[ui->imageTabs->currentIndex()];
    currentTab->setScaleFactor(currentTab->getScaleFactor() + 0.1);
}

//------------------------------------------------------------------------------
/*!
 *  Decreases the scale factor of the current tab.
 */
void Kitsune::zoomOut()
{
    // decrease scale factor for current tab by 0.1
    // tabList[ui->imageTabs->currentIndex()]->scaleContent(1.0);
    KitsuneTab *currentTab = tabList[ui->imageTabs->currentIndex()];
    currentTab->setScaleFactor(currentTab->getScaleFactor() - 0.1);
}

//------------------------------------------------------------------------------
/*!
 *  Displays information about the application in a dialog.
 */
void Kitsune::about()
{
    QMessageBox::about(this, tr("About Kitsune"),
            tr("<p>Kitsune 0.2.4-preAlpha</p> "
               "<p>Pixel Graphic and Tilemap Tool for SNES Developers</p>"
               "<p>License: Permission is hereby granted, free of charge, to any person obtaining a copy "
               "of this software and associated documentation files (the \"Software\"), to deal "
               "in the Software without restriction, including without limitation the rights "
               "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
               "copies of the Software, and to permit persons to whom the Software is "
               "furnished to do so, subject to the following conditions:</p>"
               "<p>The above copyright notice and this permission notice shall be included in all "
               "copies or substantial portions of the Software.</p>"
               "<p>Copyright (C) 2018 Georg Ziegler</p>"));
}

//------------------------------------------------------------------------------
/*!
 *  Invoked whenever a tab is closed.
 */
void Kitsune::closeTab(int tabIndex)
{
    ui->imageTabs->removeTab(tabIndex);
}

//------------------------------------------------------------------------------
/*!
 *  Connects all actions of KitsuneUi to members of the Kitsune class.
 */
void Kitsune::connectActions()
{
    // File menu
    connect(ui->openAct, &QAction::triggered, this, &Kitsune::openImage);
    connect(ui->saveAsAct, &QAction::triggered, this, &Kitsune::saveAsImage);
    connect(ui->exitAct, &QAction::triggered, this, &QWidget::close);
    // Image menu
    connect(ui->expPaletteAct, &QAction::triggered, this, &Kitsune::exportPalette);
    connect(ui->expTileSetAct, &QAction::triggered, this, &Kitsune::exportTileSet);
    // Settings menu
    connect(ui->_2bppAct, &QAction::triggered, this, &Kitsune::setBitFormat);
    connect(ui->_4bppAct, &QAction::triggered, this, &Kitsune::setBitFormat);
    // View menu
    connect(ui->zoomResetAct, &QAction::triggered, this, &Kitsune::zoomReset);
    connect(ui->zoomInAct, &QAction::triggered, this, &Kitsune::zoomIn);
    connect(ui->zoomOutAct, &QAction::triggered, this, &Kitsune::zoomOut);
    // About menu
    connect(ui->aboutAct, &QAction::triggered, this, &Kitsune::about);
    connect(ui->aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);
    // Tab functions
    connect(ui->imageTabs, &QTabWidget::tabCloseRequested, this, &Kitsune::closeTab);
}
