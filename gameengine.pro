QT       += core gui widgets
QT += 3dcore 3drender 3dinput 3dextras
TARGET = gameengine
TEMPLATE = app

SOURCES += \
    Main/main.cpp \
    Main/mainwidget.cpp \
    GameObjects/astronomicalbodyobject.cpp \
    GameObjects/camera.cpp \
    GameObjects/gameobject.cpp \
    GameObjects/meshobject.cpp \
    GameObjects/transform.cpp \
    GameObjects/chunkgameobject.cpp \
    WorldGeneration/chunk.cpp \
    WorldGeneration/worldgrid.cpp \
    WorldGeneration/block.cpp \
    Misc/geometryengine.cpp \


HEADERS += \
    Main/mainwidget.h \
    GameObjects/astronomicalbodyobject.h \
    GameObjects/camera.h \
    GameObjects/gameobject.h \
    GameObjects/meshobject.h \
    GameObjects/transform.h \
    GameObjects/chunkgameobject.h \
    WorldGeneration/chunk.h \
    WorldGeneration/worldgrid.h \
    WorldGeneration/block.h \
    Misc/geometryengine.h \
    Misc/BasicIO.h \

RESOURCES += \
    Models/obj.qrc \
    Shaders/shaders.qrc \
    Textures/textures.qrc

CONFIG += console
# install
target.path = $$[YOUR_PATH]
INSTALLS += target



