#ifndef KITSUNETAB_H
#define KITSUNETAB_H

#include <QImage>
#include <QLabel>
#include <QScrollArea>

#include "KitsuneImage.hpp"
#include "KitsuneTileData.hpp"

// TODO: Why QLabel?
class KitsuneTab : public QScrollArea
{
    Q_OBJECT

public:
    explicit KitsuneTab(QWidget *parent = 0);
    ~KitsuneTab();

    // image functions
    // bool loadFile(const QString &fileName);
    // bool saveFile(const QString &fileName);
    // void scaleImage(double factor);
    //
    // QImage getImage() { return image; }

private:
    KitsuneImage *tabContent;   // image shown in tab
    // void setImage(const QImage &newImage);
    //
    // QString fileName;
    // QImage image;
    // double scaleFactor;
};

#endif /* KITSUNETAB_H */
