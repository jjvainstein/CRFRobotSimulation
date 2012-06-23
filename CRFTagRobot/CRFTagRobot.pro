#-------------------------------------------------
#
# Project created by QtCreator 2012-06-06T10:45:11
#
#-------------------------------------------------

QT       += core gui

TARGET = CRFTagRoboto
TEMPLATE = app

DESTDIR = bin/
MOC_DIR = moc/
OBJECTS_DIR = obj/


SOURCES +=  src/main.cpp\
            src/crftagrobot.cpp \
            src/robot.cpp \
    src/stage.cpp \
    src/robotstate.cpp

HEADERS  += src/crftagrobot.h \
            src/robot.h \
    src/stage.h \
    src/robotstate.h

FORMS    += ui/crftagrobot.ui

INCLUDEPATH+= src
