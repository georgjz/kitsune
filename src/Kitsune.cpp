#include <QtWidgets>
#include <QAction>

#include "Kitsune.hpp"
#include "ui_kitsuneui.h"

Kitsune::Kitsune(QWidget *parent) :
    QMainWindow(parent),
    imageLabel(new QLabel),
    scrollArea(new QScrollArea),
    scaleFactor(1.0f),
    ui(new Ui::KitsuneUi)
{
    // set up UI. duh.
    ui->setupUi(this);
    // set QLabel background to dark
    imageLabel->setBackgroundRole(QPalette::Midlight);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(scrollArea);
    // move child/QLabel to center
    setCentralWidget(scrollArea);

    connectActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3/5);
}

Kitsune::~Kitsune()
{
    delete ui;
}

//------------------------------------------------------------------------------
bool Kitsune::loadFile(const QString &fileName)
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
void Kitsune::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    // adjust size of QLabel
    imageLabel->adjustSize();
    // ui->printAct->setEnabled(true);
    // ui->fitToWindowAct->setEnabled(true);
    // updateActions();

    // if (!ui->fitToWindowAct->isChecked())
    //     imageLabel->adjustSize();
}

//------------------------------------------------------------------------------
// bool Kitsune::saveFile(const QString &fileName)
// {
//     QImageWriter writer(fileName);
//
//     if (!writer.write(image)) {
//         QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                                  tr("Cannot write %1: %2")
//                                  .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
//         return false;
//     }
//     const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
//     statusBar()->showMessage(message);
//     return true;
// }
//
//------------------------------------------------------------------------------
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

//------------------------------------------------------------------------------
// private members
//------------------------------------------------------------------------------
void Kitsune::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

//------------------------------------------------------------------------------
// void Kitsune::saveAs()
// {
//     QFileDialog dialog(this, tr("Save File As"));
//     initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
//
//     while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
// }
//
//------------------------------------------------------------------------------
// void Kitsune::copy()
// {
// #ifndef QT_NO_CLIPBOARD
//     QGuiApplication::clipboard()->setImage(image);
// #endif // !QT_NO_CLIPBOARD
// }
//
// #ifndef QT_NO_CLIPBOARD
// static QImage clipboardImage()
// {
//     if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
//         if (mimeData->hasImage()) {
//             const QImage image = qvariant_cast<QImage>(mimeData->imageData());
//             if (!image.isNull())
//                 return image;
//         }
//     }
//     return QImage();
// }
// #endif // !QT_NO_CLIPBOARD

//------------------------------------------------------------------------------
// void Kitsune::paste()
// {
// #ifndef QT_NO_CLIPBOARD
//     const QImage newImage = clipboardImage();
//     if (newImage.isNull()) {
//         statusBar()->showMessage(tr("No image in clipboard"));
//     } else {
//         setImage(newImage);
//         setWindowFilePath(QString());
//         const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
//             .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
//         statusBar()->showMessage(message);
//     }
// #endif // !QT_NO_CLIPBOARD
// }

//------------------------------------------------------------------------------
// void Kitsune::zoomIn()
// {
//     scaleImage(1.25);
// }

//------------------------------------------------------------------------------
// void Kitsune::zoomOut()
// {
//     scaleImage(0.8);
// }

//------------------------------------------------------------------------------
// void Kitsune::normalSize()
// {
//     imageLabel->adjustSize();
//     scaleFactor = 1.0;
// }
//
//------------------------------------------------------------------------------
// void Kitsune::fitToWindow()
// {
//     bool fitToWindow = ui->fitToWindowAct->isChecked();
//     scrollArea->setWidgetResizable(fitToWindow);
//     if (!fitToWindow)
//         normalSize();
//     updateActions();
// }
//
//------------------------------------------------------------------------------
void Kitsune::about()
{
    QMessageBox::about(this, tr("About Kitsune"),
            tr("<p>Kitsune 0.2-prealpha</p> "
               "<p>Pixel Graphic and Tilemap Tool for SNES Developers</p>"
               "<p> {license}</p> "
               "<p>Copyright (C) 2018 Georg Ziegler</p>"));
}

//------------------------------------------------------------------------------
void Kitsune::connectActions()
{
    connect(ui->openAct, &QAction::triggered, this, &Kitsune::open);
    // connect(ui->saveAsAct, &QAction::triggered, this, &Kitsune::saveAs);
    // connect(ui->exitAct, &QAction::triggered, this, &QWidget::close);
    // connect(ui->copyAct, &QAction::triggered, this, &Kitsune::copy);
    // connect(ui->pasteAct, &QAction::triggered, this, &Kitsune::paste);
    // connect(ui->zoomInAct, &QAction::triggered, this, &Kitsune::zoomIn);
    // connect(ui->zoomOutAct, &QAction::triggered, this, &Kitsune::zoomOut);
    // connect(ui->normalSizeAct, &QAction::triggered, this, &Kitsune::normalSize);
    // connect(ui->fitToWindowAct, &QAction::triggered, this, &Kitsune::fitToWindow);
    connect(ui->aboutAct, &QAction::triggered, this, &Kitsune::about);
    // connect(ui->aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);
}

//------------------------------------------------------------------------------
// void Kitsune::updateActions()
// {
//     ui->saveAsAct->setEnabled(!image.isNull());
//     ui->copyAct->setEnabled(!image.isNull());
//     ui->zoomInAct->setEnabled(!ui->fitToWindowAct->isChecked());
//     ui->zoomOutAct->setEnabled(!ui->fitToWindowAct->isChecked());
//     ui->normalSizeAct->setEnabled(!ui->fitToWindowAct->isChecked());
// }

//------------------------------------------------------------------------------
// void Kitsune::scaleImage(double factor)
// {
//     Q_ASSERT(imageLabel->pixmap());
//     scaleFactor *= factor;
//     imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
//
//     adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
//     adjustScrollBar(scrollArea->verticalScrollBar(), factor);
//
//     ui->zoomInAct->setEnabled(scaleFactor < 3.0);
//     ui->zoomOutAct->setEnabled(scaleFactor > 0.333);
// }

//------------------------------------------------------------------------------
// void Kitsune::adjustScrollBar(QScrollBar *scrollBar, double factor)
// {
//     scrollBar->setValue(int(factor * scrollBar->value()
//                             + ((factor - 1) * scrollBar->pageStep()/2)));
// }
