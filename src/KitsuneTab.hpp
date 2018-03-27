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

    // tab functions
    bool loadFile(const QString &fileName);
    QString getFileName() { return tabContent->getFileName(); }

private:
    KitsuneImage *tabContent;   // image shown in tab
};

#endif /* KITSUNETAB_H */
