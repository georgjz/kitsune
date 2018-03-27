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

class KitsuneImage : public QLabel
{
    Q_OBJECT

public:
    explicit KitsuneImage(QWidget *parent = 0);
    ~KitsuneImage();

    // image functions
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void scaleImage(double factor);

    QImage getImage() { return image; }
    QString getFileName() { return fileName; }

private:
    void setImage(const QImage &newImage);

    QString fileName;
    QImage image;
    double scaleFactor;
};

#endif /* KITSUNEIMAGE_H */
