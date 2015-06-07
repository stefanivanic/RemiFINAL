#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T20:07:35
#
#-------------------------------------------------

QT       += core gui network \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemiGUI
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        game.cpp \
    card.cpp \
    group.cpp \
    selecttheme.cpp \
    playercontainer.cpp \
    talon.cpp \
    deck.cpp \
    cardcontainer.cpp \
    cardtablecontainer.cpp \
    choosecards.cpp \
    server.cpp \
    client.cpp \
    clientgame.cpp \
    servergame.cpp \
    initwindow.cpp

HEADERS  += game.h \
    card.h \
    group.h \
    selecttheme.h \
    playercontainer.h \
    talon.h \
    deck.h \
    cardcontainer.h \
    cardtablecontainer.h \
    choosecards.h \
    server.h \
    client.h \
    clientgame.h \
    servergame.h \
    initwindow.h

FORMS    += game.ui \
    card.ui \
    selecttheme.ui \
    playercontainer.ui \
    playercard.ui \
    talon.ui \
    deck.ui \
    cardcontainer.ui \
    cardtablecontainer.ui \
    choosecards.ui \
    initwindow.ui

RESOURCES += \
    res.qrc
