#include <QScrollArea>

#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"

KitsuneTab::KitsuneTab(QWidget *parent) :
    QScrollArea(parent)
    // scaleFactor(1.0)
{
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // center content
}

//------------------------------------------------------------------------------
KitsuneTab::~KitsuneTab()
{
    // delete imageLabel;
}

//------------------------------------------------------------------------------
bool KitsuneTab::loadFile(const QString &fileName)
{
    tabContent = new KitsuneImage(this);    // create image object
    setWidget(tabContent);
    return tabContent->loadFile(fileName);  // load image
}
