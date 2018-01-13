#ifndef KITSUNE_H
#define KITSUNE_H

#include <QMainWindow>
#include <QImage>

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
    void on_actionOpen_triggered();

private:
    // void createActions();
    void setImage(const QImage &newImage);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    Ui::KitsuneUi *ui;
};

#endif /* KITSUNE_H */
