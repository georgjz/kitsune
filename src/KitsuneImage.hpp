#ifndef KITSUNEIMAGE_H
#define KITSUNEIMAGE_H

#include <QImage>
#include <QLabel>

enum class BitFormats { _2bpp, _4bpp, _8bpp };
enum class TileSizes { _8by8, _16by16, _32by32 };

class KitsuneImage : public QLabel
{
    Q_OBJECT

public:
    explicit KitsuneImage(QWidget *parent = 0);
    ~KitsuneImage();

    // image functions
    bool loadFile(const QString &fileName);
    void scaleImage(double factor);
    bool processImage();        // will generate outputs

// private slots:
//     void setBitFormat(BitFormats bitFormat);
//     void setTileSize(TileSizes tileSize);

private:
    void setImage(const QImage &newImage);

    BitFormats bitFormat;
    TileSizes tileSize;
    QString fileName;
    QImage image;
    double scaleFactor;
};

#endif /* KITSUNEIMAGE_H */
