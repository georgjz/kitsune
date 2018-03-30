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

/*!
 * \class KitsuneTab
 *
 * \brief Class to handle tab functions
 *
 *  This class handles all operations relating to the tabs opened in Kitsune.
 *  The most important function is to open and close tabs and handle different
 *  display modes.
 *
 */
class KitsuneTab : public QScrollArea
{
    Q_OBJECT
    // If scaleFactor changes, emit signal to update content
    Q_PROPERTY( double value READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged )

public:
    explicit KitsuneTab(QWidget *parent = 0);               //!< Default constructor
    ~KitsuneTab();                                          //!< Default destructor

    // tab functions
    bool loadTabContent(const QString &fileName);           //!< Loads the scroll area of the tab with content
    bool saveTabContent(const QString &fileName);           //!< Saves the content of the tab
    double getScaleFactor() const { return scaleFactor; }   //!< Returns the current scale factor
    KitsuneImage* getTabContent() { return tabContent; }    //!< Returns a pointer to the tab's content
    QString getFileName() { return tabContent->getFileName(); }  //!< Returns the tab's content file name

public slots:
    void setScaleFactor(double factor);         //!< Modify the scale factor of the tab

private slots:
    void scaleContent(double factor);           //!< Scale the tab's content to a given factor

signals:
    void scaleFactorChanged(double factor);     //!< Invoked whenever scale factor changes

// protected:
    // void wheelEvent(QWheelEvent *event) override;   //!< Changes the scale factor

private:
    void connectActions();      //!< Connects all slots and signals of the KitsuneTab class

    KitsuneImage *tabContent;   //!< Pointer to the tab's content
    double scaleFactor;         //!< Scale factor to modify the tab's content
};

#endif /* KITSUNETAB_H */
