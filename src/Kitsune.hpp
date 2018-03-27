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
    // tab functions
    void closeTab(int tabIndex);    // close tab
    void newTab(int tabIndex);      // switches focus to new tab

private:
    void connectActions();           // connect actions to slots
    void scaleImage(double factor);

    QList<KitsuneTab*> tabList;
    KitsuneTileData *tileData;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
