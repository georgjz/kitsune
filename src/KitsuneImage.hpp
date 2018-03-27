#ifndef KITSUNEIMAGE_H
#define KITSUNEIMAGE_H

#include <QImage>
#include <QLabel>

#include "KitsuneTileData.hpp"

// TODO: Why QLabel?
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
