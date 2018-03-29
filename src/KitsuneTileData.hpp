#ifndef KITSUNETILEDATA_H
#define KITSUNETILEDATA_H

#include <QImage>
#include <QVector>

// TODO: Move BitFormats and TileSizes to KitsuneTab.
// TODO: Add SpriteSize enum class
enum class BitFormats { _2bpp, _4bpp, _8bpp };
enum class TileSizes { _8by8, _16by16, _32by32 };

/*!
 * \class KitsuneTileData
 *
 * \brief Class to handle the export of data in a format readable by the SNES
 *
 *  This class handles all operations relating converting and exporting data
 *  that can be used in SNES programming projects.
 *
 */
class KitsuneTileData
{
public:
    KitsuneTileData();      //!< Default constructor
    ~KitsuneTileData();     //!< Default destructor

    bool exportPalette(const QVector<QRgb> &colorTable);    //!< Exports palette to .pal
    bool exportTileSet(const QImage &image);                //!< Exports tile set to .vra
    bool exportTileMap();                                   //!< Exports tilemap to .vmp

    void setBitFormat(BitFormats bitFormat);        //!< Changes the bit format
    void setTileSize(TileSizes tileSize);           //!< Changes the tile size

private:
    BitFormats bitFormat;       //!< Holds the current bit format
    TileSizes tileSize;         //!< Holds the current tile size
};

#endif /* KITSUNETILEDATA_H */
