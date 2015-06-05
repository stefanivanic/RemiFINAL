#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T20:07:35
#
#-------------------------------------------------

QT       += core gui network

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
    client.cpp \
    server.cpp \
    connection.cpp \
    peermanager.cpp

HEADERS  += game.h \
    card.h \
    group.h \
    sign.h \
    selecttheme.h \
    playercontainer.h \
    talon.h \
    deck.h \
    cardcontainer.h \
    cardtablecontainer.h \
    client.h \
    server.h \
    connection.h \
    peermanager.h

FORMS    += game.ui \
    card.ui \
    selecttheme.ui \
    playercontainer.ui \
    playercard.ui \
    talon.ui \
    deck.ui \
    cardcontainer.ui \
    cardtablecontainer.ui
