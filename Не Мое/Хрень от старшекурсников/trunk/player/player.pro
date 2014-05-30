TEMPLATE = app
TARGET = player

QT += core \
    network \
    testlib \


INCLUDEPATH += ../common

HEADERS      =   PlayerLoop.h \
    ../common/PacketParser.h \
    ../common/MoveDirection.h \
    ../common/Map.h \
    ../common/ItemParser.h \
    ../common/Board.h \
    ../common/Boardkey.h \
    ../common/AntType.h \
    ../common/AntStatus.h \
    ../common/Ant.h \
    Frame.h \
    LogParser.h

SOURCES	     =  main.cpp \
    PlayerLoop.cpp \
    ../common/PacketParser.cpp \
    ../common/MoveDirection.cpp \
    ../common/Map.cpp \
    ../common/Board.cpp \
    ../common/Boardkey.cpp \
    ../common/AntType.cpp \
    ../common/AntStatus.cpp \
    ../common/Ant.cpp \
    Frame.cpp \
    LogParser.cpp \
