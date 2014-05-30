#-------------------------------------------------
#
# Project created by QtCreator 2012-04-16T00:50:19
#
#-------------------------------------------------

QT += core \
    network \
    testlib

QT       -= gui

TARGET = tracker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../common/PacketParser.cpp \
    ../common/MoveDirection.cpp \
    ../common/Map.cpp \
    ../common/AntType.cpp \
    ../common/Ant.cpp \
    ../common/Board.cpp \
    ../common/Boardkey.cpp \
    State.cpp \
    StateParser.cpp \
    AntLoop.cpp \
    CommandWriter.cpp \
    ../common/AntStatus.cpp \
    ../common/DynMap.cpp

HEADERS += \
    ../common/PacketParser.h \
    ../common/MoveDirection.h \
    ../common/Map.h \
    ../common/ItemParser.h \
    ../common/AntType.h \
    ../common/Ant.h \
    ../common/Board.h \
    ../common/Boardkey.h \
    State.h \
    StateParser.h \
    AntLoop.h \
    CommandWriter.h \
    ../common/AntStatus.h \
    ../common/DynMap.h

INCLUDEPATH += ../common
