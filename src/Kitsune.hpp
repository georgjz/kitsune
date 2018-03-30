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

#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>

#include "KitsuneImage.hpp"
#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"

namespace Ui
{
    class KitsuneUi;
}

/*!
 * \class Kitsune
 *
 * \brief Main class of the application
 *
 * Kitsune is the application main class that handles all all file operations,
 * input/output handling and tab management.
 *
 */
class Kitsune : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kitsune(QWidget *parent = 0);      //!< Default constructor
    ~Kitsune();                                 //!< Default destructor

private slots:
    // File Menu
    void openImage();           //!< Opens an image in a new tab.
    void saveAsImage();         //!< Saves a copy of the image in the current tab
    // Image Menu
    void exportPalette();       //!< Exports a full palette of a given image
    void exportTileSet();       //!< Exports a tile set in the given format
    // Settings Menu
    void setBitFormat();        //!< Sets the bit format for a given tab
    // View Menu
    void zoomReset();           //!< Reset zoom to 100%
    void zoomIn();              //!< Zoom in
    void zoomOut();             //!< Zoom out
    // About Menu
    void about();               //!< Displays information about the application

    // tab functions
    void changeCurrentTab(int index);   //!< Updates the pointer to the currently selected tab
    void closeTab(int tabIndex);        //!< Close the current tab

    // Zoom function
    void changeZoomLevel(int value);    //!< Invoked by signal tabList::valueChanged

protected:
    void wheelEvent(QWheelEvent *event) override;   //!< Changes the scale factor/zoom level

private:
    void connectActions();              //!< Connect actions to slots and signals

    QList<KitsuneTab*> tabList;         //!< Holds all currently open tabs
    KitsuneTab *currentTab;             //!< Points to the currently selected tab
    KitsuneTileData *tileData;          //!< Pointer to the helper class to export data
    Ui::KitsuneUi *ui;                  //!< Holds the Qt widgets of Kitsune
    QSpinBox *zoomLevel;                //!< Displays the current zoom in the status bar
};

#endif /* KITSUNE_H */
