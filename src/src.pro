QT += core gui widgets
TARGET = 1942
TEMPLATE = app

include(../common.pri)

CONFIG(debug, debug|release) {
    DESTDIR = ../debug
} else {
    DESTDIR = ../release
}

SOURCES += \
    main.cpp \
    gamewindow.cpp \
    gamescene.cpp

HEADERS += \
    gamewindow.h \
    gamescene.h

FORMS += \
    gamewindow.ui

RESOURCES += \
    ../res/assets.qrc
