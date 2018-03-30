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
#include <QGuiApplication>
#include <QPixmap>
#include <QPoint>
#include <QMessageBox>
#include <QWheelEvent>
#include <QScrollArea>

#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"

KitsuneTab::KitsuneTab(QWidget *parent) :
    QScrollArea(parent),
    scaleFactor(1.0)
{
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // center content
    connectActions();                                   // connect actions
}

//------------------------------------------------------------------------------

KitsuneTab::~KitsuneTab()
{
    // destructor
}

//------------------------------------------------------------------------------
/*!
 *  Loads the tab with the content of the given file name. Currently only
 *  standard image file formats are accepted.
 *
 *  \param fileName The path and file name to the file to be opened
 */
bool KitsuneTab::loadTabContent(const QString &fileName)
{
    tabContent = new KitsuneImage(this);    // create image object
    setWidget(tabContent);                  // set tab content as widget
    return tabContent->loadFile(fileName);  // load image
}

//------------------------------------------------------------------------------
/*!
 *  This method saves the tab's current content under the new file name
 *  at the specified location.
 *
 *  \param fileName The path and file name for the new file to be saved
 */
bool KitsuneTab::saveTabContent(const QString &fileName)
{
    // code
}

//------------------------------------------------------------------------------
/*!
 *  This method sets the tab's scale factor to a new value. This will emit the
 *  signal scaleFactorChanged() to notify all dependent members of the change.
 *
 *  \param factor scaleFactor will be set to this
 */
void KitsuneTab::setScaleFactor(double factor)
{
    scaleFactor = factor;
    emit scaleFactorChanged(scaleFactor);
}

//------------------------------------------------------------------------------
/*!
 *  This method is notified by the signal scaleFactorChanged(). It changes
 *  the tab's content to the new scale factor.
 *
 *  \param factor The tab's content will rescale to this factor
 */
void KitsuneTab::scaleContent(double factor)
{
    // NOTE: Scaling is destructive, keep original pixmap
    // TODO: check min/max scale factor
    // TODO: better scale values
    // scaleFactor = factor;                   // update scale factor
    tabContent->scaleImage(scaleFactor);    // scale tab content

    // TODO: change status bar
}

//------------------------------------------------------------------------------
/*!
 *  This method reacts to events concerning the mouse wheel. It reacts depending
 *  on the keys pressed.
 *
 *  \param event The QWheelEvent emitted by Qt
 */
// void KitsuneTab::wheelEvent(QWheelEvent *event)
// {
//     // check if mouse wheel was turned
//     int numPixels = event->delta() / 8;
//     if(numPixels == 0)
//     {
//         event->accept();
//         return;
//     }
//
//     if(numPixels > 0) { setScaleFactor(scaleFactor + 0.1); }
//     else              { setScaleFactor(scaleFactor - 0.1); }
//
//     // event has been handled
//     event->accept();
// }

//------------------------------------------------------------------------------
/*!
 *  Connects all the slots and signals of this class
 */
void KitsuneTab::connectActions()
{
    connect(this, &KitsuneTab::scaleFactorChanged, this, &KitsuneTab::scaleContent);
}
