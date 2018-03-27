#include <QScrollArea>

#include "KitsuneTab.hpp"
#include "KitsuneTileData.hpp"

KitsuneTab::KitsuneTab(QWidget *parent) :
    QScrollArea(parent)
    // scaleFactor(1.0)
{
    // setBackgroundRole(QPalette::Midlight);
    // setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // setScaledContents(true);
}

//------------------------------------------------------------------------------
KitsuneTab::~KitsuneTab()
{
    // delete imageLabel;
}

//------------------------------------------------------------------------------
