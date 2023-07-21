SOURCES += \
        main.cpp

GAMEGRID_PATH = $$OUT_PWD/../debug/GameGrid
win32:CONFIG(release, debug|release): GAMEGRID_PATH = $$OUT_PWD/../debug/GameGrid
else:win32:CONFIG(release, debug|release): GAMEGRID_PATH = $$OUT_PWD/../release/GameGrid

# Importing library
LIBS += -L$$GAMEGRID_PATH/ -lGameGrid

INCLUDEPATH += $$PWD/../debug/GameGrid
DEPENDPATH += $$PWD/../debug/GameGrid

win32-g++: PRE_TARGETDEPS += $$GAMEGRID_PATH/libGameGrid.a
else:win32:!win32-g++: PRE_TARGETDEPS += $$GAMEGRID_PATH/GameGrid.lib
else:unix:!macx: PRE_TARGETDEPS += $$GAMEGRID_PATH/libGameGrid.a

HEADERS +=
