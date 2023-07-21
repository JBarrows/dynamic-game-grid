QT       += core gui widgets

CONFIG += c++17

SOURCES += \
    board.cpp \
    cellwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    victoryoverlay.cpp \
    xocomponent.cpp

HEADERS += \
    board.h \
    cellwidget.h \
    mainwindow.h \
    victoryoverlay.h \
    xocomponent.h

GAMEGRID_PATH = $$OUT_PWD/../debug/GameGrid
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Importing library
LIBS += -L$$GAMEGRID_PATH/ -lGameGrid

INCLUDEPATH += $$PWD/../debug/GameGrid
DEPENDPATH += $$PWD/../debug/GameGrid

win32-g++: PRE_TARGETDEPS += $$GAMEGRID_PATH/libGameGrid.a
else:win32:!win32-g++: PRE_TARGETDEPS += $$GAMEGRID_PATH/GameGrid.lib
else:unix:!macx: PRE_TARGETDEPS += $$GAMEGRID_PATH/libGameGrid.a
