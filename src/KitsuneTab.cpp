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
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollArea>

#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"

KitsuneTab::KitsuneTab(QWidget *parent) :
    QScrollArea(parent),
    scaleFactor(1.0)
{
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // center content
}

//------------------------------------------------------------------------------

KitsuneTab::~KitsuneTab()
{
    // delete imageLabel;
}

//------------------------------------------------------------------------------

bool KitsuneTab::loadTabContent(const QString &fileName)
{
    tabContent = new KitsuneImage(this);    // create image object
    setWidget(tabContent);                  // set tab content as widget
    return tabContent->loadFile(fileName);  // load image
}

//------------------------------------------------------------------------------

void KitsuneTab::scaleContent(double factor)
{
    // Scaling is destructive, keep original pixmap
    // TODO: check min/max scale factor
    // TODO: better scale values
    // scaleFactor += factor;                  // update scale factor
    tabContent->scaleImage(factor);    // scale tab content

    // TODO: change status bar
}

//------------------------------------------------------------------------------

void KitsuneTab::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Mouse click position: %1, %2")
                                 .arg(event->globalX())
                                 .arg(event->globalY()) );
    }

    event->accept();
}

//------------------------------------------------------------------------------

void KitsuneTab::wheelEvent(QWheelEvent *event)
{
    // check if mouse wheel was turned
    int numPixels = event->delta() / 8;
    if(numPixels == 0)
    {
        event->accept();
        return;
    }

    if(numPixels > 0)
    { scaleContent(scaleFactor + 0.1); }
    else              { scaleContent(scaleFactor - 0.1); }

    event->accept();
    // QMessageBox::information(this, QG;uiApplication::applicationDisplayName(),
    //                          tr("Mouse wheel: %1")
    //                          .arg(QString::number(event->delta()))
    //                          );
}
