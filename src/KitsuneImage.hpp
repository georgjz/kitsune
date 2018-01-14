#ifndef KITSUNEIMAGE_H
#define KITSUNEIMAGE_H

#include <QImage>
#include <QLabel>

class KitsuneImage : public QLabel
{
    Q_OBJECT

public:
    explicit KitsuneImage(QWidget *parent = 0);
    ~KitsuneImage();

    // getter and setter
    // QLabel* getImageLabel() { return imageLabel; }

    // image functions
    bool loadFile(const QString &fileName);
    void scaleImage(double factor);

protected:
    void wheelEvent(QWheelEvent *event);
    // {
    //     // zoom scroll
    //     event->accept();
    // }

private:
    void setImage(const QImage &newImage);

    QImage image;
    // QLabel *imageLabel;
    double scaleFactor;
};

#endif /* KITSUNEIMAGE_H */
