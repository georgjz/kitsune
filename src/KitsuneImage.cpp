#include <QtWidgets>

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
void KitsuneImage::wheelEvent(QWheelEvent *event)
{
    // zoom scroll
    event->accept();
}

//------------------------------------------------------------------------------
//  private member functions
//------------------------------------------------------------------------------
void KitsuneImage::setImage(const QImage &newImage)
{
    image = newImage;
    setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    // // DEBUG
    // QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
    //                              tr("sizeHint() %1 x %2")
    //                              .arg(sizeHint().rwidth(), sizeHint().rheight()));
    // // DEBUG
    adjustSize();
}
