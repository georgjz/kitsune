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

#ifndef KITSUNETAB_H
#define KITSUNETAB_H

#include <QImage>
#include <QLabel>
#include <QScrollArea>

#include "KitsuneImage.hpp"
// #include "KitsuneTileData.hpp"

class KitsuneTab : public QScrollArea
{
    Q_OBJECT
    // If scaleFactor changes, emit signal to update content
    Q_PROPERTY( double value READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged )
    // class foo : public QObject
    // {
    //     Q_OBJECT
    //     Q_PROPERTY( int value READ getValue WRITE setValue NOTIFY valueChanged )
    // public:
    //     explicit foo( QObject* parent = nullptr ) :
    //         QObject{ parent }, i_{ 0 } {}
    //     virtual ~foo() {}
    //
    //     int getValue() const { return i_; }
    // public slots:
    //     void setValue( int value )
    //     {
    //         if ( value != i_ ) {
    //             i_ = value;
    //             emit valueChanged( i_ );
    //         }
    //     }
    // signals:
    //     void valueChanged( int value );
    // private:
    //     int i_;
    // };

public:
    explicit KitsuneTab(QWidget *parent = 0);
    ~KitsuneTab();

    // tab functions
    bool loadTabContent(const QString &fileName);   //!< loads the scroll area of the tab with content
    bool saveTabContent(const QString &fileName);   //!< saves the content of the tab
    double getScaleFactor() const { return scaleFactor; }  // get the content's scale factor
    KitsuneImage* getTabContent() { return tabContent; }
    QString getFileName() { return tabContent->getFileName(); }

public slots:
    void setScaleFactor(double factor);

private slots:
    void scaleContent(double factor);          //!< scale the content to given factor

signals:
    void scaleFactorChanged(double factor);

protected:
    // react to mouse events
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void connectActions();      // connect actions of class
    KitsuneImage *tabContent;   // image shown in tab
    double scaleFactor;
};

#endif /* KITSUNETAB_H */
