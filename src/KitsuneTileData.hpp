#ifndef KITSUNETILEDATA_H
#define KITSUNETILEDATA_H

#include <QImage>
#include <QVector>

enum class BitFormats { _2bpp, _4bpp, _8bpp };
enum class TileSizes { _8by8, _16by16, _32by32 };

class KitsuneTileData
{
public:
    KitsuneTileData();
    ~KitsuneTileData();

    bool exportPalette(const QVector<QRgb> &colorTable);    // exports palette to .pal
    bool exportTileSet(const QImage &image);                // exports tile set to .vra
    bool exportTileMap();                                   // exports tilemap to .vmp

    void setBitFormat(BitFormats bitFormat);
    void setTileSize(TileSizes tileSize);

private:
    BitFormats bitFormat;
    TileSizes tileSize;
};

#endif /* KITSUNETILEDATA_H */
