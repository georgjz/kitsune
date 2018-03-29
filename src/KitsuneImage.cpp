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

#include <QFile>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMessageBox>
#include <QString>

#include <fstream>

#include "KitsuneImage.hpp"
#include "KitsuneTileData.hpp"

KitsuneImage::KitsuneImage(QWidget *parent) :
    QLabel(parent)
{
    setBackgroundRole(QPalette::Midlight);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // setScaledContents(true);
}

//------------------------------------------------------------------------------

KitsuneImage::~KitsuneImage()
{
    // destructor
}

//------------------------------------------------------------------------------
/*!
 *  Loads a new file given by the path and file name.
 *
 *  \param fileName The path and file name of the image to be opened
 */
bool KitsuneImage::loadFile(const QString &fileName)
{
    // preserve file name
    this->fileName = QFileInfo(fileName).fileName();

    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    // TODO: status bar update
    // statusBar()->showMessage(message);
    return true;
}

//------------------------------------------------------------------------------
/*!
 *  Saves the current image to a new file given by the path and file name.
 *
 *  \param fileName The path and file name of the new file to be saved
 */
bool KitsuneImage::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if(!writer.write(image))
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }

    // TODO: status bar update
    // write to status bar
    return true;
}

//------------------------------------------------------------------------------
/*!
 *  Changes the scale of the displayed image to the new factor.
 *
 *  \param factor The new scale of the image
 */
void KitsuneImage::scaleImage(double factor)
{
    Q_ASSERT(this->pixmap());
    // produce scaled pixmap from original pixmap
    QPixmap scaledPixmap = originalPixmap.scaled(factor * originalPixmap.size(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    // set pixmap to new scaled pixmap
    setPixmap(scaledPixmap);
    // adjust label size
    adjustSize();
}

//------------------------------------------------------------------------------
/*!
 *  Sets the class's image member to the newly opened image. This member is
 *  used to extract information about the image itself.
 *
 *  \param newImage The new image to be copied into image
 */
void KitsuneImage::setImage(const QImage &newImage)
{
    image = newImage;
    setPixmap(QPixmap::fromImage(image));
    originalPixmap = *this->pixmap();          // keep original pixmap

    // TODO: why? Resize label?
    adjustSize();
}
