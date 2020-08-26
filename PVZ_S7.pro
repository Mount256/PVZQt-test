#-------------------------------------------------
#
# Project created by QtCreator 2020-08-09T22:11:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PVZ_S7
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        menu.cpp \
    startbutton.cpp \
    battletip.cpp \
    cards.cpp \
    maingame.cpp \
    selectbox.cpp \
    map.cpp \
    sun.cpp \
    pea.cpp \
    peashooter.cpp \
    plant.cpp \
    repeater.cpp \
    sunflower.cpp \
    wallnut.cpp \
    cherrybomb.cpp \
    commonzombie.cpp \
    zombie.cpp \
    quit.cpp \
    pause.cpp \
    shovel.cpp \
    car.cpp \
    snowpea.cpp \
    finishtip.cpp \
    conezombie.cpp \
    footballzombie.cpp \
    paperzombie.cpp \
    screenzombie.cpp \
    potatomine.cpp

HEADERS += \
        menu.h \
    startbutton.h \
    battletip.h \
    cards.h \
    maingame.h \
    selectbox.h \
    map.h \
    sun.h \
    pea.h \
    peashooter.h \
    plant.h \
    repeater.h \
    sunflower.h \
    wallnut.h \
    cherrybomb.h \
    commonzombie.h \
    zombie.h \
    quit.h \
    pause.h \
    shovel.h \
    car.h \
    snowpea.h \
    finishtip.h \
    conezombie.h \
    footballzombie.h \
    paperzombie.h \
    screenzombie.h \
    potatomine.h

FORMS += \
        menu.ui \
    maingame.ui \
    quit.ui \
    pause.ui \
    finishtip.ui

RESOURCES += \
    ../graphics/graphics.qrc
