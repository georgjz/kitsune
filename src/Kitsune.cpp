#include <QtWidgets>

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
    // set image properties
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(scrollArea);
    setCentralWidget(scrollArea);

    // createActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3/5);
}

Kitsune::~Kitsune()
{
    delete ui;
}

bool Kitsune::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    const QImage newImage = reader.read();
    if(newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1, %2").arg(QDir::toNativeSeperators(fileName), reader.errorString()));
        return false;
    }
    setImage(newImage);
    setWindowFilePath(fileName);

    const QString message = tr("Openend \"%1\", %2x%3, Depth: %4")
                            .arg(QDir::toNativeSeperators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
                            ui->statusbar->showMessage(message);
    return true;
}
// void Kitsune::createActions()
// {
//     // openAct =
// }
static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog { true };

    if(firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
    {
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");
    if(acceptMode == QFileDialog::AcceptSave)
    {
        dialog.setDefaultSuffix("png");
    }
}

void Kitsune::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while(dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}
