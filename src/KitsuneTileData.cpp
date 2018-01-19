#include <QFile>
#include <QFileDialog>
#include <QString>

#include "KitsuneTileData.hpp"


KitsuneTileData::KitsuneTileData() :
    bitFormat(BitFormats::_4bpp),
    tileSize(TileSizes::_8by8)
{
    // constructor
}

//------------------------------------------------------------------------------
KitsuneTileData::~KitsuneTileData()
{
    // destructor
}

//------------------------------------------------------------------------------

bool KitsuneTileData::exportPalette(const QVector<QRgb> &colorTable)
{
    // get output file name
    QString fileName = QFileDialog::getSaveFileName(Q_NULLPTR,
                                                    QObject::tr("Export Palette As"),
                                                    "",
                                                    QObject::tr("Palette Data (*.pal)"));    // create output file
    // convert colors
    QFile outputFile(fileName);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream out(&outputFile);
    out.setByteOrder(QDataStream::LittleEndian);

    for(const auto color : colorTable)
    {
        uint16_t colorR = qRed(color);
        uint16_t colorG = qGreen(color);
        uint16_t colorB = qBlue(color);
        uint16_t colorBGR555 = ((colorB & 0xfff8) << 7) |
                               ((colorG & 0xfff8) << 2) |
                               ((colorR & 0xfff8) >> 3);
        colorBGR555 &= 0x7fff;
        // uint8_t lowerByte   = colorBGR555 & 0x00ff;
        // uint8_t higherByte  = colorBGR555 >> 8;
        // paletteFile << lowerByte;
        // paletteFile << higherByte;
        out << colorBGR555;
    }
    outputFile.flush();

    return true;
}

//------------------------------------------------------------------------------

bool KitsuneTileData::exportTileSet(const QImage &image)
{
    // get output file name
    QString fileName = QFileDialog::getSaveFileName(Q_NULLPTR,
                                                    QObject::tr("Export Tile Set As"),
                                                    "",
                                                    QObject::tr("Palette Data (*.pal)"));    // create output file
    // convert colors
    QFile outputFile(fileName);
    outputFile.open(QIODevice::WriteOnly);
    QDataStream out(&outputFile);

    uint8_t bitplane0{0}, bitplane1{0}, bitplane2{0}, bitplane3{0};
    uint8_t yTilesCount{static_cast<uint8_t>(image.width() >> 3)},
            xTilesCount{static_cast<uint8_t>(image.height() >> 3)};
    uint16_t tilesCount{static_cast<uint16_t>(xTilesCount * yTilesCount)};
    uint8_t xTile{0}, yTile{0};

    uint8_t offset = (bitFormat == BitFormats::_2bpp) ? 16 : 32;

    for(auto tile = 0; tile < tilesCount; ++tile)
    {
        for(auto y = 0; y < 8; ++y)
        {
            for(auto x = 0; x < 8; ++x)
            {
                uint8_t bit = 0;
                // uint8_t index = colorIndexMap[8*xTile + x][8*yTile + y];
                uint8_t index = image.colorTable().indexOf(image.pixel(8*xTile + x, 8*yTile + y));
                bit = index & 1;
                bitplane0 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane1 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane2 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane3 |= (bit << (7 - x));
            } // x loop
            // write bitplane line to output file
            switch(bitFormat)
            {
                case BitFormats::_4bpp:
                    outputFile.seek(offset*tile + (2*y + 16) + 1);
                    out << bitplane3;
                    outputFile.seek(offset*tile + (2*y + 16));
                    out << bitplane2;
                case BitFormats::_2bpp:
                    outputFile.seek(offset*tile + 2*y + 1);
                    out << bitplane1;
                    outputFile.seek(offset*tile + 2*y);
                    out << bitplane0;
            }
            // reset bitplanes
            bitplane0 &= 0;
            bitplane1 &= 0;
            bitplane2 &= 0;
            bitplane3 &= 0;
        } // y loop
        ++xTile;
        if(xTile >= xTilesCount)
        {
            xTile = 0;              // reset counter
            ++yTile;
            if(yTile >= yTilesCount) break;
        }
    } // tile loop
    // close files
    outputFile.flush();

    return true;
}

//------------------------------------------------------------------------------

bool KitsuneTileData::exportTileMap()
{
    // code
}

//------------------------------------------------------------------------------

void KitsuneTileData::setBitFormat(BitFormats bitFormat)
{
    this->bitFormat = bitFormat;
}

//------------------------------------------------------------------------------

void KitsuneTileData::setTileSize(TileSizes tileSize)
{
    this->tileSize = tileSize;
}
