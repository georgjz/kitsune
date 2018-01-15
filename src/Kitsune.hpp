#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

#include "KitsuneImage.hpp"


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
    void openImage();
    void saveAsImage();
    void exportPalette();
    void exportTileSet();
    void about();

private:
    void connectActions();           // connect actions to slots
    void scaleImage(double factor);

    KitsuneTileData *tileData;
    KitsuneImage *kitImage;
    QScrollArea *scrollArea;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
