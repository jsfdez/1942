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
    gamescene.cpp \
    pixmapcache.cpp \
    graphicsbackgrounditem.cpp \
    graphicsbulletitem.cpp \
    graphicsplayerobject.cpp \
    graphicsenemyobject.cpp \
    abstractgraphicsplaneobject.cpp \
    graphicsview.cpp \
    graphicshudobject.cpp \
    customeasingcurve.cpp

HEADERS += \
    gamewindow.h \
    gamescene.h \
    pixmapcache.h \
    graphicsbackgrounditem.h \
    graphicsbulletitem.h \
    graphicsplayerobject.h \
    graphicsenemyobject.h \
    abstractgraphicsplaneobject.h \
    graphicsview.h \
    graphicshudobject.h \
    defines.h \
    customeasingcurve.h

FORMS += \
    gamewindow.ui

RESOURCES += \
    ../res/assets.qrc

RC_FILE = ../1942.rc
