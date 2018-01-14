#include <QtWidgets>
#include <fstream>

#include "KitsuneImage.hpp"

KitsuneImage::KitsuneImage(QWidget *parent) :
    QLabel(parent),
    scaleFactor(1.0)
{
    setBackgroundRole(QPalette::Midlight);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);
}

//------------------------------------------------------------------------------
KitsuneImage::~KitsuneImage()
{
    // delete imageLabel;
}

//------------------------------------------------------------------------------
bool KitsuneImage::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    // const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
    //     .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    // statusBar()->showMessage(message);
    return true;
}

//------------------------------------------------------------------------------
void KitsuneImage::scaleImage(double factor)
{
    Q_ASSERT(this->pixmap());
    scaleFactor *= factor;
    resize(scaleFactor * this->pixmap()->size());
}

//------------------------------------------------------------------------------
bool KitsuneImage::processImage()
{
    // this is where the magic happens...
    // TODO palette output
    // create bitplanes
    // create bitplanes output file
    std::ofstream bitplanesFile;
    // TODO dynamic file name
    bitplanesFile.open("KitsuneProcesOutput.vra", std::ios::binary | std::ios::out);
    bitplanesFile.seekp(0);

        // TODO: modulize in function
        // bitplanes that will hold data
    uint8_t bitplane0{0}, bitplane1{0}, bitplane2{0}, bitplane3{0};
    uint8_t yTilesCount{static_cast<uint8_t>(image.width() >> 3)},
            xTilesCount{static_cast<uint8_t>(image.height() >> 3)};
    uint16_t tilesCount{static_cast<uint16_t>(xTilesCount * yTilesCount)};
    uint8_t xTile{0}, yTile{0};

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
            bitplanesFile.seekp(32*tile + 2*y);
            bitplanesFile << bitplane0;
            bitplanesFile.seekp(32*tile + 2*y + 1);
            bitplanesFile << bitplane1;
            bitplanesFile.seekp(32*tile + (2*y + 16));
            bitplanesFile << bitplane2;
            bitplanesFile.seekp(32*tile + (2*y + 16) + 1);
            bitplanesFile << bitplane3;

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

    return true;  // as break point, lulz
}
//------------------------------------------------------------------------------
// void KitsuneImage::wheelEvent(QWheelEvent *event)
// {
//     // zoom scroll
//     event->accept();
// }

//------------------------------------------------------------------------------
//  private member functions
//------------------------------------------------------------------------------
void KitsuneImage::setImage(const QImage &newImage)
{
    image = newImage;
    setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    adjustSize();
}
