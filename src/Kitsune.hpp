#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>

#include "KitsuneImage.hpp"
#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"


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
    void setBitFormat();
    void about();

private:
    void connectActions();           // connect actions to slots
    void scaleImage(double factor);

    QList<KitsuneTab*> tabList;
    // QWidget *centralWidget;     // holds the central widget
    // QTabWidget *imageTabs;      // hols the image tabs
    KitsuneTileData *tileData;
    // KitsuneImage *kitImage;
    // QScrollArea *scrollArea;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
