#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>
#include <QScrollBar>

class QLabel;
class QScrollArea;

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

    bool loadFile(const QString &fileName);

private slots:
    void open();
    void saveAs();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

private:
    void connectActions();           // connect actions to slots
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
