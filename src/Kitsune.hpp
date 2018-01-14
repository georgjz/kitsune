#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

#include "KitsuneImage.hpp"

// class QLabel;
// class QScrollArea;

namespace Ui
{
    class KitsuneUi;
}

class Kitsune : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kitsune(QWidget *parent = 0);
    ~Kitsune();

private slots:
    void open();
    void process();
    // void saveAs();
    // void copy();
    // void paste();
    // void zoomIn();
    // void zoomOut();
    // void normalSize();
    // void fitToWindow();
    void about();

private:
    void connectActions();           // connect actions to slots
    // void updateActions();
    bool saveFile(const QString &fileName);
    void scaleImage(double factor);
    // void adjustScrollBar(QScrollBar *scrollBar, double factor);

    KitsuneImage *kitImage;
    QScrollArea *scrollArea;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
