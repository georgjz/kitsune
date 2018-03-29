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

#ifndef KITSUNEIMAGE_H
#define KITSUNEIMAGE_H

#include <QImage>
#include <QLabel>

#include "KitsuneTileData.hpp"

/*!
 * \class KitsuneImage
 *
 * \brief Class to handle the content of a tab
 *
 *  This class handles all operations relating to the content of a tab.
 *  The main focus are operations relating to the modification and
 *  manipulation of the image.
 *
 */
class KitsuneImage : public QLabel
{
    Q_OBJECT

public:
    explicit KitsuneImage(QWidget *parent = 0);     //!< Default constructor
    ~KitsuneImage();                                //!< Default destructor

    // image functions
    bool loadFile(const QString &fileName);         //!< Opens a new file
    bool saveFile(const QString &fileName);         //!< Saves the current file
    void scaleImage(double factor);                 //!< Changes the scale of the image
    // double getScaleFactor();

    QImage getImage() { return image; }             //!< Returns the current image
    QString getFileName() { return fileName; }      //!< Returns the image file name

private:
    void setImage(const QImage &newImage);          //!< Sets the current image

    QPixmap originalPixmap;     //!< Holds the original Pixmap
    QString fileName;           //!< Holds the image's file name
    QImage image;               //!< Holds the image's QImage file
};

#endif /* KITSUNEIMAGE_H */
