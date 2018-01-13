#-------------------------------------------------------------------------------
# Project data for qmake
# Last edit: 13 Jan 2018
#-------------------------------------------------------------------------------

TEMPLATE = app
TARGET = Kitsune

# QT += core gui
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = build/
OBJECTS_DIR = obj/
MOC_DIR = moc_generated/
UI_DIR = ui_generated/

SOURCES += \
        src/Main.cpp \
        src/Kitsune.cpp

HEADERS += \
        src/Kitsune.hpp \
        src/Kitsune.hpp

FORMS += \
        src/qtui/kitsuneui.ui
